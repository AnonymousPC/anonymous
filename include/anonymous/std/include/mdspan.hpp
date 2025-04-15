#define libcpp_assert(expr, message) assert(expr)

#include "detail/mdspan_fwd.ipp"
#include "detail/mdspan_default_accessor.ipp"
#include "detail/mdspan_extents.ipp"
#include "detail/mdspan_layout_left.ipp"
#include "detail/mdspan_layout_right.ipp"
#include "detail/mdspan_layout_stride.ipp"
#include "detail/mdspan_layout_transpose.ipp"
#include "detail/mdspan_aligned_accessor.ipp"
#include "detail/mdspan.ipp"