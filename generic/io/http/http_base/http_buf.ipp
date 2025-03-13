#pragma once

template < class protocol > struct basic_http_buf<protocol>::authorization extends public detail::io_mode<pair<string,string>> { using detail::io_mode<pair<string,string>>::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::cookie        extends public detail::io_mode<map<string,string>>  { using detail::io_mode<map<string,string>> ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::header        extends public detail::io_mode<map<string,string>>  { using detail::io_mode<map<string,string>> ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::method        extends public detail::io_mode<string>              { using detail::io_mode<string>             ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::param         extends public detail::io_mode<map<string,string>>  { using detail::io_mode<map<string,string>> ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::path          extends public detail::io_mode<string>              { using detail::io_mode<string>             ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::port          extends public detail::io_mode<int>                 { using detail::io_mode<int>                ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::proxy         extends public detail::io_mode<url>                 { using detail::io_mode<url>                ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::timeout       extends public detail::io_mode<duration>            { using detail::io_mode<duration>           ::io_mode; struct http_client_mode_tag { }; };
template < class protocol > struct basic_http_buf<protocol>::version       extends public detail::io_mode<float>               { using detail::io_mode<float>              ::io_mode; struct http_client_mode_tag { }; };

template < class protocol >
void basic_http_buf<protocol>::connect ( url website, http_client_mode auto... args )
{
    // Check scheme.
    if ( ( same_as<protocol,tcp> but website.scheme() != "http"  ) or
         ( same_as<protocol,ssl> but website.scheme() != "https" ) )
        throw network_error("unrecognized http scheme (with url = {}, scheme = {}, expected = {})", website, website.scheme(), same_as<protocol,tcp> ? "http" otherwise "https");

    // Initialize.
    init_buffer_as_client();
    init_header_as_client(website, args...);

    // Connect.
    if ( optional_proxy_midway.empty() )
        connect_without_proxy(website);
    else
        connect_through_proxy(website, optional_proxy_midway.value());

    // Set state.
    status = status_type::client;
}

template < class protocol >
void basic_http_buf<protocol>::listen ( url portal, http_server_mode auto... args )
{
    // Check scheme.
    if ( portal.scheme() != "http" and portal.scheme() != "https" )
        throw network_error("unrecognized http scheme (with url = {}, scheme = {}, expected = {})", portal, portal.scheme(), same_as<protocol,tcp> ? "http" otherwise "https");

    // Initialize.
    init_buffer_as_server();
    init_header_as_server(portal, args...);

    // Listen.
    listen_to_port(portal);

    // Set state.
    status = status_type::server;
}

template < class protocol >
void basic_http_buf<protocol>::close ( )
{
    // Disconnect.
    disconnect();

    // Reset param.
    reset_everything();

    // Set state.
    status = status_type::close;
}

template < class protocol >
bool basic_http_buf<protocol>::is_open ( ) const
{
    // Returns the tate stored in data.
    [[assume((status != status_type::close) == handle.is_open())]];
    return status != status_type::close;
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
    return status == status_type::client ? receive_more(*response_parser) otherwise
           status == status_type::server ? receive_more(*request_parser ) otherwise
                                           throw network_error("receive message failed: http_buf has not been opened");
}

template < class protocol >
int basic_http_buf<protocol>::overflow ( int c )
{
    status == status_type::client ? send_more(c, *request_serializer ) otherwise
    status == status_type::server ? send_more(c, *response_serializer) otherwise
                                    throw network_error("send message failed: http_buf has not been opened");
    return traits_type::to_int_type(c);
}

template < class protocol >
int basic_http_buf<protocol>::sync ( )
{
    status == status_type::client ? send_end(*request_serializer ) otherwise
    status == status_type::server ? send_end(*response_serializer) otherwise
                                    throw network_error("send message failed: http_buf has not been opened");
    reset_send_buffer();
    return 0;
}

template < class protocol >
void basic_http_buf<protocol>::init_buffer_as_client ( )
{
    send_request_buff  = std::make_unique<boost::beast::http::request           <boost::beast::http::string_body>>();
    request_serializer = std::make_unique<boost::beast::http::request_serializer<boost::beast::http::string_body>>(*send_request_buff);
    response_parser    = std::make_unique<boost::beast::http::response_parser   <boost::beast::http::string_body>>();
    receive_buff       = std::make_unique<boost::beast::flat_buffer>();
    response_parser->body_limit(boost::none);
    cache_header_received = false;
}

template < class protocol >
void basic_http_buf<protocol>::init_buffer_as_server ( )
{
    send_response_buff  = std::make_unique<boost::beast::http::response           <boost::beast::http::string_body>>();
    response_serializer = std::make_unique<boost::beast::http::response_serializer<boost::beast::http::string_body>>(*send_response_buff);
    request_parser      = std::make_unique<boost::beast::http::request_parser     <boost::beast::http::string_body>>();
    receive_buff        = std::make_unique<boost::beast::flat_buffer>();
    request_parser->body_limit(boost::none);
    cache_header_received = false;
}

template < class protocol >
void basic_http_buf<protocol>::init_header_as_client ( const url& website, const auto&... args )
{
    static_assert ( detail::all_different<decltype(args)...> );

    // Default settings
    current_request_method  = "GET";
    current_request_path    = website.path();
    current_request_param   = website.param() != "" ? website.param().split('&') | std::views::transform([] (const auto& kv) { return pair<string,string>(kv.partition('=')[1], kv.partition('=')[3]); }) | std::ranges::to<map<string,string>>() otherwise map<string,string>();
    current_request_version = 1.1;
    current_request_header  = map<string,string>{{"Host",       website.port() != "" ? "{}:{}"s.format(website.host(), website.port()) otherwise website.host()},  
                                                 {"User-Agent", "C++"},
                                                 {"Accept",     "*/*"}};

    // Authorization
    if ( website.authorization() != "" )
        current_request_header["Authorization"] = "Basic {}"s.format(website.authorization() | views::encode_base64 | std::ranges::to<string>());
    else if constexpr ( ( same_as<authorization,decay<decltype(args)>> or ... ) )
        current_request_header["Authorization"] = "Basic {}"s.format("{}:{}"s.format(detail::value_of_same_type<authorization>(args...).value.key(), detail::value_of_same_type<authorization>(args...).value.value()) | views::encode_base64 | std::ranges::to<string>());

    // Cookie
    else if constexpr ( ( same_as<cookie,decay<decltype(args)>> or ... ) )
        current_request_header["Cookie"] = detail::value_of_same_type<cookie>(args...).value
                                         | std::views::transform([] (const auto& kv) { return "{}={}"s.format(kv.key(), kv.value()); })
                                         | std::views::join_with("; "s)
                                         | std::ranges::to<string>();

    // Header
    else if constexpr ( ( same_as<header,decay<decltype(args)>> or ... ) )
        for ( const auto& [k, v] in detail::value_of_same_type<header>(args...).value )
            current_request_header[k] = v;

    // Method
    else if constexpr ( ( same_as<method,decay<decltype(args)>> or ... ) )
        current_request_method = detail::value_of_same_type<method>(args...).value;

    // Param
    else if constexpr ( ( same_as<param,decay<decltype(args)>> or ... ) )
        current_request_param = detail::value_of_same_type<param>(args...).value;
    
    // Path
    else if constexpr ( ( same_as<path,decay<decltype(args)>> or ... ) )
        current_request_path = detail::value_of_same_type<path>(args...).value;

    // Port
    else if constexpr ( ( same_as<port,decay<decltype(args)>> or ... ) )
        optional_port = detail::value_of_same_type<port>(args...).value;

    // Proxy
    else if constexpr ( ( same_as<proxy,decay<decltype(args)>> or ... ) )
        optional_proxy_midway = detail::value_of_same_type<proxy>(args...).value;

    // Timeout
    else if constexpr ( ( same_as<timeout,decay<decltype(args)>> or ... ) )
        handle.expires_after(std::chrono::nanoseconds(detail::value_of_same_type<timeout>(args...).value));

    // Version
    else if constexpr ( ( same_as<version,decay<decltype(args)>> or ... ) )
        current_request_version = detail::value_of_same_type<version>(args...).value;

    // Other
    else if constexpr ( sizeof...(args) >= 1 )
        static_assert(false, "invalid mode");

    // Check authorization
    if ( ( website.authorization() != "" ) + ( same_as<authorization,decay<decltype(args)>> or ... ) + ( detail::value_of_same_type_or<header>(args..., header()).value.contains("Authorization") ) >= 2 )
        throw network_error("duplicate settings: authorization repeatedly set at least 2 times: url (with value = {}), http_buf::authorization (with value = {}), http_buf::header (with value = {})", website, detail::value_of_same_type_or<authorization>(args..., authorization()).value, detail::value_of_same_type_or<header>(args..., header()).value);
    
    // Check cookie
    if ( ( same_as<cookie,decay<decltype(args)>> or ... ) and detail::value_of_same_type_or<header>(args..., header()).value.contains("Cookie") )
        throw network_error("duplicate settings: cookie both set in http_buf::cookie (with value = {}) and http_buf::header (with value = {})", detail::value_of_same_type_or<cookie>(args..., cookie()).value, detail::value_of_same_type_or<header>(args..., header()).value);

    // Check param
    if ( website.param() != "" and ( same_as<param,decay<decltype(args)>> or ... ) )
        throw network_error("duplicate settings: param both set in url (with value = {}) and http_buf::param (with value = {})", website, detail::value_of_same_type_or<param>(args..., param()).value);

    // Check path
    if ( website.path() != "" and ( same_as<path,decay<decltype(args)>> or ... ) )
        throw network_error("duplicate settings: path both set in url (with value = {}) and http_buf::path (with value = {})", website, detail::value_of_same_type_or<path>(args..., path()).value);
    if constexpr ( ( same_as<path,decay<decltype(args)>> or ... ) ) 
        if ( detail::value_of_same_type<path>(args...).value.begins_with('/') )
            throw network_error("invalid setting: path (with value = {}) should not begins with '/', as it has been default provided", detail::value_of_same_type<path>(args...).value);

    // Check port
    if ( website.port() != "" and ( same_as<port,decay<decltype(args)>> or ... ) )
        throw network_error("duplicate settings: port both set in url (with value = {}) and http_buf::port (with value = {})", website, detail::value_of_same_type_or<port>(args..., port()).value);

    // Check proxy
    if constexpr ( ( same_as<proxy,decay<decltype(args)>> or ... ) )
        if ( detail::value_of_same_type<proxy>(args...).value.scheme() != "http" )
            throw network_error("invalid setting: proxy (with value = {}) should be within http scheme", detail::value_of_same_type<proxy>(args...).value);
}

template < class protocol >
void basic_http_buf<protocol>::init_header_as_server ( const url& portal, const auto&... args )
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
auto basic_http_buf<protocol>::resolve_url ( const url& website )
{
    try
    {
        return typename protocol::resolver(io_context).resolve(
                   website.host().c_str(),
                   (website.port() != ""      ? website.port()                otherwise
                    not optional_port.empty() ? string(optional_port.value()) otherwise
                                                website.scheme()).c_str());
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("resolution failed (with local_endpoint = {}, remote_url = {})", local_endpoint_noexcept(), website).from(detail::system_error(e));
    }
}

template < class protocol >
void basic_http_buf<protocol>::connect_without_proxy ( const url& website )
{
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
        throw network_error("connection failed (with remote_url = {}, remote_endpoint = {})", website, resolve_results | std::ranges::to<vector<typename protocol::endpoint>>()).from(detail::all_attempts_failed(errpool));
}

template < class protocol >
void basic_http_buf<protocol>::connect_through_proxy ( const url& website, const url& proxy_website )
    requires same_as<protocol,tcp>
{
    connect_without_proxy(proxy_website);
    optional_proxy_target = website;
}

template < class protocol >
void basic_http_buf<protocol>::connect_through_proxy ( const url& website, const url& proxy_website )
    requires same_as<protocol,ssl> or same_as<protocol,tls>
{
    // Connect to proxy server. We demand the proxy website to be http.
    let errpool = vector<detail::system_error>();
    let proxy_results = resolve_url(proxy_website);
    for ( const auto& proxy_entry in proxy_results )
        try
        {
            // Connect proxy server
            handle.next_layer().connect(proxy_entry);

            // Prepare "CONNECT" request and response.
            let target = "{}:{}"s.format(website.host(), website.port() != ""      ? website.port()                otherwise
                                                         not optional_port.empty() ? string(optional_port.value()) otherwise
                                                         same_as<protocol,tcp>     ? "80"                          otherwise
                                                                                     "443");
            let tunnel_request  = boost::beast::http::request        <boost::beast::http::empty_body>();
            let tunnel_response = boost::beast::http::response_parser<boost::beast::http::empty_body>();
            let tunnel_buff     = boost::beast::flat_buffer();
            tunnel_request.method(boost::beast::http::verb::connect);
            tunnel_request.target(target.c_str());
            tunnel_request.set(boost::beast::http::field::host,             target.c_str());
            tunnel_request.set(boost::beast::http::field::user_agent,       request_header()["User-Agent"].c_str());
            tunnel_request.set(boost::beast::http::field::connection,       "keep-alive");
            tunnel_request.set(boost::beast::http::field::proxy_connection, "keep-alive");
            tunnel_response.skip(true); // Skip the body. Most times the response to "CONNECT" request is empty-header and empty-body.
        
            // Send request and receive response to/from proxy server.
            let buff = boost::beast::flat_buffer();
            boost::beast::http::write(handle.next_layer(),       tunnel_request );
            boost::beast::http::read (handle.next_layer(), buff, tunnel_response);
            if ( tunnel_response.get().result_int() >= 300 and tunnel_response.get().result_int() <= 599 )
                throw boost::system::system_error(boost::system::error_code(), "received {} {} from proxy server"s.format(tunnel_response.get().result_int(), std::string(tunnel_response.get().reason())));
        
            // Do SSL handshake in tunnel.
            let sni_success = SSL_set_tlsext_host_name(handle.native_handle(), website.host().c_str());
            if ( not sni_success )
                throw boost::system::system_error(boost::beast::error_code(int(ERR_get_error()), boost::asio::error::get_ssl_category()));
            handle.handshake(boost::asio::ssl::stream_base::client);
        
            break;
            break;
        }
        catch ( const boost::system::system_error& e )
        {
            errpool.push(detail::system_error(e));
        }
    if ( not errpool.empty() )
        throw network_error("connection failed (with remote_url = {})", website).from(detail::all_attempts_failed(errpool));
}

template < class protocol >
void basic_http_buf<protocol>::listen_to_port ( const url& portal )
{
    // Listen.
    let errpool = vector<detail::system_error>();
    let resolve_results = resolve_url(portal);
    for ( const auto& resolve_entry in resolve_results )
        try
        {
            typename protocol::acceptor(io_context, resolve_entry).accept(handle);
            break;
        }
        catch ( const boost::system::system_error& e )
        {
            errpool.push(detail::system_error(e));
        }
    if ( not errpool.empty() )
        throw network_error("listening failed (with local_url = {}, local_endpoint = {})", portal, resolve_results | std::ranges::to<vector<boost::asio::ip::tcp::endpoint>>()).from(detail::all_attempts_failed(errpool));
}

template < class protocol >
void basic_http_buf<protocol>::disconnect ( )
{
    // Disconnect.
    try
    {
        handle.shutdown(boost::asio::socket_base::shutdown_both);
        handle.close();
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("disconnection failed (with local_endpoint = {}, remote_endpoint = {})", local_endpoint_noexcept(), remote_endpoint_noexcept()).from(detail::system_error(e));
    }
}

template < class protocol >
void basic_http_buf<protocol>::send_more ( int c, auto& serializer )
{
    using message_type = remove_const<typename decay<decltype(serializer)>::value_type>;

    try
    {
        // Before the first message, resize the buffer.
        if ( serializer.get().body() == "" )
        {
            const_cast<std::string&>(serializer.get().body()).resize(default_buffer_size);
            setp(const_cast<char*>(serializer.get().body().data()),
                 const_cast<char*>(serializer.get().body().data()) + serializer.get().body().size());
        }

        // Send a chunked message.
        else
        {
            const_cast<message_type&>(serializer.get()).chunked(true);
            if ( not serializer.is_header_done() )
            {
                update_header_to(serializer);
                boost::beast::http::write_header(handle, serializer);
            }
            boost::asio::write(handle, boost::beast::http::make_chunk(boost::asio::buffer(serializer.get().body())));
            setp(const_cast<char*>(serializer.get().body().data()),
                 const_cast<char*>(serializer.get().body().data()) + serializer.get().body().size());
        }

        *pptr() = traits_type::to_char_type(c);
        pbump(1);
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("send {} failed (with local_endpoint = {}, remote_endpoint = {})", decay<decltype(serializer)>::value_type::is_request::value ? "request" otherwise "response", local_endpoint_noexcept(), remote_endpoint_noexcept()).from(detail::system_error(e));
    } 
}

template < class protocol >
void basic_http_buf<protocol>::send_end ( auto& serializer )
{
    using message_type = remove_const<typename decay<decltype(serializer)>::value_type>;

    try
    {
        // Send the whole message.
        if ( not serializer.get().chunked() )
        {
            update_header_to(serializer);
            const_cast<message_type&>(serializer.get()).body().resize(pptr() - pbase());
            const_cast<message_type&>(serializer.get()).prepare_payload();
            boost::beast::http::write(handle, serializer.get());
        }

        // Send the end chunks.
        else
        {
            const_cast<message_type&>(serializer.get()).body().resize(pptr() - pbase());
            boost::asio::write(handle, boost::beast::http::make_chunk(boost::asio::buffer(serializer.get().body())));
            boost::asio::write(handle, boost::beast::http::make_chunk_last());
        }

        // We will receive 1 more response.
        cache_message_receivable++;
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("send {} failed (with local_endpoint = {}, remote_endpoint = {})", decay<decltype(serializer)>::value_type::is_request::value ? "request" otherwise "response", local_endpoint_noexcept(), remote_endpoint_noexcept()).from(detail::system_error(e));
    }
}

template < class protocol >
int basic_http_buf<protocol>::receive_more ( auto& parser )
{
    try
    {
        // Receive header (if 1st time).
        if ( not parser.is_header_done() )
            receive_begin(parser);

        // Receive more body.
        if ( not parser.is_done() )
        {
            // Receive chunked body.
            parser.get().body().clear();
            int bytes = boost::beast::http::read_some(handle, *receive_buff, parser);

            // Update get area.
            setg(const_cast<char*>(parser.get().body().data()),
                 const_cast<char*>(parser.get().body().data()),
                 const_cast<char*>(parser.get().body().data()) + bytes);
            return traits_type::to_int_type(*gptr());
        }

        // Receive more response (if response is cached)
        else if ( cache_message_receivable > 0 )
        {
            reset_receive_buffer();
            return receive_more(parser);
        }

        // End.
        else
            return traits_type::eof();
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("receive {} failed (with local_endpoint = {}, remote_endpoint = {})", decay<decltype(parser)>::value_type::is_request::value ? "request" otherwise "response", local_endpoint_noexcept(), remote_endpoint_noexcept()).from(detail::system_error(e));
    }
}

template < class protocol >
void basic_http_buf<protocol>::receive_begin ( auto& parser )
{
    try
    {
        // Receive header.
        boost::beast::http::read_header(handle, *receive_buff, parser);
        update_header_from(parser);
        cache_header_received = true;

        // Set receive cache.
        cache_message_receivable--;
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("receive {} failed (with local_endpoint = {}, remote_endpoint = {})", decay<decltype(parser)>::value_type::is_request::value ? "request" otherwise "response", local_endpoint_noexcept(), remote_endpoint_noexcept()).from(detail::system_error(e));
    }
}

template < class protocol >
void basic_http_buf<protocol>::reset_send_buffer ( )
{
    if ( status == status_type::client )
    {
        // Will not reset header (stored in send_request_buff).
        request_serializer = std::make_unique<boost::beast::http::request_serializer<boost::beast::http::string_body>>(*send_request_buff);
        const_cast<std::string&>(request_serializer->get().body()).clear();
        setp(nullptr,
             nullptr);
    }

    else if ( status == status_type::server )
    {
        // Will not reset header (stored in send_response_buff).
        response_serializer = std::make_unique<boost::beast::http::response_serializer<boost::beast::http::string_body>>(*send_response_buff);
        const_cast<std::string&>(response_serializer->get().body()).clear();
        setp(nullptr,
             nullptr);
    }

    else
        throw network_error("refresh_send failed: http_buf has not been opened");
}

template < class protocol >
void basic_http_buf<protocol>::reset_receive_buffer ( )
{

    if ( status == status_type::client )
    {
        receive_buff    = std::make_unique<boost::beast::flat_buffer>();
        response_parser = std::make_unique<boost::beast::http::response_parser<boost::beast::http::string_body>>();
        response_parser->body_limit(boost::none);
        cache_header_received = false;
        setg(nullptr,
             nullptr,
             nullptr);
    }

    else if ( status == status_type::server )
    {
        receive_buff    = std::make_unique<boost::beast::flat_buffer>();
        request_parser  = std::make_unique<boost::beast::http::request_parser<boost::beast::http::string_body>>();
        request_parser->body_limit(boost::none);
        cache_header_received = false;
        setg(nullptr, 
             nullptr,
             nullptr);
    }

    else
        throw network_error("refresh_receive failed: http_buf has not been opened");
}

template < class protocol >
void basic_http_buf<protocol>::reset_everything ( )
{
    // Reset handle.
    if ( handle.is_open() )
        handle.close();

    // Reset buffer.
    request_serializer           = nullptr;
    request_parser               = nullptr;
    response_serializer          = nullptr;
    response_parser              = nullptr;
    send_request_buff            = nullptr;
    send_response_buff           = nullptr;
    receive_buff                 = nullptr;

    // Reset header.
    current_request_method       = "GET";
    current_request_path         = "";
    current_request_param        = map<string,string>();
    current_request_version      = 1.1;
    current_request_header       = map<string,string>();
    current_response_version     = 1.1;
    current_response_status_code = 200;
    current_response_reason      = "OK";
    current_response_header      = map<string,string>();

    // Reset param.
    optional_port                = nullopt;
    optional_proxy_midway        = nullopt;
    optional_proxy_target        = nullopt;
    cache_header_received        = false;
    cache_message_receivable     = 0;

    // Reset put/get area.
    setp(nullptr, nullptr);
    setg(nullptr, nullptr, nullptr);
}

template < class protocol >
void basic_http_buf<protocol>::update_header_to ( auto& serializer )
{

    if constexpr ( decay<decltype(serializer.get())>::is_request::value )
    {
        let& request = const_cast<boost::beast::http::request<boost::beast::http::string_body>&>(serializer.get());

        request.method(boost::beast::http::string_to_verb(current_request_method.c_str()) != boost::beast::http::verb::unknown ?
                       boost::beast::http::string_to_verb(current_request_method.c_str()) otherwise throw network_error("unrecognized http method {} (expected = GET, POST, ...)", current_request_method));
        request.target("/{}{}{}"s.format(current_request_path, 
                                         not current_request_param.empty() ? "?" otherwise "",
                                         current_request_param | std::views::transform([] (const auto& kv) { return "{}={}"s.format(kv.key(), kv.value()); }) 
                                                               | std::views::join_with('&')
                                                               | std::ranges::to<string>()).c_str()); // /path?key=value
        if ( not optional_proxy_midway.empty() and same_as<protocol,tcp> ) // If we are using http (not https) proxy, then request.target() should be expanded into full url, and followed with it's origin value (path, param...).
            request.target("{}://{}{}{}"s.format(optional_proxy_target.value().scheme(),
                                                 optional_proxy_target.value().host(), 
                                                 optional_proxy_target.value().port() != "" ? ":{}"s.format(optional_proxy_target.value().port()) otherwise "",
                                                 string(request.target())).c_str()); // http://final_target.com/path?key=value
        request.version(int(current_request_version * 10));
        for ( const auto& [k, v] in current_request_header )
            boost::beast::http::string_to_field(k.c_str()) != boost::beast::http::field::unknown ? 
                request.set(boost::beast::http::string_to_field(k.c_str()), v.c_str()) otherwise
                request.set(k.c_str(), v.c_str());
    }

    else
    {
        let& response = const_cast<boost::beast::http::response<boost::beast::http::string_body>&>(serializer.get());

        response.result(boost::beast::http::int_to_status(current_response_status_code) != boost::beast::http::status::unknown ? 
                        boost::beast::http::int_to_status(current_response_status_code) otherwise throw network_error("unrecognized http status code {} (expected = 200, 404, ...)", current_response_status_code));
        response.reason(current_response_reason.c_str());
        for ( const auto& [k, v] in current_response_header )
            boost::beast::http::string_to_field(k.c_str()) != boost::beast::http::field::unknown ? 
                response.set(boost::beast::http::string_to_field(k.c_str()), v.c_str()) otherwise
                response.set(k.c_str(), v.c_str());
    }
}

template < class protocol >
void basic_http_buf<protocol>::update_header_from ( auto& parser )
{
    if constexpr ( decay<decltype(parser.get())>::is_request::value )
    {
        current_request_method  = string(boost::beast::http::to_string(parser.get().method()));
        current_request_path    = string(parser.get().target()).partition('?')[1][2,-1]; // Get rid of beginning '/'.
        current_request_param   = string(parser.get().target()).partition('?')[3].split('&') | std::views::transform([] (const auto& kv) { return pair<string,string>(kv.partition('=')[1], kv.partition('=')[3]); }) | std::ranges::to<map<string,string>>();
        current_request_version = parser.get().version() / 10.0f;
        current_request_header  = parser.get() | std::views::transform([] (const auto& head) { return pair(string(head.name_string()), string(head.value())); })
                                               | std::ranges::to<map<string,string>>();
    }

    else
    {
        current_response_status_code = parser.get().result_int();
        current_response_reason      = string(parser.get().reason());
        current_request_header       = parser.get() | std::views::transform([] (const auto& head) { return pair(string(head.name_string()), string(head.value())); })
                                                    | std::ranges::to<map<string,string>>();
    }
}

template < class protocol >
string basic_http_buf<protocol>::local_endpoint_noexcept ( ) const
{
    try
    {
        return "{}://{}"s.format(same_as<protocol,tcp> ? "http" otherwise "https", handle.local_endpoint());
    }
    catch ( const boost::system::system_error& e )
    {
        return "[[bad local endpoint]]";
    }
}

template < class protocol >
string basic_http_buf<protocol>::remote_endpoint_noexcept ( ) const
{
    try
    {
        return "{}://{}"s.format(same_as<protocol,tcp> ? "http" otherwise "https", handle.remote_endpoint());
    }
    catch ( const boost::system::system_error& e )
    {
        return "[[bad remote endpoint]]";
    }
}

