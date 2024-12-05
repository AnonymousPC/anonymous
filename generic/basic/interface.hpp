#pragma once

// Config.compiler
#if defined(__GNUC__) and not defined(__clang__)
    #define compiler_gcc
#elif defined(__clang__) and not defined(_MSC_VER)
    #define compiler_clang
#elifdef _MSC_VER
    #define compiler_msvc
#elifdef __CUDACC__
    #define compiler_nvcc
#endif

// Config.system
#ifdef _WIN32
    #define system_windows
#elifdef __linux__
    #define system_linux
#elifdef __MACH__
    #define system_mac
#elifdef __ANDROID__
    #define system_android
#elifdef __APPLE__
    #define system_ios
#endif
    
// Config.architecture
#ifdef __x86_64__
    #define architecture_x86_64
#elifdef __i386__
    #define architecture_x86_32
#elifdef __aarch64__
    #define architecture_arm_64
#elifdef __arm__
    #define architecture_arm_32
#elifdef __powerpc64__
    #define architecture_power_pc_64
#elifdef __powerpc__
    #define architecture_power_pc_32
#elifdef __riscv64
    #define architecture_riscv_64
#elifdef __riscv
    #define architecture_riscv_32
#endif


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
#include <algorithm>
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
#include <string>
#include <thread>
#include <utility>

#ifdef compiler_gcc
    #define __cpp_lib_text_encoding 202412L
    #include <stacktrace>
    #include <stdfloat>
    #include <text_encoding>
    #include  "libstdc++/text_encoding.ipp"
#elifdef compiler_clang
    #include "libc++/ranges_chunk.ipp"
    #include "libc++/ranges_join_with.ipp"
    #include "libc++/ranges_stride.ipp"
    #include "libc++/text_encoding.ipp"
#endif

// Include [[std.experimental.execution]]
#ifdef compiler_gcc
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wshadow"
    #pragma GCC diagnostic ignored "-Wswitch-default"
    #pragma GCC diagnostic ignored "-Wundef"
    #pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
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
#ifdef compiler_gcc
    #pragma GCC diagnostic pop
#endif

// Include [[compiler.gcc, compiler.clang]]
#if defined(compiler_gcc) or defined(compiler_clang)
    #include <cxxabi.h>
#endif

// Include [[system.windows]]
#ifdef system_windows
    #include <winsock2.h>
    #include <windows.h>
    #include <tchar.h>
#endif

// Include [[hardware.cpu.intel.tbb]]
#ifdef architecture_x86_64
    #include <tbb/tbb.h>
#endif

// Include [[hardward.cpu.apple]]
#ifdef system_mac
#endif

// Include [[hardware.gpu.nvidia]]
#ifdef compiler_nvcc
   #include <thrust/thrust>
#endif

// Include [[third-party.boost]]
#if (defined(compiler_gcc) or defined(compiler_clang)) and not defined(_GNU_SOURCE)
    #define _GNU_SOURCE
#endif
#ifdef compiler_clang
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif
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
#ifdef compiler_clang
    #pragma clang diagnostic pop
#endif

// Include [[third-party.eigen]]
#ifdef compiler_gcc
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wclass-memaccess"
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elifdef compiler_clang
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
    #pragma clang diagnostic ignored "-Wunused-but-set-variable"
#endif
#define eigen_assert(x) do { if ( not Eigen::internal::copy_bool(x) ) throw std::runtime_error(EIGEN_MAKESTRING(x)); } while ( false )
#include <eigen3/Eigen/Eigen>
#include <eigen3/unsupported/Eigen/FFT>
#ifdef compiler_gcc
    #pragma GCC diagnostic pop
#elifdef compiler_clang
    #pragma clang diagnostic pop
#endif

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
#ifdef compiler_gcc
    #pragma GCC diagnostic ignored "-Wchanges-meaning" // Allowing more class member typedef which abbr the extended classses.
    #pragma GCC diagnostic ignored "-Wliteral-suffix"  // Allowing user-defined literal without being warned that literal not begins with '_' is kept for further standarlization.
    #pragma GCC diagnostic ignored "-Wredundant-decls" // Allowing declaration of non-template functions many times.
    #pragma GCC diagnostic ignored "-Wswitch-default"  // Has bug with co_yeild.
    #pragma GCC diagnostic ignored "-Wunused-result"   // Allowing ignore result of std::ranges::to.
#elifdef compiler_clang
    #pragma clang diagnostic ignored "-Wunused-variable" // Allowing use variable '_' as unused
#endif

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
    extern std::execution::static_thread_pool  cpu_context;
    extern std::execution::static_thread_pool& gpu_context;

    /// Include
    #include "abi.hpp"
    #include "concept.hpp"
    #include "exception.hpp"
    #include "range.hpp"
    #include "typedef.hpp"
    #include "utility.hpp"
    #include "global.hpp"

} // namespace ap
