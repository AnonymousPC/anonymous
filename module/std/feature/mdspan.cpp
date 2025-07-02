module;
#include <cassert>

export module std.feature.mdspan;
import std.compiler;

export namespace std
{
#define libcpp_assert(expr, message) assert(expr)

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

namespace __mdspan_detail {

// ------------------------------------------------------------------
// ------------ __static_array --------------------------------------
// ------------------------------------------------------------------
// array like class which provides an array of static values with get
template <class _Tp, _Tp... _Values>
struct __static_array {
  static constexpr array<_Tp, sizeof...(_Values)> __array = {_Values...};

public:
 static constexpr size_t __size() { return sizeof...(_Values); }
 static constexpr _Tp __get(size_t __index) noexcept { return __array[__index]; }

  template <size_t _Index>
 static constexpr _Tp __get() {
    return __get(_Index);
  }
};

// ------------------------------------------------------------------
// ------------ __possibly_empty_array  -----------------------------
// ------------------------------------------------------------------

// array like class which provides get function and operator [], and
// has a specialization for the size 0 case.
// This is needed to make the __maybe_static_array be truly empty, for
// all static values.

template <class _Tp, size_t _Size>
struct __possibly_empty_array {
  _Tp __vals_[_Size];
 constexpr _Tp& operator[](size_t __index) { return __vals_[__index]; }
 constexpr const _Tp& operator[](size_t __index) const { return __vals_[__index]; }
};

template <class _Tp>
struct __possibly_empty_array<_Tp, 0> {
 constexpr _Tp& operator[](size_t) { std::unreachable(); }
 constexpr const _Tp& operator[](size_t) const { std::unreachable(); }
};

// ------------------------------------------------------------------
// ------------ static_partial_sums ---------------------------------
// ------------------------------------------------------------------

// Provides a compile time partial sum one can index into

template <size_t... _Values>
struct __static_partial_sums {
 static constexpr array<size_t, sizeof...(_Values)> __static_partial_sums_impl() {
    array<size_t, sizeof...(_Values)> __values{_Values...};
    array<size_t, sizeof...(_Values)> __partial_sums{{}};
    size_t __running_sum = 0;
    for (int __i = 0; __i != sizeof...(_Values); ++__i) {
      __partial_sums[__i] = __running_sum;
      __running_sum += __values[__i];
    }
    return __partial_sums;
  }
  static constexpr array<size_t, sizeof...(_Values)> __result{__static_partial_sums_impl()};

 static constexpr size_t __get(size_t __index) { return __result[__index]; }
};

// ------------------------------------------------------------------
// ------------ __maybe_static_array --------------------------------
// ------------------------------------------------------------------

// array like class which has a mix of static and runtime values and
// only stores the runtime values.
// The type of the static and the runtime values can be different.
// The position of a dynamic value is indicated through a tag value.
template <class _TDynamic, class _TStatic, _TStatic _DynTag, _TStatic... _Values>
struct __maybe_static_array {
  static_assert(is_convertible<_TStatic, _TDynamic>::value,
                "__maybe_static_array: _TStatic must be convertible to _TDynamic");
  static_assert(is_convertible<_TDynamic, _TStatic>::value,
                "__maybe_static_array: _TDynamic must be convertible to _TStatic");

private:
  // Static values member
  static constexpr size_t __size_         = sizeof...(_Values);
  static constexpr size_t __size_dynamic_ = ((_Values == _DynTag) + ... + 0);
  using _StaticValues                     = __static_array<_TStatic, _Values...>;
  using _DynamicValues                    = __possibly_empty_array<_TDynamic, __size_dynamic_>;

  // Dynamic values member
 _DynamicValues __dyn_vals_;

  // static mapping of indices to the position in the dynamic values array
  using _DynamicIdxMap = __static_partial_sums<static_cast<size_t>(_Values == _DynTag)...>;

  template <size_t... Indices>
 static constexpr _DynamicValues __zeros(index_sequence<Indices...>) noexcept {
    return _DynamicValues{((void)Indices, 0)...};
  }

public:
 constexpr __maybe_static_array() noexcept
      : __dyn_vals_{__zeros(make_index_sequence<__size_dynamic_>())} {}

  // constructors from dynamic values only -- this covers the case for rank() == 0
  template <class... _DynVals>
    requires(sizeof...(_DynVals) == __size_dynamic_)
 constexpr __maybe_static_array(_DynVals... __vals)
      : __dyn_vals_{static_cast<_TDynamic>(__vals)...} {}

  template <class _Tp, size_t _Size >
    requires(_Size == __size_dynamic_)
 constexpr __maybe_static_array([[maybe_unused]] const span<_Tp, _Size>& __vals) {
    if constexpr (_Size > 0) {
      for (size_t __i = 0; __i < _Size; __i++)
        __dyn_vals_[__i] = static_cast<_TDynamic>(__vals[__i]);
    }
  }

  // constructors from all values -- here rank will be greater than 0
  template <class... _DynVals>
    requires(sizeof...(_DynVals) != __size_dynamic_)
 constexpr __maybe_static_array(_DynVals... __vals) {
    static_assert((sizeof...(_DynVals) == __size_), "Invalid number of values.");
    _TDynamic __values[__size_] = {static_cast<_TDynamic>(__vals)...};
    for (size_t __i = 0; __i < __size_; __i++) {
      _TStatic __static_val = _StaticValues::__get(__i);
      if (__static_val == _DynTag) {
        __dyn_vals_[_DynamicIdxMap::__get(__i)] = __values[__i];
      } else
        // Not catching this could lead to out of bounds errors later
        // e.g. using my_mdspan_t = mdspan<int, extents<int, 10>>; my_mdspan_t = m(new int[5], 5);
        // Right-hand-side construction looks ok with allocation and size matching,
        // and since (potentially elsewhere defined) my_mdspan_t has static size m now thinks its range is 10 not 5
        libcpp_assert(
            __values[__i] == static_cast<_TDynamic>(__static_val),
            "extents construction: mismatch of provided arguments with static extents.");
    }
  }

