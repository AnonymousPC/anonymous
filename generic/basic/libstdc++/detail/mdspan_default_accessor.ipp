#pragma once

namespace std
{

template <class _ElementType>
struct default_accessor {
  static_assert(!is_array_v<_ElementType>, "default_accessor: template argument may not be an array type");
  static_assert(!is_abstract_v<_ElementType>, "default_accessor: template argument may not be an abstract class");

  using offset_policy    = default_accessor;
  using element_type     = _ElementType;
  using reference        = _ElementType&;
  using data_handle_type = _ElementType*;

 constexpr default_accessor() noexcept = default;
  template <class _OtherElementType>
    requires(is_convertible_v<_OtherElementType (*)[], element_type (*)[]>)
 constexpr default_accessor(default_accessor<_OtherElementType>) noexcept {}

 constexpr reference access(data_handle_type __p, size_t __i) const noexcept { return __p[__i]; }
 constexpr data_handle_type offset(data_handle_type __p, size_t __i) const noexcept {
    return __p + __i;
  }
};

} // namespace std



