#pragma once

/// Auxiliary

namespace aux
{
    void try_for_each ( const auto&, auto, auto );
}


/// Subclass

struct http_buf::client_mode_type
{
    pair<string,string> authorization = {};
    map<string,string>  cookie        = {};
    map<string,string>  header        = {};
    string              method        = "";
    map<string,string>  param         = {};
    string              path          = "";
    optional<int>       port          = nullopt;
    url                 proxy         = {};
    optional<duration>  timeout       = nullopt;
    optional<float>     version       = nullopt;
};

struct http_buf::server_mode_type
{

};




/// Class http_buf

// Interface

void http_buf::connect ( url website, http_client_mode auto... args )
{
    // Check state.
    if ( opened != open_type::close )
        throw network_error("connection failed: http_buf has been already opened (with mode = {}, local-endpoint = {}, remote-endpoint = {})",
                            opened == open_type::client ? "client" otherwise "server", local_endpoint_noexcept(), remote_endpoint_noexcept());

    // Check scheme.
    if ( website.scheme() != "http" and website.scheme() != "https" )
        throw network_error("unrecognized http scheme (with url = {}, expected = [[begins with http://, https://]])", website);

    // Create http handle.
    initialize_as(open_type::client);

    // Set request.
    set_client_request(website, std::forward<decltype(args)>(args)...);

    // Connect.
    if ( modes_proxy.empty() )
        connect_without_proxy(website);
    else
        connect_through_proxy(website, modes_proxy.value());

    // Set state.
    opened = open_type::client;
}

void http_buf::listen ( url portal, http_server_mode auto... args )
{
    // Check state.
    if ( opened != open_type::close )
        throw network_error("listening failed: http_buf has been already opened (with mode = {}, local-endpoint = {}, remote-endpoint = {})",
                            opened == open_type::client ? "client" otherwise "server", local_endpoint_noexcept(), remote_endpoint_noexcept());

    // Check scheme.
    if ( portal.scheme() != "http" and portal.scheme() != "https" )
        throw network_error("unrecognized http scheme (with url = {}, expected = [[begins with http://, https://]])", portal);

    // Create http handle.
    initialize_as(open_type::server);

    // Set response.
    set_server_response(portal, std::forward<decltype(args)>(args)...);

    // Listen.
    listen_to_port(portal);

    // Set state.
    opened = open_type::server;
}




// Auxiliary

void http_buf::set_client_request ( const url& website, const auto&... args )
{
    auto& request = const_cast<boost::beast::http::request<boost::beast::http::string_body>&>(request_serializer->get());

    // Set default header.
    request.method(boost::beast::http::verb::get);
    request.target(('/' + website.path() + (website.param() != "" ? "?" otherwise "") + website.param()).c_str());
    request.version(11);
    request.set(boost::beast::http::field::host,       (website.host() + (website.port() != "" ? ':' + website.port() otherwise "")).c_str());
    request.set(boost::beast::http::field::user_agent, "C++");
    request.set(boost::beast::http::field::accept,     "*/*");

    // Set header.
    if constexpr ( sizeof...(args) >= 1 )
    {
        let modes = make_client_mode(website, std::forward<decltype(args)>(args)...);

        // Authorization
        if ( website.authorization() != "" )
            request.set(boost::beast::http::field::authorization, "Basic {}"s.format(encode_base64(website.authorization())).c_str());
        else if ( modes.authorization != pair<string,string>{"", ""} )
            request.set(boost::beast::http::field::authorization, "Basic {}"s.format(encode_base64("{}:{}"s.format(modes.authorization.key(), modes.authorization.value()))).c_str());

        // Cookie
        if ( not modes.cookie.empty() )
            request.set(boost::beast::http::field::cookie, (modes.cookie | std::views::transform([] (const auto& kv) { return "{}={}"s.format(kv.key(), kv.value()); })
                                                                         | std::views::join_with("; "s)
                                                                         | std::ranges::to<string>()).c_str());

        // Header
        for ( const auto& [k, v] in modes.header )
            if ( boost::beast::http::string_to_field(k.c_str()) != boost::beast::http::field::unknown )
                request.set(boost::beast::http::string_to_field(k.c_str()), v.c_str());
            else
                request.set(k.c_str(), v.c_str());

        // Method
        if ( modes.method != "" )
        {
            if ( boost::beast::http::string_to_verb(string(modes.method).upper().c_str()) != boost::beast::http::verb::unknown )
                request.method(boost::beast::http::string_to_verb(string(modes.method).upper().c_str()));
            else
                throw network_error("unrecognized http method (expected = GET, POST, ...): {}", modes.method);
        }

        // Param, Path
        if ( not modes.param.empty() or modes.path != "" )
        {
            let cur_path  = website.path ();
            let cur_param = website.param();

            if ( modes.path != "" )
                cur_path = not modes.path.begins_with('/') ? modes.path otherwise modes.path[2,-1];
            if ( not modes.param.empty() )
                cur_param = modes.param | std::views::transform([] (const auto& kv) { return "{}={}"s.format(kv.key(), kv.value()); })
                                        | std::views::join_with('&')
                                        | std::ranges::to<string>();

            request.target(('/' + cur_path + (cur_param != "" ? "?" otherwise "") + cur_param).c_str());
        }

        // Port
        if ( not modes.port.empty() )
        {
            request.set(boost::beast::http::field::host, (website.host() + ':' + string(modes.port.value())).c_str());
            modes_port = modes.port;
        }

        // Proxy
        if ( modes.proxy != "" )
            modes_proxy = modes.proxy;

        // Timeout
        if ( not modes.timeout.empty() )
            http_handle->expires_after(std::chrono::nanoseconds(modes.timeout.value()));

        // Version
        if ( not modes.version.empty() )
        {
            if ( string(modes.version.value()) == "1" or string(modes.version.value()) == "1.1" ) // Convert to string, thus allow tiny error.
                request.version(int(modes.version.value() * 10));
            else
                throw network_error("unrecognized http version: {}", modes.version.value());
        }
    }
}

