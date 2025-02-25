#pragma once

template < class protocol >
void basic_http_buf<protocol>::establish_proxy_tunnel ( const url& website, const url& proxy_website )
{
    // Establish proxy tunnel.
    let errpool = vector<detail::system_error>();
    let ip_list = resolve(website);
    for ( const auto& ip in ip_list )
    {
        // Turn ip into string.
        let ip_str = string(ip.endpoint().address().to_string()) + ':' + string(ip.endpoint().port());

        // Prepare "CONNECT" request and response.
        let tunnel_request  = boost::beast::http::request        <boost::beast::http::empty_body>();
        let tunnel_response = boost::beast::http::response_parser<boost::beast::http::empty_body>();
        let tunnel_buff     = boost::beast::flat_buffer();
        tunnel_request.method(boost::beast::http::verb::connect);
        tunnel_request.target(ip_str.c_str());
        tunnel_request.set(boost::beast::http::field::host,             ip_str.c_str());
        tunnel_request.set(boost::beast::http::field::user_agent,       string(request_serializer->get()["User-Agent"]).c_str());
        tunnel_request.set(boost::beast::http::field::connection,       "keep-alive");
        tunnel_request.set(boost::beast::http::field::proxy_connection, "keep-alive");
        tunnel_response.skip(true); // Skip the body. Most times the response to "CONNECT" request is empty-header and empty-body.

        try
        {
            // Send request and receive response to/from proxy server.
            let buff = boost::beast::flat_buffer();
            boost::beast::http::write(handle,       tunnel_request );
            boost::beast::http::read (handle, buff, tunnel_response);

            if ( tunnel_response.get().result_int() >= 300 and tunnel_response.get().result_int() <= 599 )
                throw boost::system::system_error(boost::system::error_code(), "received {} {} from proxy server"s.format(tunnel_response.get().result_int(), tunnel_response.get().reason()));
    
            // SSL server name indication.
            let sni_success = SSL_set_tlsext_host_name(handle.native_handle(), website.host().c_str());
            if ( not sni_success )
                throw boost::system::system_error(boost::beast::error_code(int(ERR_get_error()), boost::asio::error::get_ssl_category()));
    
            // SSL handshake.
            https_handle->handshake(boost::asio::ssl::stream_base::client);

            break;
        }
        catch ( const boost::system::system_error& e )
        {
            errpool.push(detail::system_error(e));
        }
    }
    if ( not errpool.empty() )
        throw network_error("establishment of proxy tunnel failed (with local_endpoint = {}, remote_url = {}, remote_endpoint = {}, proxy_url = {})", local_endpoint_noexcept(), website, ip_list | std::ranges::to<vector<boost::asio::ip::tcp::endpoint>>(), proxy_website).from(detail::all_attempts_failed(errpool));
}

void http_buf::listen_to_port ( const url& portal )
{
    // Listen.
    let errpool = vector<detail::system_error>();
    let ip_list = resolve(portal);
    for ( const auto& ip in ip_list )
        try
        {
            boost::asio::ip::tcp::acceptor(io_context, ip).accept(*http_handle);
            break;
        }
        catch ( const boost::system::system_error& e )
        {
            errpool.push(detail::system_error(e));
        }
    if ( not errpool.empty() )
        throw network_error("listening failed (with local_url = {}, local_endpoint = {}, layer = socket)", portal, ip_list | std::ranges::to<vector<boost::asio::ip::tcp::endpoint>>()).from(detail::all_attempts_failed(errpool));

    // SSL
    if ( portal.scheme() == "https" )
    {
        // Create SSL handle.
        https_handle = std::make_unique<boost::asio::ssl::stream<boost::asio::ip::tcp::socket&>>(*http_handle, ssl_context);

        // SSL handshake.
        try
        {
            https_handle->handshake(boost::asio::ssl::stream_base::server);
        }
        catch ( const boost::system::system_error& e )
        {
            throw network_error("listening failed (with local_url = {}, local_endpoint = {}, remote_endpoint = {}, layer = https/ssl)", portal, local_endpoint_noexcept(), remote_endpoint_noexcept()).from(detail::system_error(e));
        }
    }
}


