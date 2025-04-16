#pragma once

template < class protocol >
class basic_http_stream
    extends public std::iostream
{
    public: // Core
        basic_http_stream  ( );
        basic_http_stream  ( url, http_client_mode auto... );
        basic_http_stream  ( basic_http_stream&& );
       ~basic_http_stream  ( );
        basic_http_stream& operator = ( basic_http_stream&& );

    public: // Interface
        basic_http_stream& connect ( url, http_client_mode auto... );
        basic_http_stream& listen  ( url, http_server_mode auto... );
        basic_http_stream& close   ( );
        bool               is_open ( ) const;

    public: // Interface (cache)
              url                 local_endpoint       ( ) const;
              url                 remote_endpoint      ( ) const;
              string&             request_method       ( );
        const string&             request_method       ( ) const;
              string&             request_path         ( );
        const string&             request_path         ( ) const;
              map<string,string>& request_param        ( );
        const map<string,string>& request_param        ( ) const;
              float&              request_version      ( );
        const float&              request_version      ( ) const;
              map<string,string>& request_header       ( );
        const map<string,string>& request_header       ( ) const;
              float&              response_version     ( );
        const float&              response_version     ( ) const;
              int&                response_status_code ( );
        const int&                response_status_code ( ) const;
              string&             response_reason      ( );
        const string&             response_reason      ( ) const;
              map<string,string>& response_header      ( );
        const map<string,string>& response_header      ( ) const;

    public: // Modes
        using authorization = basic_http_buf<protocol>::authorization;
        using cookie        = basic_http_buf<protocol>::cookie;
        using header        = basic_http_buf<protocol>::header;
        using method        = basic_http_buf<protocol>::method;
        using param         = basic_http_buf<protocol>::param;
        using path          = basic_http_buf<protocol>::path;
        using port          = basic_http_buf<protocol>::port;
        using proxy         = basic_http_buf<protocol>::proxy;
        using timeout       = basic_http_buf<protocol>::timeout;
        using version       = basic_http_buf<protocol>::version;

    private: // Data
        std::unique_ptr<basic_http_buf<protocol>> buff_ptr = std::make_unique<basic_http_buf<protocol>>();
};




#include "http_stream.cpp"