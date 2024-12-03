#pragma once

/// Class http_get

// Core

http_get::http_get ( const char* website, http_client_mode auto... args )
{
    connect(website, std::forward<decltype(args)>(args)...);
}

http_get::http_get ( const url& website, http_client_mode auto... args )
{
    connect(website, std::forward<decltype(args)>(args)...);
}

// Interface (override)

http_get& http_get::connect ( const url& website, http_client_mode auto... args )
{
    // Check args.
    static_assert(((not std::same_as<decltype(args),method>) and ...), "method is fixed to get");

    // Connect website.
    http_interface::connect(website);
    let stream = http_stream(url(self), method("get"), std::forward<decltype(args)>(args)...);

    // Send request.
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