  template <class _Tp, size_t _Size>
    requires(_Size != __size_dynamic_)
 constexpr __maybe_static_array(const span<_Tp, _Size>& __vals) {
    static_assert((_Size == __size_) || (__size_ == dynamic_extent));
    for (size_t __i = 0; __i < __size_; __i++) {
      _TStatic __static_val = _StaticValues::__get(__i);
      if (__static_val == _DynTag) {
        __dyn_vals_[_DynamicIdxMap::__get(__i)] = static_cast<_TDynamic>(__vals[__i]);
      } else
        // Not catching this could lead to out of bounds errors later
        // e.g. using my_mdspan_t = mdspan<int, extents<int, 10>>; my_mdspan_t = m(new int[N], span<int,1>(&N));
        // Right-hand-side construction looks ok with allocation and size matching,
        // and since (potentially elsewhere defined) my_mdspan_t has static size m now thinks its range is 10 not N
        libcpp_assert(
            static_cast<_TDynamic>(__vals[__i]) == static_cast<_TDynamic>(__static_val),
            "extents construction: mismatch of provided arguments with static extents.");
    }
  }

  // access functions
 static constexpr _TStatic __static_value(size_t __i) noexcept {
    libcpp_assert(__i < __size_, "extents access: index must be less than rank");
    return _StaticValues::__get(__i);
  }

 constexpr _TDynamic __value(size_t __i) const {
    libcpp_assert(__i < __size_, "extents access: index must be less than rank");
    _TStatic __static_val = _StaticValues::__get(__i);
    return __static_val == _DynTag ? __dyn_vals_[_DynamicIdxMap::__get(__i)] : static_cast<_TDynamic>(__static_val);
  }
 constexpr _TDynamic operator[](size_t __i) const {
    libcpp_assert(__i < __size_, "extents access: index must be less than rank");
    return __value(__i);
  }

  // observers
 static constexpr size_t __size() { return __size_; }
 static constexpr size_t __size_dynamic() { return __size_dynamic_; }
};

// Function to check whether a value is representable as another type
// value must be a positive integer : returns false
// if _From is not an integral, we just check positivity
template <integral _To, class _From>
  requires(integral<_From>)
 constexpr bool __is_representable_as(_From __value) {
  using _To_u   = make_unsigned_t<_To>;
  using _From_u = make_unsigned_t<_From>;
  if constexpr (is_signed_v<_From>) {
    if (__value < 0)
      return false;
  }
  if constexpr (static_cast<_To_u>(numeric_limits<_To>::max()) >= static_cast<_From_u>(numeric_limits<_From>::max())) {
    return true;
  } else {
    return static_cast<_To_u>(numeric_limits<_To>::max()) >= static_cast<_From_u>(__value);
  }
}

template <integral _To, class _From>
  requires(!integral<_From>)
 constexpr bool __is_representable_as(_From __value) {
  if constexpr (is_signed_v<_To>) {
    if (static_cast<_To>(__value) < 0)
      return false;
  }
  return true;
}

template <integral _To, class... _From>
 constexpr bool __are_representable_as(_From... __values) {
  return (__mdspan_detail::__is_representable_as<_To>(__values) && ... && true);
}

template <integral _To, class _From, size_t _Size>
 constexpr bool __are_representable_as(span<_From, _Size> __values) {
  for (size_t __i = 0; __i < _Size; __i++)
    if (!__mdspan_detail::__is_representable_as<_To>(__values[__i]))
      return false;
  return true;
}

}

// ------------------------------------------------------------------
// ------------ extents ---------------------------------------------
// ------------------------------------------------------------------

// Class to describe the extents of a multi dimensional array.
// Used by mdspan, mdarray and layout mappings.
// See ISO C++ standard [mdspan.extents]

template <class _IndexType, size_t... _Extents>
class extents {
public:
  // typedefs for integral types used
  using index_type = _IndexType;
  using size_type  = make_unsigned_t<index_type>;
  using rank_type  = size_t;

  static_assert(is_integral<index_type>::value && !is_same<index_type, bool>::value,
                "extents::index_type must be a signed or unsigned integer type");
  static_assert(((__mdspan_detail::__is_representable_as<index_type>(_Extents) || (_Extents == dynamic_extent)) && ...),
                "extents ctor: arguments must be representable as index_type and nonnegative");

private:
  static constexpr rank_type __rank_         = sizeof...(_Extents);
  static constexpr rank_type __rank_dynamic_ = ((_Extents == dynamic_extent) + ... + 0);

  // internal storage type using __maybe_static_array
  using _Values = __mdspan_detail::__maybe_static_array<_IndexType, size_t, dynamic_extent, _Extents...>;
  [[no_unique_address]] _Values __vals_;

public:
  // [mdspan.extents.obs], observers of multidimensional index space
 static constexpr rank_type rank() noexcept { return __rank_; }
 static constexpr rank_type rank_dynamic() noexcept { return __rank_dynamic_; }

 constexpr index_type extent(rank_type __r) const noexcept { return __vals_.__value(__r); }
 static constexpr size_t static_extent(rank_type __r) noexcept {
    return _Values::__static_value(__r);
  }

  // [mdspan.extents.cons], constructors
 constexpr extents() noexcept = default;

  // Construction from just dynamic or all values.
  // Precondition check is deferred to __maybe_static_array constructor
  template <class... _OtherIndexTypes>
    requires((is_convertible_v<_OtherIndexTypes, index_type> && ...) &&
             (is_nothrow_constructible_v<index_type, _OtherIndexTypes> && ...) &&
             (sizeof...(_OtherIndexTypes) == __rank_ || sizeof...(_OtherIndexTypes) == __rank_dynamic_))
 constexpr explicit extents(_OtherIndexTypes... __dynvals) noexcept
      : __vals_(static_cast<index_type>(__dynvals)...) {
    // Not catching this could lead to out of bounds errors later
    // e.g. mdspan m(ptr, dextents<char, 1>(200u)); leads to an extent of -56 on m
    libcpp_assert(__mdspan_detail::__are_representable_as<index_type>(__dynvals...),
                                        "extents ctor: arguments must be representable as index_type and nonnegative");
  }

  template <class _OtherIndexType, size_t _Size>
    requires(is_convertible_v<const _OtherIndexType&, index_type> &&
             is_nothrow_constructible_v<index_type, const _OtherIndexType&> &&
             (_Size == __rank_ || _Size == __rank_dynamic_))
  explicit(_Size != __rank_dynamic_)
     constexpr extents(const array<_OtherIndexType, _Size>& __exts) noexcept
      : __vals_(span(__exts)) {
    // Not catching this could lead to out of bounds errors later
    // e.g. mdspan m(ptr, dextents<char, 1>(array<unsigned,1>(200))); leads to an extent of -56 on m
    libcpp_assert(__mdspan_detail::__are_representable_as<index_type>(span(__exts)),
                                        "extents ctor: arguments must be representable as index_type and nonnegative");
  }

