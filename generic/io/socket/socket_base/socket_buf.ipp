#pragma once

template < class protocol >
void basic_socket_buf<protocol>::connect ( url website )
{
    // Check port to be explicit.
    if ( website.port() == "" )
        throw network_error("unknown default port for {} scheme (with url = {}, port = [[implicit]], expected = [[explicit]])", protocol::name(), website);

    // Connect.
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
        throw network_error("connection failed (with local_endpoint = {}, remote_url = {}, remote_endpoint = {}, protocol = {})", local_endpoint_noexcept(), website, resolve_results | std::ranges::to<vector<typename protocol::endpoint>>(), protocol::name()).from(detail::all_attempts_failed(errpool));

    // Initialize send.
    send_buff.resize(protocol::default_buffer_size());
    setp(send_buff.begin(),
         send_buff.end());
}

template < class protocol >
void basic_socket_buf<protocol>::listen ( url portal )
{
    // Check port to be explicit.
    if ( portal.port() == "" )
        throw network_error("unknown default port for {} scheme (with url = {}, port = [[implicit]], expected = [[explicit]])", protocol::name(), portal);

    // Listen.
    let errpool = vector<detail::system_error>();
    let resolve_results = resolve_url(portal);
    for ( const auto& resolve_entry in resolve_results )
        try
        {
            if constexpr ( requires { typename protocol::acceptor; } )
                typename protocol::acceptor(io_context, resolve_entry.endpoint()).accept(handle);
            else
            {
                handle.open(resolve_entry.address().is_v4() ? protocol::v4() )
            }
            break;
        }
        catch ( const boost::system::system_error& e )
        {
            errpool.push(detail::system_error(e));
        }
    if ( not errpool.empty() )
        throw network_error("listening failed (with local_url = {}, local_endpoint = {}, protocol = {})", portal, resolve_results | std::ranges::to<vector<typename protocol::endpoint>>(), protocol::name()).from(detail::all_attempts_failed(errpool));

    // Initialize send.
    send_buff.resize(protocol::default_buffer_size());
    setp(send_buff.begin(),
         send_buff.end());
}

template < class protocol >
void basic_socket_buf<protocol>::close ( )
{
    try
    {
        // Shutdown and close.
        handle.shutdown(boost::asio::socket_base::shutdown_both);
        handle.close();
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
        return "{}://{}"s.format(protocol::name(), handle.local_endpoint());
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
        return "{}://{}"s.format(protocol::name(), handle.remote_endpoint());
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
    // Initialize receive.
    if ( receive_buff == "" )
        receive_buff.resize(protocol::default_buffer_size());

    try
    {
        // Receive message.
        int bytes = handle.read_some(boost::asio::mutable_buffer(receive_buff.begin(), receive_buff.size()));

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
}

template < class protocol >
int basic_socket_buf<protocol>::overflow ( int c )
{
    try
    {
        // Send message.
        int bytes = handle.write_some(boost::asio::const_buffer(send_buff.begin(), send_buff.size()));

        // Set put area
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
}

template < class protocol >
int basic_socket_buf<protocol>::sync ( )
{
    try
    {
        // Send message.
        boost::asio::write(handle, boost::asio::const_buffer(send_buff.data(), pptr() - send_buff.data()));
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
        return "{}://{}"s.format(protocol::name(), string(handle.local_endpoint()));
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
        return "{}://{}"s.format(protocol::name(), string(handle.remote_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        return "[[bad remote endpoint]]";
    }
}

template < class protocol >
auto basic_socket_buf<protocol>::resolve_url ( const url& website )
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