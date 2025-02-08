#pragma once

/// Class url

const std::regex url::regex = std::regex
(
    R"(([a-z]+://))"                                                                                                                             // Essential: protocal.
    R"(([a-zA-Z0-9\-._~%]+:[a-zA-Z0-9\-._~%]+@)?)"                                                                                                      // Optional:  usermame-password.
    R"(([a-zA-Z0-9\-._~%]+|\[[a-fA-F0-9:.]+\]))"                                                                                                        // Essential: domain/ipv4/ipv6.
    R"((:\d{1,5}?)?)"                                                                                                                                   // Optional:  port.
    R"((/(?:[a-zA-Z0-9\-._~%!$&'()*+,;=:@]+(?:/[a-zA-Z0-9\-._~%!$&'()*+,;=:@]+)*)?)?)"                                                                  // Optional:  path to resource.
    R"((\?(?:[a-zA-Z0-9\-._~%!$&'()*+,;=:@]+=[a-zA-Z0-9\-._~%!$&'()*+,;=:@]+(?:&[a-zA-Z0-9\-._~%!$&'()*+,;=:@]+=[a-zA-Z0-9\-._~%!$&'()*+,;=:@]+)*)?)?)" // Optional:  parameters.
    R"((\#(?:[a-zA-Z0-9\-._~%!$&'()*+,;=:@/?]+)?)?)"                                                                                                    // Optional:  fragment.
);



// Core

url::url ( string website )
    extends string ( std::move(website) )
{

}

// Parse

string url::scheme ( ) const
{
    try
    {
        let part = self.split(url::regex)[1];
        return part.ends_with("://") ? part[1,-4] otherwise throw network_error("failed to parse scheme from url {}", self);
    }
    catch ( const regex_error& )
    {
        throw network_error("url {} does not matches url::regex (example: https://username:password@www.host.com:12345/path/to/resource?key1=value1&key2=value2#fragment3)", self);
    }
}

string url::authorization ( ) const
{
    try
    {
        let part = self.split(url::regex)[2];
        return part.ends_with('@') ? part[1,-2] otherwise part;
    }
    catch ( const regex_error& )
    {
        throw network_error("url {} does not matches url::regex (example: https://username:password@www.host.com:12345/path/to/resource?key1=value1&key2=value2#fragment3)", self);
    }
}

string url::host ( ) const
{
    try
    {
        let part = self.split(url::regex)[3];
        return part != "" ? part otherwise throw network_error("failed to parse host from url {}", self);
    }
    catch ( const regex_error& )
    {
        throw network_error("url {} does not matches url::regex (example: https://username:password@www.host.com:12345/path/to/resource?key1=value1&key2=value2#fragment3)", self);
    }
}

string url::port ( ) const
{
    try
    {
        let part = self.split(url::regex)[4];
        return part.begins_with(':') ? part[2,-1] otherwise part;
    }
    catch ( const regex_error& )
    {
        throw network_error("url {} does not matches url::regex (example: https://username:password@www.host.com:12345/path/to/resource?key1=value1&key2=value2#fragment3)", self);
    }
}

string url::path ( ) const
{
    try
    {
        let part = self.split(url::regex)[5];
        return part.begins_with('/') ? part[2,-1] otherwise part;
    }
    catch ( const regex_error& )
    {
        throw network_error("url {} does not matches url::regex (example: https://username:password@www.host.com:12345/path/to/resource?key1=value1&key2=value2#fragment3)", self);
    }
}

string url::param ( ) const
{
    try
    {
        let part = self.split(url::regex)[6];
        return part.begins_with('?') ? part[2,-1] otherwise part;
    }
    catch ( const regex_error& )
    {
        throw network_error("url {} does not matches url::regex (example: https://username:password@www.host.com:12345/path/to/resource?key1=value1&key2=value2#fragment3)", self);
    }
}

string url::fragment ( ) const
{
    try
    {
        let part = self.split(url::regex)[7];
        return part.begins_with('#') ? part[2,-1] otherwise part;
    }
    catch ( const regex_error& )
    {
        throw network_error("url {} does not matches url::regex (example: https://username:password@www.host.com:12345/path/to/resource?key1=value1&key2=value2#fragment3)", self);
    }
}
