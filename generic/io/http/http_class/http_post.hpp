#pragma once

class http_post
    extends public http_interface<http_post>,
            public vector<string>
{
    public: // Core
        using http_interface<http_post>::http_interface;
        http_post ( const char*, const printable auto&, http_client_mode auto... );
        http_post ( const url&,  const printable auto&, http_client_mode auto... );

    public: // Interface
        http_post& connect ( const url&, const printable auto&, http_client_mode auto... );

    public: // Modes
        using http_interface<http_post>::content_encoding;
        using http_interface<http_post>::max_redirect;
};

#include "http_post.ipp"