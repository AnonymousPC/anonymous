#pragma once

// Include [[std]]
#include <algorithm>
#include <cassert>
#include <charconv>
#include <chrono>
#include <concepts>
#include <csignal>
#include <execution>
#include <filesystem>
#include <format>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <new>
#include <numbers>
#include <print>
#include <ranges>
#include <regex>
#include <set>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>

// Include [[std.feature]]
#ifdef __STDCPP_FLOAT16_T__ // #
    #include <stdfloat>
#endif
#ifdef __cpp_lib_text_encoding // #
    #include <text_encoding>
#else
    #include "std/text_encoding.hpp"
#endif
#ifdef __cpp_lib_inplace_vector // #
    #include <inplace_vector>
#else
    #include "std/inplace_vector.hpp"
#endif
#ifndef __cpp_lib_is_layout_compatible // #
    #include "std/is_layout_compatible.hpp"
#endif
#ifdef __cpp_lib_mdspan // #
    #include <mdspan>
    #include "std/detail/mdspan_layout_transpose.ipp"
    #include "std/detail/mdspan_aligned_accessor.ipp"
#else
    #include "std/mdspan.hpp"
#endif
#ifndef __cpp_lib_ranges_chunk // #
    #include "std/ranges_chunk.hpp"
#endif
#ifndef __cpp_lib_ranges_join_with // #
    #include "std/ranges_join_with.hpp"
#endif
#ifndef __cpp_lib_ranges_starts_ends_with // #
    #include "std/ranges_starts_ends_with.hpp"
#endif
#ifndef __cpp_lib_ranges_stride // #
    #include "std/ranges_stride.hpp"
#endif
#ifndef __cpp_lib_ranges_zip // #
    #include "std/ranges_zip.hpp"
#endif
#ifdef __cpp_lib_stacktrace // #
    #include <stacktrace>
#else
    #include "std/stacktrace.hpp"
#endif

// Include [[std.experimental.execution]]

#include <stdexec/execution.hpp>
#include <exec/static_thread_pool.hpp>
#include <exec/single_thread_context.hpp>
#include <exec/system_context.hpp>
#include <execpools/tbb/tbb_thread_pool.hpp>
namespace std { namespace execution { using namespace ::stdexec; } }

// Include [[system.windows]]
#ifdef _WIN32
    #include <winsock2.h>
    #include <windows.h>
    #include <tchar.h>
#endif

// Include [[hardware.cpu.general]]
#include <tbb/tbb.h>

// Include [[hardware.gpu.general]]
#define CL_TARGET_OPENCL_VERSION 300
#include <clblast.h>

// Include [[hardware.gpu.nvidia]]
#ifdef __NVCC__
    #include <nvexec/stream_context.cuh>
    #include <thrust/device_ptr.h>
    #include <thrust/device_reference.h>
    #include <thrust/device_vector.h>
#endif

// Include [[hardware.gpu.amd]]
#ifdef __HIPCC__
#endif 

// Include [[third-party.boost]]
#ifndef debug
    #define BOOST_DISABLE_ASSERTS
#endif
#define BOOST_COMPUTE_HAVE_THREAD_LOCAL
#define BOOST_COMPUTE_THREAD_SAFE
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/bimap.hpp>
#include <boost/compute.hpp>
#include <boost/compute/container/stack.hpp>
#include <boost/container/container_fwd.hpp>
#include <boost/date_time.hpp>
#include <boost/dll.hpp>
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
#include <boost/mysql.hpp>
#include <boost/phoenix.hpp>
#include <boost/process/v2.hpp> 
#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/stacktrace.hpp>

// Include [[third-party.eigen]]
#ifdef debug
    #define eigen_assert(expr) do { if ( not bool(expr) ) throw std::runtime_error(EIGEN_MAKESTRING(expr)); } while ( false )
#else
    #define eigen_assert(expr)
#endif
#if defined(__GNUC__) and not defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wclass-memaccess"
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <eigen3/Eigen/Eigen>
#include <eigen3/unsupported/Eigen/FFT>
#include <eigen3/unsupported/Eigen/CXX11/Tensor>
#if defined(__GNUC__) and not defined(__clang__)
    #pragma GCC diagnostic pop
#endif




// Compiler.g++
#if defined(__GNUC__) and not defined(__clang__)
    #pragma GCC diagnostic ignored "-Wchanges-meaning" // Allowing more class member typedef which abbr the extended classses.
    #pragma GCC diagnostic ignored "-Wliteral-suffix"  // Allowing user-defined literal without being warned that literal not begins with '_' is reserved for further standarlization.
    #pragma GCC diagnostic ignored "-Wredundant-decls" // Allowing declaration of non-template functions many times.
    #pragma GCC diagnostic ignored "-Wswitch-default"  // Has bug with co_yeild.
    #pragma GCC diagnostic ignored "-Wunused-result"   // Allowing ignore result of std::ranges::to.
#endif

// Compiler.clang++
#ifdef __clang__
    #pragma clang diagnostic ignored "-Wassume"                // Allowing assumption with (potential) side-effects to be quiet.
    #pragma clang diagnostic ignored "-Wunknown-attributes"    // Allowing [[assume(bool-expr)]]
    #pragma clang diagnostic ignored "-Wunused-result"         // Allowing data | std::ranges::to<views::ostream>(stream).
    #pragma clang diagnostic ignored "-Wuser-defined-literals" // Allowing user-defined literal without being warned that literal not begins with '_' is reserved for further standarlization. 
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
    namespace asioexec { }
    namespace email    { }
    namespace mysql    { }
    namespace neural   { }
    namespace spirit   { }

    /// Common.abi
    std::string demangle ( const std::type_info& );

    /// Common.concept
    // See concept.h.

    /// Common.exception
    class exception;
        class logic_error;
            class value_error;
                class index_error;
                class key_error;
            class type_error;
        class runtime_error;
            class string_error;
                class encode_error;
                class format_error;
                class parse_error;
                class regex_error;
            class io_error;
                class file_error;
                class pipe_error;
                class serial_port_error;
                class network_error;
            class device_error;
                class cuda_error;
                class opencl_error;
                class tbb_error;
            class math_error;
                class linalg_error;

    /// Common.print
    class print_t;

    /// Common.range
    template < class type > class range;

    /// Device
    class cpu;
    class cuda;
    class hip;
    class mps;
    class opencl;
    class system;
    class tbb;

    /// Include
    #include "common/common.hpp"
    #include "device/device.hpp"
    #include "global/global.hpp"

    /// Global
    constexpr           print_t                   print             = print_t();
    inline              exec::static_thread_pool& execution_context = cpu::execution_context;
    inline thread_local std::mt19937&             random_context    = cpu::random_context;

} // namespace ap
