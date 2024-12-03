#pragma once

class http_get
    extends public http_interface<http_get>,
            public vector<string>
{
    public: // Core
        using http_interface<http_get>::http_interface;
        http_get ( const char*, http_client_mode auto... );
        http_get ( const url&,  http_client_mode auto...  );

    public: // Interface (override)
        http_get& connect ( const url&, http_client_mode auto... );

    public: // Mode
        using http_interface<http_get>::max_redirect;
};

#include "http_get.ipp"