  template <class _OtherIndexType, size_t _Size>
    requires(is_convertible_v<const _OtherIndexType&, index_type> &&
             is_nothrow_constructible_v<index_type, const _OtherIndexType&> &&
             (_Size == __rank_ || _Size == __rank_dynamic_))
  explicit(_Size != __rank_dynamic_)
     constexpr extents(const span<_OtherIndexType, _Size>& __exts) noexcept
      : __vals_(__exts) {
    // Not catching this could lead to out of bounds errors later
    // e.g. array a{200u}; mdspan<int, dextents<char,1>> m(ptr, extents(span<unsigned,1>(a))); leads to an extent of -56
    // on m
    libcpp_assert(__mdspan_detail::__are_representable_as<index_type>(__exts),
                                        "extents ctor: arguments must be representable as index_type and nonnegative");
  }

private:
  // Function to construct extents storage from other extents.
  template <size_t _DynCount, size_t _Idx, class _OtherExtents, class... _DynamicValues>
    requires(_Idx < __rank_)
 constexpr _Values __construct_vals_from_extents(
      integral_constant<size_t, _DynCount>,
      integral_constant<size_t, _Idx>,
      const _OtherExtents& __exts,
      _DynamicValues... __dynamic_values) noexcept {
    if constexpr (static_extent(_Idx) == dynamic_extent)
      return __construct_vals_from_extents(
          integral_constant<size_t, _DynCount + 1>(),
          integral_constant<size_t, _Idx + 1>(),
          __exts,
          __dynamic_values...,
          __exts.extent(_Idx));
    else
      return __construct_vals_from_extents(
          integral_constant<size_t, _DynCount>(), integral_constant<size_t, _Idx + 1>(), __exts, __dynamic_values...);
  }

  template <size_t _DynCount, size_t _Idx, class _OtherExtents, class... _DynamicValues>
    requires((_Idx == __rank_) && (_DynCount == __rank_dynamic_))
 constexpr _Values __construct_vals_from_extents(
      integral_constant<size_t, _DynCount>,
      integral_constant<size_t, _Idx>,
      const _OtherExtents&,
      _DynamicValues... __dynamic_values) noexcept {
    return _Values{static_cast<index_type>(__dynamic_values)...};
  }

public:
  // Converting constructor from other extents specializations
  template <class _OtherIndexType, size_t... _OtherExtents>
    requires((sizeof...(_OtherExtents) == sizeof...(_Extents)) &&
             ((_OtherExtents == dynamic_extent || _Extents == dynamic_extent || _OtherExtents == _Extents) && ...))
  explicit((((_Extents != dynamic_extent) && (_OtherExtents == dynamic_extent)) || ...) ||
           (static_cast<make_unsigned_t<index_type>>(numeric_limits<index_type>::max()) <
            static_cast<make_unsigned_t<_OtherIndexType>>(numeric_limits<_OtherIndexType>::max())))
     constexpr extents(const extents<_OtherIndexType, _OtherExtents...>& __other) noexcept
      : __vals_(
            __construct_vals_from_extents(integral_constant<size_t, 0>(), integral_constant<size_t, 0>(), __other)) {
    if constexpr (rank() > 0) {
      for (size_t __r = 0; __r < rank(); __r++) {
        if constexpr (static_cast<make_unsigned_t<index_type>>(numeric_limits<index_type>::max()) <
                      static_cast<make_unsigned_t<_OtherIndexType>>(numeric_limits<_OtherIndexType>::max())) {
          // Not catching this could lead to out of bounds errors later
          // e.g. dextents<char,1>> e(dextents<unsigned,1>(200)) leads to an extent of -56 on e
          libcpp_assert(
              __mdspan_detail::__is_representable_as<index_type>(__other.extent(__r)),
              "extents ctor: arguments must be representable as index_type and nonnegative");
        }
        // Not catching this could lead to out of bounds errors later
        // e.g. mdspan<int, extents<int, 10>> m = mdspan<int, dextents<int, 1>>(new int[5], 5);
        // Right-hand-side construction was ok, and m now thinks its range is 10 not 5
        libcpp_assert(
            (_Values::__static_value(__r) == dynamic_extent) ||
                (static_cast<index_type>(__other.extent(__r)) == static_cast<index_type>(_Values::__static_value(__r))),
            "extents construction: mismatch of provided arguments with static extents.");
      }
    }
  }

