#pragma once

class tcp
    extends public boost::asio::ip::tcp
{
    public:
        constexpr static string name                ( ) { return "tcp"; }
        constexpr static bool   connection_oriented ( ) { return true; }
        constexpr static int    default_buffer_size ( ) { return 4096; }
};

class udp
    extends public boost::asio::ip::udp
{
    public:
        constexpr static string name                ( ) { return "udp"; }
        constexpr static bool   connection_oriented ( ) { return false; }
        constexpr static int    default_buffer_size ( ) { return 65536; }
};

class icmp
    extends public boost::asio::ip::icmp
{
    public:
        constexpr static string name                ( ) { return "icmp"; }
        constexpr static bool   connection_oriented ( ) { return false; }
        constexpr static int    default_buffer_size ( ) { return 65536; }
};

class ssl
    extends public tcp
{
    public:
        class acceptor;
        using endpoint = tcp::endpoint;
        using resolver = tcp::resolver;
        class socket;

    public:
        constexpr static string name                ( ) { return "ssl"; }
        constexpr static bool   connection_oriented ( ) { return true; }
        constexpr static int    default_buffer_size ( ) { return 4096; }
};

#include "ssl.hpp"