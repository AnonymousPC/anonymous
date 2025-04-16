module;
#include <__functional/bind_back.h>
#include <__type_traits/maybe_const.h>
#include <__ranges/non_propagating_cache.h>
#include <__ranges/range_adaptor.h>

export module anonymous.std;
import std;
import boost;

// Include [[std.feature]]
#ifndef __cpp_lib_inplace_vector
    #include "include/inplace_vector.hpp"
#endif

#ifndef __cpp_lib_is_layout_compatible
    #include "include/is_layout_compatible.hpp"
#endif

#ifndef __cpp_lib_aligned_accessor
    #include "include/detail/mdspan_aligned_accessor.ipp"
#endif

#ifndef __cpp_lib_mdspan
    #include "include/detail/mdspan.ipp"
#else
    #include "include/detail/mdspan_layout_transpose.ipp"
    #include "include/detail/mdspan_aligned_accessor.ipp"
#endif

#ifndef __cpp_lib_ranges_chunk
    #include "include/ranges_chunk.hpp"
#endif

#ifndef __cpp_lib_ranges_join_with
    #include "include/ranges_join_with.hpp"
#endif

#ifndef __cpp_lib_ranges_starts_ends_with
    #include "include/ranges_starts_ends_with.hpp"
#endif

#ifndef __cpp_lib_ranges_stride
    #include "include/ranges_stride.hpp"
#endif

#ifndef __cpp_lib_ranges_zip
    #include "include/ranges_zip.hpp"
#endif

#ifndef __cpp_lib_stacktrace
    #include "include/stacktrace.hpp"
#endif