auto http_buf::make_client_mode ( const url& website, auto prm, auto... args )
{
    static_assert(aux::all_different<decltype(prm),decltype(args)...>, "modes must be unique");
    return make_client_mode(client_mode_type(), website, std::forward<decltype(prm)>(prm), std::forward<decltype(args)>(args)...);
}

auto http_buf::make_client_mode ( client_mode_type modes, const url& website, auto prm, auto... args )
{
    // Update modes parameters.
    if constexpr ( std::same_as<decltype(prm),authorization> )
        modes.authorization = std::move(prm.value);

    else if constexpr ( std::same_as<decltype(prm),cookie> )
        modes.cookie = std::move(prm.value);

    else if constexpr ( std::same_as<decltype(prm),header> )
        modes.header = std::move(prm.value);

    else if constexpr ( std::same_as<decltype(prm),method> )
        modes.method = std::move(prm.value);

    else if constexpr ( std::same_as<decltype(prm),param> )
        modes.param = std::move(prm.value);

    else if constexpr ( std::same_as<decltype(prm),path> )
        modes.path = std::move(prm.value);

    else if constexpr ( std::same_as<decltype(prm),port> )
        modes.port = std::move(prm.value);

    else if constexpr ( std::same_as<decltype(prm),proxy> )
        modes.proxy = std::move(prm.value);

    else if constexpr ( std::same_as<decltype(prm),timeout> )
        modes.timeout = std::move(prm.value);

    else if constexpr ( std::same_as<decltype(prm),version> )
        modes.version = std::move(prm.value);

    else if constexpr ( not http_client_mode<decltype(prm)> )
        static_assert(false, "invalid mode");


    // Continue making modes ...
    if constexpr ( sizeof...(args) >= 1 )
        return make_client_mode(modes, website, std::forward<decltype(args)>(args)...);

    // ... Or return already maked modes (and check it)
    else
    {
        // Authorization.
        if ( (website.authorization() != "") + (modes.header.keys().contains("Authorization")) + (modes.authorization != pair<string,string>{"", ""}) >= 2 )
            throw network_error("conflict settings: authorization repeatedly set at least 2 times: url (with url = {}, authorization = {}), http_buf::header (with header = {}), http_buf::authorization (with value = {})",
                                website, website.authorization() != ""             ? website.authorization()                                          otherwise "\"\"",
                                modes.header.keys().contains("Authorization")      ? "Authorization: Basic {}"s.format(modes.header["Authorization"]) otherwise "\"\"",
                                modes.authorization != pair<string,string>{"", ""} ? modes.authorization                                              otherwise pair<string,string>{"\"\"", "\"\""});

        // Cookie.
        if ( modes.header.keys().contains("Cookie") and not modes.cookie.empty() )
            throw network_error("conflict settings: cookie both set in http_buf::header (with header = {}) and http_buf::cookie (with value = {})",
                                "Cookie: {}"s.format(modes.header["Cookie"]), modes.cookie);

        // Param.
        if ( website.param() != "" and not modes.param.empty() )
            throw network_error("conflict settings: param both set in url (with url = {}, param = {}) and http_buf::param (with value = {})",
                                website, website.param(), modes.param);

        // Path.
        if ( website.path() != "" and modes.path != "" )
            throw network_error("conflict settings: path both set in url (with url = {}, param = {}) and http_buf::path (with value = {})",
                                website, website.path(), modes.path);

        if ( modes.path != "" and modes.path.begins_with('/') )
            throw network_error("invalid settings: path should not begins with '/', as it has been default provided (with url = {}, path = {})",
                                website, website.path());

        // Port.
        if ( website.port() != "" and not modes.port.empty() )
            throw network_error("conflict settings: port both set in url (with url = {}, port = {}) and http_buf::port (with value = {})",
                                website, website.port(), modes.port.value());

        return modes;
    }
}

