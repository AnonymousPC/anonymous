#pragma once
#include "../container/interface.hpp"
#include "../math/interface.hpp"

namespace ap
{
    /// File
    class file_bmp;
    class file_csv;
    class file_html;
    class file_idx;
    class file_json;
    class file_jpg;
    class file_pcap;
    class file_png;
    class file_pnm;
    class file_tiff;
    class file_tga;
    class file_txt;
    class file_wav;

    class file_stream;
    class path;

    bool     is_file              ( const path& );
    path     create_file          ( const path& );
    path     try_create_file      ( const path& );
    path     remove_file          ( const path& );
    path     try_remove_file      ( const path& );
    path     copy_file            ( const path&, const path& );
    path     try_copy_file        ( const path&, const path& );
    path     move_file            ( const path&, const path& );
    path     try_move_file        ( const path&, const path& );
    path     rename_file          ( const path&, const path& );
    path     try_rename_file      ( const path&, const path& );
    intmax_t size_of_file         ( const path& );
    path     current_directory    ( );
    bool     is_directory         ( const path& );
    path     create_directory     ( const path& );
    path     try_create_directory ( const path& );
    path     remove_directory     ( const path& );
    path     try_remove_directory ( const path& );
    path     copy_directory       ( const path&, const path& );
    path     try_copy_directory   ( const path&, const path& );
    path     move_directory       ( const path&, const path& );
    path     try_move_directory   ( const path&, const path& );
    path     rename_directory     ( const path&, const path& );
    path     try_rename_directory ( const path&, const path& );
    intmax_t size_of_directory    ( const path& );

    template < class type > concept file_mode = requires { typename type::file_mode_tag; };

    /// Http
    class http_get;
    class http_post;
    class http_server;

    class http_buf;
    class http_stream;

    template < class type > concept http_client_mode = requires { typename type::http_client_mode_tag; };
    template < class type > concept http_server_mode = requires { typename type::http_server_mode_tag; };

    /// Pipe
    class pipe_command;

    class pipe_buf;
    class pipe_stream;

    template < class type > concept pipe_mode = requires { typename type::pipe_mode_tag; };

    /// Socket
    class icmp_ping;

    template < class protocol > class basic_socket_buf;
    template < class protocol > class basic_socket_stream;
    using tcp_stream  = basic_socket_stream<boost::asio::ip::tcp>;
    using udp_stream  = basic_socket_stream<boost::asio::ip::udp>;
    using icmp_stream = basic_socket_stream<boost::asio::ip::icmp>;

    /// Utility
    class color;
    class time_point;
    class ipv4;
    class ipv6;
    class url;
    class duration;
    using timeout = duration;

    constexpr color      red         ( );
    constexpr color      orange      ( );
    constexpr color      yellow      ( );
    constexpr color      green       ( );
    constexpr color      blue        ( );
    constexpr color      purple      ( );
    constexpr color      white       ( );
    constexpr color      grey        ( );
    constexpr color      black       ( );

    constexpr time_point now         ( );
    constexpr time_point today       ( );
    constexpr time_point date        ( int_type auto, int_type auto, int_type auto );

    constexpr duration   hour        ( number_type auto );
    constexpr duration   minute      ( number_type auto );
    constexpr duration   second      ( number_type auto );
    constexpr duration   millisecond ( number_type auto );
    constexpr duration   microsecond ( number_type auto );
    constexpr duration   nanosecond  ( number_type auto );

    constexpr void       sleep       ( duration );
    constexpr void       sleep_for   ( duration );
    constexpr void       sleep_until ( time_point );
    constexpr int        time_zone   ( );

    /// Global
    extern boost::asio::ssl::context  global_ssl_client_context;
    extern boost::asio::ssl::context  global_ssl_server_context;
    extern string                     global_http_user_agent;

    /// Include
    #include "utility/utility.hpp" // First.
    #include "file/file.hpp"
    #include "http/http.hpp"
    #include "pipe/pipe.hpp"
    #include "tcp_udp_icmp/tcp_udp_icmp.hpp"
    #include "serial_port/serial_port.hpp"
    #include "usb/usb.hpp"
    #include "websocket/websocket.hpp"

    /// Literal
    namespace literals
    {
        constexpr duration operator ""h   ( unsigned long long val ) { return hour        ( static_cast<long long>(val) ); }
        constexpr duration operator ""h   ( long double        val ) { return hour        ( val ); }
        constexpr duration operator ""m   ( unsigned long long val ) { return minute      ( static_cast<long long>(val) ); }
        constexpr duration operator ""m   ( long double        val ) { return minute      ( val ); }
        constexpr duration operator ""s   ( unsigned long long val ) { return second      ( static_cast<long long>(val) ); }
        constexpr duration operator ""s   ( long double        val ) { return second      ( val ); }
        constexpr duration operator ""ms  ( unsigned long long val ) { return millisecond ( static_cast<long long>(val) ); }
        constexpr duration operator ""ms  ( long double        val ) { return millisecond ( val ); }
        constexpr duration operator ""us  ( unsigned long long val ) { return microsecond ( static_cast<long long>(val) ); }
        constexpr duration operator ""us  ( long double        val ) { return microsecond ( val ); }
        constexpr duration operator ""ns  ( unsigned long long val ) { return nanosecond  ( static_cast<long long>(val) ); }
        constexpr duration operator ""ns  ( long double        val ) { return nanosecond  ( val ); }
    }

    /// DLL.Global
    #if dll
        boost::asio::ssl::context  global_ssl_client_context = boost::asio::ssl::context(boost::asio::ssl::context::tlsv12_client);
        boost::asio::ssl::context  global_ssl_server_context = boost::asio::ssl::context(boost::asio::ssl::context::tlsv12_server);
        string                     global_http_user_agent    = "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:132.0) Gecko/20100101 Firefox/132.0"s;
    #endif

    /// DLL.Initialize
    #if dll
        class global_io_initializer_type
        {
            private: // Constructor
                global_io_initializer_type ( )
                {
                    try
                    {
                        global_ssl_client_context.set_default_verify_paths();
                        global_ssl_server_context.set_options(boost::asio::ssl::context::default_workarounds
                                                             |boost::asio::ssl::context::no_sslv2
                                                             |boost::asio::ssl::context::single_dh_use);
                        global_ssl_server_context.use_certificate_chain_file("C:/Server/cert.pem");
                        global_ssl_server_context.use_private_key_file      ("C:/Server/key.pem", boost::asio::ssl::context::file_format::pem);
                        global_ssl_server_context.use_tmp_dh_file           ("C:/Server/dh.pem");
                    }
                    catch ( const boost::system::system_error& e )
                    {
                        throw network_error("ssl server context failed to initialize [[caused by {}: {}]]",
                                            typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
                    }
                }

            private: // Instance.
                static global_io_initializer_t global_io_initializer;
        };
        global_io_initializer_t global_io_initializer_t::global_io_initializer;
    #endif
}
