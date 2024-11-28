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
#define __cpp_lib_text_encoding 202306L
#include <algorithm>
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
    #include <execpools/tbb/tbb_thread_pool.hpp>
#pragma GCC diagnostic pop

// Include [[compiler.gcc, compiler.clang]]
#if defined(__GNUC__) or defined(__clang__)
    #include <cxxabi.h>
#endif

// Include [[system.windows]]
#ifdef _WIN32
    #include <winsock2.h>
    #include <windows.h>
    #include <tchar.h>
#endif

// Include [[hardware.cpu.intel.tbb]]
#include <tbb/tbb.h>

// Include [[hardware.gpu.nvidia.cuda]]
// #include <thrust/thrust>

// Include [[third-party.boost]]
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

// Include [[third-party.eigen]]
#define eigen_assert(x) do { if ( not Eigen::internal::copy_bool(x) ) throw std::runtime_error(EIGEN_MAKESTRING(x)); } while ( false )
#include <eigen3/Eigen/Eigen>
#include <eigen3/unsupported/Eigen/FFT>

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
#ifdef __GNUC__
    #pragma GCC diagnostic ignored "-Wliteral-suffix"  // Allowing user-defined literal without being warned that literal not begins with '_' is kept for further standarlization.
    #pragma GCC diagnostic ignored "-Wredundant-decls" // Allowing declaration of non-template functions many times.
    #pragma GCC diagnostic ignored "-Wswitch-default"  // Has bug with co_yeild.
#endif

// Logic
#define abstract 0    // Usage: virtual int func() = abstract;
#define but and       // Usage: while ( x > 0 but x < 100 ) ...
#define extends :     // Usage: class array extends pubic array_algo { };
#define in :          // Usage: for ( auto element in array ) ...
#define let auto      // Usage: let x = 1;
#define otherwise :   // Usage: x > y ? print("yes") otherwise print("no");
#define self (*this)  // Usage: self[1] = 100;







// Standard experimental
namespace std
{
    // [[std.experimental.execution]]
    namespace execution
    {
        using namespace ::stdexec;
        using namespace ::exec;
        using namespace ::execpools;
    }

    // [[std.experimental.text_encoding]]
    std::text_encoding std::text_encoding::environment() { return std::text_encoding::UTF8; };
}





namespace ap
{
    /// Subnamespace
    inline namespace constants { }
    inline namespace literals  { }

    namespace abi       { }
    namespace audio     { }
    namespace neural    { }
    namespace spirit    { }
    namespace stock     { }

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
        std::string demangle ( const std::stacktrace& );
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
    extern std::execution::tbb_thread_pool  global_cpu_context;
    extern std::execution::tbb_thread_pool& global_gpu_context;
    extern boost::asio::io_context          global_io_context;

    /// Include
    #include "abi.hpp"
    #include "concept.hpp"
    #include "exception.hpp"
    #include "range.hpp"
    #include "typedef.hpp"
    #include "utility.hpp"

    /// DLL.Global
    #if dll
        std::execution::tbb_thread_pool  global_cpu_context = std::execution::tbb_thread_pool(16);
        std::execution::tbb_thread_pool& global_gpu_context = global_cpu_context;
        boost::asio::io_context          global_io_context  = boost::asio::io_context(2);
    #endif

    /// DLL.Initialize
    #if dll
        class global_basic_initializer_t
        {
            private: // Constructor
                global_basic_initializer_type ( )
                {
                    // Standard.print
                    std::cout << std::boolalpha;

                    // Standard.signal
                    std::signal(SIGABRT, abort_signal);
                    std::signal(SIGFPE,  floating_point_exception_signal);
                    std::signal(SIGILL,  illegal_instruction_signal);
                    std::signal(SIGINT,  interrupt_signal);
                    std::signal(SIGSEGV, segmentation_violation_signal);
                    std::signal(SIGTERM, terminate_signal);

                    // Windows
                    #ifdef _WIN32
                        SetConsoleCP      (CP_UTF8);
                        SetConsoleOutputCP(CP_UTF8);
                    #endif
                }

            private: // Functions
                static void abort_signal                    ( int ) { throw ap::abort_signal();                    };
                static void floating_point_exception_signal ( int ) { throw ap::floating_point_exception_signal(); };
                static void illegal_instruction_signal      ( int ) { throw ap::illegal_instruction_signal();      };
                static void interrupt_signal                ( int ) { throw ap::interrupt_signal();                };
                static void segmentation_violation_signal   ( int ) { throw ap::segmentation_violation_signal();   };
                static void terminate_signal                ( int ) { throw ap::terminate_signal();                };

            private: // Instance
                static thread_local global_basic_initializer_t global_basic_initializer;
        };
        thread_local global_basic_initializer_t global_basic_initializer_t::global_basic_initializer;
    #endif

} // namespace ap
