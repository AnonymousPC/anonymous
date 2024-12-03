#pragma once

/// Class icmp_ping

// Core

icmp_ping::icmp_ping ( const char* website, const printable auto& body )
{
    ping(website, body);
}

icmp_ping::icmp_ping ( const url& website, const printable auto& body )
{
    ping(website, body);
}

// Interface (override)

icmp_ping& icmp_ping::ping ( const url& website, const printable auto& body )
{
    // Ping website.
    icmp_interface::ping(website);
    let stream = icmp_stream(website);

    // Send ping request.
    let str = ""s;

    // Receive ping response.
    let response = views::binary_istream<char>(stream)
                 | std::ranges::to<string>();

    // Parse ping response.
    ttl =

    return self;
}

