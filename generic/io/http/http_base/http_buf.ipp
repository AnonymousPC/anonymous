#pragma once

struct http_buf::authorization extends public detail::io_mode<pair<string,string>> { using detail::io_mode<pair<string,string>>::io_mode; struct http_client_mode_tag { }; };
struct http_buf::cookie        extends public detail::io_mode<map<string,string>>  { using detail::io_mode<map<string,string>> ::io_mode; struct http_client_mode_tag { }; };
struct http_buf::header        extends public detail::io_mode<map<string,string>>  { using detail::io_mode<map<string,string>> ::io_mode; struct http_client_mode_tag { }; };
struct http_buf::method        extends public detail::io_mode<string>              { using detail::io_mode<string>             ::io_mode; struct http_client_mode_tag { }; };
struct http_buf::param         extends public detail::io_mode<map<string,string>>  { using detail::io_mode<map<string,string>> ::io_mode; struct http_client_mode_tag { }; };
struct http_buf::path          extends public detail::io_mode<string>              { using detail::io_mode<string>             ::io_mode; struct http_client_mode_tag { }; };
struct http_buf::port          extends public detail::io_mode<int>                 { using detail::io_mode<int>                ::io_mode; struct http_client_mode_tag { }; };
struct http_buf::proxy         extends public detail::io_mode<url>                 { using detail::io_mode<url>                ::io_mode; struct http_client_mode_tag { }; };
struct http_buf::timeout       extends public detail::io_mode<duration>            { using detail::io_mode<duration>           ::io_mode; struct http_client_mode_tag { }; };
struct http_buf::version       extends public detail::io_mode<float>               { using detail::io_mode<float>              ::io_mode; struct http_client_mode_tag { }; };

void http_buf::connect ( url website, http_client_mode auto... args )
{
    // Check state.
    if ( opened != open_type::close )
        throw network_error("connection failed: http_buf has been already opened (with mode = {}, local_endpoint = {}, remote_endpoint = {})",
                            opened == open_type::client ? "client" otherwise "server", local_endpoint_noexcept(), remote_endpoint_noexcept());

    // Check scheme.
    if ( website.scheme() != "http" and website.scheme() != "https" )
        throw network_error("unrecognized http scheme (with url = {}, expected = [[begins with http://, https://]])", website);

    // Create http handle.
    initialize_as(open_type::client);

    // Set request.
    set_client_request(website, args...);

    // Connect.
    if ( optional_proxy_midway.empty() )
        connect_without_proxy(website);
    else
        connect_through_proxy(website, optional_proxy_midway.value());

    // Set state.
    opened = open_type::client;
}

void http_buf::listen ( url portal, http_server_mode auto... args )
{
    // Check state.
    if ( opened != open_type::close )
        throw network_error("listening failed: http_buf has been already opened (with mode = {}, local_endpoint = {}, remote_endpoint = {})",
                            opened == open_type::client ? "client" otherwise "server", local_endpoint_noexcept(), remote_endpoint_noexcept());

    // Check scheme.
    if ( portal.scheme() != "http" and portal.scheme() != "https" )
        throw network_error("unrecognized http scheme (with url = {}, expected = [[begins with http:// or https://]])", portal);

    // Create http handle.
    initialize_as(open_type::server);

    // Set response.
    set_server_response(portal, args...);

    // Listen.
    listen_to_port(portal);

    // Set state.
    opened = open_type::server;
}




// Auxiliary

void http_buf::set_client_request ( const url& website, const auto&... args )
{
    static_assert ( detail::all_different<decltype(args)...> );

    // Default settings
    current_request_method  = "get";
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

    // Timeout
    if constexpr ( ( same_as<timeout,decay<decltype(args)>> or ... ) )
        http_handle->expires_after(std::chrono::nanoseconds(detail::value_of_same_type<timeout>(args...).value));

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

void http_buf::set_server_response ( const url& portal, const auto&... args )
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
