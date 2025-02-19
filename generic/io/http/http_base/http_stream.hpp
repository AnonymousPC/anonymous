#pragma once

class http_stream
    extends public std::iostream
{
    public: // Core
        http_stream  ( );
        http_stream  ( url, http_client_mode auto... );
        http_stream  ( http_stream&& );
       ~http_stream  ( );
        http_stream& operator = ( http_stream&& );

    public: // Interface
        http_stream& connect ( url, http_client_mode auto... );
        http_stream& listen  ( url, http_server_mode auto... );
        http_stream& close   ( );
        bool         is_open ( ) const;

    public: // Interface (cache)
        url                local_endpoint       ( ) const;
        url                remote_endpoint      ( ) const;
        string             request_method       ( ) const;
        string             request_path         ( ) const;
        float              request_version      ( ) const;
        map<string,string> request_header       ( ) const;
        int                response_status_code ( ) const;
        string             response_reason      ( ) const;
        map<string,string> response_header      ( ) const;

    public: // Override
        std::ostream& flush ( );

    public: // Modes
        using authorization = http_buf::authorization;
        using cookie        = http_buf::cookie;
        using header        = http_buf::header;
        using method        = http_buf::method;
        using param         = http_buf::param;
        using path          = http_buf::path;
        using port          = http_buf::port;
        using proxy         = http_buf::proxy;
        using timeout       = http_buf::timeout;
        using version       = http_buf::version;

    private: // Data
        std::unique_ptr<http_buf> buff_ptr = std::make_unique<http_buf>();
};




#include "http_stream.ipp"
#if dll
    #include "http_stream.cpp"
#endif