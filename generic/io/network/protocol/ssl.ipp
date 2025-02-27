#pragma once

void ssl::acceptor::accept ( auto&& sock, auto&&... args )
{
    self.tcp::acceptor::accept(sock.next_layer(), std::forward<decltype(args)>(args)...);

    try
    {
        sock.handshake(boost::asio::ssl::stream_base::server);
    }
    catch (...) 
    { 
        sock.close();
        throw; 
    }
}

ssl::socket::socket ( auto&&... args )
    extends boost::asio::ssl::stream<tcp::socket>(typename tcp::socket(std::forward<decltype(args)>(args)...), ssl_context)
{
    
}

void ssl::socket::connect ( auto&&... args )
{
    self.next_layer().connect(std::forward<decltype(args)>(args)...);

    if constexpr ( requires { first_value_of(args...).host_name(); } )
    {
        let sni = SSL_set_tlsext_host_name(self.native_handle(), first_value_of(args...).host_name().c_str());
        if ( not sni )
            throw boost::system::system_error(boost::beast::error_code(int(ERR_get_error()), boost::asio::error::get_ssl_category()));
    }

    try
    { 
        self.handshake(boost::asio::ssl::stream_base::client);
    }
    catch (...)
    { 
        self.next_layer().close();
        throw; 
    }
}   

void ssl::socket::shutdown ( auto&&... args )
{
    self.boost::asio::ssl::stream<tcp::socket>::shutdown();
    self.next_layer().shutdown(std::forward<decltype(args)>(args)...);
}

void ssl::socket::close ( auto&&... args )
{
    self.next_layer().close(std::forward<decltype(args)>(args)...);
}

ssl::endpoint ssl::socket::local_endpoint ( ) const
{
    return self.next_layer().local_endpoint();
}

ssl::endpoint ssl::socket::remote_endpoint ( ) const
{
    return self.next_layer().remote_endpoint();
}