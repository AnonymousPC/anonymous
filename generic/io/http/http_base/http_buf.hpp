#pragma once

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

    public: // Modes
        template < class type >
        struct mode_base;

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

    private: // Typedef (mode)
        struct client_mode_type;
        struct server_mode_type;

    private: // Typedef (data)
        enum class open_type
        {
            close  = 0,
            client = 1,
            server = 2
        };

        constexpr static const int default_buffer_size = 3;

    private: // Data
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

    private: // Auxiliary
        using resolve_type = boost::asio::ip::tcp::resolver::results_type;

        // In .hpp
        void        set_client_request       ( const url&, const auto&... );
        auto        make_client_mode         (       const url&, auto, auto... );
        auto        make_client_mode         ( auto, const url&, auto, auto... );
        void        set_server_response      ( const url&, const auto&... );
        auto        make_server_mode         (       const url&, auto, auto... );
        auto        make_server_mode         ( auto, const url&, auto, auto... );

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
        string       encode_base64            ( const string& );
};






// Subclass

template < class type >
struct http_buf::mode_base
{
    type value = type();
    constexpr mode_base ( type );
};

template < pair_type type >
struct http_buf::mode_base<type>
{
    type value = type();
    constexpr mode_base ( typename type::key_type, typename type::value_type );
    constexpr mode_base ( type );
};

template < map_type type >
struct http_buf::mode_base<type>
{
    type value = type();
    constexpr mode_base ( type::key_type, type::value_type );
    constexpr mode_base ( pair<typename type::key_type,typename type::value_type> );
    constexpr mode_base ( type );
};


struct http_buf::authorization extends public http_buf::mode_base<pair<string,string>> { using mode_base::mode_base; struct http_client_mode_tag{}; };;
struct http_buf::cookie        extends public http_buf::mode_base<map<string,string>>  { using mode_base::mode_base; struct http_client_mode_tag{}; };
struct http_buf::header        extends public http_buf::mode_base<map<string,string>>  { using mode_base::mode_base; struct http_client_mode_tag{}; };
struct http_buf::method        extends public http_buf::mode_base<string>              { using mode_base::mode_base; struct http_client_mode_tag{}; };
struct http_buf::param         extends public http_buf::mode_base<map<string,string>>  { using mode_base::mode_base; struct http_client_mode_tag{}; };
struct http_buf::path          extends public http_buf::mode_base<string>              { using mode_base::mode_base; struct http_client_mode_tag{}; };
struct http_buf::port          extends public http_buf::mode_base<int>                 { using mode_base::mode_base; struct http_client_mode_tag{}; };
struct http_buf::proxy         extends public http_buf::mode_base<url>                 { using mode_base::mode_base; struct http_client_mode_tag{}; };
struct http_buf::timeout       extends public http_buf::mode_base<duration>            { using mode_base::mode_base; struct http_client_mode_tag{}; };
struct http_buf::version       extends public http_buf::mode_base<float>               { using mode_base::mode_base; struct http_client_mode_tag{}; };




#include "http_buf.ipp"
#if dll
    #include "http_buf.cpp"
#endif