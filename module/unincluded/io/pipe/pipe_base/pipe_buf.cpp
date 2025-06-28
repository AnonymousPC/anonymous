/// Class pipe_buf

// Interface

void pipe_buf::close ( )
{
    // Close handle.
    try
    {
        stdin_pipe .close();
        stdout_pipe.close();
        stderr_pipe.close();
        handle->terminate();
    }
    catch ( const boost::system::system_error& e )
    {
        throw pipe_error("close failed (with process_id = {})", process_id_noexcept()).from(detail::system_error(e));
    }
    
    // Clean resource.
    handle = nullptr;
    stdin_buff .clear();
    stdout_buff.clear();
    stderr_buff.clear();
    setp(nullptr, nullptr);
    setg(nullptr, nullptr, nullptr);
}

bool pipe_buf::is_open ( ) const
{
    return handle != nullptr;
}

bool pipe_buf::is_running ( ) const
{
    return handle != nullptr and handle->running();
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
    auto stdout_errc = boost::system::error_code();
    stdout_pipe.async_read_some(boost::asio::mutable_buffer(stdout_buff.begin(), stdout_buff.size()),
                                [&] (const boost::system::error_code& errc, size_t bytes)
                                {
                                    if ( errc == boost::system::error_code() )
                                    {
                                        stderr_pipe.cancel();
                                        setg(stdout_buff.begin(),
                                             stdout_buff.begin(),
                                             stdout_buff.begin() + bytes);
                                    }
                                    else
                                        stdout_errc = errc;
                                });
    auto stderr_errc = boost::system::error_code();
    stderr_pipe.async_read_some(boost::asio::mutable_buffer(stderr_buff.begin(), stderr_buff.size()),
                                [&] (const boost::system::error_code& errc, size_t bytes)
                                {
                                    if ( errc == boost::system::error_code() )
                                    {
                                        stdout_pipe.cancel();
                                        setg(stderr_buff.begin(),
                                             stderr_buff.begin(),
                                             stderr_buff.begin() + bytes);
                                    }
                                    else
                                        stderr_errc = errc;
                                });

    // Run task.
    ctx.run();

    // Return
    if ( stdout_errc == boost::system::error_code() or stderr_error == boost::system::error_code() ) // One of operation suceeded.
        return traits_type::to_int_type(*gptr());
    else if ( stdout_errc == boost::asio::error::eof and stderr_error == boost::asio::error::eof )
        return traits_type::eof();
    else
    {
        auto errpool = vector<detail::system_error>{detail::system_error(boost::system::system_error(stdout_errc)), detail::system_error(boost::system::system_error(stderr_errc))};
        throw pipe_error("read data failed (with process_id = {}, pipe = [stdout, stderr])", process_id_noexcept()).from(detail::all_attempts_failed(errpool));
    }
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
        throw pipe_error("write data failed (with process_id = {}, pipe = stdin)", process_id_noexcept()).from(detail::system_error(e));
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
        throw pipe_error("write data failed (with process_id = {}, pipe = stdin)", process_id_noexcept()).from(detail::system_error(e));
    }
}

string pipe_buf::process_id_noexcept ( ) const
{
    try
    {
        return string(handle->id());
    }
    catch ( const boost::system::system_error& e )
    {
        return "[[bad process id]]";
    }
}
