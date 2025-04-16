#pragma once

void ssl::acceptor::accept ( auto& sock, auto&&... args )
{
    self.tcp::acceptor::accept(sock.next_layer(), std::forward<decltype(args)>(args)...);
    try { sock.handshake(boost::asio::ssl::stream_base::server); } catch (...) { sock.close(); throw; }
}

ssl::socket::socket ( auto&&... args )
    extends boost::asio::ssl::stream<typename tcp::socket>(tcp::socket(std::forward<decltype(args)>(args)...), ssl_context)
{

}

void ssl::socket::connect ( auto&&... args )
{
    self.next_layer().connect(args...);
    if constexpr ( requires { first_value_of(args...).host_name(); } )
    {
        auto sni = SSL_set_tlsext_host_name(self.native_handle(), first_value_of(args...).host_name().c_str());
        if ( not sni )
            throw boost::system::system_error(boost::system::error_code(int(ERR_get_error()), boost::asio::error::get_ssl_category()));
    }
    try { self.handshake(boost::asio::ssl::stream_base::client); } catch (...) { self.next_layer().close(); throw; }
}

void ssl::socket::shutdown ( auto&&... args )
{
    self.boost::asio::ssl::stream<typename tcp::socket>::shutdown();
    self.next_layer().shutdown(std::forward<decltype(args)>(args)...);
}

void ssl::socket::close ( auto&&... args )
{
    self.next_layer().close(std::forward<decltype(args)>(args)...);
}

std::size_t ssl::socket::send ( auto&&... args )
{
    return self.boost::asio::ssl::stream<typename tcp::socket>::write_some(std::forward<decltype(args)>(args)...);
}

std::size_t ssl::socket::receive ( auto&&... args )
{
    return self.boost::asio::ssl::stream<typename tcp::socket>::read_some(std::forward<decltype(args)>(args)...);
}