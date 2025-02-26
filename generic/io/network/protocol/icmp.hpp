#pragma once

class icmp
{
    public:
        class acceptor;
        using endpoint = boost::asio::ip::icmp::endpoint;
        using resolver = boost::asio::ip::icmp::resolver;
        using socket   = boost::asio::ip::icmp::socket;

    public:
        constexpr static string name                ( ) { return "icmp"; }
        constexpr static bool   connection_oriented ( ) { return false; }
        constexpr static int    default_buffer_size ( ) { return 65507; } // 65535 - 20(ip_header) - 8(icmp_header)
        constexpr static int    max_buffer_size     ( ) { return 65507; }
};

#include "icmp.ipp"