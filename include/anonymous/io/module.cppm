export module anonymous.io;
import std;
import boost;
import anonymous.basic;
import anonymous.container;

export namespace anonymous
{
    /// Concept
    template < class type > concept reader       = requires ( type r, char* c, int s ) { { r.      read (c, s); } -> integral;               };
    template < class type > concept writer       = requires ( type r, char* c, int s ) { { r.      write(c, s); } -> integral;               };
    template < class type > concept async_reader = requires ( type r, char* c, int s ) { { r.async_read (c, s); } -> std::execution::sender; };
    template < class type > concept async_writer = requires ( type r, char* c, int s ) { { r.async_write(c, s); } -> std::execution::sender; };


    /// File
    class file_stream;

    class file_bmp;
    class file_csv;
    class file_dll;
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

    /// Pipe
    class pipe_stream;

    void wait_process      ( int );
    void suspend_process   ( int );
    void resume_process    ( int );
    void interrupt_process ( int );
    int  exit_process      ( int );
    int  terminate_process ( int );

    /// Socket
    using tcp  = boost::asio::ip::tcp;
    using udp  = boost::asio::ip::udp;
    using icmp = boost::asio::ip::icmp;
    class ssl;
    class tls;
    template < class protocol > class basic_socket_stream;
    using tcp_stream  = basic_socket_stream<tcp>;
    using udp_stream  = basic_socket_stream<udp>;
    using icmp_stream = basic_socket_stream<icmp>;
    using ssl_stream  = basic_socket_stream<ssl>;
    using tls_stream  = basic_socket_stream<tls>;

    class url;

    /// Serial port
    class serial_port_stream;

    /// Http
    template < class protocol > class basic_http_stream; // protocol can be one of tcp, ssl and tls.
    using http_stream  = basic_http_stream<tcp>;
    using https_stream = basic_http_stream<ssl>; 

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
    constexpr time_point date        ( integral auto, integral auto, integral auto );

    constexpr duration   hour        ( numeric auto );
    constexpr duration   minute      ( numeric auto );
    constexpr duration   second      ( numeric auto );
    constexpr duration   millisecond ( numeric auto );
    constexpr duration   microsecond ( numeric auto );
    constexpr duration   nanosecond  ( numeric auto );

    constexpr void       sleep       ( duration );
    constexpr void       sleep_for   ( duration );
    constexpr void       sleep_until ( time_point );
    constexpr int        time_zone   ( );

    /// Global
    extern boost::asio::ssl::context ssl_context;
    extern boost::asio::ssl::context tls_context;
    
    /// Include
    #include "utility/utility.hpp" // First.
    #include "file/file.hpp"
    #include "pipe/pipe.hpp"
    #include "serial_port/serial_port.hpp"
    #include "socket/socket.hpp"
    #include "http/http.hpp"
    #include "global/global.hpp"

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
