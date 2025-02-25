#pragma once

class ssl::socket
    extends public boost::asio::ssl::stream<tcp::socket>
{   
    public:
        socket ( auto&&... args )
            extends boost::asio::ssl::stream<tcp::socket>(typename tcp::socket(std::forward<decltype(args)>(args)...), ssl_context)
        {
            
        }

        void connect ( auto&&... args )
        {
            self.next_layer().connect(std::forward<decltype(args)>(args)...);
            try { self.handshake(boost::asio::ssl::stream_base::client); } catch (...) { self.next_layer().close(); throw; }
        }   

        void bind ( auto&&... args )
        {
            self.next_layer().bind(std::forward<decltype(args)>(args)...);
        }

        void shutdown ( auto&&... args )
        {
            self.boost::asio::ssl::stream<tcp::socket>::shutdown();
            self.next_layer().shutdown(std::forward<decltype(args)>(args)...);
        }

        void close ( auto&&... args )
        {
            self.next_layer().close();
        }

        endpoint local_endpoint ( ) const
        {
            return self.next_layer().local_endpoint();
        }

        endpoint remote_endpoint ( ) const
        {
            return self.next_layer().remote_endpoint();
        }
};

class ssl::acceptor
    extends public tcp::acceptor
{
    public:
        using tcp::acceptor::acceptor;

        void accept ( ssl::socket& sock, auto&&... args )
        {
            tcp::acceptor::accept(sock.next_layer(), std::forward<decltype(args)>(args)...);
            try { sock.handshake(boost::asio::ssl::stream_base::server); } catch (...) { sock.close(); throw; }
        }
};