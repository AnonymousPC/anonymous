#pragma once

template < class protocol >
void basic_socket_buf<protocol>::connect ( url website )
{
    if ( website.scheme() != protocol_name() )
        throw network_error("unrecognized {} scheme (with url = {}, scheme = {}, expected = {})", protocol_name(), website, website.scheme(), protocol_name());

    if ( website.port() == "" )
        throw network_error("unknown default port for {} scheme (with url = {}, port = [[implicit]], expected = [[explicit]])", protocol_name(), website);

    let errpool = vector<detail::system_error>();
    let resolve_results = resolve_url(website);
    for ( const auto& resolve_entry in resolve_results )
        try
        {
            handle.connect(resolve_entry);
            break;
        }
        catch ( const boost::system::system_error& e )
        {
            errpool.push(detail::system_error(e));
        }
    if ( not errpool.empty() )
        throw network_error("connection failed (with local_endpoint = {}, remote_url = {}, remote_endpoint = {}, protocol = {})", local_endpoint_noexcept(), website, resolve_results | std::ranges::to<vector<typename protocol::endpoint>>(), protocol_name()).from(detail::all_attempts_failed(errpool));
}

template < class protocol >
void basic_socket_buf<protocol>::listen ( url portal )
{
    if ( portal.scheme() != protocol_name() )
        throw network_error("unrecognized {} scheme (with url = {}, scheme = {}, expected = {})", protocol_name(), portal, portal.scheme(), protocol_name());

    if ( portal.port() == "" )
        throw network_error("unknown default port for {} scheme (with url = {}, port = [[implicit]], expected = [[explicit]])", protocol_name(), portal);

    let errpool = vector<detail::system_error>();
    let resolve_results = resolve_url(portal);
    for ( const auto& resolve_entry in resolve_results )
        try
        {
            if constexpr ( requires { typename protocol::acceptor; } )
                typename protocol::acceptor(io_context, resolve_entry).accept(handle);

            else
            {
                handle.open(resolve_entry.endpoint().protocol());
                handle.bind(resolve_entry.endpoint());

                receive_buff.resize(default_buffer_size);
                let remote_edp = typename protocol::endpoint();
                int bytes = handle.receive_from(boost::asio::mutable_buffer(receive_buff.begin(), receive_buff.size()), remote_edp);
                handle.connect(remote_edp);
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
        throw network_error("listening failed (with local_url = {}, local_endpoint = {}, protocol = {})", portal, resolve_results | std::ranges::to<vector<typename protocol::endpoint>>(), protocol_name()).from(detail::all_attempts_failed(errpool));
}

template < class protocol >
void basic_socket_buf<protocol>::close ( )
{
    try
    {
        handle.shutdown(boost::asio::socket_base::shutdown_both);
        handle.close();
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("disconnection failed (with local_endpoint = {}, remote_endpoint = {}, protocol = {})", local_endpoint_noexcept(), remote_endpoint_noexcept(), protocol_name()).from(detail::system_error(e));     
    }

    send_buff   .clear();
    receive_buff.clear();
    setp(nullptr, nullptr);
    setg(nullptr, nullptr, nullptr);
}

template < class protocol >
bool basic_socket_buf<protocol>::is_open ( ) const
{
    return handle.is_open();
}


// Inteface (cache)

template < class protocol >
url basic_socket_buf<protocol>::local_endpoint ( ) const
{
    try
    {
        return "{}://{}"s.format(protocol::name(), string(handle.local_endpoint()));
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
        return "{}://{}"s.format(protocol::name(), string(handle.remote_endpoint()));
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
    try
    {
        if ( receive_buff == "" )
            receive_buff.resize(default_buffer_size);

        if constexpr ( requires { handle.read_some(boost::asio::mutable_buffer(receive_buff.begin(), receive_buff.size())); })
        {
            int bytes = handle.read_some(boost::asio::mutable_buffer(receive_buff.begin(), receive_buff.size()));
            setg(receive_buff.begin(),
                 receive_buff.begin(),
                 receive_buff.begin() + bytes);
        }

        else
            if ( eback() == egptr() )
            {
                int bytes = handle.receive(boost::asio::mutable_buffer(receive_buff.begin(), receive_buff.size()));
                setg(receive_buff.begin(),
                     receive_buff.begin(),
                     receive_buff.begin() + bytes);
            }
            else
            {
                setg(nullptr,
                     nullptr,
                     nullptr); // Reset everything to nullptr, which looks like we are the first time receiving message.
                return traits_type::eof();
            }

        return traits_type::to_int_type(*gptr());
    }
    catch ( const boost::system::system_error& e )
    {
        if ( e.code() == boost::asio::error::eof )
            return traits_type::eof();
        else
            throw network_error("receive message failed (with local_endpoint = {}, remote_endpoint = {}, protocol = {})", local_endpoint_noexcept(), remote_endpoint_noexcept(), protocol_name()).from(detail::system_error(e));
    }
}

template < class protocol >
int basic_socket_buf<protocol>::overflow ( int c )
{
    try
    {
        if ( send_buff == "" )
        {
            send_buff.resize(default_buffer_size);
            setp(send_buff.begin(),
                 send_buff.end());
        }

        else if constexpr ( requires { handle.write_some(boost::asio::const_buffer(send_buff.begin(), send_buff.size())); })
        {
            int bytes = handle.write_some(boost::asio::const_buffer(send_buff.begin(), send_buff.size()));
            std::move(send_buff.begin() + bytes, send_buff.end(), send_buff.begin());
            setp(send_buff.end() - bytes,
                 send_buff.end());
        }

        else
        {
            handle.send(boost::asio::const_buffer(send_buff.begin(), send_buff.size()));
            setp(send_buff.begin(),
                 send_buff.end());
        }

        *pptr() = traits_type::to_int_type(c);
        pbump(1);
        return traits_type::to_int_type(c);
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("send message failed (with local_endpoint = {}, remote_endpoint = {}, protocol = {})", local_endpoint_noexcept(), remote_endpoint_noexcept(), protocol_name()).from(detail::system_error(e));
    }
}

template < class protocol >
int basic_socket_buf<protocol>::sync ( )
{
    try
    {
        handle.send(boost::asio::const_buffer(send_buff.begin(), pptr() - send_buff.begin()));
        setp(send_buff.begin(),
             send_buff.end());
        return 0;
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("send message failed (with local_endpoint = {}, remote_endpoint = {}, protocol = {})", local_endpoint_noexcept(), remote_endpoint_noexcept(), protocol_name()).from(detail::system_error(e));
    }
}



// Auxiliary

template < class protocol >
string basic_socket_buf<protocol>::local_endpoint_noexcept ( ) const
{
    try
    {
        return "{}://{}"s.format(protocol_name(), string(handle.local_endpoint()));
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
        return "{}://{}"s.format(protocol_name(), string(handle.remote_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        return "[[bad remote endpoint]]";
    }
}

template < class protocol >
string basic_socket_buf<protocol>::protocol_name ( ) const
{
    return string(typeid(protocol)).right_partition("::")[-1];
}

template < class protocol >
auto basic_socket_buf<protocol>::resolve_url ( const url& website ) const
{
    try
    {
        return typename protocol::resolver(io_context).resolve(
                   website.host().c_str(),
                   website.port().c_str());
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("resolution failed (with local_endpoint = {}, remote_url = {}, protocol = {})", local_endpoint_noexcept(), website, protocol_name()).from(detail::system_error(e));
    }
}