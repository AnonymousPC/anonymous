#define libcpp_assert(expr, message) assert(expr)

// #include "mdspan/mdspan_fwd.cpp"
// #include "mdspan/mdspan_default_accessor.cpp"
// #include "mdspan/mdspan_extents.cpp"
// #include "mdspan/mdspan_layout_left.cpp"
// #include "mdspan/mdspan_layout_right.cpp"
// #include "mdspan/mdspan_layout_stride.cpp"
#include "mdspan/mdspan_layout_transpose.cpp"
#include "mdspan/mdspan_aligned_accessor.cpp"


export namespace std
{

// Helper for lightweight test checking that one did pass a layout policy as LayoutPolicy template argument
namespace __mdspan_detail {
template <class _Layout, class _Extents>
concept __has_invalid_mapping = !requires { typename _Layout::template mapping<_Extents>; };
} // namespace __mdspan_detail

template <class _ElementType,
          class _Extents,
          class _LayoutPolicy   = layout_right,
          class _AccessorPolicy = default_accessor<_ElementType> >
class mdspan {
private:
  static_assert(__mdspan_detail::__is_extents_v<_Extents>,
                "mdspan: Extents template parameter must be a specialization of extents.");
  static_assert(!is_array_v<_ElementType>, "mdspan: ElementType template parameter may not be an array type");
  static_assert(!is_abstract_v<_ElementType>, "mdspan: ElementType template parameter may not be an abstract class");
  static_assert(is_same_v<_ElementType, typename _AccessorPolicy::element_type>,
                "mdspan: ElementType template parameter must match AccessorPolicy::element_type");
  static_assert(!__mdspan_detail::__has_invalid_mapping<_LayoutPolicy, _Extents>,
                "mdspan: LayoutPolicy template parameter is invalid. A common mistake is to pass a layout mapping "
                "instead of a layout policy");

public:
  using extents_type     = _Extents;
  using layout_type      = _LayoutPolicy;
  using accessor_type    = _AccessorPolicy;
  using mapping_type     = typename layout_type::template mapping<extents_type>;
  using element_type     = _ElementType;
  using value_type       = remove_cv_t<element_type>;
  using index_type       = typename extents_type::index_type;
  using size_type        = typename extents_type::size_type;
  using rank_type        = typename extents_type::rank_type;
  using data_handle_type = typename accessor_type::data_handle_type;
  using reference        = typename accessor_type::reference;

   static constexpr rank_type rank() noexcept { return extents_type::rank(); }
   static constexpr rank_type rank_dynamic() noexcept { return extents_type::rank_dynamic(); }
   static constexpr size_t static_extent(rank_type __r) noexcept {
    return extents_type::static_extent(__r);
  }
   constexpr index_type extent(rank_type __r) const noexcept {
    return __map_.extents().extent(__r);
  };

public:
  //--------------------------------------------------------------------------------
  // [mdspan.mdspan.cons], mdspan constructors, assignment, and destructor

   constexpr mdspan()
    requires((extents_type::rank_dynamic() > 0) && is_default_constructible_v<data_handle_type> &&
             is_default_constructible_v<mapping_type> && is_default_constructible_v<accessor_type>)
  = default;
   constexpr mdspan(const mdspan&) = default;
   constexpr mdspan(mdspan&&)      = default;

  template <class... _OtherIndexTypes>
    requires((is_convertible_v<_OtherIndexTypes, index_type> && ...) &&
             (is_nothrow_constructible_v<index_type, _OtherIndexTypes> && ...) &&
             ((sizeof...(_OtherIndexTypes) == rank()) || (sizeof...(_OtherIndexTypes) == rank_dynamic())) &&
             is_constructible_v<mapping_type, extents_type> && is_default_constructible_v<accessor_type>)
   explicit constexpr mdspan(data_handle_type __p, _OtherIndexTypes... __exts)
      : __ptr_(std::move(__p)), __map_(extents_type(static_cast<index_type>(std::move(__exts))...)), __acc_{} {}

  template <class _OtherIndexType, size_t _Size>
    requires(is_convertible_v<const _OtherIndexType&, index_type> &&
             is_nothrow_constructible_v<index_type, const _OtherIndexType&> &&
             ((_Size == rank()) || (_Size == rank_dynamic())) && is_constructible_v<mapping_type, extents_type> &&
             is_default_constructible_v<accessor_type>)
  explicit(_Size != rank_dynamic())
       constexpr mdspan(data_handle_type __p, const array<_OtherIndexType, _Size>& __exts)
      : __ptr_(std::move(__p)), __map_(extents_type(__exts)), __acc_{} {}

