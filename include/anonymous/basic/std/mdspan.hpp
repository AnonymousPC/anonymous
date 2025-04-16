#define libcpp_assert(expr, message) assert(expr)

// #include "detail/mdspan_fwd.cpp"
// #include "detail/mdspan_default_accessor.cpp"
// #include "detail/mdspan_extents.cpp"
// #include "detail/mdspan_layout_left.cpp"
// #include "detail/mdspan_layout_right.cpp"
// #include "detail/mdspan_layout_stride.cpp"
#include "detail/mdspan_layout_transpose.cpp"
#include "detail/mdspan_aligned_accessor.cpp"
#include "detail/mdspan.cpp"