  // Comparison operator
  template <class _OtherIndexType, size_t... _OtherExtents>
 friend constexpr bool
  operator==(const extents& __lhs, const extents<_OtherIndexType, _OtherExtents...>& __rhs) noexcept {
    if constexpr (rank() != sizeof...(_OtherExtents)) {
      return false;
    } else {
      for (rank_type __r = 0; __r < __rank_; __r++) {
        // avoid warning when comparing signed and unsigner integers and pick the wider of two types
        using _CommonType = common_type_t<index_type, _OtherIndexType>;
        if (static_cast<_CommonType>(__lhs.extent(__r)) != static_cast<_CommonType>(__rhs.extent(__r))) {
          return false;
        }
      }
    }
    return true;
  }
};

// Recursive helper classes to implement dextents alias for extents
namespace __mdspan_detail {

template <class _IndexType, size_t _Rank, class _Extents = extents<_IndexType>>
struct __make_dextents;

template <class _IndexType, size_t _Rank, size_t... _ExtentsPack>
struct __make_dextents< _IndexType, _Rank, extents<_IndexType, _ExtentsPack...>> {
  using type =
      typename __make_dextents< _IndexType, _Rank - 1, extents<_IndexType, dynamic_extent, _ExtentsPack...>>::type;
};

template <class _IndexType, size_t... _ExtentsPack>
struct __make_dextents< _IndexType, 0, extents<_IndexType, _ExtentsPack...>> {
  using type = extents<_IndexType, _ExtentsPack...>;
};

} // end namespace __mdspan_detail

// [mdspan.extents.dextents], alias template
template <class _IndexType, size_t _Rank>
using dextents = typename __mdspan_detail::__make_dextents<_IndexType, _Rank>::type;

// Deduction guide for extents
template <class... _IndexTypes>
extents(_IndexTypes...) -> extents<size_t, size_t(((void)sizeof(_IndexTypes), dynamic_extent))...>;

namespace __mdspan_detail {

// Helper type traits for identifying a class as extents.
template <class _Tp>
struct __is_extents : false_type {};

template <class _IndexType, size_t... _ExtentsPack>
struct __is_extents<extents<_IndexType, _ExtentsPack...>> : true_type {};

template <class _Tp>
inline constexpr bool __is_extents_v = __is_extents<_Tp>::value;

// Function to check whether a set of indices are a multidimensional
// index into extents. This is a word of power in the C++ standard
// requiring that the indices are larger than 0 and smaller than
// the respective extents.

template <integral _IndexType, class _From>
  requires(integral<_From>)
 constexpr bool __is_index_in_extent(_IndexType __extent, _From __value) {
  if constexpr (is_signed_v<_From>) {
    if (__value < 0)
      return false;
  }
  using _Tp = common_type_t<_IndexType, _From>;
  return static_cast<_Tp>(__value) < static_cast<_Tp>(__extent);
}

template <integral _IndexType, class _From>
  requires(!integral<_From>)
 constexpr bool __is_index_in_extent(_IndexType __extent, _From __value) {
  if constexpr (is_signed_v<_IndexType>) {
    if (static_cast<_IndexType>(__value) < 0)
      return false;
  }
  return static_cast<_IndexType>(__value) < __extent;
}

template <size_t... _Idxs, class _Extents, class... _From>
 constexpr bool
__is_multidimensional_index_in_impl(index_sequence<_Idxs...>, const _Extents& __ext, _From... __values) {
  return (__mdspan_detail::__is_index_in_extent(__ext.extent(_Idxs), __values) && ...);
}

template <class _Extents, class... _From>
 constexpr bool __is_multidimensional_index_in(const _Extents& __ext, _From... __values) {
  return __mdspan_detail::__is_multidimensional_index_in_impl(
      make_index_sequence<_Extents::rank()>(), __ext, __values...);
}

}

struct layout_left {
  template <class _Extents>
  class mapping;
};

struct layout_right {
  template <class _Extents>
  class mapping;
};

struct layout_stride {
  template <class _Extents>
  class mapping;
};


template <class _Extents>
class layout_left::mapping {
public:
  static_assert(__mdspan_detail::__is_extents<_Extents>::value,
                "layout_left::mapping template argument must be a specialization of extents.");

  using extents_type = _Extents;
  using index_type   = typename extents_type::index_type;
  using size_type    = typename extents_type::size_type;
  using rank_type    = typename extents_type::rank_type;
  using layout_type  = layout_left;

private:
 static constexpr bool __required_span_size_is_representable(const extents_type& __ext) {
    if constexpr (extents_type::rank() == 0)
      return true;

    index_type __prod = __ext.extent(0);
    for (rank_type __r = 1; __r < extents_type::rank(); __r++) {
      bool __overflowed = __builtin_mul_overflow(__prod, __ext.extent(__r), &__prod);
      if (__overflowed)
        return false;
    }
    return true;
  }

  static_assert((extents_type::rank_dynamic() > 0) || __required_span_size_is_representable(extents_type()),
                "layout_left::mapping product of static extents must be representable as index_type.");

public:
  // [mdspan.layout.left.cons], constructors
 constexpr mapping() noexcept               = default;
 constexpr mapping(const mapping&) noexcept = default;
 constexpr mapping(const extents_type& __ext) noexcept : __extents_(__ext) {
    // not catching this could lead to out-of-bounds access later when used inside mdspan
    // mapping<dextents<char, 2>> map(dextents<char, 2>(40,40)); map(10, 3) == -126
    libcpp_assert(
        __required_span_size_is_representable(__ext),
        "layout_left::mapping extents ctor: product of extents must be representable as index_type.");
  }

  template <class _OtherExtents>
    requires(is_constructible_v<extents_type, _OtherExtents>)
 constexpr explicit(!is_convertible_v<_OtherExtents, extents_type>)
      mapping(const mapping<_OtherExtents>& __other) noexcept
      : __extents_(__other.extents()) {
    // not catching this could lead to out-of-bounds access later when used inside mdspan
    // mapping<dextents<char, 2>> map(mapping<dextents<int, 2>>(dextents<int, 2>(40,40))); map(10, 3) == -126
    libcpp_assert(
        __mdspan_detail::__is_representable_as<index_type>(__other.required_span_size()),
        "layout_left::mapping converting ctor: other.required_span_size() must be representable as index_type.");
  }

  template <class _OtherExtents>
    requires(is_constructible_v<extents_type, _OtherExtents> && _OtherExtents::rank() <= 1)
 constexpr explicit(!is_convertible_v<_OtherExtents, extents_type>)
      mapping(const layout_right::mapping<_OtherExtents>& __other) noexcept
      : __extents_(__other.extents()) {
    // not catching this could lead to out-of-bounds access later when used inside mdspan
    // Note: since this is constraint to rank 1, extents itself would catch the invalid conversion first
    //       and thus this libcpp_assertion should never be triggered, and keeping it here for consistency
    // layout_left::mapping<dextents<char, 1>> map(
    //           layout_right::mapping<dextents<unsigned, 1>>(dextents<unsigned, 1>(200))); map.extents().extent(0) ==
    //           -56
    libcpp_assert(
        __mdspan_detail::__is_representable_as<index_type>(__other.required_span_size()),
        "layout_left::mapping converting ctor: other.required_span_size() must be representable as index_type.");
  }

  template <class _OtherExtents>
    requires(is_constructible_v<extents_type, _OtherExtents>)
 constexpr explicit(extents_type::rank() > 0)
      mapping(const layout_stride::mapping<_OtherExtents>& __other) noexcept
      : __extents_(__other.extents()) {
    if constexpr (extents_type::rank() > 0) {
      libcpp_assert(
          ([&]() {
            using _CommonType = common_type_t<typename extents_type::index_type, typename _OtherExtents::index_type>;
            for (rank_type __r = 0; __r < extents_type::rank(); __r++)
              if (static_cast<_CommonType>(stride(__r)) != static_cast<_CommonType>(__other.stride(__r)))
                return false;
            return true;
          }()),
          "layout_left::mapping from layout_stride ctor: strides are not compatible with layout_left.");
      libcpp_assert(
          __mdspan_detail::__is_representable_as<index_type>(__other.required_span_size()),
          "layout_left::mapping from layout_stride ctor: other.required_span_size() must be representable as "
          "index_type.");
    }
  }

