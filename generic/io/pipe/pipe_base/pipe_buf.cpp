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
    stdout_pipe.cancel();
    stderr_pipe.cancel();
    let stdout_error = std::exception_ptr();
    stdout_pipe.async_read_some(boost::asio::mutable_buffer(stdout_buff.begin(), stdout_buff.size()),
                                [&] (const boost::system::error_code& error, std::size_t bytes)
                                {
                                    if ( error == boost::system::error_code() )
                                    {
                                        stderr_pipe.cancel();
                                        setg(stdout_buff.begin(),
                                             stdout_buff.begin(),
                                             stdout_buff.begin() + bytes);
                                    }
                                    else
                                        throw pipe_error("failed to read from pipe (with stream = stdout) [[caused by {}: {}]]",
                                                         typeid(boost::system::system_error), string(boost::system::system_error(error).what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
                                });
    let stderr_error = std::exception_ptr();
    stderr_pipe.async_read_some(boost::asio::mutable_buffer(stderr_buff.begin(), stderr_buff.size()),
                                [&] (const boost::system::error_code& error, std::size_t bytes)
                                {
                                    if ( error == boost::system::error_code() )
                                    {
                                        stdout_pipe.cancel();
                                        setg(stderr_buff.begin(),
                                             stderr_buff.begin(),
                                             stderr_buff.begin() + bytes);
                                    }
                                    else
                                        throw pipe_error("failed to read from pipe (with stream = stderr) [[caused by {}: {}]]",
                                                         typeid(boost::system::system_error), string(boost::system::system_error(error).what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
                                });

    // Run task.
    let stdout_task = std::execution::schedule(cpu_context.get_scheduler())
                    | std::execution::then([&] { context_handle->run(); })
                    | std::execution::upon_error([&] (const std::exception_ptr& e) { stdout_error = std::make_exception_ptr(e); });
    let stderr_task = std::execution::schedule(cpu_context.get_scheduler()) 
                    | std::execution::then([&] { context_handle->run(); });
                    | std::execution::upon_error([&] (const std::exception_ptr& e) { stderr_error = std::make_exception_ptr(e); });
    std::execution::sync_wait(std::execution::when_all(stdout_task, stderr_task));
    context_handle->restart();

    // Define eof error-code.
    #ifdef _WIN32
        let eof = boost::asio::error::eof;
    #elif defined(__linux__) or defined(__APPLE__)
        let eof = boost::asio::error::eof;
    #endif

    // Return
    if ( stdout_error == boost::system::error_code() or stderr_error == boost::system::error_code() ) // One of operation suceeded.
        return traits_type::to_int_type(*gptr());
    else if ( stdout_error == eof and stderr_error == eof ) // Both meets eof.
        return traits_type::eof();
    else
        throw pipe_error("failed to read from pipe (with process-id = {}): [[try 1 with exception {}: {}]], [[try 2 with exception {}: {}]]",
                         process_handle->id(),
                         ,
                         typeid(boost::system::system_error), string(boost::system::system_error(stderr_error).what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
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