  template <class _OtherIndexType, size_t _Size>
    requires(is_convertible_v<const _OtherIndexType&, index_type> &&
             is_nothrow_constructible_v<index_type, const _OtherIndexType&> &&
             ((_Size == rank()) || (_Size == rank_dynamic())) && is_constructible_v<mapping_type, extents_type> &&
             is_default_constructible_v<accessor_type>)
  explicit(_Size != rank_dynamic())
       constexpr mdspan(data_handle_type __p, span<_OtherIndexType, _Size> __exts)
      : __ptr_(std::move(__p)), __map_(extents_type(__exts)), __acc_{} {}

   constexpr mdspan(data_handle_type __p, const extents_type& __exts)
    requires(is_default_constructible_v<accessor_type> && is_constructible_v<mapping_type, const extents_type&>)
      : __ptr_(std::move(__p)), __map_(__exts), __acc_{} {}

   constexpr mdspan(data_handle_type __p, const mapping_type& __m)
    requires(is_default_constructible_v<accessor_type>)
      : __ptr_(std::move(__p)), __map_(__m), __acc_{} {}

   constexpr mdspan(data_handle_type __p, const mapping_type& __m, const accessor_type& __a)
      : __ptr_(std::move(__p)), __map_(__m), __acc_(__a) {}

  template <class _OtherElementType, class _OtherExtents, class _OtherLayoutPolicy, class _OtherAccessor>
    requires(is_constructible_v<mapping_type, const typename _OtherLayoutPolicy::template mapping<_OtherExtents>&> &&
             is_constructible_v<accessor_type, const _OtherAccessor&>)
  explicit(!is_convertible_v<const typename _OtherLayoutPolicy::template mapping<_OtherExtents>&, mapping_type> ||
           !is_convertible_v<const _OtherAccessor&, accessor_type>)
       constexpr mdspan(
          const mdspan<_OtherElementType, _OtherExtents, _OtherLayoutPolicy, _OtherAccessor>& __other)
      : __ptr_(__other.__ptr_), __map_(__other.__map_), __acc_(__other.__acc_) {
    static_assert(is_constructible_v<data_handle_type, const typename _OtherAccessor::data_handle_type&>,
                  "mdspan: incompatible data_handle_type for mdspan construction");
    static_assert(
        is_constructible_v<extents_type, _OtherExtents>, "mdspan: incompatible extents for mdspan construction");

    // The following precondition is part of the standard, and is unlikely to be triggered.
    // The extents constructor checks this and the mapping must be storing the extents, since
    // its extents() function returns a const reference to extents_type.
    // The only way this can be triggered is if the mapping conversion constructor would for example
    // always construct its extents() only from the dynamic extents, instead of from the other extents.
    if constexpr (rank() > 0) {
      for (size_t __r = 0; __r < rank(); __r++) {
        // Not catching this could lead to out of bounds errors later
        // e.g. mdspan<int, dextents<char,1>, non_checking_layout> m =
        //        mdspan<int, dextents<unsigned, 1>, non_checking_layout>(ptr, 200); leads to an extent of -56 on m
        libcpp_assert(
            (static_extent(__r) == dynamic_extent) ||
                (static_cast<index_type>(__other.extent(__r)) == static_cast<index_type>(static_extent(__r))),
            "mdspan: conversion mismatch of source dynamic extents with static extents");
      }
    }
  }

   constexpr mdspan& operator=(const mdspan&) = default;
   constexpr mdspan& operator=(mdspan&&)      = default;

  //--------------------------------------------------------------------------------
  // [mdspan.mdspan.members], members

  template <class... _OtherIndexTypes>
    requires((is_convertible_v<_OtherIndexTypes, index_type> && ...) &&
             (is_nothrow_constructible_v<index_type, _OtherIndexTypes> && ...) &&
             (sizeof...(_OtherIndexTypes) == rank()))
   constexpr reference operator[](_OtherIndexTypes... __indices) const {
    // Note the standard layouts would also check this, and user provided ones may not, so we
    // check the precondition here
    libcpp_assert(__mdspan_detail::__is_multidimensional_index_in(extents(), __indices...),
                                        "mdspan: operator[] out of bounds access");
    return __acc_.access(__ptr_, __map_(static_cast<index_type>(std::move(__indices))...));
  }

  template <class _OtherIndexType>
    requires(is_convertible_v<const _OtherIndexType&, index_type> &&
             is_nothrow_constructible_v<index_type, const _OtherIndexType&>)
   constexpr reference operator[](const array< _OtherIndexType, rank()>& __indices) const {
    return __acc_.access(__ptr_, [&]<size_t... _Idxs>(index_sequence<_Idxs...>) {
      return __map_(__indices[_Idxs]...);
    }(make_index_sequence<rank()>()));
  }

  template <class _OtherIndexType>
    requires(is_convertible_v<const _OtherIndexType&, index_type> &&
             is_nothrow_constructible_v<index_type, const _OtherIndexType&>)
   constexpr reference operator[](span<_OtherIndexType, rank()> __indices) const {
    return __acc_.access(__ptr_, [&]<size_t... _Idxs>(index_sequence<_Idxs...>) {
      return __map_(__indices[_Idxs]...);
    }(make_index_sequence<rank()>()));
  }

