#pragma once

#define libcpp_assert(expr, message) assert(expr)

#include "mdspan_fwd.ipp"
#include "mdspan_default_accessor.ipp"
#include "mdspan_extents.ipp"
#include "mdspan_layout_left.ipp"
#include "mdspan_layout_right.ipp"
#include "mdspan_layout_stride.ipp"
#include "mdspan_mdspan.ipp"