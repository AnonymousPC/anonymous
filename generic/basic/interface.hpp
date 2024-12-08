#pragma once

// Macro.begin
#ifdef debug
    #if debug
        #define tmp_debug_symbol
    #endif
    #undef debug
#endif

#ifdef dll
    #if dll
        #define tmp_dll_symbol
    #endif
    #undef dll
#endif

// Include [[std]]
#define __cpp_lib_text_encoding 202412L
#include <algorithm>
#include <cassert>
#include <charconv>
#include <chrono>
#include <concepts>
#include <csignal>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <new>
#include <numbers>
#include <print>
#include <ranges>
#include <regex>
#include <stacktrace>
#include <stdfloat>
#include <string>
#include <text_encoding>
#include <thread>
#include <utility>

// Include [[std.experimental.execution]]
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wswitch-default"
#pragma GCC diagnostic ignored "-Wundef"
#pragma GCC diagnostic ignored "-Wunused-parameter"
    #include <stdexec/execution.hpp>
    #include <exec/static_thread_pool.hpp>
    #include <exec/timed_scheduler.hpp>
    #include <exec/when_any.hpp>
    namespace std
    {
        namespace execution
        {
            using namespace ::stdexec;
            using namespace ::exec;
        }
    }
#pragma GCC diagnostic pop

// Include [[std.experimental.text_encoding]]
std::text_encoding std::text_encoding::environment ( )
{
    #ifdef _WIN32
        return std::text_encoding::GBK;
    #elifdef __linux__
        return std::text_encoding::UTF8;
    #elifdef __APPLE__
        return std::text_encoding::UTF8;
    #else
        return std::text_encoding::unknown;
    #endif
};

// Include [[compiler]]
#include <cxxabi.h>

// Include [[system.windows]]
#ifdef _WIN32
    #include <winsock2.h>
    #include <windows.h>
    #include <tchar.h>
#endif

// Include [[hardware.cpu.intel.tbb]]
#ifdef _WIN32
    #include <tbb/tbb.h>
#endif

// Include [[third-party.boost]]
#define _GNU_SOURCE
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/date_time.hpp>
#include <boost/gil.hpp>
#include <boost/gil/extension/io/bmp.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/io/pnm.hpp>
#include <boost/gil/extension/io/tiff.hpp>
#include <boost/gil/extension/io/targa.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/locale.hpp>
#include <boost/phoenix.hpp>
#include <boost/process/v2.hpp> 
#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/stacktrace.hpp>

// Include [[third-party.eigen]]
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wclass-memaccess"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    #define eigen_assert(expr) do { if ( not bool(expr) ) throw std::runtime_error(EIGEN_MAKESTRING(expr)); } while ( false )
    #include <eigen3/Eigen/Eigen>
    #include <eigen3/unsupported/Eigen/FFT>
#pragma GCC diagnostic pop

// Include [[third-party.mpg123]]
#include <mpg123.h>

// Include [[third-party.flac]]
#include <FLAC++/all.h>

// Macro.end
#ifdef tmp_debug_symbol
    #undef tmp_debug_symbol
    #define debug true
#endif

#ifdef tmp_dll_symbol
    #undef tmp_dll_symbol
    #define dll true
#endif




// Compiler
#pragma GCC diagnostic ignored "-Wchanges-meaning" // Allowing more class member typedef which abbr the extended classses.
#pragma GCC diagnostic ignored "-Wliteral-suffix"  // Allowing user-defined literal without being warned that literal not begins with '_' is reserved for further standarlization.
#pragma GCC diagnostic ignored "-Wredundant-decls" // Allowing declaration of non-template functions many times.
#pragma GCC diagnostic ignored "-Wswitch-default"  // Has bug with co_yeild.
#pragma GCC diagnostic ignored "-Wunused-result"   // Allowing ignore result of std::ranges::to.

// Logic
#define abstract 0    // Usage: virtual int func() = abstract;
#define but and       // Usage: while ( x > 0 but x < 100 ) ...
#define extends :     // Usage: class array extends pubic array_algo { };
#define in :          // Usage: for ( auto element in array ) ...
#define let auto      // Usage: let x = 1;
#define otherwise :   // Usage: x > y ? print("yes") otherwise print("no");
#define self (*this)  // Usage: self[1] = 100;








namespace ap
{
    /// Subnamespace
    inline namespace constants { }
    inline namespace literals  { }

    namespace abi    { }
    namespace audio  { }
    namespace neural { }
    namespace spirit { }
    namespace stock  { }

    /// Class
    template < class type, bool continuous > class range;

    /// Concept
    template < class input_type, class value_type = void > concept range_type = []
    {
        if constexpr ( requires { typename input_type::range_tag; } )
            if constexpr ( std::is_void<value_type>::value )
                return true;
            else
                return std::convertible_to<typename input_type::value_type,value_type>;
        else
            return false;
    } ();
    // More omitted... see concept.h.

    /// Abi
    namespace abi
    {
        std::string demangle ( const char* );
        #if __cpp_lib_stacktrace
            std::string demangle ( const std::stacktrace& );
        #else
            std::string demangle ( const boost::stacktrace::stacktrace& );
        #endif
    }

    /// Exception
    class exception;
        class logic_error;
            class value_error;
            class index_error;
            class key_error;
            class nullptr_error;

        class runtime_error;
            class type_error;
            class format_error;
            class regex_error;
            class file_error;
            class network_error;
            class math_error;

        class signal;
            class abort_signal;
            class floating_point_exception_signal;
            class illegal_instruction_signal;
            class interrupt_signal;
            class segmentation_violation_signal;
            class terminate_signal;

    /// Function
    /* lambda function */ // void print ( const printable auto&... );
    /* lambda function */ // auto input ( const printable auto&... );

    /// Global
    std::execution::static_thread_pool  cpu_context = std::execution::static_thread_pool(std::thread::hardware_concurrency() / 2);
    std::execution::static_thread_pool& gpu_context = cpu_context;

    /// Include
    #include "abi.hpp"
    #include "concept.hpp"
    #include "exception.hpp"
    #include "print.hpp"
    #include "range.hpp"
    #include "typedef.hpp"
    #include "initialize.hpp"

} // namespace ap
