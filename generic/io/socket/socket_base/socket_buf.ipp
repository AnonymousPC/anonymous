#pragma once

/// Class basic_socket_buf (connection-oriented)

// Interface

template < class protocol >
void basic_socket_buf<protocol>::connect ( url website )
{
    // Check scheme.
    if ( website.scheme() != protocol::name() )
        throw network_error("unrecognized {} scheme (with url = {}, scheme = {}, expected = {})", protocol::name(), website, website.scheme(), protocol::name());

    // Check port.
    if ( website.port() == "" )
        throw network_error("unknown default port for {} scheme (with url = {}, port = [[implicit]], expected = [[explicit]])", protocol::name(), website);

    // Connect.
    let errpool = vector<detail::system_error>();
    let ip_list = resolve(website);
    for ( const auto& ip in ip_list )
        try
        {
            socket.connect(ip);
            break;
        }
        catch ( const boost::system::system_error& e )
        {
            errpool.push(detail::system_error(e));
        }
    if ( not errpool.empty() )
        throw network_error("connection failed (with local_endpoint = {}, remote_url = {}, remote_endpoint = {}, protocol = {})", local_endpoint_noexcept(), website, ip_list | std::ranges::to<vector<typename protocol::endpoint>>(), protocol::name()).from(detail::all_attempts_failed(errpool));
}

template < class protocol >
void basic_socket_buf<protocol>::listen ( url portal )
{
    // Check scheme.
    if ( portal.scheme() != protocol::name() )
        throw network_error("unrecognized {} scheme (with url = {}, scheme = {}, expected = {})", protocol::name(), portal, portal.scheme(), protocol::name());

    // Check port.
    if ( portal.port() == "" )
        throw network_error("unknown default port for {} scheme (with url = {}, port = [[implicit]], expected = [[explicit]])", protocol::name(), portal);

    // Listen.
    let errpool = vector<detail::system_error>();
    let ip_list = resolve(portal);
    for ( const auto& ip in ip_list )
        try
        {
            if constexpr ( protocol::connection_oriented() )
                // Accept a connection.
                typename protocol::acceptor(io_context, ip).accept(socket);

            else // if constexpr ( not protocol::connection_oriented() )
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
                setg(receive_buff.begin(),
                     receive_buff.begin(),
                     receive_buff.begin() + bytes);
            }

            break;
        }
        catch ( const boost::system::system_error& e )
        {
            errpool.push(detail::system_error(e));
        }
    if ( not errpool.empty() )
        throw network_error("listening failed (with local_url = {}, local_endpoint = {}, protocol = {})", portal, ip_list | std::ranges::to<vector<typename protocol::endpoint>>(), protocol::name()).from(detail::all_attempts_failed(errpool));
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
        throw network_error("disconnection failed (with local_endpoint = {}, remote_endpoint = {}, protocol = {})", local_endpoint_noexcept(), remote_endpoint_noexcept(), protocol::name()).from(detail::system_error(e));     
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
        return "{}://{}"s.format(protocol::name(), string(socket.local_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("bad local endpoint").from(detail::system_error(e));
    }
}

