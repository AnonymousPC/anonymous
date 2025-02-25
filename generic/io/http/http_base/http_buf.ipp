#pragma once

template < class protocol > struct basic_http_buf<protocol>::authorization extends public detail::io_mode<pair<string,string>> { using detail::io_mode<pair<string,string>>::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::cookie        extends public detail::io_mode<map<string,string>>  { using detail::io_mode<map<string,string>> ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::header        extends public detail::io_mode<map<string,string>>  { using detail::io_mode<map<string,string>> ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::method        extends public detail::io_mode<string>              { using detail::io_mode<string>             ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::param         extends public detail::io_mode<map<string,string>>  { using detail::io_mode<map<string,string>> ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::path          extends public detail::io_mode<string>              { using detail::io_mode<string>             ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::port          extends public detail::io_mode<int>                 { using detail::io_mode<int>                ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::proxy         extends public detail::io_mode<url>                 { using detail::io_mode<url>                ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::version       extends public detail::io_mode<float>               { using detail::io_mode<float>              ::io_mode; struct http_client_mode_tag { }; };

template < class protocol >
void basic_http_buf<protocol>::connect ( url website, http_client_mode auto... args )
{
    // Check scheme.
    if ( ( same_as<protocol,tcp> but website.scheme() != "http" or
         ( same_as<protocol,ssl> but website.scheme() != "https" ) )
        throw network_error("unrecognized http scheme (with url = {}, expected = {})", website, same_as<protocol,tcp> ? "http" otherwise "https");

    // Create http handle.
    initialize_as(client);

    // Set request.
    set_client_request(website, args...);

    // Connect.
    if ( optional_proxy_midway.empty() )
        connect_without_proxy(website);
    else
        connect_through_proxy(website, optional_proxy_midway.value());

    // Set state.
    status = client;
}

template < class protocol >
void basic_http_buf<protocol>::listen ( url portal, http_server_mode auto... args )
{
    // Check scheme.
    if ( ( same_as<protocol,tcp> but portal.scheme() != "http" ) or
         ( same_as<protocol,ssl> but portal.scheme() != "https" ) )
        throw network_error("unrecognized http scheme (with url = {}, expected = {})", portal, same_as<protocol,tcp> ? "http" otherwise "https");

    // Create http handle.
    initialize_as(server);

    // Set response.
    set_server_response(portal, args...);

    // Listen.
    listen_to_port(portal);

    // Set state.
    status = server;
}

template < class protocol >
void basic_http_buf<protocol>::close ( )
{
    // Disconnect.
    disconnect();

    // Reset param.
    reset_param();

    // Set state.
    status = none;
}

bool http_buf::is_open ( ) const
{
    return handle.is_open();
}


template < class protocol >
url basic_http_buf<protocol>::local_endpoint ( ) const
{
    try
    {
        return "{}://{}"s.format(same_as<protocol,tcp> ? "http" otherwise "https", handle.local_endpoint());
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("bad local endpoint").from(detail::system_error(e));
    }
}

template < class protocol >
url basic_http_buf<protocol>::remote_endpoint ( ) const
{
    try
    {
        return "{}://{}"s.format(same_as<protocol,tcp> ? "http" otherwise "https", handle.remote_endpoint());
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("bad remote endpoint").from(detail::system_error(e));
    }
}

template < class protocol >
string& basic_http_buf<protocol>::request_method ( )
{
    return current_request_method;
}

template < class protocol >
const string& basic_http_buf<protocol>::request_method ( ) const
{
    return current_request_method;
}

template < class protocol >
string& basic_http_buf<protocol>::request_path ( )
{
    return current_request_path;
}

template < class protocol >
const string& basic_http_buf<protocol>::request_path ( ) const
{
    return current_request_path;
}

template < class protocol >
map<string,string>& basic_http_buf<protocol>::request_param ( )
{
    return current_request_param;
}

template < class protocol >
const map<string,string>& basic_http_buf<protocol>::request_param ( ) const
{
    return current_request_param;
}

template < class protocol >
float& basic_http_buf<protocol>::request_version ( )
{
    return current_request_version;
}

template < class protocol >
const float& basic_http_buf<protocol>::request_version ( ) const
{
    return current_request_version;
}

template < class protocol >
map<string,string>& basic_http_buf<protocol>::request_header ( )
{
    return current_request_header;
}

template < class protocol >
const map<string,string>& basic_http_buf<protocol>::request_header ( ) const
{
    return current_request_header;
}

template < class protocol >
float& basic_http_buf<protocol>::response_version ( )
{
    return current_response_version;
}

template < class protocol >
const float& basic_http_buf<protocol>::response_version ( ) const
{
    return current_response_version;
}

template < class protocol >
int& basic_http_buf<protocol>::response_status_code ( )
{
    return current_response_status_code;
}

template < class protocol >
const int& basic_http_buf<protocol>::response_status_code ( ) const
{
    return current_response_status_code;
}

template < class protocol >
string& basic_http_buf<protocol>::response_reason ( )
{
    return current_response_reason;
}

template < class protocol >
const string& basic_http_buf<protocol>::response_reason ( ) const
{
    return current_response_reason;
}

template < class protocol >
map<string,string>& basic_http_buf<protocol>::response_header ( )
{
    return current_response_header;
}

template < class protocol >
const map<string,string>& basic_http_buf<protocol>::response_header ( ) const
{
    return current_response_header;
}

template < class protocol >
int basic_http_buf<protocol>::underflow ( )
{
    return status == client ? receive_more(*response_parser) otherwise
           status == server ? receive_more(*request_parser ) otherwise
                              throw network_error("receive message failed: basic_http_buf has not been opened");
}

template < class protocol >
int basic_http_buf<protocol>::overflow ( int c )
{
    status == client ? send_more(c, *request_serializer ) otherwise
    status == server ? send_more(c, *response_serializer) otherwise
                       throw network_error("send message failed: basic_http_buf has not been opened");
    return traits_type::to_int_type(c);
}

template < class protocol >
int basic_http_buf<protocol>::sync ( )
{
    opened == open_type::client ? send_end(*request_serializer ) otherwise
    opened == open_type::server ? send_end(*response_serializer) otherwise
                                  throw network_error("send message failed: http_buf has not been opened");
    refresh_send();
    return 0;
}

template < class protocol >
void basic_http_buf<protocol>::set_client_request ( const url& website, const auto&... args )
{
    static_assert ( detail::all_different<decltype(args)...> );

    // Default settings
    current_request_method  = "GET";
    current_request_path    = website.path();
    current_request_param   = website.param() != "" ? website.param().split('&') | std::views::transform([] (const auto& kv) { return pair<string,string>(kv.partition('=')[1], kv.partition('=')[3]); }) | std::ranges::to<map<string,string>>() otherwise map<string,string>();
    current_request_version = 1.1;
    current_request_header  = map<string,string>{{"Host",       website.port() != "" ? "{}:{}"s.format(website.host(), website.port()) otherwise website.host()},  
                                                 {"User-Agent", "C++"},
                                                 {"Accept",     "*/*"} };

    // Authorization
    if ( website.authorization() != "" )
        current_request_header["Authorization"] = "Basic {}"s.format(website.authorization() | views::encode_base64 | std::ranges::to<string>());
    if constexpr ( ( same_as<authorization,decay<decltype(args)>> or ... ) )
        current_request_header["Authorization"] = "Basic {}:{}"s.format("{}:{}"s.format(detail::value_of_same_type<authorization>(args...).value.key(), detail::value_of_same_type<authorization>(args...).value.value()) | views::encode_base64 | std::ranges::to<string>());

    // Cookie
    if constexpr ( ( same_as<cookie,decay<decltype(args)>> or ... ) )
        current_request_header["Cookie"] = detail::value_of_same_type<cookie>(args...).value
                                         | std::views::transform([] (const auto& kv) { return "{}={}"s.format(kv.key(), kv.value()); })
                                         | std::views::join_with("; "s)
                                         | std::ranges::to<string>();

    // Header
    if constexpr ( ( same_as<header,decay<decltype(args)>> or ... ) )
        for ( const auto& [k, v] in detail::value_of_same_type<header>(args...).value )
            current_request_header[k] = v;

    // Method
    if constexpr ( ( same_as<method,decay<decltype(args)>> or ... ) )
        current_request_method = detail::value_of_same_type<method>(args...).value;

    // Param
    if constexpr ( ( same_as<param,decay<decltype(args)>> or ... ) )
        current_request_param = detail::value_of_same_type<param>(args...).value;
    
    // Path
    if constexpr ( ( same_as<path,decay<decltype(args)>> or ... ) )
        current_request_path = detail::value_of_same_type<path>(args...).value;

    // Port
    if constexpr ( ( same_as<port,decay<decltype(args)>> or ... ) )
        optional_port = detail::value_of_same_type<port>(args...).value;

    // Proxy
    if constexpr ( ( same_as<proxy,decay<decltype(args)>> or ... ) )
        optional_proxy_midway = detail::value_of_same_type<proxy>(args...).value;

    // Version
    if constexpr ( ( same_as<version,decay<decltype(args)>> or ... ) )
        current_request_version = detail::value_of_same_type<version>(args...).value;

    // Duplicate settings
    if ( ( website.authorization() != "" ) + ( same_as<authorization,decay<decltype(args)>> or ... ) + ( detail::value_of_same_type_or<header>(args..., header()).value.contains("Authorization") ) >= 2 )
        throw network_error("duplicate settings: authorization repeatedly set at least 2 times: url (with value = {}), http_buf::authorization (with value = {}), http_buf::header (with value = {})",
                            website, detail::value_of_same_type_or<authorization>(args..., authorization()).value, detail::value_of_same_type_or<header>(args..., header()).value);
    
    if ( ( same_as<cookie,decay<decltype(args)>> or ... ) and detail::value_of_same_type_or<header>(args..., header()).value.contains("Cookie") )
        throw network_error("duplicate settings: cookie both set in http_buf::cookie (with value = {}) and http_buf::header (with value = {})",
                            detail::value_of_same_type_or<cookie>(args..., cookie()).value, detail::value_of_same_type_or<header>(args..., header()).value);

    // Param.
    if ( website.param() != "" and ( same_as<param,decay<decltype(args)>> or ... ) )
        throw network_error("duplicate settings: param both set in url (with value = {}) and http_buf::param (with value = {})",
                            website, detail::value_of_same_type_or<param>(args..., param()).value);

    // Path.
    if ( website.path() != "" and ( same_as<path,decay<decltype(args)>> or ... ) )
        throw network_error("duplicate settings: path both set in url (with value = {}) and http_buf::path (with value = {})",
                            website, detail::value_of_same_type_or<path>(args..., path()).value);
    if ( detail::value_of_same_type_or<path>(args..., path()).value.begins_with('/') )
        throw network_error("invalid setting: path (with value = {}) should not begins with '/', as it has been default provided",
                            detail::value_of_same_type_or<path>(args..., path()).value);

    // Port.
    if ( website.port() != "" and ( same_as<port,decay<decltype(args)>> or ... ) )
        throw network_error("duplicate settings: port both set in url (with value = {}) and http_buf::port (with value = {})",
                            website, detail::value_of_same_type_or<port>(args..., port()).value);

}

template < class protocol >
void basic_http_buf<protocol>::set_server_response ( const url& portal, const auto&... args )
{
    static_assert ( detail::all_different<decltype(args)...> );

    // Default settings
    current_response_version     = 1.1;
    current_response_status_code = 200;
    current_response_reason      = "OK";
    current_response_header      = map<string,string>{{"Server",                       "C++"},
                                                      {"Content-Type",                 "text/plain"},
                                                      {"Access-Control-Allow-Origin",  "*"},
                                                      {"Access-Control-Allow-Methods", "GET"},
                                                      {"Access-Control-Allow-Headers", "Content-Type"}};
}

template < class protocol >
auto basic_http_buf<protocol>::resolve ( const url& website )
{
    try
    {
        return typename protocol::resolver(io_context).resolve(
                   website.host().c_str(),
                   website.port() != ""      ? website.port().c_str()                otherwise
                   not optional_port.empty() ? string(optional_port.value()).c_str() otherwise
                   same_as<protocol,tcp>     ? "80"                                  otherwise
                                               "443"
               );
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("resolution failed (with local_endpoint = {}, remote_url = {}, layer = http/tcp)", local_endpoint_noexcept(), website).from(detail::system_error(e));
    }
}

template < class protocol >
void basic_http_buf<protocol>::connect_without_proxy ( const url& website )
{
    // Connect.
    let errpool = vector<detail::system_error>();
    let ip_list = resolve(website);
    for ( const auto& ip in ip_list )
        try
        {
            handle.connect(ip);
            break;
        }
        catch ( const boost::system::system_error& e )
        {
            errpool.push(detail::system_error(e));
        }
    if ( not errpool.empty() )
        throw network_error("connection failed (with remote_url = {}, remote_endpoint = {})", website, ip_list | std::ranges::to<vector<boost::asio::ip::tcp::endpoint>>()).from(detail::all_attempts_failed(errpool));

    // SSL.
    if ( same_as<protocol,ssl> )
    {
        // SSL server name indication.
        let sni_success = SSL_set_tlsext_host_name(handle.native_handle(), website.host().c_str());
        if ( not sni_success )
            throw network_error("connection failed (with local_endpoint = {}, remote_url = {}, remote_endpoint = {}, layer = https/ssl)", local_endpoint_noexcept(), website, remote_endpoint_noexcept()).from(detail::system_error(boost::system::system_error(boost::beast::error_code(int(ERR_get_error()), boost::asio::error::get_ssl_category()))));
    }
}

template < class protocol >
void basic_http_buf<protocol>::connect_through_proxy ( const url& website, const url& proxy_website )
{
    // Status error.
    if ( status != none )
        throw network_error("connection failed: http_buf has been already opened (with mode = {}, local_endpoint = {}, remote_endpoint = {})", opened == open_type::client ? "client" otherwise "server", local_endpoint_noexcept(), remote_endpoint_noexcept());

    // Connect to proxy server.
    connect_without_proxy(proxy_website);

    // Http:  request into full url.
    // Https: establish proxy tunnel.
    if constexpr ( same_as<protocol,tcp> )
        optional_proxy_target = website;

    else // if constexpr ( same_as<protocol,ssl> )
        establish_proxy_tunnel(website, proxy_website);
}