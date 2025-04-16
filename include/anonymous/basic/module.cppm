module;
#include <csignal>
#include <__functional/bind_back.h>
#include <__type_traits/maybe_const.h>
#include <__ranges/non_propagating_cache.h>
#include <__ranges/range_adaptor.h>

export module anonymous.basic;
import std;
import stdexec;
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

export namespace std::execution
{
    using namespace stdexec;
}

export namespace anonymous
{
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
    #include "init/init.hpp"

    /// Global
    constexpr           detail::print_t              print             = detail::print_t();
    inline              cpu::execution_context_type& execution_context = cpu::execution_context;
    inline thread_local cpu::random_context_type&    random_context    = cpu::random_context;

} // namespace anonymous
