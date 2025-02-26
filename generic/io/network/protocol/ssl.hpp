#pragma once

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
        constexpr static int    max_buffer_size     ( ) { return std::numeric_limits<int>::max(); }
};

class ssl::acceptor
    extends public tcp::acceptor
{
    public:
        using tcp::acceptor::acceptor;
        
        void accept ( ssl::socket&, auto&&... );
};

class ssl::socket
    extends public boost::asio::ssl::stream<tcp::socket>
{   
    public:
        socket ( auto&&... );

        void connect  ( auto&&... );
        void shutdown ( auto&&... );
        void close    ( auto&&... );

        endpoint local_endpoint  ( ) const;
        endpoint remote_endpoint ( ) const;
};

#include "ssl.ipp"