   constexpr mapping& operator=(const mapping&) noexcept = default;

  // [mdspan.layout.left.obs], observers
   constexpr const extents_type& extents() const noexcept { return __extents_; }

   constexpr index_type required_span_size() const noexcept {
    index_type __size = 1;
    for (size_t __r = 0; __r < extents_type::rank(); __r++)
      __size *= __extents_.extent(__r);
    return __size;
  }

  template <class... _Indices>
    requires((sizeof...(_Indices) == extents_type::rank()) && (is_convertible_v<_Indices, index_type> && ...) &&
             (is_nothrow_constructible_v<index_type, _Indices> && ...))
   constexpr index_type operator()(_Indices... __idx) const noexcept {
    // Mappings are generally meant to be used for accessing allocations and are meant to guarantee to never
    // return a value exceeding required_span_size(), which is used to know how large an allocation one needs
    // Thus, this is a canonical point in multi-dimensional data structures to make invalid element access checks
    // However, mdspan does check this on its own, so for now we avoid double checking in hardened mode
    libcpp_assert(__mdspan_detail::__is_multidimensional_index_in(__extents_, __idx...),
                                 "layout_left::mapping: out of bounds indexing");
    array<index_type, extents_type::rank()> __idx_a{static_cast<index_type>(__idx)...};
    return [&]<size_t... _Pos>(index_sequence<_Pos...>) {
      index_type __res = 0;
      ((__res = __idx_a[extents_type::rank() - 1 - _Pos] + __extents_.extent(extents_type::rank() - 1 - _Pos) * __res),
       ...);
      return __res;
    }(make_index_sequence<sizeof...(_Indices)>());
  }

   static constexpr bool is_always_unique() noexcept { return true; }
   static constexpr bool is_always_exhaustive() noexcept { return true; }
   static constexpr bool is_always_strided() noexcept { return true; }

   static constexpr bool is_unique() noexcept { return true; }
   static constexpr bool is_exhaustive() noexcept { return true; }
   static constexpr bool is_strided() noexcept { return true; }

   constexpr index_type stride(rank_type __r) const noexcept
    requires(extents_type::rank() > 0)
  {
    // While it would be caught by extents itself too, using a too large __r
    // is functionally an out of bounds access on the stored information needed to compute strides
    libcpp_assert(
        __r < extents_type::rank(), "layout_left::mapping::stride(): invalid rank index");
    index_type __s = 1;
    for (rank_type __i = 0; __i < __r; __i++)
      __s *= __extents_.extent(__i);
    return __s;
  }

  template <class _OtherExtents>
    requires(_OtherExtents::rank() == extents_type::rank())
   friend constexpr bool
  operator==(const mapping& __lhs, const mapping<_OtherExtents>& __rhs) noexcept {
    return __lhs.extents() == __rhs.extents();
  }

private:
 extents_type __extents_{};
};

template <class _Extents>
class layout_right::mapping {
public:
  static_assert(__mdspan_detail::__is_extents<_Extents>::value,
                "layout_right::mapping template argument must be a specialization of extents.");

  using extents_type = _Extents;
  using index_type   = typename extents_type::index_type;
  using size_type    = typename extents_type::size_type;
  using rank_type    = typename extents_type::rank_type;
  using layout_type  = layout_right;

private:
   static constexpr bool __required_span_size_is_representable(const extents_type& __ext) {
    if constexpr (extents_type::rank() == 0)
      return true;

    index_type __prod = __ext.extent(0);
    for (rank_type __r = 1; __r < extents_type::rank(); __r++) {
      bool __overflowed = __builtin_mul_overflow(__prod, __ext.extent(__r), &__prod);
      if (__overflowed)
        return false;
    }
    return true;
  }

  static_assert((extents_type::rank_dynamic() > 0) || __required_span_size_is_representable(extents_type()),
                "layout_right::mapping product of static extents must be representable as index_type.");

public:
  // [mdspan.layout.right.cons], constructors
   constexpr mapping() noexcept               = default;
   constexpr mapping(const mapping&) noexcept = default;
   constexpr mapping(const extents_type& __ext) noexcept : __extents_(__ext) {
    // not catching this could lead to out-of-bounds access later when used inside mdspan
    // mapping<dextents<char, 2>> map(dextents<char, 2>(40,40)); map(3, 10) == -126
    libcpp_assert(
        __required_span_size_is_representable(__ext),
        "layout_right::mapping extents ctor: product of extents must be representable as index_type.");
  }

  template <class _OtherExtents>
    requires(is_constructible_v<extents_type, _OtherExtents>)
   constexpr explicit(!is_convertible_v<_OtherExtents, extents_type>)
      mapping(const mapping<_OtherExtents>& __other) noexcept
      : __extents_(__other.extents()) {
    // not catching this could lead to out-of-bounds access later when used inside mdspan
    // mapping<dextents<char, 2>> map(mapping<dextents<int, 2>>(dextents<int, 2>(40,40))); map(3, 10) == -126
    libcpp_assert(
        __mdspan_detail::__is_representable_as<index_type>(__other.required_span_size()),
        "layout_right::mapping converting ctor: other.required_span_size() must be representable as index_type.");
  }

  template <class _OtherExtents>
    requires(is_constructible_v<extents_type, _OtherExtents> && _OtherExtents::rank() <= 1)
   constexpr explicit(!is_convertible_v<_OtherExtents, extents_type>)
      mapping(const layout_left::mapping<_OtherExtents>& __other) noexcept
      : __extents_(__other.extents()) {
    // not catching this could lead to out-of-bounds access later when used inside mdspan
    // Note: since this is constraint to rank 1, extents itself would catch the invalid conversion first
    //       and thus this libcpp_assertion should never be triggered, and keeping it here for consistency
    // layout_right::mapping<dextents<char, 1>> map(
    //           layout_left::mapping<dextents<unsigned, 1>>(dextents<unsigned, 1>(200))); map.extents().extent(0) ==
    //           -56
    libcpp_assert(
        __mdspan_detail::__is_representable_as<index_type>(__other.required_span_size()),
        "layout_right::mapping converting ctor: other.required_span_size() must be representable as index_type.");
  }

