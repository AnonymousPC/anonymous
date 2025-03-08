#pragma once

void tls::acceptor::accept ( auto& sock, auto&&... args )
{
    self.tcp::acceptor::accept(sock.next_layer(), std::forward<decltype(args)>(args)...);
    try { sock.handshake(boost::asio::ssl::stream_base::server); } catch (...) { sock.close(); throw; }
}

tls::socket::socket ( auto&&... args )
    extends boost::asio::ssl::stream<typename tcp::socket>(tcp::socket(std::forward<decltype(args)>(args)...), tls_context)
{

}

void tls::socket::connect ( auto&&... args )
{
    self.next_layer().connect(args...);
    if constexpr ( requires { first_value_of(args...).host_name(); } )
    {
        let sni = SSL_set_tlsext_host_name(self.native_handle(), first_value_of(args...).host_name().c_str());
        if ( not sni )
            throw boost::system::system_error(boost::system::error_code(int(ERR_get_error()), boost::asio::error::get_ssl_category()));
    }
    try { self.handshake(boost::asio::ssl::stream_base::client); } catch (...) { self.next_layer().close(); throw; }
}

void tls::socket::shutdown ( auto&&... args )
{
    self.boost::asio::ssl::stream<typename tcp::socket>::shutdown();
    self.next_layer().shutdown(std::forward<decltype(args)>(args)...);
}

void tls::socket::close ( auto&&... args )
{
    self.next_layer().close(std::forward<decltype(args)>(args)...);
}

std::size_t tls::socket::send ( auto&&... args )
{
    return self.boost::asio::ssl::stream<typename tcp::socket>::write_some(std::forward<decltype(args)>(args)...);
}

std::size_t tls::socket::receive ( auto&&... args )
{
    return self.boost::asio::ssl::stream<typename tcp::socket>::read_some(std::forward<decltype(args)>(args)...);
}

tls::endpoint tls::socket::local_endpoint ( ) const
{
    return self.next_layer().local_endpoint();
}

tls::endpoint tls::socket::remote_endpoint ( ) const
{
    return self.next_layer().remote_endpoint();
}