void http_buf::disconnect ( )
{
    // Prepare error which logs the first exception.
    // As error may occur in this disconnect(), but 
    // no matter what happens, we shall insist clearing
    // all the resources first and finally throw
    // the error to caller function.
    let err = optional<network_error>(nullopt);

    // Shutdown https handle.
    try
    {
        if ( https_handle != nullptr )
            https_handle->shutdown();
    }
    catch ( const boost::system::system_error& e )
    {
        if ( err.empty() )
            err = network_error("disconnection failed (with local_endpoint = {}, remote_endpoint = {}, layer = https/ssl)", local_endpoint_noexcept(), remote_endpoint_noexcept()).from(detail::system_error(e));
    }

    // Shutdown http handle.
    try
    {
        http_handle->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    }
    catch ( const boost::system::system_error& e )
    {
        if ( err.empty() )
            err = network_error("disconnection failed (with local_endpoint = {}, remote_endpoint = {}, layer = http/tcp)", local_endpoint_noexcept(), remote_endpoint_noexcept()).from(detail::system_error(e));
    }

    // Shutdown socket.
    try
    {
        http_handle->close();
    }
    catch ( const boost::system::system_error& e )
    {
        if ( err.empty() )
            err = network_error("disconnection failed (with local_endpoint = {}, remote_endpoint = {}, layer = socket)", local_endpoint_noexcept(), remote_endpoint_noexcept()).from(detail::system_error(e));
    }

    // Delete https_handle.
    https_handle = nullptr;

    // Throw exception if occured.
    if ( not err.empty() )
        throw err.value();
}

void http_buf::send_more ( int c, auto& serializer )
{
    using message_type = remove_const<typename decay<decltype(serializer)>::value_type>;

    try
    {
        // Set state.
        const_cast<message_type&>(serializer.get()).chunked(true);

        // Send header (for the first time).
        if ( not serializer.is_header_done() )
        {
            update_header_to(serializer);
            https_handle == nullptr ? boost::beast::http::write_header(*http_handle,  serializer) otherwise
                                      boost::beast::http::write_header(*https_handle, serializer);
        }

        // Send chunked body.
        https_handle == nullptr ? boost::asio::write(*http_handle,  boost::beast::http::make_chunk(boost::asio::buffer(serializer.get().body()))) otherwise
                                  boost::asio::write(*https_handle, boost::beast::http::make_chunk(boost::asio::buffer(serializer.get().body()))); // body() is always full.

        // Refresh put area.
        setp(const_cast<char*>(serializer.get().body().data()),
             const_cast<char*>(serializer.get().body().data()) + serializer.get().body().size());
        *pptr() = traits_type::to_char_type(c);
        pbump(1);
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("send {} failed (with local_endpoint = {}, remote_endpoint = {}, layer = {}, chunked = true)",
                            decay<decltype(serializer)>::value_type::is_request::value ? "request" otherwise "response",
                            local_endpoint_noexcept(), remote_endpoint_noexcept(), https_handle == nullptr ? "http/tcp" otherwise "https/ssl"
                           ).from(detail::system_error(e));
    } 
}

void http_buf::send_end ( auto& serializer )
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
            https_handle == nullptr ? boost::beast::http::write(*http_handle,  serializer.get()) otherwise
                                      boost::beast::http::write(*https_handle, serializer.get());
        }

        // Send the end chunks.
        else
        {
            const_cast<message_type&>(serializer.get()).body().resize(pptr() - pbase());
            https_handle == nullptr ? boost::asio::write(*http_handle,  boost::beast::http::make_chunk(boost::asio::buffer(serializer.get().body()))) otherwise
                                      boost::asio::write(*https_handle, boost::beast::http::make_chunk(boost::asio::buffer(serializer.get().body())));
            https_handle == nullptr ? boost::asio::write(*http_handle,  boost::beast::http::make_chunk_last()) otherwise
                                      boost::asio::write(*https_handle, boost::beast::http::make_chunk_last());
        }

        // Set cache.
        cache_message_receivable++;
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("send {} failed (with local_endpoint = {}, remote_endpoint = {}, layer = {}, chunked = {})",
                            decay<decltype(serializer)>::value_type::is_request::value ? "request" otherwise "response",
                            local_endpoint_noexcept(), remote_endpoint_noexcept(), https_handle == nullptr ? "http/tcp" otherwise "https/ssl", serializer.get().chunked()
                           ).from(detail::system_error(e));
    }
}

