#pragma once

const std::regex url::regex = std::regex
(
    R"(([a-z]+://))"                                                                                                                                    // Essential: protocal.
    R"(([a-zA-Z0-9\-._~%]+:[a-zA-Z0-9\-._~%]+@)?)"                                                                                                      // Optional:  usermame-password.
    R"(([a-zA-Z0-9\-._~%]+|(?:\d{1,3}\.){3}(?:\d{1,3})|(?:[a-fA-F0-9]{0,4}:){7}(?:[a-fA-F0-9]{0,4})))"                                                          // Essential: domain/ipv4/ipv6.
    R"((:\d{1,5})?)"                                                                                                                                    // Optional:  port.
    R"((/(?:[a-zA-Z0-9\-._~%!$&'()*+,;=:@]+(?:/[a-zA-Z0-9\-._~%!$&'()*+,;=:@]+)*)?)?)"                                                                  // Optional:  path to resource.
    R"((\?(?:[a-zA-Z0-9\-._~%!$&'()*+,;=:@]+=[a-zA-Z0-9\-._~%!$&'()*+,;=:@]+(?:&[a-zA-Z0-9\-._~%!$&'()*+,;=:@]+=[a-zA-Z0-9\-._~%!$&'()*+,;=:@]+)*)?)?)" // Optional:  parameters.
    R"((\#(?:[a-zA-Z0-9\-._~%!$&'()*+,;=:@/?]+)?)?)"                                                                                                    // Optional:  fragment.
);

string url::scheme ( ) const
{
    try
    {
        auto part = self.split(url::regex)[1];
        return part.ends_with("://") ? part[1,-4] : throw network_error("failed to parse scheme from url {}", self);
    }
    catch ( const regex_error& )
    {
        throw network_error("failed to parse url (with url = {}, example = {})", self, "https://username:password@www.host.com:12345/path/to/resource?key1=value1&key2=value2#fragment3");
    }
}

string url::authorization ( ) const
{
    try
    {
        auto part = self.split(url::regex)[2];
        return part.ends_with('@') ? part[1,-2] : part;
    }
    catch ( const regex_error& )
    {
        throw network_error("failed to parse url (with url = {}, example = {})", self, "https://username:password@www.host.com:12345/path/to/resource?key1=value1&key2=value2#fragment3");
    }
}

string url::host ( ) const
{
    try
    {
        auto part = self.split(url::regex)[3];
        return part != "" ? part : throw network_error("failed to parse host from url {}", self);
    }
    catch ( const regex_error& )
    {
        throw network_error("failed to parse url (with url = {}, example = {})", self, "https://username:password@www.host.com:12345/path/to/resource?key1=value1&key2=value2#fragment3");
    }
}

string url::port ( ) const
{
    try
    {
        auto part = self.split(url::regex)[4];
        return part.begins_with(':') ? part[2,-1] : part;
    }
    catch ( const regex_error& )
    {
        throw network_error("failed to parse url (with url = {}, example = {})", self, "https://username:password@www.host.com:12345/path/to/resource?key1=value1&key2=value2#fragment3");
    }
}

string url::path ( ) const
{
    try
    {
        auto part = self.split(url::regex)[5];
        return part.begins_with('/') ? part[2,-1] : part;
    }
    catch ( const regex_error& )
    {
        throw network_error("failed to parse url (with url = {}, example = {})", self, "https://username:password@www.host.com:12345/path/to/resource?key1=value1&key2=value2#fragment3");
    }
}

string url::param ( ) const
{
    try
    {
        auto part = self.split(url::regex)[6];
        return part.begins_with('?') ? part[2,-1] : part;
    }
    catch ( const regex_error& )
    {
        throw network_error("failed to parse url (with url = {}, example = {})", self, "https://username:password@www.host.com:12345/path/to/resource?key1=value1&key2=value2#fragment3");
    }
}

string url::fragment ( ) const
{
    try
    {
        auto part = self.split(url::regex)[7];
        return part.begins_with('#') ? part[2,-1] : part;
    }
    catch ( const regex_error& )
    {
        throw network_error("failed to parse url (with url = {}, example = {})", self, "https://username:password@www.host.com:12345/path/to/resource?key1=value1&key2=value2#fragment3");
    }
}
