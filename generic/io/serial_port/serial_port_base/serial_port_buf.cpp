#pragma once

void serial_port_buf::open ( string serial_port )
{
    try
    {
        handle.open(serial_port.c_str());
    }
    catch ( const boost::system::system_error& e )
    {
        throw serial_port_error("open failed (with serial_port = {})", serial_port).from(e);
    }
}

void serial_port_buf::close ( )
{
    try
    {
        handle.close();
    }
    catch ( boost::system::system_error& e )
    {
        throw serial_port_error("close failed").from(e);
    }

    send_buff   .clear();
    receive_buff.clear();
    setp(nullptr, nullptr);
    setg(nullptr, nullptr, nullptr);
}

bool serial_port_buf::is_open ( ) const
{
    return handle.is_open();
}

int serial_port_buf::underflow ( )
{
    try
    {
        if ( receive_buff == "" )
            receive_buff.resize(default_buffer_size);

        int bytes = handle.read_some(boost::asio::mutable_buffer(receive_buff.begin(), receive_buff.size()));
        setg(receive_buff.begin(),
             receive_buff.begin(),
             receive_buff.begin() + bytes);

        return traits_type::to_int_type(*gptr());
    }
    catch ( const boost::system::system_error& e )
    {
        if ( e.code() == boost::asio::error::eof )
            return traits_type::eof();
        else
            throw serial_port_error("read data failed").from(e);
    }
}

int serial_port_buf::overflow ( int c )
{
    try
    {
        if ( send_buff == "" )
        {
            send_buff.resize(default_buffer_size);
            setp(send_buff.begin(),
                 send_buff.end());
        }

        else
        {
            int bytes = handle.write_some(boost::asio::const_buffer(send_buff.begin(), send_buff.size()));
            std::move(send_buff.begin() + bytes,
                      send_buff.end(),
                      send_buff.begin());
            setp(send_buff.end() - bytes,
                 send_buff.end());
        }

        *pptr() = traits_type::to_int_type(c);
        pbump(1);
        return traits_type::to_int_type(c);
    }
    catch ( const boost::system::system_error& e )
    {
        throw serial_port_error("write data failed").from(e);
    }
}

int serial_port_buf::sync ( )
{
    try
    {
        boost::asio::write(handle, boost::asio::const_buffer(send_buff.begin(), pptr() - send_buff.begin()));
        setp(send_buff.begin(),
             send_buff.end());
        return 0;
    }
    catch ( const boost::system::system_error& e )
    {
        throw serial_port_error("write data failed").from(e);
    }
}