int http_buf::receive_more ( auto& parser )
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
            int bytes = https_handle == nullptr ? boost::beast::http::read_some(*http_handle,  *receive_buff, parser) otherwise
                                                  boost::beast::http::read_some(*https_handle, *receive_buff, parser);

            // Refresh get area.
            setg(const_cast<char*>(parser.get().body().data()),
                 const_cast<char*>(parser.get().body().data()),
                 const_cast<char*>(parser.get().body().data()) + bytes);

            return traits_type::to_int_type(*gptr());
        }

        // Receive more response (if response is cached)
        else if ( cache_message_receivable > 0 )
        {
            refresh_receive();
            return receive_more(parser);
        }

        // End.
        else
            return traits_type::eof();
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("receive {} failed (with local_endpoint = {}, remote_endpoint = {}, layer = {})",
                            decay<decltype(parser)>::value_type::is_request::value ? "request" otherwise "response",
                            local_endpoint_noexcept(), remote_endpoint_noexcept(), https_handle == nullptr ? "tcp" otherwise "ssl"
                           ).from(detail::system_error(e));
    }
}

void http_buf::receive_begin ( auto& parser )
{
    try
    {
        // Receive header.
        https_handle == nullptr ? boost::beast::http::read_header(*http_handle,  *receive_buff, parser) otherwise
                                  boost::beast::http::read_header(*https_handle, *receive_buff, parser);
        update_header_from(parser);
        cache_header_received = true;

        // Set cache.
        cache_message_receivable--;
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("receive {} failed (with local_endpoint = {}, remote_endpoint = {}, layer = {})",
                            decay<decltype(parser)>::value_type::is_request::value ? "request" otherwise "response",
                            local_endpoint_noexcept(), remote_endpoint_noexcept(), https_handle == nullptr ? "tcp" otherwise "ssl"
                           ).from(detail::system_error(e));
    }
}

void http_buf::refresh_send ( )
{
    if ( opened == open_type::client )
    {
        // Will not reset header (stored in send_request_buff).
        request_serializer = std::make_unique<boost::beast::http::request_serializer<boost::beast::http::string_body>>(*send_request_buff);
        const_cast<boost::beast::http::request<boost::beast::http::string_body>&>(request_serializer->get()).body().resize(default_buffer_size);
        setp(const_cast<char*>(request_serializer->get().body().data()),
             const_cast<char*>(request_serializer->get().body().data()) + request_serializer->get().body().size());
    }

    else if ( opened == open_type::server )
    {
        // Will not reset header (stored in send_response_buff).
        response_serializer = std::make_unique<boost::beast::http::response_serializer<boost::beast::http::string_body>>(*send_response_buff);
        const_cast<boost::beast::http::response<boost::beast::http::string_body>&>(response_serializer->get()).body().resize(default_buffer_size);
        setp(const_cast<char*>(response_serializer->get().body().data()),
             const_cast<char*>(response_serializer->get().body().data()) + response_serializer->get().body().size());
    }

    else
        throw network_error("refresh_send as open_mode::close");
}

void http_buf::refresh_receive ( )
{

    if ( opened == open_type::client )
    {
        receive_buff    = std::make_unique<boost::beast::flat_buffer>();
        response_parser = std::make_unique<boost::beast::http::response_parser<boost::beast::http::string_body>>();
        response_parser->body_limit(boost::none);
        cache_header_received = false;
        setg(nullptr, nullptr, nullptr);
    }

    else if ( opened == open_type::server )
    {
        receive_buff    = std::make_unique<boost::beast::flat_buffer>();
        request_parser  = std::make_unique<boost::beast::http::request_parser<boost::beast::http::string_body>>();
        request_parser->body_limit(boost::none);
        cache_header_received = false;
        setg(nullptr, nullptr, nullptr);
    }

    else
        throw network_error("refresh_receive as open_mode::close");
}

