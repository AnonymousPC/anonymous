#pragma once

template < class type > concept http_client_mode = requires { typename type::http_client_mode_tag; };
template < class type > concept http_server_mode = requires { typename type::http_server_mode_tag; };

class http_buf
    extends public std::streambuf
{
    public: // Interface
        void connect ( url, http_client_mode auto... );
        void listen  ( url, http_server_mode auto... );
        void close   ( );
        bool is_open ( ) const;

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
        enum class open_type { close, client, server };
        /* boost::beast::tcp_stream         is not movable. */
        /* boost::beast::http::basic_parser is not movable. */
        /* boost::beast::http::response     is movable, but has bug and actually moves nothing */
        /* Thus, pack everything in a std::unique_ptr */
        std::unique_ptr<boost::beast::tcp_stream>                                                 http_handle              = nullptr;
        std::unique_ptr<boost::asio::ssl::stream<boost::beast::tcp_stream&>>                      https_handle             = nullptr;
        std::unique_ptr<boost::beast::http::request_serializer <boost::beast::http::string_body>> request_serializer       = nullptr;
        std::unique_ptr<boost::beast::http::request_parser     <boost::beast::http::string_body>> request_parser           = nullptr;
        std::unique_ptr<boost::beast::http::response_serializer<boost::beast::http::string_body>> response_serializer      = nullptr;
        std::unique_ptr<boost::beast::http::response_parser    <boost::beast::http::string_body>> response_parser          = nullptr;
        std::unique_ptr<boost::beast::http::request <boost::beast::http::string_body>>            send_request_buff        = nullptr;
        std::unique_ptr<boost::beast::http::response<boost::beast::http::string_body>>            send_response_buff       = nullptr;
        std::unique_ptr<boost::beast::flat_buffer>                                                receive_buff             = nullptr;

        open_type                                                                                 opened                   = open_type::close;
        optional<int>                                                                             modes_port               = nullopt;
        optional<url>                                                                             modes_proxy              = nullopt;
        bool                                                                                      cache_header_received    = false;
        int                                                                                       cache_message_receivable = 0;

    private: // Detail
        struct client_mode_type;
        struct server_mode_type;
        using resolve_type = boost::asio::ip::tcp::resolver::results_type;
        constexpr static const int default_buffer_size = 3;

        // In .hpp
        void         set_client_request       (                   const url&, const auto&... );
        auto         make_client_mode         (                   const url&, auto, auto... );
        auto         make_client_mode         ( client_mode_type, const url&, auto, auto... );
        void         set_server_response      (                   const url&, const auto&... );
        auto         make_server_mode         (                   const url&, auto, auto... );
        auto         make_server_mode         ( server_mode_type, const url&, auto, auto... );

        // In .cpp
        resolve_type resolve                  ( const url& );
        void         connect_without_proxy    ( const url& );
        void         connect_through_proxy    ( const url&, const url& );
        void         disconnect               ( );
        void         establish_proxy_tunnel   ( const url&, const url& );
        void         listen_to_port           ( const url& );
        void         send_more                ( int, auto& /*serializer*/ );
        void         send_end                 (      auto& /*serializer*/ );
        int          receive_more             (      auto& /*parser*/     );
        void         receive_begin            (      auto& /*parser*/     );
        void         initialize_as            ( open_type );
        void         refresh_send             ( );
        void         refresh_receive          ( );
        void         reset_param              ( );
        string       local_endpoint_noexcept  ( ) const;
        string       remote_endpoint_noexcept ( ) const;
};



#include "http_buf.ipp"
#if dll
    #include "http_buf.cpp"
#endif