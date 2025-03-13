#pragma once

template < class type > concept http_client_mode = requires { typename type::http_client_mode_tag; };
template < class type > concept http_server_mode = requires { typename type::http_server_mode_tag; };

template < class protocol >
class basic_http_buf
    extends public std::streambuf
{
    private: // Precondition
        static_assert ( same_as<protocol,tcp> or same_as<protocol,ssl> or same_as<protocol,tls> );

    public: // Interface
        void connect ( url, http_client_mode auto... );
        void listen  ( url, http_server_mode auto... );
        void close   ( );
        bool is_open ( ) const;

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

    protected: // Interface (virtual)
        virtual int underflow ( )                          override;
        virtual int overflow  ( int = traits_type::eof() ) override;
        virtual int sync      ( )                          override;

    public: // Client modes
        struct authorization;
        struct cookie;
        struct header;
        struct method;
        struct param;
        struct path;
        struct port;
        struct proxy;
        struct timeout;
        struct version;

    public: // Server modes

    private: // Data
        enum class status_type { close, client, server };

        // boost::beast::tcp_stream         is not movable.
        // boost::beast::http::basic_parser is not movable.
        // boost::beast::http::response     is movable, but has bug and actually moves nothing.
        // Thus, pack everything in a std::unique_ptr.

        // Handle
        typename protocol::socket                                                                 handle                       = typename protocol::socket(io_context);

        // Buffer
        std::unique_ptr<boost::beast::http::request_serializer <boost::beast::http::string_body>> request_serializer           = nullptr;
        std::unique_ptr<boost::beast::http::request_parser     <boost::beast::http::string_body>> request_parser               = nullptr;
        std::unique_ptr<boost::beast::http::response_serializer<boost::beast::http::string_body>> response_serializer          = nullptr;
        std::unique_ptr<boost::beast::http::response_parser    <boost::beast::http::string_body>> response_parser              = nullptr;
        std::unique_ptr<boost::beast::http::request            <boost::beast::http::string_body>> send_request_buff            = nullptr;
        std::unique_ptr<boost::beast::http::response           <boost::beast::http::string_body>> send_response_buff           = nullptr;
        std::unique_ptr<boost::beast::flat_buffer>                                                receive_buff                 = nullptr;

        // Header
        string                                                                                    current_request_method       = "";
        string                                                                                    current_request_path         = "";
        map<string,string>                                                                        current_request_param        = {};
        float                                                                                     current_request_version      = 0;
        map<string,string>                                                                        current_request_header       = {};
        float                                                                                     current_response_version     = 0;
        int                                                                                       current_response_status_code = 0;
        string                                                                                    current_response_reason      = "";
        map<string,string>                                                                        current_response_header      = {};

        // Param
        status_type                                                                               status                       = status_type::close;
        optional<int>                                                                             optional_port                = nullopt;
        optional<url>                                                                             optional_proxy_midway        = nullopt;
        optional<url>                                                                             optional_proxy_target        = nullopt;
        bool                                                                                      cache_header_received        = false;
        int                                                                                       cache_message_receivable     = 0;

    private: // Detail
        void   init_buffer_as_client       ( );
        void   init_buffer_as_server       ( );
        void   init_header_as_client       ( const url&, const auto&... );
        void   init_header_as_server       ( const url&, const auto&... );
        auto   resolve_url                 ( const url& );
        void   connect_without_proxy       ( const url& );
        void   connect_through_proxy       ( const url&, const url& ) requires same_as<protocol,tcp>;
        void   connect_through_proxy       ( const url&, const url& ) requires same_as<protocol,ssl> or same_as<protocol,tls>;
        void   listen_to_port              ( const url& );
        void   disconnect                  ( );
        void   send_more                   ( int, auto& /*serializer*/ );
        void   send_end                    (      auto& /*serializer*/ );
        int    receive_more                (      auto& /*parser*/     );
        void   receive_begin               (      auto& /*parser*/     );
        void   update_header_to            (      auto& /*serializer*/ );
        void   update_header_from          (      auto& /*parser*/     );
        void   reset_send_buffer           ( );
        void   reset_receive_buffer        ( );
        void   reset_everything            ( );
        string local_endpoint_noexcept     ( ) const;
        string remote_endpoint_noexcept    ( ) const;

    private: // Settings
        constexpr static const int default_buffer_size = 4096;
};



#include "http_buf.ipp"