void http_buf::initialize_as ( open_type open_mode )
{
    http_handle = std::make_unique<boost::asio::ip::tcp::socket>(io_context);

    if ( open_mode == open_type::client )
    {
        send_request_buff  = std::make_unique<boost::beast::http::request           <boost::beast::http::string_body>>();
        request_serializer = std::make_unique<boost::beast::http::request_serializer<boost::beast::http::string_body>>(*send_request_buff);
        const_cast<boost::beast::http::request<boost::beast::http::string_body>&>(request_serializer->get()).body().resize(default_buffer_size);
        setp(const_cast<char*>(request_serializer->get().body().data()),
             const_cast<char*>(request_serializer->get().body().data()) + request_serializer->get().body().size());

        receive_buff    = std::make_unique<boost::beast::flat_buffer>();
        response_parser = std::make_unique<boost::beast::http::response_parser<boost::beast::http::string_body>>();
        response_parser->body_limit(boost::none);
        cache_header_received = false;
    }

    else if ( open_mode == open_type::server )
    {
        send_response_buff  = std::make_unique<boost::beast::http::response           <boost::beast::http::string_body>>();
        response_serializer = std::make_unique<boost::beast::http::response_serializer<boost::beast::http::string_body>>(*send_response_buff);
        const_cast<boost::beast::http::response<boost::beast::http::string_body>&>(response_serializer->get()).body().resize(default_buffer_size);
        setp(const_cast<char*>(response_serializer->get().body().data()),
             const_cast<char*>(response_serializer->get().body().data()) + response_serializer->get().body().size());

        receive_buff   = std::make_unique<boost::beast::flat_buffer>();
        request_parser = std::make_unique<boost::beast::http::request_parser<boost::beast::http::string_body>>();
        request_parser->body_limit(boost::none);
        cache_header_received = false;
    }

    else
        throw network_error("initialize as open_mode::close");
}

void http_buf::update_header_from ( auto& parser )
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

void http_buf::update_header_to ( auto& serializer )
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
                                                               | std::ranges::to<string>()).c_str()); // "/path?key=value"
        if ( not optional_proxy_midway.empty() and https_handle == nullptr ) // If we are using http proxy, then request.target() should be expanded into full url that we desire to access.
            request.target("{}://{}{}{}"s.format(optional_proxy_target.value().scheme(),
                                                 optional_proxy_target.value().host(), 
                                                 optional_proxy_target.value().port() != "" ? ":{}"s.format(optional_proxy_target.value().port()) otherwise "",
                                                 string(request.target())).c_str()); // "http://final_target.com/path?key=value"
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

void http_buf::reset_param ( )
{
    // Reset params.
    http_handle                  = nullptr;
    https_handle                 = nullptr;
    request_serializer           = nullptr;
    request_parser               = nullptr;
    response_serializer          = nullptr;
    response_parser              = nullptr;
    send_request_buff            = nullptr;
    send_response_buff           = nullptr;
    receive_buff                 = nullptr;

    // Reset states.
    optional_port                = nullopt;
    optional_proxy_midway        = nullopt;
    optional_proxy_target        = nullopt;
    current_request_method       = "GET";
    current_request_path         = "";
    current_request_param        = map<string,string>();
    current_request_version      = 1.1;
    current_request_header       = map<string,string>();
    current_response_version     = 1.1;
    current_response_status_code = 200;
    current_response_reason      = "OK";
    current_response_header      = map<string,string>();
    cache_header_received        = false;
    cache_message_receivable     = 0;

    // Reset put/get area.
    setp(nullptr, nullptr);
    setg(nullptr, nullptr, nullptr);
}






string http_buf::local_endpoint_noexcept ( ) const
{
    try
    {
        return "{}://{}"s.format(https_handle == nullptr ? "http" otherwise "https", string(http_handle->local_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        return "[[bad local endpoint]]";
    }
}

string http_buf::remote_endpoint_noexcept ( ) const
{
    try
    {
        return "{}://{}"s.format(https_handle == nullptr ? "http" otherwise "https", string(http_handle->remote_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        return "[[bad remote endpoint]]";
    }
}























