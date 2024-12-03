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
    try
    {
        if ( stdout_buff == "" )
            stdout_buff.resize(default_buffer_size);

        int bytes = stdout_pipe.read_some(boost::asio::mutable_buffer(stdout_buff.begin(), stdout_buff.size()));
        setg(stdout_buff.begin(),
             stdout_buff.begin(),
             stdout_buff.begin() + bytes);

        return traits_type::to_int_type(*gptr());
    }
    catch ( const boost::system::system_error& e )
    {
        // As pipe_buf::eof is always not explicitly marked, attempting to
        // read all data will inevitably meet boost::asio::error::broken_pipe.
        if ( e.code() == boost::asio::error::broken_pipe )
            return traits_type::eof();
        else
            throw pipe_error("failed to read from pipe.stdout (with process-id = {}) [[caused by {}: {}]]",
                             process_handle->id(),
                             typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
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
