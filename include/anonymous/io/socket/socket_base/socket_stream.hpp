#pragma once

template < class protocol >
class basic_socket_stream
    extends public std::iostream
{
    public: // Core
        basic_socket_stream ( );
        basic_socket_stream ( url );
        basic_socket_stream ( basic_socket_stream&& );
       ~basic_socket_stream ( );
        basic_socket_stream& operator = ( basic_socket_stream&& );

    public: // Interface
        basic_socket_stream& connect ( url );
        basic_socket_stream& listen  ( url );
        basic_socket_stream& close   ( );
        bool                 is_open ( ) const;

    public: // Interface
        url local_endpoint  ( ) const;
        url remote_endpoint ( ) const;

    private: // Data
        std::unique_ptr<basic_socket_buf<protocol>> buff_ptr = std::make_unique<basic_socket_buf<protocol>>();
};

#include "socket_stream.cpp"