#pragma once

/// Class http_post

// Core

http_post::http_post ( const char* website, const printable auto& body, http_client_mode auto... args )
{
    connect(website, body, std::forward<decltype(args)>(args)...);
}

http_post::http_post ( const url& website, const printable auto& body, http_client_mode auto... args )
{
    connect(website, body, std::forward<decltype(args)>(args)...);
}

// Interface (override)

http_post& http_post::connect ( const url& website, const printable auto& body, http_client_mode auto... args )
{
    // Check args.
    static_assert(((not same_as<decltype(args),method>) and ...), "method is fixed to post");

    // Content encoding.
    let request_encoding = [&] -> optional<string>
    {
        if constexpr ( not is_void<decltype(extract<content_encoding>(args...))> )
            return extract<content_encoding>(args...).value;
        else if constexpr ( not is_void<decltype(extract<header>(args...))> )
            return extract<header>(args...).value.keys().contains("Content-Encoding") ? optional(extract<header>(args...).value["Content-Encoding"]) otherwise nullopt;
        else
            return nullopt;
    } ();

    // Connect website.
    http_interface::connect(website);
    let stream = [&]
    {
        if constexpr ( not is_void<decltype(extract<content_encoding>(args...))> )
        {
            if constexpr ( not is_void<decltype(extract<header>(args...))> )
            {
                extract<header>(args...).value["Content-Encoding"] = extract<content_encoding>(args...).value;
                return http_stream(url(self), method("POST"), std::forward<decltype(args)>(args)...);
            }
            else
                return http_stream(url(self), method("POST"), std::forward<decltype(args)>(args)..., header("Content-Encoding", extract<content_encoding>(args...).value));
        }
        else
            return http_stream(url(self), method("POST"), std::forward<decltype(args)>(args)...);
    } ();

    // Send request.
    if ( request_encoding.empty() )
        stream << body;
    else
    {
        let encode_stream = encode(stream, request_encoding.value());
        encode_stream << body;
    }
    stream.flush();

    // Receive response.
    stream.peek();

    // Read response body.
    if ( not stream.response_header().contains("Content-Encoding") )
        static_cast<vector<string>&>(self)
            = views::binary_istream<char>(stream)
            | std::views::lazy_split('\n')
            | std::views::transform ([] (const auto& stream_line)
                {
                    let line = stream_line
                             | std::ranges::to<string>();
                    return line.ends_with('\r') ? line.pop() otherwise line;
                })
            | std::ranges::to<vector<string>>();

    else
    {
        let decode_stream = decode(stream, stream.response_header()["Content-Encoding"]);
        static_cast<vector<string>&>(self)
            = views::binary_istream<char>(decode_stream)
            | std::views::lazy_split('\n')
            | std::views::transform ([] (const auto& stream_line)
                {
                    let line = stream_line
                             | std::ranges::to<string>();
                    return line.ends_with('\r') ? line.pop() otherwise line;
                })
            | std::ranges::to<vector<string>>();
    }

    return self;
}