  template <class _OtherExtents>
    requires(is_constructible_v<extents_type, _OtherExtents>)
   constexpr explicit(extents_type::rank() > 0)
      mapping(const layout_stride::mapping<_OtherExtents>& __other) noexcept
      : __extents_(__other.extents()) {
    if constexpr (extents_type::rank() > 0) {
      libcpp_assert(
          ([&]() {
            using _CommonType = common_type_t<typename extents_type::index_type, typename _OtherExtents::index_type>;
            for (rank_type __r = 0; __r < extents_type::rank(); __r++)
              if (static_cast<_CommonType>(stride(__r)) != static_cast<_CommonType>(__other.stride(__r)))
                return false;
            return true;
          }()),
          "layout_right::mapping from layout_stride ctor: strides are not compatible with layout_right.");
      libcpp_assert(
          __mdspan_detail::__is_representable_as<index_type>(__other.required_span_size()),
          "layout_right::mapping from layout_stride ctor: other.required_span_size() must be representable as "
          "index_type.");
    }
  }

   constexpr mapping& operator=(const mapping&) noexcept = default;

  // [mdspan.layout.right.obs], observers
   constexpr const extents_type& extents() const noexcept { return __extents_; }

   constexpr index_type required_span_size() const noexcept {
    index_type __size = 1;
    for (size_t __r = 0; __r < extents_type::rank(); __r++)
      __size *= __extents_.extent(__r);
    return __size;
  }

  template <class... _Indices>
    requires((sizeof...(_Indices) == extents_type::rank()) && (is_convertible_v<_Indices, index_type> && ...) &&
             (is_nothrow_constructible_v<index_type, _Indices> && ...))
   constexpr index_type operator()(_Indices... __idx) const noexcept {
    // Mappings are generally meant to be used for accessing allocations and are meant to guarantee to never
    // return a value exceeding required_span_size(), which is used to know how large an allocation one needs
    // Thus, this is a canonical point in multi-dimensional data structures to make invalid element access checks
    // However, mdspan does check this on its own, so for now we avoid double checking in hardened mode
    libcpp_assert(__mdspan_detail::__is_multidimensional_index_in(__extents_, __idx...),
                                 "layout_right::mapping: out of bounds indexing");
    return [&]<size_t... _Pos>(index_sequence<_Pos...>) {
      index_type __res = 0;
      ((__res = static_cast<index_type>(__idx) + __extents_.extent(_Pos) * __res), ...);
      return __res;
    }(make_index_sequence<sizeof...(_Indices)>());
  }

   static constexpr bool is_always_unique() noexcept { return true; }
   static constexpr bool is_always_exhaustive() noexcept { return true; }
   static constexpr bool is_always_strided() noexcept { return true; }

   static constexpr bool is_unique() noexcept { return true; }
   static constexpr bool is_exhaustive() noexcept { return true; }
   static constexpr bool is_strided() noexcept { return true; }

   constexpr index_type stride(rank_type __r) const noexcept
    requires(extents_type::rank() > 0)
  {
    // While it would be caught by extents itself too, using a too large __r
    // is functionally an out of bounds access on the stored information needed to compute strides
    libcpp_assert(
        __r < extents_type::rank(), "layout_right::mapping::stride(): invalid rank index");
    index_type __s = 1;
    for (rank_type __i = extents_type::rank() - 1; __i > __r; __i--)
      __s *= __extents_.extent(__i);
    return __s;
  }

  template <class _OtherExtents>
    requires(_OtherExtents::rank() == extents_type::rank())
   friend constexpr bool
  operator==(const mapping& __lhs, const mapping<_OtherExtents>& __rhs) noexcept {
    return __lhs.extents() == __rhs.extents();
  }

private:
   extents_type __extents_{};
};

namespace __mdspan_detail {
template <class _Layout, class _Mapping>
constexpr bool __is_mapping_of =
    is_same_v<typename _Layout::template mapping<typename _Mapping::extents_type>, _Mapping>;

template <class _Mapping>
concept __layout_mapping_alike = requires {
  requires __is_mapping_of<typename _Mapping::layout_type, _Mapping>;
  requires __is_extents_v<typename _Mapping::extents_type>;
  { _Mapping::is_always_strided() } -> same_as<bool>;
  { _Mapping::is_always_exhaustive() } -> same_as<bool>;
  { _Mapping::is_always_unique() } -> same_as<bool>;
  bool_constant<_Mapping::is_always_strided()>::value;
  bool_constant<_Mapping::is_always_exhaustive()>::value;
  bool_constant<_Mapping::is_always_unique()>::value;
};
}

template <class _Extents>
class layout_stride::mapping {
public:
  static_assert(__mdspan_detail::__is_extents<_Extents>::value,
                "layout_stride::mapping template argument must be a specialization of extents.");

  using extents_type = _Extents;
  using index_type   = typename extents_type::index_type;
  using size_type    = typename extents_type::size_type;
  using rank_type    = typename extents_type::rank_type;
  using layout_type  = layout_stride;

private:
  static constexpr rank_type __rank_ = extents_type::rank();

  // Used for default construction check and mandates
   static constexpr bool __required_span_size_is_representable(const extents_type& __ext) {
    if constexpr (__rank_ == 0)
      return true;

    index_type __prod = __ext.extent(0);
    for (rank_type __r = 1; __r < __rank_; __r++) {
      bool __overflowed = __builtin_mul_overflow(__prod, __ext.extent(__r), &__prod);
      if (__overflowed)
        return false;
    }
    return true;
  }

  template <class _OtherIndexType>
   static constexpr bool
  __required_span_size_is_representable(const extents_type& __ext, span<_OtherIndexType, __rank_> __strides) {
    if constexpr (__rank_ == 0)
      return true;

    index_type __size = 1;
    for (rank_type __r = 0; __r < __rank_; __r++) {
      // We can only check correct conversion of _OtherIndexType if it is an integral
      if constexpr (is_integral_v<_OtherIndexType>) {
        using _CommonType = common_type_t<index_type, _OtherIndexType>;
        if (static_cast<_CommonType>(__strides[__r]) > static_cast<_CommonType>(numeric_limits<index_type>::max()))
          return false;
      }
      if (__ext.extent(__r) == static_cast<index_type>(0))
        return true;
      index_type __prod     = (__ext.extent(__r) - 1);
      bool __overflowed_mul = __builtin_mul_overflow(__prod, static_cast<index_type>(__strides[__r]), &__prod);
      if (__overflowed_mul)
        return false;
      bool __overflowed_add = __builtin_add_overflow(__size, __prod, &__size);
      if (__overflowed_add)
        return false;
    }
    return true;
  }

