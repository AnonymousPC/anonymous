#pragma once

class udp
    extends public boost::asio::ip::udp
{
    public:
        class acceptor;
        using endpoint = boost::asio::ip::udp::endpoint;
        using resolver = boost::asio::ip::udp::resolver;
        class socket;

    public:
        constexpr static string name                ( ) { return "udp"; }
        constexpr static bool   connection_oriented ( ) { return false; }
        constexpr static int    default_buffer_size ( ) { return 65507; } // 65535 - 20(ip_header) - 8(udp_header)
        constexpr static int    max_buffer_size     ( ) { return 65507; }
};

class udp::acceptor
{
    public:
        acceptor ( boost::asio::io_context&, udp::endpoint );

        void accept ( udp::socket& );

    private:
        udp::endpoint local_edp = udp::endpoint();
};

class udp::socket
    extends public boost::asio::ip::udp::socket
{
    public:
        using boost::asio::ip::udp::socket::socket;
        
        std::size_t read_some  ( auto&&... );
        std::size_t write_some ( auto&&... );
};

#include "udp.ipp"