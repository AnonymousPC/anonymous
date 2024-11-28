#pragma once

/// Class basic_socket_interface

// Core

template < class protocol, class type >
basic_socket_interface<protocol,type>::basic_socket_interface ( basic_socket_interface&& init )
    extends socket_url  ( std::exchange ( init.socket_url,  ""    ) ),
            socket_open ( std::exchange ( init.socket_open, false ) )
{

}

template < class protocol, class type >
basic_socket_interface<protocol,type>& basic_socket_interface<protocol,type>::operator = ( basic_socket_interface&& init )
{
    socket_url  = std::exchange ( init.socket_url,  ""    );
    socket_open = std::exchange ( init.socket_open, false );
    return self;
}



// Interface (override)

template < class protocol, class type >
type& basic_socket_interface<protocol,type>::ping ( const url& website )
{
    if ( socket_open )
        throw network_error("cannot ping {} {}: {}_interface has already pinged {}", protocol_name(), website, protocol_name(), socket_url);

    socket_url  = website;
    socket_open = true;
    return static_cast<type&>(self);
}

// Interface (non-override)

template < class protocol, class type >
type& basic_socket_interface<protocol,type>::close ( )
{
    if ( not socket_open )
        throw network_error("cannot close {}: {}_interface has not been opened", protocol_name(), protocol_name());

    socket_url  = "";
    socket_open = false;
    return static_cast<type&>(self);
}

// Conversion

template < class protocol, class type >
basic_socket_interface<protocol,type>::operator url ( ) const
{
    return socket_url;
}

// Auxiliary

template < class protocol, class type >
string basic_socket_interface<protocol,type>::protocol_name ( ) const
{
    if constexpr ( std::same_as<protocol,boost::asio::ip::tcp> )
        return "tcp";
    else if constexpr ( std::same_as<protocol,boost::asio::ip::udp> )
        return "udp";
    else if constexpr ( std::same_as<protocol,boost::asio::ip::icmp> )
        return "icmp";
    else
        static_assert(false, "unrecognizd protocol");
}