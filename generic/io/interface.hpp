#pragma once

namespace ap
{
    /// Email
    class email_send;
    template < class type > concept email_mode = requires { typename type::email_mode_tag; };

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
    class tcp;
    class udp;
    class icmp;
    class ssl;
    template < class protocol > class basic_socket_buf;
    template < class protocol > class basic_socket_stream;
    using tcp_stream  = basic_socket_stream<tcp>;
    using udp_stream  = basic_socket_stream<udp>;
    using icmp_stream = basic_socket_stream<icmp>;
    using ssl_stream  = basic_socket_stream<ssl>;

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
    boost::asio::io_context   io_context         = boost::asio::io_context();
    boost::asio::ssl::context ssl_client_context = boost::asio::ssl::context(boost::asio::ssl::context_base::tls_client);
    boost::asio::ssl::context ssl_server_context = boost::asio::ssl::context(boost::asio::ssl::context_base::tls_server);
    
    /// Include
    #include "utility/utility.hpp" // First.
    #include "file/file.hpp"
    #include "http/http.hpp"
    #ifndef _WIN32
        #include "pipe/pipe.hpp"
    #endif
    // #include "serial_port/serial_port.hpp"
    #include "socket/socket.hpp"
    // #include "usb/usb.hpp"
    // #include "websocket/websocket.hpp"
    // #include "email/email.hpp"
    // #include "initialize.hpp"

    /// Literal
    inline namespace literals
    {
        constexpr duration operator ""h   ( unsigned long long val ) { return hour        ( static_cast<long long>(val) ); }
        constexpr duration operator ""h   ( long double        val ) { return hour        ( val ); }
        constexpr duration operator ""min ( unsigned long long val ) { return minute      ( static_cast<long long>(val) ); }
        constexpr duration operator ""min ( long double        val ) { return minute      ( val ); }
        constexpr duration operator ""s   ( unsigned long long val ) { return second      ( static_cast<long long>(val) ); }
        constexpr duration operator ""s   ( long double        val ) { return second      ( val ); }
        constexpr duration operator ""ms  ( unsigned long long val ) { return millisecond ( static_cast<long long>(val) ); }
        constexpr duration operator ""ms  ( long double        val ) { return millisecond ( val ); }
        constexpr duration operator ""us  ( unsigned long long val ) { return microsecond ( static_cast<long long>(val) ); }
        constexpr duration operator ""us  ( long double        val ) { return microsecond ( val ); }
        constexpr duration operator ""ns  ( unsigned long long val ) { return nanosecond  ( static_cast<long long>(val) ); }
        constexpr duration operator ""ns  ( long double        val ) { return nanosecond  ( val ); }
    }
}
