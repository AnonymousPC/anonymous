namespace ranges {

template<input_range _Vp>
    requires view<_Vp>
  class stride_view : public view_interface<stride_view<_Vp>>
  {
    _Vp _M_base;
    range_difference_t<_Vp> _M_stride;

    template<bool _Const> using _Base = __maybe_const<_Const, _Vp>;

    template<bool _Const>
    struct __iter_cat
    { };

    template<bool _Const>
      requires forward_range<_Base<_Const>>
    struct __iter_cat<_Const>
    {
    private:
      static auto
      _S_iter_cat()
      {
	using _Cat = typename iterator_traits<iterator_t<_Base<_Const>>>::iterator_category;
	if constexpr (derived_from<_Cat, random_access_iterator_tag>)
	  return random_access_iterator_tag{};
	else
	  return _Cat{};
      }
    public:
      using iterator_category = decltype(_S_iter_cat());
    };

    template<bool> class _Iterator;

  public:
    constexpr explicit
    stride_view(_Vp __base, range_difference_t<_Vp> __stride)
    : _M_base(std::move(__base)), _M_stride(__stride)
    { }

    constexpr _Vp
    base() const& requires copy_constructible<_Vp>
    { return _M_base; }

    constexpr _Vp
    base() &&
    { return std::move(_M_base); }

    constexpr range_difference_t<_Vp>
    stride() const noexcept
    { return _M_stride; }

    constexpr auto
    begin() requires (!__simple_view<_Vp>)
    { return _Iterator<false>(this, ranges::begin(_M_base)); }

    constexpr auto
    begin() const requires range<const _Vp>
    { return _Iterator<true>(this, ranges::begin(_M_base)); }

    constexpr auto
    end() requires (!__simple_view<_Vp>)
    {
      if constexpr (common_range<_Vp> && sized_range<_Vp> && forward_range<_Vp>)
	{
	  auto __missing = (_M_stride - ranges::distance(_M_base) % _M_stride) % _M_stride;
	  return _Iterator<false>(this, ranges::end(_M_base), __missing);
	}
      else if constexpr (common_range<_Vp> && !bidirectional_range<_Vp>)
	return _Iterator<false>(this, ranges::end(_M_base));
      else
        return default_sentinel;
    }

    constexpr auto
    end() const requires range<const _Vp>
    {
      if constexpr (common_range<const _Vp> && sized_range<const _Vp>
		    && forward_range<const _Vp>)
	{
	  auto __missing = (_M_stride - ranges::distance(_M_base) % _M_stride) % _M_stride;
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
      return __to_unsigned_like
	(__div_ceil(ranges::distance(_M_base), _M_stride));
    }

    constexpr auto
    size() const requires sized_range<const _Vp>
    {
      return __to_unsigned_like
	(__div_ceil(ranges::distance(_M_base), _M_stride));
    }
  };

  template<typename _Range>
    stride_view(_Range&&, range_difference_t<_Range>) -> stride_view<views::all_t<_Range>>;

  template<typename _Vp>
    inline constexpr bool enable_borrowed_range<stride_view<_Vp>>
      = enable_borrowed_range<_Vp>;

  template<input_range _Vp>
    requires view<_Vp>
  template<bool _Const>
  class stride_view<_Vp>::_Iterator : public __iter_cat<_Const>
  {
    using _Parent = __maybe_const<_Const, stride_view>;
    using _Base = stride_view::_Base<_Const>;

    iterator_t<_Base> _M_current = iterator_t<_Base>();
    sentinel_t<_Base> _M_end = sentinel_t<_Base>();
    range_difference_t<_Base> _M_stride = 0;
    range_difference_t<_Base> _M_missing = 0;

    constexpr
    _Iterator(_Parent* __parent, iterator_t<_Base> __current,
	      range_difference_t<_Base> __missing = 0)
    : _M_current(std::move(__current)), _M_end(ranges::end(__parent->_M_base)),
      _M_stride(__parent->_M_stride), _M_missing(__missing)
    { }

    static auto
    _S_iter_concept()
    {
      if constexpr (random_access_range<_Base>)
	return random_access_iterator_tag{};
      else if constexpr (bidirectional_range<_Base>)
	return bidirectional_iterator_tag{};
      else if constexpr (forward_range<_Base>)
	return forward_iterator_tag{};
      else
	return input_iterator_tag{};
    }

    friend stride_view;

  public:
    using difference_type = range_difference_t<_Base>;
    using value_type = range_value_t<_Base>;
    using iterator_concept = decltype(_S_iter_concept());
    // iterator_category defined in stride_view::__iter_cat

    _Iterator() requires default_initializable<iterator_t<_Base>> = default;

    constexpr
    _Iterator(_Iterator<!_Const> __other)
      requires _Const
	&& convertible_to<iterator_t<_Vp>, iterator_t<_Base>>
	&& convertible_to<sentinel_t<_Vp>, sentinel_t<_Base>>
     : _M_current(std::move(__other._M_current)), _M_end(std::move(__other._M_end)),
       _M_stride(__other._M_stride), _M_missing(__other._M_missing)
     { }

    constexpr iterator_t<_Base>
    base() &&
    { return std::move(_M_current); }

    constexpr const iterator_t<_Base>&
    base() const & noexcept
    { return _M_current; }

    constexpr decltype(auto)
    operator*() const
    { return *_M_current; }

    constexpr _Iterator&
    operator++()
    {
      _M_missing = ranges::advance(_M_current, _M_stride, _M_end);
      return *this;
    }

    constexpr void
    operator++(int)
    { ++*this; }

    constexpr _Iterator
    operator++(int) requires forward_range<_Base>
    {
      auto __tmp = *this;
      ++*this;
      return __tmp;
    }

    constexpr _Iterator&
    operator--() requires bidirectional_range<_Base>
    {
      ranges::advance(_M_current, _M_missing - _M_stride);
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
    operator+=(difference_type __n) requires random_access_range<_Base>
    {
      if (__n > 0)
	{
	  _M_missing = ranges::advance(_M_current, _M_stride * __n, _M_end);
	}
      else if (__n < 0)
	{
	  ranges::advance(_M_current, _M_stride * __n + _M_missing);
	  _M_missing = 0;
	}
      return *this;
    }

    constexpr _Iterator&
    operator-=(difference_type __n) requires random_access_range<_Base>
    { return *this += -__n; }

    constexpr decltype(auto) operator[](difference_type __n) const
      requires random_access_range<_Base>
    { return *(*this + __n); }

    friend constexpr bool
    operator==(const _Iterator& __x, default_sentinel_t)
    { return __x._M_current == __x._M_end; }

    friend constexpr bool
    operator==(const _Iterator& __x, const _Iterator& __y)
      requires equality_comparable<iterator_t<_Base>>
    { return __x._M_current == __y._M_current; }

    friend constexpr bool
    operator<(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base>
    { return __x._M_current < __y._M_current; }

    friend constexpr bool
    operator>(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base>
    { return __y._M_current < __x._M_current; }

    friend constexpr bool
    operator<=(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base>
    { return !(__y._M_current < __x._M_current); }

    friend constexpr bool
    operator>=(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base>
    { return !(__x._M_current < __y._M_current); }

    friend constexpr auto
    operator<=>(const _Iterator& __x, const _Iterator& __y)
        requires random_access_range<_Base> && three_way_comparable<iterator_t<_Base>>
    { return __x._M_current <=> __y._M_current; }

    friend constexpr _Iterator
    operator+(const _Iterator& __i, difference_type __n)
      requires random_access_range<_Base>
    {
      auto __r = __i;
      __r += __n;
      return __r;
    }

    friend constexpr _Iterator
    operator+(difference_type __n, const _Iterator& __i)
      requires random_access_range<_Base>
    { return __i + __n; }

    friend constexpr _Iterator
    operator-(const _Iterator& __i, difference_type __n)
      requires random_access_range<_Base>
    {
      auto __r = __i;
      __r -= __n;
      return __r;
    }

    friend constexpr difference_type
    operator-(const _Iterator& __x, const _Iterator& __y)
      requires sized_sentinel_for<iterator_t<_Base>, iterator_t<_Base>>
    {
      auto __n = __x._M_current - __y._M_current;
      if constexpr (forward_range<_Base>)
	return (__n + __x._M_missing - __y._M_missing) / __x._M_stride;
      else if (__n < 0)
	return -__div_ceil(-__n, __x._M_stride);
      else
	return __div_ceil(__n, __x._M_stride);
    }

    friend constexpr difference_type
    operator-(default_sentinel_t __y, const _Iterator& __x)
      requires sized_sentinel_for<sentinel_t<_Base>, iterator_t<_Base>>
    { return __div_ceil(__x._M_end - __x._M_current, __x._M_stride); }

    friend constexpr difference_type
    operator-(const _Iterator& __x, default_sentinel_t __y)
      requires sized_sentinel_for<sentinel_t<_Base>, iterator_t<_Base>>
    { return -(__y - __x); }

    friend constexpr range_rvalue_reference_t<_Base>
    iter_move(const _Iterator& __i)
      noexcept(noexcept(ranges::iter_move(__i._M_current)))
    { return ranges::iter_move(__i._M_current); }

    friend constexpr void
    iter_swap(const _Iterator& __x, const _Iterator& __y)
      noexcept(noexcept(ranges::iter_swap(__x._M_current, __y._M_current)))
      requires indirectly_swappable<iterator_t<_Base>>
    { ranges::iter_swap(__x._M_current, __y._M_current); }
  };

  namespace views
  {
      template<typename _Range, typename _Dp>
	concept __can_stride_view
	  = requires { stride_view(std::declval<_Range>(), std::declval<_Dp>()); };

    struct _Stride : range_adaptor_closure<_Stride>
    {
      template<viewable_range _Range, typename _Dp = range_difference_t<_Range>>
	requires __can_stride_view<_Range, _Dp>
	constexpr auto
	operator() [[nodiscard]] (_Range&& __r, type_identity_t<_Dp> __n) const
	{ return stride_view(std::forward<_Range>(__r), __n); }

      template<typename _Dp>
    constexpr auto
    operator() [[nodiscard]] (_Dp&& __r) const
    {
      return __pipeable(std::bind_back(*this, std::forward<_Dp>(__r)));
    }

      static constexpr int _S_arity = 2;
      static constexpr bool _S_has_simple_extra_args = true;
    };

    inline constexpr _Stride stride;
  }


} // namespace ranges
