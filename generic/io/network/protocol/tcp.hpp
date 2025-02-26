#pragma once

class tcp
    extends public boost::asio::ip::tcp
{
    public:
        using acceptor = boost::asio::ip::tcp::acceptor;
        using endpoint = boost::asio::ip::tcp::endpoint;
        using resolver = boost::asio::ip::tcp::resolver;
        using socket   = boost::asio::ip::tcp::socket;

    public:
        constexpr static string name                ( ) { return "tcp"; }
        constexpr static bool   connection_oriented ( ) { return true; }
        constexpr static int    default_buffer_size ( ) { return 4096; }
        constexpr static int    max_buffer_size     ( ) { return std::numeric_limits<int>::max(); }
};

#include "tcp.ipp"