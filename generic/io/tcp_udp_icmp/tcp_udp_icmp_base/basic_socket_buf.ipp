#pragma once

namespace detail
{
    template < class protocol >
    concept connection_oriented = std::same_as<protocol,boost::asio::ip::tcp>;

    template < class protocol >
    concept connectionless = std::same_as<protocol,boost::asio::ip::udp> or
                             std::same_as<protocol,boost::asio::ip::icmp>;
}





/// Class basic_socket_buf (connection-oriented)

// Interface

template < class protocol >
void basic_socket_buf<protocol>::connect ( url website )
{
    // Check scheme.
    if ( website.scheme() != protocol_name() )
        throw network_error("unrecognized {} scheme (with url = {}, scheme = {}, expected = {})", protocol_name(), website, website.scheme(), protocol_name());

    // Check port.
    if ( website.port() == "" )
        throw network_error("unknown default port for {} scheme (with url = {}, port = [[implicit]], expected = [[explicit]])", protocol_name(), website);

    // Connect.
    detail::try_for_each(resolve(website),
        [&] (const auto& ip)
        {
            try
            {
                socket.connect(ip);
            }
            catch ( const boost::system::system_error& e )
            {
                throw network_error("connection failed (with remote-endpoint = {}) [[caused by {}: {}]]",
                                    ip.endpoint(), typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
            }
        },
        [&] (const auto& errors)
        {
            throw network_error("connection failed (with local-endpoint = {}, remote-url = {}, protocol = {}): {}",
                                local_endpoint_noexcept(), website, protocol_name(), errors);
        });
}

template < class protocol >
void basic_socket_buf<protocol>::listen ( url portal )
{
    // Check scheme.
    if ( portal.scheme() != protocol_name() )
        throw network_error("unrecognized {} scheme (with url = {}, scheme = {}, expected = {})", protocol_name(), portal, portal.scheme(), protocol_name());

    // Check port.
    if ( portal.port() == "" )
        throw network_error("unknown default port for {} scheme (with url = {}, port = [[implicit]], expected = [[explicit]])", protocol_name(), portal);

    // Listen.
    detail::try_for_each(resolve(portal),
        [&] (const auto& ip)
        {
            try
            {
                if constexpr ( detail::connection_oriented<protocol> )
                    // Accept a connection.
                    boost::asio::basic_socket_acceptor<protocol>(io_context, ip).accept(socket);

                else if constexpr ( detail::connectionless<protocol> )
                {
                    // Bind the local endpoint.
                    if ( ip.endpoint().address().is_v4() )
                        socket.open(protocol::v4());
                    else
                        socket.open(protocol::v6());
                    socket.bind(ip.endpoint());

                    // Accept whole message. The maximum length is fixed to 65535 in connectionless protocols (udp, icmp).
                    receive_buff.resize(65535);
                    let endpoint = typename protocol::endpoint();
                    int bytes    = socket.receive_from(boost::asio::mutable_buffer(receive_buff.begin(), receive_buff.size()), endpoint);
                    socket.connect(endpoint);
                    received = true;

                    // Set get area.
                    setg(receive_buff.data(),
                         receive_buff.data(),
                         receive_buff.data() + bytes);
                }
            }
            catch ( const boost::system::system_error& e )
            {
                throw network_error("listening failed (with local-endpoint = {}) [[caused by {}: {}]]",
                                    ip.endpoint(), typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
            }
        },
        [&] (const auto& errors )
        {
            throw network_error("listening failed (with local-url = {}, protocol = {}): {}",
                                portal, protocol_name(), errors);
        });
}

template < class protocol >
void basic_socket_buf<protocol>::close ( )
{
    try
    {
        // Shutdown and close.
        socket.shutdown(boost::asio::socket_base::shutdown_both);
        socket.close();
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("disconnection failed (with local-endpoint = {}, remote-endpoint = {}, protocol = {}) [[caused by {}: {}]]",
                            local_endpoint_noexcept(), remote_endpoint_noexcept(), protocol_name(),
                            typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }

    // Reset params.
    send_buff   .clear();
    receive_buff.clear();
    setp(nullptr, nullptr);
    setg(nullptr, nullptr, nullptr);
    received = false;
}

template < class protocol >
bool basic_socket_buf<protocol>::is_open ( ) const
{
    return socket.is_open();
}


// Inteface (cache)

template < class protocol >
url basic_socket_buf<protocol>::local_endpoint ( ) const
{
    try
    {
        return "{}://{}"s.format(protocol_name(), string(socket.local_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("bad local endpoint [[caused by {}: {}]]",
                            typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}

template < class protocol >
url basic_socket_buf<protocol>::remote_endpoint ( ) const
{
    try
    {
        return "{}://{}"s.format(protocol_name(), string(socket.remote_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("bad remote endpoint [[caused by {}: {}]]",
                            typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}


// Interface (virtual)

template < class protocol >
int basic_socket_buf<protocol>::underflow ( )
{
    if constexpr ( detail::connection_oriented<protocol> )
        try
        {
            // Receive message.
            if ( receive_buff == "" )
                receive_buff.resize(default_buffer_size);
            int bytes = socket.receive(boost::asio::mutable_buffer(receive_buff.begin(), receive_buff.size()));

            // Set get area.
            setg(receive_buff.data(),
                 receive_buff.data(),
                 receive_buff.data() + bytes);
            return traits_type::to_int_type(*gptr());
        }
        catch ( const boost::system::system_error& e )
        {
            if ( e.code() == boost::asio::error::eof )
                return traits_type::eof();
            else
                throw network_error("receive message failed (with local-endpoint = {}, remote-endpoint = {}, protocol = {}) [[caused by {}: {}]]",
                                    local_endpoint_noexcept(), remote_endpoint_noexcept(), protocol_name(),
                                    typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
        }

    else if constexpr ( detail::connectionless<protocol> )
        try
        {
            if ( not received ) // Datagram has not been received: then receive new message.
            {
                // Receive new message. The maximum length is fixed to 65535 in connectionless protocols (udp, icmp).
                receive_buff.resize(65535);
                int bytes = socket.receive(boost::asio::mutable_buffer(receive_buff.begin(), receive_buff.size()));
                received = true;

                // Set get area.
                setg(receive_buff.data(),
                     receive_buff.data(),
                     receive_buff.data() + bytes);
                return traits_type::to_int_type(*gptr());
            }

            else // Datagram has been received: then notify eof.
            {
                // End of message.
                received = false;
                return traits_type::eof();
            }
        }
        catch ( const boost::system::system_error& e )
        {
            throw network_error("receive message failed (with local-endpoint = {}, remote-endpoint = {}, protocol = {}) [[caused by {}: {}]]",
                                local_endpoint_noexcept(), remote_endpoint_noexcept(), protocol_name(),
                                typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
        }
}

template < class protocol >
int basic_socket_buf<protocol>::overflow ( int c )
{
    if constexpr ( detail::connection_oriented<protocol> )
        try
        {
            // Send message if buffer is full, or create buffer space at first for further writing. Connection-oriented protocol allows chunk message.
            if ( send_buff == "" )
                send_buff.resize(default_buffer_size);
            else
                socket.send(boost::asio::const_buffer(send_buff.begin(), send_buff.size()));

            // Set put area.
            setp(send_buff.data(),
                 send_buff.data() + send_buff.size());
            *pptr() = traits_type::to_int_type(c);
            pbump(1);
            return traits_type::to_int_type(c);
        }
        catch ( const boost::system::system_error& e )
        {
            throw network_error("send message failed (with local-endpoint = {}, remote-endpoint = {}, protocol = {}) [[caused by {}: {}]]",
                                local_endpoint_noexcept(), remote_endpoint_noexcept(), protocol_name(),
                                typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
        }

    else if constexpr ( detail::connectionless<protocol> )
    {
        // Prepare more buffer. Connectionless protocol demands the whole message to be sent in once.
        send_buff.resize(send_buff.size() + default_buffer_size);

        // Set put area.
        setp(send_buff.data(),
             send_buff.data() + send_buff.size());
        pbump(send_buff.size() - default_buffer_size);
        *pptr() = traits_type::to_int_type(c);
        pbump(1);
        return traits_type::to_int_type(c);
    }
}

template < class protocol >
int basic_socket_buf<protocol>::sync ( )
{
    try
    {
        // Send message.
        socket.send(boost::asio::const_buffer(send_buff.data(), pptr() - send_buff.data()));

        // Set put area.
        setp(send_buff.data(),
             send_buff.data() + send_buff.size());
        return 0;
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("send message failed (with local-endpoint = {}, remote-endpoint = {}, protocol = {}) [[caused by {}: {}]]",
                            local_endpoint_noexcept(), remote_endpoint_noexcept(), protocol_name(),
                            typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}



// Auxiliary

template < class protocol >
string basic_socket_buf<protocol>::local_endpoint_noexcept ( ) const
{
    try
    {
        return "{}://{}"s.format(protocol_name(), string(socket.local_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        return "[[bad local endpoint [[caused by {}: {}]]]]"s
               .format(typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}

template < class protocol >
string basic_socket_buf<protocol>::remote_endpoint_noexcept ( ) const
{
    try
    {
        return "{}://{}"s.format(protocol_name(), string(socket.remote_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        return "[[bad local endpoint [[caused by {}: {}]]]]"s
               .format(typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}

template < class protocol >
string basic_socket_buf<protocol>::protocol_name ( ) const
{
    if constexpr ( std::same_as<protocol,boost::asio::ip::tcp> )
        return "tcp";
    else if constexpr ( std::same_as<protocol,boost::asio::ip::udp> )
        return "udp";
    else if constexpr ( std::same_as<protocol,boost::asio::ip::icmp> )
        return "icmp";
    else
        static_assert(false, "unrecognized protocol");
}

template < class protocol >
auto basic_socket_buf<protocol>::resolve ( const url& website )
{
    try
    {
        return boost::asio::ip::basic_resolver<protocol>(io_context).resolve(
                   website.host().c_str(),
                   website.port().c_str());
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("resolution failed (with local-endpoint = {}, remote-url = {}, protocol = {}) [[caused by {}: {}]]",
                            local_endpoint_noexcept(), website, protocol_name(),
                            typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}