template < class protocol >
url basic_socket_buf<protocol>::remote_endpoint ( ) const
{
    try
    {
        return "{}://{}"s.format(protocol::name(), string(socket.remote_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("bad remote endpoint").from(detail::system_error(e));
    }
}


// Interface (virtual)

template < class protocol >
int basic_socket_buf<protocol>::underflow ( )
{
    if constexpr ( protocol::connection_oriented() )
        try
        {
            // Receive message.
            if ( receive_buff == "" )
                receive_buff.resize(default_buffer_size);
            int bytes = socket.read_some(boost::asio::mutable_buffer(receive_buff.begin(), receive_buff.size()));

            // Set get area.
            setg(receive_buff.begin(),
                 receive_buff.begin(),
                 receive_buff.begin() + bytes);
            return traits_type::to_int_type(*gptr());
        }
        catch ( const boost::system::system_error& e )
        {
            if ( e.code() == boost::asio::error::eof )
                return traits_type::eof();
            else
                throw network_error("receive message failed (with local_endpoint = {}, remote_endpoint = {}, protocol = {})", local_endpoint_noexcept(), remote_endpoint_noexcept(), protocol::name()).from(detail::system_error(e));
        }

    else // if constexpr ( not protocol::connection_oriented() )
        try
        {
            if ( not received ) // Datagram has not been received: then receive new message.
            {
                // Receive new message. The maximum length is fixed to 65535 in connectionless protocols (udp, icmp).
                receive_buff.resize(65535);
                int bytes = boost::asio::read(socket, boost::asio::mutable_buffer(receive_buff.begin(), receive_buff.size()));
                received = true;

                // Set get area.
                setg(receive_buff.begin(),
                     receive_buff.begin(),
                     receive_buff.begin() + bytes);
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
            throw network_error("receive message failed (with local_endpoint = {}, remote_endpoint = {}, protocol = {})", local_endpoint_noexcept(), remote_endpoint_noexcept(), protocol::name()).from(detail::system_error(e));
        }
}

template < class protocol >
int basic_socket_buf<protocol>::overflow ( int c )
{
    if constexpr ( protocol::connection_oriented() )
        try
        {
            // Send message if buffer is full, or create buffer space at first for further writing. Connection-oriented protocol allows chunk message.
            int bytes = default_buffer_size;
            if ( send_buff == "" )
                send_buff.resize(default_buffer_size);
            else
                bytes = socket.write_some(boost::asio::const_buffer(send_buff.begin(), send_buff.size()));

            // Set put area.
            std::move(send_buff.begin() + bytes, send_buff.end(), send_buff.begin());
            setp(send_buff.end() - bytes,
                 send_buff.end());
            *pptr() = traits_type::to_int_type(c);
            pbump(1);
            return traits_type::to_int_type(c);
        }
        catch ( const boost::system::system_error& e )
        {
            throw network_error("send message failed (with local_endpoint = {}, remote_endpoint = {}, protocol = {})", local_endpoint_noexcept(), remote_endpoint_noexcept(), protocol::name()).from(detail::system_error(e));
        }

    else // if constexpr ( not protocol::connection_oriented() )
    {
        // Prepare more buffer. Connectionless protocol demands the whole message to be sent in once.
        send_buff.resize(send_buff.size() + default_buffer_size);

        // Set put area.
        setp(send_buff.begin(),
             send_buff.end());
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
        boost::asio::write(socket, boost::asio::const_buffer(send_buff.data(), pptr() - send_buff.data()));

        // Set put area.
        setp(send_buff.data(),
             send_buff.data() + send_buff.size());
        return 0;
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("send message failed (with local_endpoint = {}, remote_endpoint = {}, protocol = {})", local_endpoint_noexcept(), remote_endpoint_noexcept(), protocol::name()).from(detail::system_error(e));
    }
}



// Auxiliary

template < class protocol >
string basic_socket_buf<protocol>::local_endpoint_noexcept ( ) const
{
    try
    {
        return "{}://{}"s.format(protocol::name(), string(socket.local_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        return "[[bad local endpoint]]";
    }
}

template < class protocol >
string basic_socket_buf<protocol>::remote_endpoint_noexcept ( ) const
{
    try
    {
        return "{}://{}"s.format(protocol::name(), string(socket.remote_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        return "[[bad remote endpoint]]";
    }
}

template < class protocol >
auto basic_socket_buf<protocol>::resolve ( const url& website )
{
    try
    {
        return typename protocol::resolver(io_context).resolve(
                   website.host().c_str(),
                   website.port().c_str());
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("resolution failed (with local_endpoint = {}, remote_url = {}, protocol = {})", local_endpoint_noexcept(), website, protocol::name()).from(detail::system_error(e));
    }
}