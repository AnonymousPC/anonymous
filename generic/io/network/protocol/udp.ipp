#pragma once

udp::acceptor::acceptor ( boost::asio::io_context&, udp::endpoint edp )
    extends local_edp ( std::move(edp) )
{
    
}

void udp::acceptor::accept ( udp::socket& sock )
{
    // Bind the local endpoint.
    if ( local_edp.address().is_v4() )
        sock.open(udp::v4());
    else
        sock.open(udp::v6());
    sock.bind(local_edp);

    // Accept message.
    try
    {
        let remote_edp = udp::endpoint();
        let buff = string().resize(3);
        sock.receive_from(boost::asio::mutable_buffer(buff.begin(), buff.size()), remote_edp);
        print("udp.acceptor.accept.receive_from: we received a partial message: {}"s.format(buff));
        sock.connect(remote_edp);
    }
    catch ( const boost::system::system_error& )
    {
        sock.close();
        throw;
    }
}

std::size_t udp::socket::read_some ( auto&&... args )
{
    if constexpr ( sizeof...(args) == 1 )
        return self.receive(std::forward<decltype(args)>(args)...);
    else if constexpr ( sizeof...(args) == 2 )
        return self.receive(std::forward<decltype(first_value_of(args...))>(first_value_of(args...)), 
                            boost::asio::socket_base::message_flags(),
                            std::forward<decltype(second_value_of(args...))>(second_value_of(args...)));
    else
        static_assert(false, "unknown overload");
}

std::size_t udp::socket::write_some ( auto&&... args )
{
    if constexpr ( sizeof...(args) == 1 )
        return self.send(std::forward<decltype(args)>(args)...);
    else if constexpr ( sizeof...(args) == 2 )
        return self.send(std::forward<decltype(first_value_of(args...))>(first_value_of(args...)), 
                         boost::asio::socket_base::message_flags(),
                         std::forward<decltype(second_value_of(args...))>(second_value_of(args...)));
    else
        static_assert(false, "unknown overload");
}