void http_buf::set_server_response ( const url& portal, const auto&... args )
{
    auto& response = const_cast<boost::beast::http::response<boost::beast::http::string_body>&>(response_serializer->get());

    // Set default header.
    response.result(boost::beast::http::status::ok);
    response.version(11);
    response.set(boost::beast::http::field::server,                       "C++");
    response.set(boost::beast::http::field::content_type,                 "text/plain");
    response.set(boost::beast::http::field::access_control_allow_origin,  "*");
    response.set(boost::beast::http::field::access_control_allow_methods, "GET");
    response.set(boost::beast::http::field::access_control_allow_headers, "Content-Type");

    // Set header.
    if constexpr ( sizeof...(args) >= 1 )
    {
        let modes = make_server_mode(portal, std::forward<decltype(args)>(args)...);
        //...
    }

    // Set body.
    response.body().resize(4096);
    setp(const_cast<char*>(response.body().data()),
         const_cast<char*>(response.body().data()) + response.body().size());
}

auto http_buf::make_server_mode ( const url& portal, auto prm, auto... args )
{
    static_assert(aux::all_different<decltype(prm),decltype(args)...>, "modes must be unique");
    return make_server_mode(client_mode_type(), portal, std::forward<decltype(prm)>(prm), std::forward<decltype(args)>(args)...);
}

auto http_buf::make_server_mode ( server_mode_type modes, const url& portal, auto prm, auto... args )
{
    // Update modes parameters.

    // Continue making modes ...
    if constexpr ( sizeof...(args) >= 1 )
        return make_client_mode(modes, portal, std::forward<decltype(args)>(args)...);

    // ... Or return already maked modes (and check it)
    else
    {
        if ( portal.port() == "" )
            throw network_error("invalid settings: port must be explicitly defined when listening it (with portal = {}, port = {})",
                                portal, portal.port());

        return modes;
    }
}







/// Class netstream::mode_base

template < class type >
constexpr http_buf::mode_base<type>::mode_base ( type v )
    extends value ( std::move ( v ) )
{

}



template < pair_type type >
constexpr http_buf::mode_base<type>::mode_base ( type::key_type k, type::value_type v )
    extends value ( { std::move(k), std::move(v) } )
{

}

template < pair_type type >
constexpr http_buf::mode_base<type>::mode_base ( type p )
    extends value ( std::move(p) )
{

}



template < map_type type >
constexpr http_buf::mode_base<type>::mode_base ( type::key_type k, type::value_type v )
    extends value ( { { std::move(k), std::move(v) } } )
{

}

template < map_type type >
constexpr http_buf::mode_base<type>::mode_base ( pair<typename type::key_type, typename type::value_type> kv )
    extends value ( { std::move(kv) } )
{

}

template < map_type type >
constexpr http_buf::mode_base<type>::mode_base ( type m )
    extends value ( std::move(m) )
{

}









/// Auxiliary

void aux::try_for_each ( const auto& inputs, auto on_operation, auto on_error )
{
    let success = false;
    let except  = array<string>();

    for ( const auto& val in inputs )
    {
        try
        {
            on_operation(val);
            success = true;
            break;
        }
        catch ( const std::exception& e )
        {
            except.push("try {} throws an exception {}: {}"s.format(except.size()+1, typeid(e), e.what()));
        }
    }

    if ( not success )
    {
        let errors = '\n' +
                   ( except
                   | std::views::transform([] (const auto& error) { return "  " + error; ; })
                   | std::views::join_with('\n')
                   | std::ranges::to<string>()
                   );
        on_error(errors);
    }
}