  // compute offset of a strided layout mapping
  template <class _StridedMapping>
   static constexpr index_type __offset(const _StridedMapping& __mapping) {
    if constexpr (_StridedMapping::extents_type::rank() == 0) {
      return static_cast<index_type>(__mapping());
    } else if (__mapping.required_span_size() == static_cast<typename _StridedMapping::index_type>(0)) {
      return static_cast<index_type>(0);
    } else {
      return [&]<size_t... _Pos>(index_sequence<_Pos...>) {
        return static_cast<index_type>(__mapping((_Pos ? 0 : 0)...));
      }(make_index_sequence<__rank_>());
    }
  }

  // compute the permutation for sorting the stride array
  // we never actually sort the stride array
   constexpr void __bubble_sort_by_strides(array<rank_type, __rank_>& __permute) const {
    for (rank_type __i = __rank_ - 1; __i > 0; __i--) {
      for (rank_type __r = 0; __r < __i; __r++) {
        if (__strides_[__permute[__r]] > __strides_[__permute[__r + 1]]) {
          swap(__permute[__r], __permute[__r + 1]);
        } else {
          // if two strides are the same then one of the associated extents must be 1 or 0
          // both could be, and you can't have one larger than 1 come first
          if ((__strides_[__permute[__r]] == __strides_[__permute[__r + 1]]) &&
              (__extents_.extent(__permute[__r]) > static_cast<index_type>(1)))
            swap(__permute[__r], __permute[__r + 1]);
        }
      }
    }
  }

  static_assert((extents_type::rank_dynamic() > 0) || __required_span_size_is_representable(extents_type()),
                "layout_stride::mapping product of static extents must be representable as index_type.");

public:
  // [mdspan.layout.stride.cons], constructors
   constexpr mapping() noexcept : __extents_(extents_type()) {
    // Note the nominal precondition is covered by above static libcpp_assert since
    // if rank_dynamic is != 0 required_span_size is zero for default construction
    if constexpr (__rank_ > 0) {
      index_type __stride = 1;
      for (rank_type __r = __rank_ - 1; __r > static_cast<rank_type>(0); __r--) {
        __strides_[__r] = __stride;
        __stride *= __extents_.extent(__r);
      }
      __strides_[0] = __stride;
    }
  }

   constexpr mapping(const mapping&) noexcept = default;

  template <class _OtherIndexType>
    requires(is_convertible_v<const _OtherIndexType&, index_type> &&
             is_nothrow_constructible_v<index_type, const _OtherIndexType&>)
   constexpr mapping(const extents_type& __ext, span<_OtherIndexType, __rank_> __strides) noexcept
      : __extents_(__ext), __strides_([&]<size_t... _Pos>(index_sequence<_Pos...>) {
          return __mdspan_detail::__possibly_empty_array<index_type, __rank_>{
              static_cast<index_type>(std::as_const(__strides[_Pos]))...};
        }(make_index_sequence<__rank_>())) {
    libcpp_assert(
        ([&]<size_t... _Pos>(index_sequence<_Pos...>) {
          // For integrals we can do a pre-conversion check, for other types not
          if constexpr (is_integral_v<_OtherIndexType>) {
            return ((__strides[_Pos] > static_cast<_OtherIndexType>(0)) && ... && true);
          } else {
            return ((static_cast<index_type>(__strides[_Pos]) > static_cast<index_type>(0)) && ... && true);
          }
        }(make_index_sequence<__rank_>())),
        "layout_stride::mapping ctor: all strides must be greater than 0");
    libcpp_assert(
        __required_span_size_is_representable(__ext, __strides),
        "layout_stride::mapping ctor: required span size is not representable as index_type.");
    if constexpr (__rank_ > 1) {
      libcpp_assert(
          ([&]<size_t... _Pos>(index_sequence<_Pos...>) {
            // basically sort the dimensions based on strides and extents, sorting is represented in permute array
            array<rank_type, __rank_> __permute{_Pos...};
            __bubble_sort_by_strides(__permute);

            // check that this permutations represents a growing set
            for (rank_type __i = 1; __i < __rank_; __i++)
              if (static_cast<index_type>(__strides[__permute[__i]]) <
                  static_cast<index_type>(__strides[__permute[__i - 1]]) * __extents_.extent(__permute[__i - 1]))
                return false;
            return true;
          }(make_index_sequence<__rank_>())),
          "layout_stride::mapping ctor: the provided extents and strides lead to a non-unique mapping");
    }
  }

  template <class _OtherIndexType>
    requires(is_convertible_v<const _OtherIndexType&, index_type> &&
             is_nothrow_constructible_v<index_type, const _OtherIndexType&>)
   constexpr mapping(const extents_type& __ext,
                                          const array<_OtherIndexType, __rank_>& __strides) noexcept
      : mapping(__ext, span(__strides)) {}

