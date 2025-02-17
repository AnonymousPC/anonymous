#pragma once

class ssl::acceptor
    extends public tcp::acceptor
{
    public:
        using tcp::acceptor::acceptor;

        void accept ( auto&& sock, auto&&... args )
        {
            tcp::acceptor::accept(std::forward<decltype(sock)>(sock), std::forward<decltype(args)>(args)...);
            sock.handshake(boost::asio::ssl::stream_base::server);
        }
};

class ssl::socket
    extends protected tcp::socket,
            public    boost::asio::ssl::stream<tcp::socket&>
{
    public:
        socket ( auto&&... args )
            extends tcp::socket ( std::forward<decltype(args)>(args)... ),
                    boost::asio::ssl::stream<tcp::socket&> ( static_cast<tcp::socket&>(self), ssl_client_context )
        {
            
        }

        void connect ( auto&&... args )
        {
            tcp::socket::connect(std::forward<decltype(args)>(args)...);
            boost::asio::ssl::stream<tcp::socket&>::handshake(boost::asio::ssl::stream_base::client);
        }   

        void shutdown ( auto&&... args )
        {
            boost::asio::ssl::stream<tcp::socket&>::shutdown();
            tcp::socket::shutdown(std::forward<decltype(args)>(args)...);
        }

        using tcp::socket::close,
              tcp::socket::local_endpoint,
              tcp::socket::remote_endpoint;

        using boost::asio::ssl::stream<tcp::socket&>::read_some,
              boost::asio::ssl::stream<tcp::socket&>::write_some;

        friend class ssl::acceptor;
};