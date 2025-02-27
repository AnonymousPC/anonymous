#pragma once

class ssl::acceptor
    extends public tcp::acceptor
{
    public:
        using tcp::acceptor::acceptor;
        
        void accept ( auto&&, auto&&... );
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