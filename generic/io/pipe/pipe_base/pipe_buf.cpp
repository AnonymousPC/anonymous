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
    let stdout_error = boost::system::error_code();
    stdout_pipe.async_read_some(boost::asio::mutable_buffer(stdout_buff.data(), stdout_buff.size()),
                                [&] (const boost::system::error_code& error, std::size_t bytes)
                                {
                                    if ( error == boost::system::error_code() )
                                    {
                                        stderr_pipe.cancel();
                                        setg(stdout_buff.data(),
                                             stdout_buff.data(),
                                             stdout_buff.data() + bytes);
                                    }
                                    else
                                        stdout_error = error;
                                });
    let stderr_error = boost::system::error_code();
    stderr_pipe.async_read_some(boost::asio::mutable_buffer(stderr_buff.data(), stderr_buff.size()),
                                [&] (const boost::system::error_code& error, std::size_t bytes)
                                {
                                    if ( error == boost::system::error_code() )
                                    {
                                        stdout_pipe.cancel();
                                        setg(stderr_buff.data(),
                                             stderr_buff.data(),
                                             stderr_buff.data() + bytes);
                                    }
                                    else
                                        stderr_error = error;
                                });

    // Run task.
    let stdout_task = std::execution::schedule(cpu::execution_context.get_scheduler())
                    | std::execution::then([&] { context_handle->run(); });
    let stderr_task = std::execution::schedule(cpu::execution_context.get_scheduler()) 
                    | std::execution::then([&] { context_handle->run(); });
    std::execution::sync_wait(std::execution::when_all(stdout_task, stderr_task));
    context_handle->restart();

    // Return
    if ( stdout_error == boost::system::error_code() or stderr_error == boost::system::error_code() ) // One of operation suceeded.
        return traits_type::to_int_type(*gptr());
    #ifdef _WIN32
    else if ( stdout_error == boost::asio::error::broken_pipe and stderr_error == boost::asio::error::broken_pipe ) // Both meets eof.
    #elifdef __linux__
    else if ( stdout_error == boost::asio::error::eof and stderr_error == boost::asio::error::eof ) // Both meets eof.
    #elifdef __APPLE__
    else if ( stdout_error == boost::asio::error::eof and stderr_error == boost::asio::error::eof ) // Both meets eof.
    #endif
        return traits_type::eof();
    else
    {
        detail::try_for_each(std::views::iota(1, 3),
            [&] (int try_count)
            {
                try_count == 1 ? throw pipe_error("failed to read from pipe (with stream = stdout) [[caused by {}: {}]]",
                                                  typeid(boost::system::system_error), string(boost::system::system_error(stdout_error).what()).encode(std::text_encoding::environment(), std::text_encoding::literal())) otherwise
                                 throw pipe_error("failed to read from pipe (with stream = stderr) [[caused by {}: {}]]",
                                                  typeid(boost::system::system_error), string(boost::system::system_error(stderr_error).what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
            },
            [&] (const auto& errors)
            {
                throw pipe_error("failed to read from pipe (with process-id = {}): {}", 
                                 process_handle->id(), errors);
            });
        return traits_type::eof();
    }
}

int pipe_buf::overflow ( int c )
{
    try
    {
        if ( stdin_buff == "" )
        {
            stdin_buff.resize(default_buffer_size);
            setp(stdin_buff.data(),
                 stdin_buff.data() + stdin_buff);
        }
        else
        {
            int bytes = stdin_pipe.write_some(boost::asio::const_buffer(stdin_buff.c_str(), stdin_buff.size()));
            std::move(stdin_buff.data() + bytes,
                      stdin_buff.data() + stdin_buff.size(),
                      stdin_buff.data());
            setp(stdin_buff.data() + stdin_buff.size() - bytes,
                 stdin_buff.data() + stdin_buff.size());
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
        boost::asio::write(stdin_pipe, boost::asio::const_buffer(stdin_buff.data(), pptr() - stdin_buff.data()));
        setp(stdin_buff.data(),
             stdin_buff.data() + stdin_buff.size());
        return 0;
    }
    catch ( const boost::system::system_error& e )
    {
        throw pipe_error("failed to write to pipe.stdin (with process-id = {}) [[caused by {}: {}]]",
                         process_handle->id(),
                         typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}
