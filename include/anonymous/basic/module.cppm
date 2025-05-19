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

import cuda;
import thrust;

// Std.feature
#ifndef __cpp_lib_inplace_vector
    #include "std/inplace_vector.hpp"
#endif

#ifndef __cpp_lib_is_layout_compatible
    #include "std/is_layout_compatible.hpp"
#endif

#ifndef __cpp_lib_mdspan
    #include "std/mdspan.hpp"
#else
    #include "std/mdspan/mdspan_layout_transpose.cpp"

    #ifndef __cpp_lib_aligned_accessor
        #include "std/mdspan/mdspan_aligned_accessor.cpp"
    #endif
#endif

#ifndef __cpp_lib_ranges
    #include "std/ranges.hpp"
#else
    #include "std/ranges/ranges_typedef.cpp"

    #ifndef __cpp_lib_ranges_as_const
        #include "std/ranges/iterator_const.cpp"
    #endif
    
    #ifndef __cpp_lib_ranges_chunk
        #include "std/ranges/ranges_chunk.cpp"
    #endif

    #ifndef __cpp_lib_ranges_join_with
        #include "std/ranges/ranges_join_with.cpp"
    #endif 

    #ifndef __cpp_lib_ranges_starts_ends_with
        #include "std/ranges/ranges_starts_ends_with.cpp"
    #endif

    #ifndef __cpp_lib_ranges_stride
        #include "std/ranges/ranges_stride.cpp"
    #endif

    #ifndef __cpp_lib_ranges_zip
        #include "std/ranges/ranges_zip.cpp"
    #endif
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

    /// Macro
    #include "macro.cpp"

    /// Concept
    #include "concept.cpp"

    /// Common.algo
    template < int min, int max, int stride = 1 > constexpr void for_constexpr     ( auto&& /*operations*/ );
    template < int min, int max, int stride = 1 > constexpr bool all_of_constexpr  ( auto&& /*preds*/ );
    template < int min, int max, int stride = 1 > constexpr bool any_of_constexpr  ( auto&& /*preds*/ );
    template < int min, int max, int stride = 1 > constexpr bool none_of_constexpr ( auto&& /*preds*/ );

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

    /// Common.range
    constexpr auto range ( integral auto );
    constexpr auto range ( integral auto, integral auto );
    constexpr auto range ( integral auto, integral auto, integral auto );

    /// Device
    class cpu;
    class cuda;
    class system;
    class tbb;

    /// Include
    #include "common/common.hpp"
    #include "device/device.hpp"
    #include "init/init.hpp"

    /// Global
                 cpu::execution_context_type& execution_context = cpu::execution_context;
    thread_local cpu::random_context_type&    random_context    = cpu::random_context;

} // namespace anonymous

export inline namespace __global__
{
    #include "utility/export/typedef.hpp"
}

export namespace std
{
    #include "utility/export/std/common_type.hpp"
    #include "utility/export/std/formatter.hpp"
    
} // namespace std



