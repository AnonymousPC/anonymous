#pragma once

template < class type >
class http_interface
{
    public: // Core
        http_interface ( )                                    = default;
        http_interface ( const http_interface&  )             = delete;
        http_interface (       http_interface&& );
        http_interface& operator = ( const http_interface&  ) = delete;
        http_interface& operator = (       http_interface&& );

    protected: // Interface (override)
        type& connect ( const url& );
        type& listen  ( const url& );

    public: // Interface (non-override)
        type& close   ( );
        bool  is_open ( ) const;

    public: // Conversion
        operator url ( ) const;

    public: // Modes
        using authorization = http_stream::authorization;
        using cookie        = http_stream::cookie;
        using header        = http_stream::header;
        using method        = http_stream::method;
        using param         = http_stream::param;
        using path          = http_stream::path;
        using port          = http_stream::port;
        using proxy         = http_stream::proxy;
        using timeout       = http_stream::timeout;
        using version       = http_stream::version;

    protected: // Modes (optional)
        struct content_encoding;
        struct max_redirect;

    protected: // Encoding
        class decode;
        class encode;

    protected: // Auxiliary
        template < class result_type > static void  extract ( );
        template < class result_type > static auto& extract ( auto& arg1, auto&... args ) requires       ( same_as<result_type,decay<decltype(arg1)>> or ... or same_as<result_type,decay<decltype(args)>> );
        template < class result_type > static void  extract ( auto& arg1, auto&... args ) requires ( not ( same_as<result_type,decay<decltype(arg1)>> or ... or same_as<result_type,decay<decltype(args)>> ) );

    private: // Data
        url  http_url  = "";
        bool http_open = false;
};

#include "http_interface.ipp"