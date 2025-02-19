#pragma once

/// Class http_stream

// Core

http_stream::http_stream ( url website, http_client_mode auto... args )
    extends std::iostream ( nullptr )
{
    // Initialize
    rdbuf(buff_ptr.get());

    // Set exception cases.
    exceptions(std::ios::badbit);

    // Connect.
    connect(std::move(website), std::forward<decltype(args)>(args)...);
}

// Interface

http_stream& http_stream::connect ( url website, http_client_mode auto... args )
{
    // Connect.
    let ptr = dynamic_cast<http_buf*>(rdbuf());
    if ( ptr != nullptr )
        ptr->connect(std::move(website), std::forward<decltype(args)>(args)...);
    else
        throw network_error("http_stream.rdbuf() does not point to a http_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(http_buf));

    return self;
}

http_stream& http_stream::listen ( url portal, http_server_mode auto... args )
{
    // Listen.
    let ptr = dynamic_cast<http_buf*>(rdbuf());
    if ( ptr != nullptr )
        ptr->listen(std::move(portal), std::forward<decltype(args)>(args)...);
    else
        throw network_error("http_stream.rdbuf() does not point to a http_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(http_buf));

    return self;
}