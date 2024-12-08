#pragma once

/// Class pipe_buf

// Interface

void pipe_buf::close ( )
{
    // Close handle.
    if ( is_open() )
    {
        try
        {
            stdin_pipe .close();
            stdout_pipe.close();
            stderr_pipe.close();
        }
        catch ( const boost::system::system_error& e )
        {
            throw pipe_error("failed to close pipe (with process-id = {}): cannot close stdin/stdout/stderr [[caused by {}: {}]]",
                             process_handle->id(), typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
        }

        try
        {
            if ( is_running() )
                process_handle->terminate();
        }
        catch ( const boost::system::system_error& e )
        {
            throw pipe_error("failed to close pipe (with process-id = {}): cannot terminate process [[caused by {}: {}]]",
                             process_handle->id(), typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
        }
    }

    else
        throw pipe_error("failed to close pipe: pipe is not opened");

    // Clean resource.
    process_handle = nullptr;
    stdin_buff .clear();
    stdout_buff.clear();
    stderr_buff.clear();
    setp(nullptr, nullptr);
    setg(nullptr, nullptr, nullptr);
}

bool pipe_buf::is_open ( ) const
{
    return process_handle != nullptr;
}

bool pipe_buf::is_running ( ) const
{
    return process_handle != nullptr and process_handle->running();
}


// Interface (virtual)

int pipe_buf::underflow ( )
{
    // Reserve space.
    if ( stdout_buff == "" )
        stdout_buff.resize(default_buffer_size);
    if ( stderr_buff == "" )
        stderr_buff.resize(default_buffer_size);

    // Post task.
    stdout_pipe.async_read_some(boost::asio::mutable_buffer(stdout_buff.begin(), stdout_buff.size()),
                                [&] (const boost::system::error_code& error, std::size_t bytes)
                                {
                                  //  print("stdout.pipe read {} bytes, error = {}"s.format(bytes, string(boost::system::system_error(error).what()).encode(std::text_encoding::environment(), std::text_encoding::literal())));
                                    stderr_pipe.cancel();
                                    if ( error == boost::system::error_code() or    // OK.
                                         error == boost::asio::error::eof or        // Linux/MacOS: process exit.
                                         error == boost::asio::error::broken_pipe ) // Windows:     process exit.
                                        setg(stdout_buff.begin(),
                                             stdout_buff.begin(),
                                             stdout_buff.begin() + bytes);
                                    else if ( error != boost::asio::error::operation_aborted )
                                        throw pipe_error("failed to read from pipe.stdout (with process-id = {}) [[caused by {}: {}]]",
                                                         process_handle->id(), typeid(boost::system::system_error), boost::system::system_error(error).what());
                                });
    stderr_pipe.async_read_some(boost::asio::mutable_buffer(stderr_buff.begin(), stderr_buff.size()),
                                [&] (const boost::system::error_code& error, std::size_t bytes)
                                {
                                 //   print("stderr.pipe read {} bytes, error = {}"s.format(bytes, string(boost::system::system_error(error).what()).encode(std::text_encoding::environment(), std::text_encoding::literal())));
                                    stdout_pipe.cancel();
                                    if ( error == boost::system::error_code() or    // OK.
                                         error == boost::asio::error::eof or        // Linux/MacOS: process exit.
                                         error == boost::asio::error::broken_pipe ) // Windows:     process exit.
                                        setg(stderr_buff.begin(),
                                             stderr_buff.begin(),
                                             stderr_buff.begin() + bytes);
                                    else if ( error != boost::asio::error::operation_aborted )
                                        throw pipe_error("failed to read from pipe.stderr (with process-id = {}) [[caused by {}: {}]]",
                                                         process_handle->id(), typeid(boost::system::system_error), boost::system::system_error(error).what());
                                });

    // Run task.
    let task = std::execution::schedule(cpu_context.get_scheduler())
             | std::execution::bulk(2, [&] (int) { context_handle->run(); });
    std::execution::sync_wait(task);

    // Return.
    return traits_type::to_int_type(*gptr());
}

int pipe_buf::overflow ( int c )
{
    try
    {
        if ( stdin_buff == "" )
        {
            stdin_buff.resize(default_buffer_size);
            setp(stdin_buff.begin(),
                 stdin_buff.end());
        }
        else
        {
            int bytes = stdin_pipe.write_some(boost::asio::const_buffer(stdin_buff.c_str(), stdin_buff.size()));
            std::move(stdin_buff.begin() + bytes,
                      stdin_buff.end(),
                      stdin_buff.begin());
            setp(stdin_buff.end() - bytes,
                 stdin_buff.end());
        }

        *pptr() = traits_type::to_int_type(c);
        pbump(1);
        return traits_type::to_int_type(c);
    }
    catch ( const boost::system::system_error& e )
    {
        throw pipe_error("failed to write to pipe.stdin (with process-id = {}) [[caused by {}: {}]]",
                         process_handle->id(),
                         typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}

int pipe_buf::sync ( )
{
    try
    {
        boost::asio::write(stdin_pipe, boost::asio::const_buffer(stdin_buff.begin(), pptr() - stdin_buff.begin()));
        setp(stdin_buff.begin(),
             stdin_buff.end());
        return 0;
    }
    catch ( const boost::system::system_error& e )
    {
        throw pipe_error("failed to write to pipe.stdin (with process-id = {}) [[caused by {}: {}]]",
                         process_handle->id(),
                         typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}
