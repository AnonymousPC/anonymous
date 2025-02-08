#pragma once

/// Class http_buf

// Interface

void http_buf::close ( )
{
    // Check state.
    if ( opened == open_type::close )
        throw network_error("disconnection failed: http_buf has not been opened");

    // Disconnect.
    disconnect();

    // Reset param.
    reset_param();

    // Set state.
    opened = open_type::close;
}

bool http_buf::is_open ( ) const
{
    // Returns the tate stored in data.
    return opened != open_type::close;
}


// Interface (cache)

url http_buf::local_endpoint ( ) const
{
    if ( opened == open_type::close )
        throw network_error("call http_buf::local_endpoint() in unexpected state (with current = close, expected = client/server)");

    try
    {
        return "{}://{}"s.format(https_handle == nullptr ? "http" otherwise "https", string(http_handle->socket().local_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("bad local endpoint [[caused by {}: {}]]",
                            typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}

url http_buf::remote_endpoint ( ) const
{
    if ( opened == open_type::close )
        throw network_error("call http_buf::remote_endpoint() in unexpected state (with current = close, expected = client/server)");

    try
    {
        return "{}://{}"s.format(https_handle == nullptr ? "http" otherwise "https", string(http_handle->socket().remote_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("bad remote endpoint [[caused by {}: {}]]",
                            typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}

string http_buf::request_method ( ) const
{
    return opened != open_type::server ? throw network_error("call http_buf::request_method() in unexpected state (with current = {}, expected = server)", opened == open_type::client ? "client" otherwise "close") otherwise
           not cache_header_received   ? throw network_error("call http_buf::request_method() before request is received") otherwise
                                         string(boost::beast::http::to_string(request_parser->get().method()));
}

string http_buf::request_path ( ) const
{
    return opened != open_type::server ? throw network_error("call http_buf::request_path() in unexpected state (with current = {}, expected = server)", opened == open_type::client ? "client" otherwise "close") otherwise
           not cache_header_received   ? throw network_error("call http_buf::request_path() before request is received") otherwise
                                         string(request_parser->get().target()).begins_with('/') ? string(request_parser->get().target())[2,-1] otherwise string(request_parser->get().target()); // Get rid of beginning '/'.
}

float http_buf::request_version ( ) const
{
    return opened != open_type::server ? throw network_error("call http_buf::request_version() in unexpected state (with current = {}, expected = server)", opened == open_type::client ? "client" otherwise "close") otherwise
           not cache_header_received   ? throw network_error("call http_buf::request_version() before request is received") otherwise
                                         float(request_parser->get().version()) / 10;
}

map<string,string> http_buf::request_header ( ) const
{
    return opened != open_type::server ? throw network_error("call http_buf::request_header() in unexpected state (with current = {}, expected = server)", opened == open_type::client ? "client" otherwise "close") otherwise
           not cache_header_received   ? throw network_error("call http_buf::request_header() before request is received") otherwise
                                         request_parser->get() | std::views::transform([] (const auto& head) { return pair(string(head.name_string()), string(head.value())); })
                                                               | std::ranges::to<map<string,string>>();
}

int http_buf::response_status_code ( ) const
{
    return opened != open_type::client ? throw network_error("call http_buf::response_status_code() in unexpected state (with current = {}, expected = client)", opened == open_type::server ? "server" otherwise "close") otherwise
           not cache_header_received   ? throw network_error("call http_buf::response_status_code() before request is received") otherwise
                                         response_parser->get().result_int();
}

string http_buf::response_reason ( ) const
{
    return opened != open_type::client ? throw network_error("call http_buf::response_reason() in unexpected state (with current = {}, expected = client)", opened == open_type::server ? "server" otherwise "close") otherwise
           not cache_header_received   ? throw network_error("call http_buf::response_reason() before request is received") otherwise
                                         string(response_parser->get().reason());
}

map<string,string> http_buf::response_header ( ) const
{
    return opened != open_type::client ? throw network_error("call http_buf::response_header() in unexpected state (with current = {}, expected = client)", opened == open_type::server ? "server" otherwise "close") otherwise
           not cache_header_received   ? throw network_error("call http_buf::response_header() before request is received") otherwise
                                         response_parser->get() | std::views::transform([] (const auto& head) { return pair(string(head.name_string()), string(head.value())); })
                                                                | std::ranges::to<map<string,string>>();
}


// Interface (virtual)

int http_buf::underflow ( )
{
    return opened == open_type::client ? receive_more(*response_parser) otherwise
           opened == open_type::server ? receive_more(*request_parser ) otherwise
                                         throw network_error("receive message failed: http_buf has not been opened");
}

int http_buf::overflow ( int c )
{
    opened == open_type::client ? send_more(c, *request_serializer ) otherwise
    opened == open_type::server ? send_more(c, *response_serializer) otherwise
                                  throw network_error("send message failed: http_buf has not been opened");
    return traits_type::to_int_type(c);
}

int http_buf::sync ( )
{
    if ( opened == open_type::client )
    {
        send_end(*request_serializer);
        refresh_send();
    }

    else if ( opened == open_type::server )
    {
        send_end(*response_serializer);
        refresh_send();
    }

    else
        throw network_error("send message failed: http_buf has not been opened");

    return 0;
}






// Auxiliary

http_buf::resolve_type http_buf::resolve ( const url& website )
{
    try
    {
        return boost::asio::ip::tcp::resolver(io_context).resolve(
                   website.host().c_str(),
                   (website.port() != ""  ? website.port()             otherwise
                   not modes_port.empty() ? string(modes_port.value()) otherwise
                                            website.scheme()).c_str());
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("resolution failed (with local-endpoint = {}, remote-url = {}, layer = http/tcp) [[caused by {}: {}]]",
                            local_endpoint_noexcept(), website,
                            typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}

void http_buf::connect_without_proxy ( const url& website )
{
    // Connect.
    detail::try_for_each(resolve(website),
        [&] (const auto& ip)
        {
            try
            {
                http_handle->connect(ip);
            }
            catch ( const boost::system::system_error& e )
            {
                throw network_error("connection failed (with remote-endpoint = {}) [[caused by {}: {}]]",
                                    ip.endpoint(), typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
            }
        },
        [&] (const auto& errors)
        {
            throw network_error("connection failed (with local-endpoint = {}, remote-url = {}, layer = http/tcp): {}",
                                local_endpoint_noexcept(), website, errors);
        });

    // SSL.
    if ( website.scheme() == "https" )
    {
        // Create SSL handle.
        https_handle = std::make_unique<boost::asio::ssl::stream<boost::beast::tcp_stream&>>(*http_handle, ssl_client_context);

        // SSL server name indication.
        let sni_success = SSL_set_tlsext_host_name(https_handle->native_handle(), website.host().c_str());
        if ( not sni_success )
            throw network_error("connection failed (with local-endpoint = {}, remote-url = {}, remote-endpoint = {}, layer = https/ssl) [[caused by {}: {}]]",
                                local_endpoint_noexcept(), website, remote_endpoint_noexcept(),
                                "openssl", boost::system::system_error(boost::beast::error_code(int(ERR_get_error()), boost::asio::error::get_ssl_category())).what());

        // SSL handshake.
        try
        {
            https_handle->handshake(boost::asio::ssl::stream_base::client);
        }
        catch ( const boost::system::system_error& e )
        {
            throw network_error("connection failed (with local-endpoint = {}, remote-url = {}, remote-endpoint = {}, layer = https/ssl) [[caused by {}: {}]]",
                                local_endpoint_noexcept(), website, remote_endpoint_noexcept(),
                                typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
        }
    }
}

void http_buf::connect_through_proxy ( const url& website, const url& proxy_website )
{
    // Status error.
    if ( opened != open_type::close )
        throw network_error("connection failed: http_buf has been already opened (with mode = {}, local-endpoint = {}, remote-endpoint = {})",
                            opened == open_type::client ? "client" otherwise "server", local_endpoint_noexcept(), remote_endpoint_noexcept());

    // Connect to proxy server.
    try
    {
        connect_without_proxy(proxy_website);
    }
    catch ( const network_error& )
    {
        throw network_error("connection failed (with local-endpoint = {}, remote-url = {}, proxy-url = {}, layer = http/tcp): cannot connect to proxy server",
                            local_endpoint_noexcept(), website, proxy_website);
    }

    // Http:  request into full url.
    // Https: establish proxy tunnel.
    if ( website.scheme() == "http" )
        const_cast<boost::beast::http::request<boost::beast::http::string_body>&>(request_serializer->get())
        .target((website.scheme() + "://" +
                 website.host() +
                 (website.port() != "" ? ':' + website.port() otherwise "") +
                 string(request_serializer->get().target())
                ).c_str());

    else if ( website.scheme() == "https" )
        establish_proxy_tunnel(website, proxy_website);

    else
        throw network_error("connection failed (with local-endpoint = {}, remote-url = {}, proxy-url = {}): proxy on scheme {} is undefined",
                            local_endpoint_noexcept(), website, proxy_website, website.scheme());
}


void http_buf::disconnect ( )
{
    // Prepare error which logs the first exception.
    let error = optional<network_error>(nullopt);

    // Shutdown https handle.
    try
    {
        if ( https_handle != nullptr )
            https_handle->shutdown();
    }
    catch ( const boost::system::system_error& e )
    {
        if ( not error.empty() )
            error = network_error("disconnection failed (with local-endpoint = {}, remote-endpoint = {}, layer = https/ssl) [[caused by {}: {}]]",
                                  local_endpoint_noexcept(), remote_endpoint_noexcept(),
                                  typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }

    // Shutdown http handle.
    try
    {
        http_handle->socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    }
    catch ( const boost::system::system_error& e )
    {
        if ( not error.empty() )
            error = network_error("disconnection failed (with local-endpoint = {}, remote-endpoint = {}, layer = http/tcp) [[caused by {}: {}]]",
                                  local_endpoint_noexcept(), remote_endpoint_noexcept(),
                                  typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }

    // Shutdown socket.
    try
    {
        http_handle->socket().close();
    }
    catch ( const boost::system::system_error& e )
    {
        if ( not error.empty() )
            error = network_error("disconnection failed (with local-endpoint = {}, remote-endpoint = {}, layer = socket) [[caused by {}: {}]]",
                                  local_endpoint_noexcept(), remote_endpoint_noexcept(),
                                  typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }

    // Delete https_handle.
    https_handle = nullptr;

    // Throw exception if occured.
    if ( not error.empty() )
        throw error.value();
}

void http_buf::establish_proxy_tunnel ( const url& website, const url& proxy_website )
{
    // Establish proxy tunnel.
    detail::try_for_each(resolve(website),
        [&] (const auto& ip)
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

            // Send request and receive response to/from proxy server..
            try
            {
                https_handle == nullptr ? boost::beast::http::write(*http_handle,  tunnel_request ) otherwise
                                          boost::beast::http::write(*https_handle, tunnel_request );
            }
            catch ( const boost::system::system_error& e )
            {
                throw network_error("establishment of proxy tunnel failed (with remote-endpoint = {}, layer = http/tcp): cannot send request to proxy server [[caused by {}: {}]]",
                                    ip.endpoint(), typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
            }
            try
            {
                let buff = boost::beast::flat_buffer();
                https_handle == nullptr ? boost::beast::http::read(*http_handle,  buff, tunnel_response) otherwise
                                          boost::beast::http::read(*https_handle, buff, tunnel_response);
            }
            catch ( const boost::system::system_error& e )
            {
                throw network_error("establishment of proxy tunnel failed (with remote-enpdoint = {}, layer = http/tcp): cannot receive response from proxy server [[caused by {}: {}]]",
                                    ip.endpoint(), typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
            }
            if ( tunnel_response.get().result_int() >= 300 and tunnel_response.get().result_int() <= 599 )
                throw network_error("establishment of proxy tunnel failed (with remote-endpoint = {}, layer = http/tcp): received \"{} {}\" from proxy server",
                                    ip.endpoint(), tunnel_response.get().result_int(), tunnel_response.get().reason());

            // Create SSL handle (might have been created in connect(proxy_website)).
            if ( https_handle == nullptr )
                https_handle = std::make_unique<boost::asio::ssl::stream<boost::beast::tcp_stream&>>(*http_handle, ssl_client_context);

            // SSL server name indication.
            let sni_success = SSL_set_tlsext_host_name(https_handle->native_handle(), website.host().c_str());
            if ( not sni_success )
                throw network_error("establishment of proxy tunnel failed (with remote-endpoint = {}, layer = https/ssl): cannot set ssl server name indication to \"{}\" [[caused by {}: {}]]",
                                    ip.endpoint(), website.host(), "openssl", boost::system::system_error(boost::beast::error_code(int(ERR_get_error()), boost::asio::error::get_ssl_category())).what());

            // SSL handshake.
            try
            {
                https_handle->handshake(boost::asio::ssl::stream_base::client);
            }
            catch ( const boost::system::system_error& e )
            {
                throw network_error("establishment of proxy tunnel failed (with remote-endpoint = {}, layer = https/ssl): ssl handshake failed [[caused by {}: {}]]",
                                    ip.endpoint(), typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
            }
        },
        [&] (const auto& errors)
        {
            throw network_error("establishment of proxy tunnel failed (with local-endpoint = {}, remote-url = {}, proxy-url = {}): {}",
                                local_endpoint_noexcept(), website, proxy_website, errors);
        });
}

void http_buf::listen_to_port ( const url& portal )
{
    // Listen.
    detail::try_for_each(resolve(portal),
        [&] (const auto& ip)
        {
            try
            {
                boost::asio::ip::tcp::acceptor(io_context, ip).accept(http_handle->socket());
            }
            catch ( const boost::system::system_error& e )
            {
                throw network_error("listening failed (with local-endpoint = {}): [[caused by {}: {}]]",
                                    ip.endpoint(), typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
            }
        },
        [&] (const auto& errors)
        {
            throw network_error("listening failed (with local-url = {}, layer = socket): {}",
                                portal, errors);
        });

    // SSL
    if ( portal.scheme() == "https" )
    {
        // Create SSL handle.
        https_handle = std::make_unique<boost::asio::ssl::stream<boost::beast::tcp_stream&>>(*http_handle, ssl_server_context);

        // SSL handshake.
        try
        {
            https_handle->handshake(boost::asio::ssl::stream_base::server);
        }
        catch ( const boost::system::system_error& e )
        {
            throw network_error("listening failed (with local-url = {}, local-endpoint = {}, remote-endpoint = {}, layer = https/ssl) [[caused by {}: {}]]",
                                portal, local_endpoint_noexcept(), remote_endpoint_noexcept(),
                                typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
        }
    }
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
        throw network_error("send {} failed (with local-endpoint = {}, remote-endpoint = {}, layer = {}, chunked = true) [[caused by {}: {}]]",
                            decay<decltype(serializer)>::value_type::is_request::value ? "request" otherwise "response",
                            local_endpoint_noexcept(), remote_endpoint_noexcept(), https_handle == nullptr ? "http/tcp" otherwise "https/ssl",
                            typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
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
        throw network_error("send {} failed (with local-endpoint = {}, remote-endpoint = {}, layer = {}, chunked = {}) [[caused by {}: {}]]",
                            decay<decltype(serializer)>::value_type::is_request::value ? "request" otherwise "response",
                            local_endpoint_noexcept(), remote_endpoint_noexcept(), https_handle == nullptr ? "http/tcp" otherwise "https/ssl", serializer.get().chunked(),
                            typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
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
        throw network_error("receive {} failed (with local-endpoint = {}, remote-endpoint = {}, layer = {}) [[caused by {}: {}]]",
                            decay<decltype(parser)>::value_type::is_request::value ? "request" otherwise "response",
                            local_endpoint_noexcept(), remote_endpoint_noexcept(), https_handle == nullptr ? "tcp" otherwise "ssl",
                            typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}

void http_buf::receive_begin ( auto& parser )
{
    try
    {
        // Receive header.
        https_handle == nullptr ? boost::beast::http::read_header(*http_handle,  *receive_buff, parser) otherwise
                                  boost::beast::http::read_header(*https_handle, *receive_buff, parser);
        cache_header_received = true;

        // Set cache.
        cache_message_receivable--;
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("receive {} failed (with local-endpoint = {}, remote-endpoint = {}, layer = {}) [[caused by {}: {}]]",
                            decay<decltype(parser)>::value_type::is_request::value ? "request" otherwise "response",
                            local_endpoint_noexcept(), remote_endpoint_noexcept(), https_handle == nullptr ? "tcp" otherwise "ssl",
                            typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}







void http_buf::initialize_as ( open_type open_mode )
{
    http_handle = std::make_unique<boost::beast::tcp_stream>(io_context);

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

void http_buf::reset_param ( )
{
    // Reset params.
    http_handle              = nullptr;
    https_handle             = nullptr;
    request_serializer       = nullptr;
    request_parser           = nullptr;
    response_serializer      = nullptr;
    response_parser          = nullptr;
    send_request_buff        = nullptr;
    send_response_buff       = nullptr;
    receive_buff             = nullptr;

    // Reset states.
    modes_port               = nullopt;
    modes_proxy              = nullopt;
    cache_header_received    = false;
    cache_message_receivable = 0;

    // Reset put/get area.
    setp(nullptr, nullptr);
    setg(nullptr, nullptr, nullptr);
}






string http_buf::local_endpoint_noexcept ( ) const
{
    try
    {
        return "{}://{}"s.format(https_handle == nullptr ? "http" otherwise "https", string(http_handle->socket().local_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        return "[[bad local endpoint [[caused by {}: {}]]]]"s
               .format(typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}

string http_buf::remote_endpoint_noexcept ( ) const
{
    try
    {
        return "{}://{}"s.format(https_handle == nullptr ? "http" otherwise "https", string(http_handle->socket().remote_endpoint()));
    }
    catch ( const boost::system::system_error& e )
    {
        return "[[bad remote endpoint [[caused by {}: {}]]]]"s
               .format(typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }
}






string http_buf::encode_base64 ( const string& inputs )
{
    constexpr static const string_view chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    string outputs = "";

    int val  = 0;
    int valb = -6;
    for ( uint8_t ch in inputs )
    {
        val   = (val << 8) + ch;
        valb += 8;

        while (valb >= 0)
        {
            outputs.push(chars[((val >> valb) & 0x3F) + 1]);
            valb -= 6;
        }
    }

    if ( valb > -6 )
        outputs.push(chars[(((val << 8) >> (valb + 8)) & 0x3F) + 1]);

    while ( outputs.size() % 4 != 0 )
        outputs.push('=');

    return outputs;
}


















