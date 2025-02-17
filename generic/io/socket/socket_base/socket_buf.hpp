#pragma once

template < class protocol >
class basic_socket_buf
    extends public std::streambuf
{
    public: // Interface
        void connect ( url );
        void listen  ( url );
        void close   ( );
        bool is_open ( ) const;

    public: // Interface (cache)
        url local_endpoint  ( ) const;
        url remote_endpoint ( ) const;

    protected: // Interface (virtual)
        virtual int underflow ( )                          override;
        virtual int overflow  ( int = traits_type::eof() ) override;
        virtual int sync      ( )                          override;

    private: // Auxiliary
        string local_endpoint_noexcept  ( ) const;
        string remote_endpoint_noexcept ( ) const;
        string protocol_name            ( ) const;
        auto   resolve                  ( const url& );

    private: // Typedef
        constexpr static const int default_buffer_size = 4096;

    private: // Data
        typename protocol::socket socket       = typename protocol::socket(io_context);
        string                    send_buff    = "";
        string                    receive_buff = "";
        bool                      received     = false; // Used in connectionless cases.
};


#include "socket_buf.ipp"