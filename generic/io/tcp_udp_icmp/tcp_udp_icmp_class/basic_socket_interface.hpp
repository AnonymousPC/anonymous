#pragma once

template < class protocol, class type >
class basic_socket_interface
{
    public: // Core
        basic_socket_interface ( )                                            = default;
        basic_socket_interface ( const basic_socket_interface&  )             = delete;
        basic_socket_interface (       basic_socket_interface&& );
        basic_socket_interface& operator = ( const basic_socket_interface&  ) = delete;
        basic_socket_interface& operator = (       basic_socket_interface&& );

    protected: // Interface (override)
        type& ping ( const url& );

    public: // Interface (non-override)
        type& close ( );

    public: // Conversion
        operator url ( ) const;

    private: // Data
        url  socket_url  = "";
        bool socket_open = false;

    private: // Auxilliary
        string protocol_name ( ) const;
};



template < class type > using tcp_interface  = basic_socket_interface<boost::asio::ip::tcp, type>;
template < class type > using udp_interface  = basic_socket_interface<boost::asio::ip::udp, type>;
template < class type > using icmp_interface = basic_socket_interface<boost::asio::ip::icmp,type>;


#include "basic_socket_interface.ipp"