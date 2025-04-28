module;
#include <csignal> // macros: SIGINT, SIGABRT, ...
#include <__functional/bind_back.h>
#include <__type_traits/maybe_const.h>
#include <__ranges/non_propagating_cache.h>
#include <__ranges/range_adaptor.h>

export module anonymous.basic;
import std;
import stdexec;
import plf;
import boost;
import Eigen;
import tbb;
import clblast;

// Std.feature
#ifndef __cpp_lib_inplace_vector
    #include "std/inplace_vector.hpp"
#endif

#ifndef __cpp_lib_is_layout_compatible
    #include "std/is_layout_compatible.hpp"
#endif

#ifndef __cpp_lib_aligned_accessor
    #include "std/detail/mdspan_aligned_accessor.cpp"
#endif

#ifndef __cpp_lib_mdspan
    #include "std/detail/mdspan.cpp"
#else
    #include "std/detail/mdspan_layout_transpose.cpp"
    #include "std/detail/mdspan_aligned_accessor.cpp"
#endif

#ifndef __cpp_lib_ranges_chunk
    #include "std/ranges_chunk.hpp"
#endif

#ifndef __cpp_lib_ranges_join_with
    #include "std/ranges_join_with.hpp"
#endif 

#ifndef __cpp_lib_ranges_starts_ends_with
    #include "std/ranges_starts_ends_with.hpp"
#endif

#ifndef __cpp_lib_ranges_stride
    #include "std/ranges_stride.hpp"
#endif

#ifndef __cpp_lib_ranges_zip
    #include "std/ranges_zip.hpp"
#endif

#ifndef __cpp_lib_stacktrace
    #include "std/stacktrace.hpp"
#endif

#ifndef __cpp_lib_text_encoding
    #include "std/text_encoding.hpp"
#endif

export namespace std::execution
{
    using namespace stdexec; // C++26 proposal.
}

export namespace std
{
    using namespace plf; // C++26 proposal.
}

export namespace anonymous
{
    /// Config
    #ifdef NDEBUG
        constexpr bool debug = false;
    #else
        constexpr bool debug = true;
    #endif

    /// Common.algo
    template < int min, int max, int stride = 1 > constexpr void for_constexpr        ( auto&& /*operations*/   );
    template < int min, int max, int stride = 1 > constexpr bool all_of_constexpr     ( auto&& /*preds*/ );
    template < int min, int max, int stride = 1 > constexpr bool any_of_constexpr     ( auto&& /*preds*/ );
    template < int min, int max, int stride = 1 > constexpr bool none_of_constexpr    ( auto&& /*preds*/ );
    template < int min, int max, int stride = 1 > constexpr auto accumulate_constexpr ( auto&& /*vals*/, auto&& /*init*/ );
    template < int min, int max, int stride = 1 > constexpr auto accumulate_constexpr ( auto&& /*vals*/, auto&& /*init*/, auto&& /*op*/ );

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
            class text_error;
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
    class opencl;
    class system;
    class tbb;

    /// Include
    #include "macro.cpp"
    #include "common/common.hpp"
    #include "device/device.hpp"
    #include "init/init.hpp"

    /// Global
    constexpr    print_t                      print             = print_t();
                 cpu::execution_context_type& execution_context = cpu::execution_context;
    thread_local cpu::random_context_type&    random_context    = cpu::random_context;

} // namespace anonymous

export namespace boost::compute
{
    #include "device/opencl/type/export/boost_compute.hpp"
    #include "device/opencl/operator/export/boost_compute.hpp"
    
} // namespace boost::compute