  template <class _StridedLayoutMapping>
    requires(__mdspan_detail::__layout_mapping_alike<_StridedLayoutMapping> &&
             is_constructible_v<extents_type, typename _StridedLayoutMapping::extents_type> &&
             _StridedLayoutMapping::is_always_unique() && _StridedLayoutMapping::is_always_strided())
   constexpr explicit(
      !(is_convertible_v<typename _StridedLayoutMapping::extents_type, extents_type> &&
        (__mdspan_detail::__is_mapping_of<layout_left, _StridedLayoutMapping> ||
         __mdspan_detail::__is_mapping_of<layout_right, _StridedLayoutMapping> ||
         __mdspan_detail::__is_mapping_of<layout_stride, _StridedLayoutMapping>)))
      mapping(const _StridedLayoutMapping& __other) noexcept
      : __extents_(__other.extents()), __strides_([&]<size_t... _Pos>(index_sequence<_Pos...>) {
          // stride() only compiles for rank > 0
          if constexpr (__rank_ > 0) {
            return __mdspan_detail::__possibly_empty_array<index_type, __rank_>{
                static_cast<index_type>(__other.stride(_Pos))...};
          } else {
            return __mdspan_detail::__possibly_empty_array<index_type, 0>{};
          }
        }(make_index_sequence<__rank_>())) {
    // stride() only compiles for rank > 0
    if constexpr (__rank_ > 0) {
      libcpp_assert(
          ([&]<size_t... _Pos>(index_sequence<_Pos...>) {
            return ((static_cast<index_type>(__other.stride(_Pos)) > static_cast<index_type>(0)) && ... && true);
          }(make_index_sequence<__rank_>())),
          "layout_stride::mapping converting ctor: all strides must be greater than 0");
    }
    libcpp_assert(
        __mdspan_detail::__is_representable_as<index_type>(__other.required_span_size()),
        "layout_stride::mapping converting ctor: other.required_span_size() must be representable as index_type.");
    libcpp_assert(static_cast<index_type>(0) == __offset(__other),
                                        "layout_stride::mapping converting ctor: base offset of mapping must be zero.");
  }

   constexpr mapping& operator=(const mapping&) noexcept = default;

  // [mdspan.layout.stride.obs], observers
   constexpr const extents_type& extents() const noexcept { return __extents_; }

   constexpr array<index_type, __rank_> strides() const noexcept {
    return [&]<size_t... _Pos>(index_sequence<_Pos...>) {
      return array<index_type, __rank_>{__strides_[_Pos]...};
    }(make_index_sequence<__rank_>());
  }

   constexpr index_type required_span_size() const noexcept {
    if constexpr (__rank_ == 0) {
      return static_cast<index_type>(1);
    } else {
      return [&]<size_t... _Pos>(index_sequence<_Pos...>) {
        if ((__extents_.extent(_Pos) * ... * 1) == 0)
          return static_cast<index_type>(0);
        else
          return static_cast<index_type>(
              static_cast<index_type>(1) +
              (((__extents_.extent(_Pos) - static_cast<index_type>(1)) * __strides_[_Pos]) + ... +
               static_cast<index_type>(0)));
      }(make_index_sequence<__rank_>());
    }
  }

  template <class... _Indices>
    requires((sizeof...(_Indices) == __rank_) && (is_convertible_v<_Indices, index_type> && ...) &&
             (is_nothrow_constructible_v<index_type, _Indices> && ...))
   constexpr index_type operator()(_Indices... __idx) const noexcept {
    // Mappings are generally meant to be used for accessing allocations and are meant to guarantee to never
    // return a value exceeding required_span_size(), which is used to know how large an allocation one needs
    // Thus, this is a canonical point in multi-dimensional data structures to make invalid element access checks
    // However, mdspan does check this on its own, so for now we avoid double checking in hardened mode
    libcpp_assert(__mdspan_detail::__is_multidimensional_index_in(__extents_, __idx...),
                                 "layout_stride::mapping: out of bounds indexing");
    return [&]<size_t... _Pos>(index_sequence<_Pos...>) {
      return ((static_cast<index_type>(__idx) * __strides_[_Pos]) + ... + index_type(0));
    }(make_index_sequence<sizeof...(_Indices)>());
  }

   static constexpr bool is_always_unique() noexcept { return true; }
   static constexpr bool is_always_exhaustive() noexcept { return false; }
   static constexpr bool is_always_strided() noexcept { return true; }

   static constexpr bool is_unique() noexcept { return true; }
  // The answer of this function is fairly complex in the case where one or more
  // extents are zero.
  // Technically it is meaningless to query is_exhaustive() in that case, and unfortunately
  // the way the standard defines this function, we can't give a simple true or false then.
   constexpr bool is_exhaustive() const noexcept {
    if constexpr (__rank_ == 0)
      return true;
    else {
      index_type __span_size = required_span_size();
      if (__span_size == static_cast<index_type>(0)) {
        if constexpr (__rank_ == 1)
          return __strides_[0] == 1;
        else {
          rank_type __r_largest = 0;
          for (rank_type __r = 1; __r < __rank_; __r++)
            if (__strides_[__r] > __strides_[__r_largest])
              __r_largest = __r;
          for (rank_type __r = 0; __r < __rank_; __r++)
            if (__extents_.extent(__r) == 0 && __r != __r_largest)
              return false;
          return true;
        }
      } else {
        return required_span_size() == [&]<size_t... _Pos>(index_sequence<_Pos...>) {
          return (__extents_.extent(_Pos) * ... * static_cast<index_type>(1));
        }(make_index_sequence<__rank_>());
      }
    }
  }
   static constexpr bool is_strided() noexcept { return true; }

  // according to the standard layout_stride does not have a constraint on stride(r) for rank>0
  // it still has the precondition though
   constexpr index_type stride(rank_type __r) const noexcept {
    libcpp_assert(__r < __rank_, "layout_stride::mapping::stride(): invalid rank index");
    return __strides_[__r];
  }

  template <class _OtherMapping>
    requires(__mdspan_detail::__layout_mapping_alike<_OtherMapping> &&
             (_OtherMapping::extents_type::rank() == __rank_) && _OtherMapping::is_always_strided())
   friend constexpr bool operator==(const mapping& __lhs, const _OtherMapping& __rhs) noexcept {
    if (__offset(__rhs))
      return false;
    if constexpr (__rank_ == 0)
      return true;
    else {
      return __lhs.extents() == __rhs.extents() && [&]<size_t... _Pos>(index_sequence<_Pos...>) {
        // avoid warning when comparing signed and unsigner integers and pick the wider of two types
        using _CommonType = common_type_t<index_type, typename _OtherMapping::index_type>;
        return ((static_cast<_CommonType>(__lhs.stride(_Pos)) == static_cast<_CommonType>(__rhs.stride(_Pos))) && ... &&
                true);
      }(make_index_sequence<__rank_>());
    }
  }

private:
 extents_type __extents_{};
 __mdspan_detail::__possibly_empty_array<index_type, __rank_> __strides_{};
};

// Helper for lightweight test checking that one did pass a layout policy as LayoutPolicy template argument
namespace __mdspan_detail {
template <class _Layout, class _Extents>
concept __has_invalid_mapping = !requires { typename _Layout::template mapping<_Extents>; };
}

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

}

