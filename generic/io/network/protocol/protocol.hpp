#pragma once

class tcp
{
    public:
        using acceptor = boost::asio::ip::tcp::acceptor;
        using endpoint = boost::asio::ip::tcp::endpoint;
        using resolver = boost::asio::ip::tcp::resolver;
        using socket   = boost::asio::ip::tcp::socket;

    public:
        constexpr static string name                ( ) { return "tcp"; }
        constexpr static bool   connection_oriented ( ) { return true; }
};

class udp
{
    public:
        using endpoint = boost::asio::ip::udp::endpoint;
        using resolver = boost::asio::ip::udp::resolver;
        using socket   = boost::asio::ip::udp::socket;

    public:
    constexpr static string name                ( ) { return "udp"; }
    constexpr static bool   connection_oriented ( ) { return false; }
};

class icmp
{
    public:
        using endpoint = boost::asio::ip::icmp::endpoint;
        using resolver = boost::asio::ip::icmp::resolver;
        using socket   = boost::asio::ip::icmp::socket;

    public:
    constexpr static string name                ( ) { return "icmp"; }
    constexpr static bool   connection_oriented ( ) { return false; }
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
};

#include "protocol.ipp"