   constexpr size_type size() const noexcept {
    // Could leave this as only checked in debug mode: semantically size() is never
    // guaranteed to be related to any accessible range
    libcpp_assert(
        false == ([&]<size_t... _Idxs>(index_sequence<_Idxs...>) {
          size_type __prod = 1;
          return (__builtin_mul_overflow(__prod, extent(_Idxs), &__prod) || ... || false);
        }(make_index_sequence<rank()>())),
        "mdspan: size() is not representable as size_type");
    return [&]<size_t... _Idxs>(index_sequence<_Idxs...>) {
      return ((static_cast<size_type>(__map_.extents().extent(_Idxs))) * ... * size_type(1));
    }(make_index_sequence<rank()>());
  }

  [[nodiscard]]  constexpr bool empty() const noexcept {
    return [&]<size_t... _Idxs>(index_sequence<_Idxs...>) {
      return (rank() > 0) && ((__map_.extents().extent(_Idxs) == index_type(0)) || ... || false);
    }(make_index_sequence<rank()>());
  }

   friend constexpr void swap(mdspan& __x, mdspan& __y) noexcept {
    swap(__x.__ptr_, __y.__ptr_);
    swap(__x.__map_, __y.__map_);
    swap(__x.__acc_, __y.__acc_);
  }

   constexpr const extents_type& extents() const noexcept { return __map_.extents(); };
   constexpr const data_handle_type& data_handle() const noexcept { return __ptr_; };
   constexpr const mapping_type& mapping() const noexcept { return __map_; };
   constexpr const accessor_type& accessor() const noexcept { return __acc_; };

  // per LWG-4021 "mdspan::is_always_meow() should be noexcept"
   static constexpr bool is_always_unique() noexcept { return mapping_type::is_always_unique(); };
   static constexpr bool is_always_exhaustive() noexcept {
    return mapping_type::is_always_exhaustive();
  };
   static constexpr bool is_always_strided() noexcept {
    return mapping_type::is_always_strided();
  };

   constexpr bool is_unique() const { return __map_.is_unique(); };
   constexpr bool is_exhaustive() const { return __map_.is_exhaustive(); };
   constexpr bool is_strided() const { return __map_.is_strided(); };
   constexpr index_type stride(rank_type __r) const { return __map_.stride(__r); };

private:
 data_handle_type __ptr_{};
 mapping_type __map_{};
 accessor_type __acc_{};

  template <class, class, class, class>
  friend class mdspan;
};

template <class _ElementType, class... _OtherIndexTypes>
  requires((is_convertible_v<_OtherIndexTypes, size_t> && ...) && (sizeof...(_OtherIndexTypes) > 0))
explicit mdspan(_ElementType*, _OtherIndexTypes...)
    -> mdspan<_ElementType, dextents<size_t, sizeof...(_OtherIndexTypes)>>;

template <class _Pointer>
  requires(is_pointer_v<remove_reference_t<_Pointer>>)
mdspan(_Pointer&&) -> mdspan<remove_pointer_t<remove_reference_t<_Pointer>>, extents<size_t>>;

template <class _CArray>
  requires(is_array_v<_CArray> && (rank_v<_CArray> == 1))
mdspan(_CArray&) -> mdspan<remove_all_extents_t<_CArray>, extents<size_t, extent_v<_CArray, 0>>>;

template <class _ElementType, class _OtherIndexType, size_t _Size>
mdspan(_ElementType*, const array<_OtherIndexType, _Size>&) -> mdspan<_ElementType, dextents<size_t, _Size>>;

template <class _ElementType, class _OtherIndexType, size_t _Size>
mdspan(_ElementType*, span<_OtherIndexType, _Size>) -> mdspan<_ElementType, dextents<size_t, _Size>>;

// This one is necessary because all the constructors take `data_handle_type`s, not
// `_ElementType*`s, and `data_handle_type` is taken from `accessor_type::data_handle_type`, which
// seems to throw off automatic deduction guides.
template <class _ElementType, class _OtherIndexType, size_t... _ExtentsPack>
mdspan(_ElementType*, const extents<_OtherIndexType, _ExtentsPack...>&)
    -> mdspan<_ElementType, extents<_OtherIndexType, _ExtentsPack...>>;

template <class _ElementType, class _MappingType>
mdspan(_ElementType*, const _MappingType&)
    -> mdspan<_ElementType, typename _MappingType::extents_type, typename _MappingType::layout_type>;

template <class _MappingType, class _AccessorType>
mdspan(const typename _AccessorType::data_handle_type, const _MappingType&, const _AccessorType&)
    -> mdspan<typename _AccessorType::element_type,
              typename _MappingType::extents_type,
              typename _MappingType::layout_type,
              _AccessorType>;

} // namespace std
