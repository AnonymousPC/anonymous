#pragma once

namespace std {
inline namespace __1 { 
namespace ranges {

    template<typename _Tp>
    constexpr _Tp __div_ceil(_Tp __num, _Tp __denom)
    {
      _Tp __r = __num / __denom;
      if (__num % __denom)
	++__r;
      return __r;
    }

  template<class _Tp>
    struct __my_non_propagating_cache_helper { struct type { }; };

  template<class _Tp>
    requires is_object_v<_Tp>
    struct __my_non_propagating_cache_helper<_Tp> { using type = __non_propagating_cache<_Tp>; };

  template<class _Tp>
    using __my_non_propagating_cache = __my_non_propagating_cache_helper<_Tp>::type;

  template<view _Vp>
    requires input_range<_Vp>
  class chunk_view : public view_interface<chunk_view<_Vp>>
  {
    _Vp _M_base;
    range_difference_t<_Vp> _M_n;
    range_difference_t<_Vp> _M_remainder = 0;
    __my_non_propagating_cache<iterator_t<_Vp>> _M_current;

    class _OuterIter;
    class _InnerIter;

  public:
    constexpr explicit
    chunk_view(_Vp __base, range_difference_t<_Vp> __n)
      : _M_base(std::move(__base)), _M_n(__n)
    { assert(__n >= 0); }

    constexpr _Vp
    base() const & requires copy_constructible<_Vp>
    { return _M_base; }

    constexpr _Vp
    base() &&
    { return std::move(_M_base); }

    constexpr _OuterIter
    begin()
    {
      _M_current.__emplace(ranges::begin(_M_base));
      _M_remainder = _M_n;
      return _OuterIter(*this);
    }

    constexpr default_sentinel_t
    end() const noexcept
    { return default_sentinel; }

    constexpr auto
    size() requires sized_range<_Vp>
    {
      return __to_unsigned_like(__div_ceil
					  (ranges::distance(_M_base), _M_n));
    }

    constexpr auto
    size() const requires sized_range<const _Vp>
    {
      return __to_unsigned_like(__div_ceil
					  (ranges::distance(_M_base), _M_n));
    }
  };

  template<typename _Range>
    chunk_view(_Range&&, range_difference_t<_Range>) -> chunk_view<views::all_t<_Range>>;

  template<view _Vp>
    requires input_range<_Vp>
  class chunk_view<_Vp>::_OuterIter
  {
    chunk_view* _M_parent;

    constexpr explicit
    _OuterIter(chunk_view& __parent) noexcept
      : _M_parent(std::addressof(__parent))
    { }

    friend chunk_view;

  public:
    using iterator_concept = input_iterator_tag;
    using difference_type = range_difference_t<_Vp>;

    struct value_type;

    _OuterIter(_OuterIter&&) = default;
    _OuterIter& operator=(_OuterIter&&) = default;

    constexpr value_type
    operator*() const
    {
      assert(*this != default_sentinel);
      return value_type(*_M_parent);
    }

    constexpr _OuterIter&
    operator++()
    {
      assert(*this != default_sentinel);
      ranges::advance(*_M_parent->_M_current, _M_parent->_M_remainder,
		      ranges::end(_M_parent->_M_base));
      _M_parent->_M_remainder = _M_parent->_M_n;
      return *this;
    }

    constexpr void
    operator++(int)
    { ++*this; }

    friend constexpr bool
    operator==(const _OuterIter& __x, default_sentinel_t)
    {
      return *__x._M_parent->_M_current == ranges::end(__x._M_parent->_M_base)
	&& __x._M_parent->_M_remainder != 0;
    }

    friend constexpr difference_type
    operator-(default_sentinel_t, const _OuterIter& __x)
    requires sized_sentinel_for<sentinel_t<_Vp>, iterator_t<_Vp>>
    {
      const auto __dist = ranges::end(__x._M_parent->_M_base) - *__x._M_parent->_M_current;

      if (__dist < __x._M_parent->_M_remainder)
	return __dist == 0 ? 0 : 1;

      return 1 + __div_ceil(__dist - __x._M_parent->_M_remainder,
				      __x._M_parent->_M_n);
    }

    friend constexpr difference_type
    operator-(const _OuterIter& __x, default_sentinel_t __y)
    requires sized_sentinel_for<sentinel_t<_Vp>, iterator_t<_Vp>>
    { return -(__y - __x); }
  };

  template<view _Vp>
    requires input_range<_Vp>
  struct chunk_view<_Vp>::_OuterIter::value_type : view_interface<value_type>
  {
  private:
    chunk_view* _M_parent;

    constexpr explicit
    value_type(chunk_view& __parent) noexcept
    : _M_parent(std::addressof(__parent))
    { }

    friend _OuterIter;

  public:
    constexpr _InnerIter
    begin() const noexcept
    { return _InnerIter(*_M_parent); }

    constexpr default_sentinel_t
    end() const noexcept
    { return default_sentinel; }

    constexpr auto
    size() const
    requires sized_sentinel_for<sentinel_t<_Vp>, iterator_t<_Vp>>
    {
      return __to_unsigned_like
	(ranges::min(_M_parent->_M_remainder,
		     ranges::end(_M_parent->_M_base) - *_M_parent->_M_current));
    }
  };

  template<view _Vp>
    requires input_range<_Vp>
  class chunk_view<_Vp>::_InnerIter
  {
    chunk_view* _M_parent;

    constexpr explicit
    _InnerIter(chunk_view& __parent) noexcept
    : _M_parent(std::addressof(__parent))
    { }

    friend _OuterIter::value_type;

  public:
    using iterator_concept = input_iterator_tag;
    using difference_type = range_difference_t<_Vp>;
    using value_type = range_value_t<_Vp>;

    _InnerIter(_InnerIter&&) = default;
    _InnerIter& operator=(_InnerIter&&) = default;

    constexpr const iterator_t<_Vp>&
    base() const &
    { return *_M_parent->_M_current; }

    constexpr range_reference_t<_Vp>
    operator*() const
    {
      assert(*this != default_sentinel);
      return **_M_parent->_M_current;
    }

    constexpr _InnerIter&
    operator++()
    {
      assert(*this != default_sentinel);
      ++*_M_parent->_M_current;
      if (*_M_parent->_M_current == ranges::end(_M_parent->_M_base))
	_M_parent->_M_remainder = 0;
      else
	--_M_parent->_M_remainder;
      return *this;
    }

    constexpr void
    operator++(int)
    { ++*this; }

    friend constexpr bool
    operator==(const _InnerIter& __x, default_sentinel_t) noexcept
    { return __x._M_parent->_M_remainder == 0; }

    friend constexpr difference_type
    operator-(default_sentinel_t, const _InnerIter& __x)
      requires sized_sentinel_for<sentinel_t<_Vp>, iterator_t<_Vp>>
    {
      return ranges::min(__x._M_parent->_M_remainder,
			 ranges::end(__x._M_parent->_M_base) - *__x._M_parent->_M_current);
    }

    friend constexpr difference_type
    operator-(const _InnerIter& __x, default_sentinel_t __y)
      requires sized_sentinel_for<sentinel_t<_Vp>, iterator_t<_Vp>>
    { return -(__y - __x); }
  };

  template<view _Vp>
    requires forward_range<_Vp>
  class chunk_view<_Vp> : public view_interface<chunk_view<_Vp>>
  {
    _Vp _M_base;
    range_difference_t<_Vp> _M_n;
    template<bool> class _Iterator;

  public:
    constexpr explicit
    chunk_view(_Vp __base, range_difference_t<_Vp> __n)
    : _M_base(std::move(__base)), _M_n(__n)
    { assert(__n > 0); }

    constexpr _Vp
    base() const & requires copy_constructible<_Vp>
    { return _M_base; }

    constexpr _Vp
    base() &&
    { return std::move(_M_base); }

    constexpr auto
    begin() requires (!__simple_view<_Vp>)
    { return _Iterator<false>(this, ranges::begin(_M_base)); }

    constexpr auto
    begin() const requires forward_range<const _Vp>
    { return _Iterator<true>(this, ranges::begin(_M_base)); }

    constexpr auto
    end() requires (!__simple_view<_Vp>)
    {
      if constexpr (common_range<_Vp> && sized_range<_Vp>)
	{
	  auto __missing = (_M_n - ranges::distance(_M_base) % _M_n) % _M_n;
	  return _Iterator<false>(this, ranges::end(_M_base), __missing);
	}
      else if constexpr (common_range<_Vp> && !bidirectional_range<_Vp>)
	return _Iterator<false>(this, ranges::end(_M_base));
      else
	return default_sentinel;
    }

    constexpr auto
    end() const requires forward_range<const _Vp>
    {
      if constexpr (common_range<const _Vp> && sized_range<const _Vp>)
	{
	  auto __missing = (_M_n - ranges::distance(_M_base) % _M_n) % _M_n;
	  return _Iterator<true>(this, ranges::end(_M_base), __missing);
	}
      else if constexpr (common_range<const _Vp> && !bidirectional_range<const _Vp>)
	return _Iterator<true>(this, ranges::end(_M_base));
      else
	return default_sentinel;
    }

    constexpr auto
    size() requires sized_range<_Vp>
    {
      return __to_unsigned_like(__div_ceil
					  (ranges::distance(_M_base), _M_n));
    }

    constexpr auto
    size() const requires sized_range<const _Vp>
    {
      return __to_unsigned_like(__div_ceil
					  (ranges::distance(_M_base), _M_n));
    }
  };

  template<typename _Vp>
    inline constexpr bool enable_borrowed_range<chunk_view<_Vp>>
      = forward_range<_Vp> && enable_borrowed_range<_Vp>;

  template<view _Vp>
    requires forward_range<_Vp>
  template<bool _Const>
  class chunk_view<_Vp>::_Iterator
  {
    using _Parent = __maybe_const<_Const, chunk_view>;
    using _Base = __maybe_const<_Const, _Vp>;

    iterator_t<_Base> _M_current = iterator_t<_Base>();
    sentinel_t<_Base> _M_end = sentinel_t<_Base>();
    range_difference_t<_Base> _M_n = 0;
    range_difference_t<_Base> _M_missing = 0;

    constexpr
    _Iterator(_Parent* __parent, iterator_t<_Base> __current,
	      range_difference_t<_Base> __missing = 0)
    : _M_current(__current), _M_end(ranges::end(__parent->_M_base)),
      _M_n(__parent->_M_n), _M_missing(__missing)
    { }

    static auto
    _S_iter_cat()
    {
      if constexpr (random_access_range<_Base>)
	return random_access_iterator_tag{};
      else if constexpr (bidirectional_range<_Base>)
	return bidirectional_iterator_tag{};
      else
	return forward_iterator_tag{};
    }

    friend chunk_view;

  public:
    using iterator_category = input_iterator_tag;
    using iterator_concept = decltype(_S_iter_cat());
    using value_type = decltype(views::take(subrange(_M_current, _M_end), _M_n));
    using difference_type = range_difference_t<_Base>;

    _Iterator() = default;

    constexpr _Iterator(_Iterator<!_Const> __i)
      requires _Const
	&& convertible_to<iterator_t<_Vp>, iterator_t<_Base>>
	&& convertible_to<sentinel_t<_Vp>, sentinel_t<_Base>>
    : _M_current(std::move(__i._M_current)), _M_end(std::move(__i._M_end)),
      _M_n(__i._M_n), _M_missing(__i._M_missing)
    { }

    constexpr iterator_t<_Base>
    base() const
    { return _M_current; }

    constexpr value_type
    operator*() const
    {
      assert(_M_current != _M_end);
      return views::take(subrange(_M_current, _M_end), _M_n);
    }

    constexpr _Iterator&
    operator++()
    {
      assert(_M_current != _M_end);
      _M_missing = ranges::advance(_M_current, _M_n, _M_end);
      return *this;
    }

    constexpr _Iterator
    operator++(int)
    {
      auto __tmp = *this;
      ++*this;
      return __tmp;
    }

    constexpr _Iterator&
    operator--() requires bidirectional_range<_Base>
    {
      ranges::advance(_M_current, _M_missing - _M_n);
      _M_missing = 0;
      return *this;
    }

    constexpr _Iterator
    operator--(int) requires bidirectional_range<_Base>
    {
      auto __tmp = *this;
      --*this;
      return __tmp;
    }

    constexpr _Iterator&
    operator+=(difference_type __x)
      requires random_access_range<_Base>
    {
      if (__x > 0)
	{
    assert(ranges::distance(_M_current, _M_end) > _M_n * (__x - 1));
	  _M_missing = ranges::advance(_M_current, _M_n * __x, _M_end);
	}
      else if (__x < 0)
	{
	  ranges::advance(_M_current, _M_n * __x + _M_missing);
	  _M_missing = 0;
	}
      return *this;
    }

    constexpr _Iterator&
    operator-=(difference_type __x)
      requires random_access_range<_Base>
    { return *this += -__x; }

    constexpr value_type
    operator[](difference_type __n) const
      requires random_access_range<_Base>
    { return *(*this + __n); }

    friend constexpr bool
    operator==(const _Iterator& __x, const _Iterator& __y)
    { return __x._M_current == __y._M_current; }

    friend constexpr bool
    operator==(const _Iterator& __x, default_sentinel_t)
    { return __x._M_current == __x._M_end; }

    friend constexpr bool
    operator<(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base>
    { return __x._M_current > __y._M_current; }

    friend constexpr bool
    operator>(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base>
    { return __y < __x; }

    friend constexpr bool
    operator<=(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base>
    { return !(__y < __x); }

    friend constexpr bool
    operator>=(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base>
    { return !(__x < __y); }

    friend constexpr auto
    operator<=>(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base>
	&& three_way_comparable<iterator_t<_Base>>
    { return __x._M_current <=> __y._M_current; }

    friend constexpr _Iterator
    operator+(const _Iterator& __i, difference_type __n)
      requires random_access_range<_Base>
    {
      auto __r  = __i;
      __r += __n;
      return __r;
    }

    friend constexpr _Iterator
    operator+(difference_type __n, const _Iterator& __i)
      requires random_access_range<_Base>
    {
      auto __r  = __i;
      __r += __n;
      return __r;
    }

    friend constexpr _Iterator
    operator-(const _Iterator& __i, difference_type __n)
      requires random_access_range<_Base>
    {
      auto __r  = __i;
      __r -= __n;
      return __r;
    }

    friend constexpr difference_type
    operator-(const _Iterator& __x, const _Iterator& __y)
      requires sized_sentinel_for<iterator_t<_Base>, iterator_t<_Base>>
    {
      return (__x._M_current - __y._M_current
	      + __x._M_missing - __y._M_missing) / __x._M_n;
    }

    friend constexpr difference_type
    operator-(default_sentinel_t __y, const _Iterator& __x)
      requires sized_sentinel_for<sentinel_t<_Base>, iterator_t<_Base>>
    { return __div_ceil(__x._M_end - __x._M_current, __x._M_n); }

    friend constexpr difference_type
    operator-(const _Iterator& __x, default_sentinel_t __y)
      requires sized_sentinel_for<sentinel_t<_Base>, iterator_t<_Base>>
    { return -(__y - __x); }
  };

  namespace views
  {
      template<typename _Range, typename _Dp>
	concept __can_chunk_view
	  = requires { chunk_view(std::declval<_Range>(), std::declval<_Dp>()); };

    struct _Chunk : __range_adaptor_closure<_Chunk>
    {
      template<viewable_range _Range, typename _Dp = range_difference_t<_Range>>
	requires __can_chunk_view<_Range, _Dp>
	constexpr auto
	operator() [[nodiscard]] (_Range&& __r, type_identity_t<_Dp> __n) const
	{ 
      return chunk_view(std::forward<_Range>(__r), __n);
    }

      template <typename _Dp>
    constexpr auto
    operator() [[nodiscard]] (_Dp&& __n) const
    {
      return __range_adaptor_closure_t(std::__bind_back(*this, std::forward<_Dp>(__n)));
    }


      static constexpr int _S_arity = 2;
      static constexpr bool _S_has_simple_extra_args = true;
    };

    

    inline constexpr _Chunk chunk;
  }

} // namespace ranges
} // namespace __1
} // namespace std