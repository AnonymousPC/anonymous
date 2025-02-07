#pragma once


namespace std
{

struct layout_left {
  template <class _Extents>
  class mapping;
};

// Layout policy with a mapping which corresponds to C-style array layouts
struct layout_right {
  template <class _Extents>
  class mapping;
};

// Layout policy with a unique mapping where strides are arbitrary
struct layout_stride {
  template <class _Extents>
  class mapping;
};

// Layout policy added by user.
// Defined in "mdspan_layout_transpose.ipp"
// template <class _Layout>
// struct layout_transpose {
//     template <class _Extents> class mapping;
// };


} // namespace std
