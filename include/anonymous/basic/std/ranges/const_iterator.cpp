export namespace std {
    
  template<indirectly_readable _It>
    using iter_const_reference_t
      = common_reference_t<const iter_value_t<_It>&&, iter_reference_t<_It>>;

  template<input_iterator _It> class basic_const_iterator;

  namespace __detail
  {
    template<typename _It>
      concept __constant_iterator = input_iterator<_It>
	&& same_as<iter_const_reference_t<_It>, iter_reference_t<_It>>;

    template<typename _Tp>
      inline constexpr bool __is_const_iterator = false;

    template<typename _It>
      inline constexpr bool __is_const_iterator<basic_const_iterator<_It>> = true;

    template<typename _Tp>
      concept __not_a_const_iterator = !__is_const_iterator<_Tp>;

    template<indirectly_readable _It>
      using __iter_const_rvalue_reference_t
	= common_reference_t<const iter_value_t<_It>&&, iter_rvalue_reference_t<_It>>;

    template<typename _It>
      struct __basic_const_iterator_iter_cat
      { };

    template<forward_iterator _It>
      struct __basic_const_iterator_iter_cat<_It>
      { using iterator_category = std::iterator_traits<_It>::iterator_category; };
  } // namespace detail

  template<input_iterator _It>
    using const_iterator
      = __conditional_t<__detail::__constant_iterator<_It>, _It, basic_const_iterator<_It>>;

  namespace __detail
  {
    template<typename _Sent>
      struct __const_sentinel
      { using type = _Sent; };

    template<input_iterator _Sent>
      struct __const_sentinel<_Sent>
      { using type = const_iterator<_Sent>; };
  } // namespace __detail

  template<semiregular _Sent>
    using const_sentinel = typename __detail::__const_sentinel<_Sent>::type;

  template<input_iterator _It>
  class basic_const_iterator
  : public __detail::__basic_const_iterator_iter_cat<_It>
  {
    _It _M_current = _It();
    using __reference = iter_const_reference_t<_It>;
    using __rvalue_reference = __detail::__iter_const_rvalue_reference_t<_It>;

    static auto
    _S_iter_concept()
    {
      if constexpr (contiguous_iterator<_It>)
	return contiguous_iterator_tag{};
      else if constexpr (random_access_iterator<_It>)
	return random_access_iterator_tag{};
      else if constexpr (bidirectional_iterator<_It>)
	return bidirectional_iterator_tag{};
      else if constexpr (forward_iterator<_It>)
	return forward_iterator_tag{};
      else
	return input_iterator_tag{};
    }

    template<input_iterator _It2> friend class basic_const_iterator;

  public:
    using iterator_concept = decltype(_S_iter_concept());
    using value_type = iter_value_t<_It>;
    using difference_type = iter_difference_t<_It>;

    basic_const_iterator() requires default_initializable<_It> = default;

    constexpr
    basic_const_iterator(_It __current)
    noexcept(is_nothrow_move_constructible_v<_It>)
    : _M_current(std::move(__current))
    { }

    template<convertible_to<_It> _It2>
      constexpr
      basic_const_iterator(basic_const_iterator<_It2> __current)
      noexcept(is_nothrow_constructible_v<_It, _It2>)
      : _M_current(std::move(__current._M_current))
      { }

    template<__different_from<basic_const_iterator> _Tp>
      requires convertible_to<_Tp, _It>
      constexpr
      basic_const_iterator(_Tp&& __current)
      noexcept(is_nothrow_constructible_v<_It, _Tp>)
      : _M_current(std::forward<_Tp>(__current))
      { }

    constexpr const _It&
    base() const & noexcept
    { return _M_current; }

    constexpr _It
    base() &&
    noexcept(is_nothrow_move_constructible_v<_It>)
    { return std::move(_M_current); }

    constexpr __reference
    operator*() const
    noexcept(noexcept(static_cast<__reference>(*_M_current)))
    { return static_cast<__reference>(*_M_current); }

    constexpr const auto*
    operator->() const
    noexcept(contiguous_iterator<_It> || noexcept(*_M_current))
    requires is_lvalue_reference_v<iter_reference_t<_It>>
      && same_as<remove_cvref_t<iter_reference_t<_It>>, value_type>
    {
      if constexpr (contiguous_iterator<_It>)
	return std::to_address(_M_current);
      else
	return std::addressof(*_M_current);
    }

    constexpr basic_const_iterator&
    operator++()
    noexcept(noexcept(++_M_current))
    {
      ++_M_current;
      return *this;
    }

    constexpr void
    operator++(int)
    noexcept(noexcept(++_M_current))
    { ++_M_current; }

    constexpr basic_const_iterator
    operator++(int)
    noexcept(noexcept(++*this) && is_nothrow_copy_constructible_v<basic_const_iterator>)
    requires forward_iterator<_It>
    {
      auto __tmp = *this;
      ++*this;
      return __tmp;
    }

    constexpr basic_const_iterator&
    operator--()
    noexcept(noexcept(--_M_current))
    requires bidirectional_iterator<_It>
    {
      --_M_current;
      return *this;
    }

    constexpr basic_const_iterator
    operator--(int)
    noexcept(noexcept(--*this) && is_nothrow_copy_constructible_v<basic_const_iterator>)
    requires bidirectional_iterator<_It>
    {
      auto __tmp = *this;
      --*this;
      return __tmp;
    }

    constexpr basic_const_iterator&
    operator+=(difference_type __n)
    noexcept(noexcept(_M_current += __n))
    requires random_access_iterator<_It>
    {
      _M_current += __n;
      return *this;
    }

    constexpr basic_const_iterator&
    operator-=(difference_type __n)
    noexcept(noexcept(_M_current -= __n))
    requires random_access_iterator<_It>
    {
      _M_current -= __n;
      return *this;
    }

    constexpr __reference
    operator[](difference_type __n) const
    noexcept(noexcept(static_cast<__reference>(_M_current[__n])))
    requires random_access_iterator<_It>
    { return static_cast<__reference>(_M_current[__n]); }

    template<sentinel_for<_It> _Sent>
      constexpr bool
      operator==(const _Sent& __s) const
      noexcept(noexcept(_M_current == __s))
      { return _M_current == __s; }

    template<__detail::__not_a_const_iterator _CIt>
      requires __detail::__constant_iterator<_CIt> && convertible_to<_It, _CIt>
    constexpr
    operator _CIt() const&
    { return _M_current; }

    template<__detail::__not_a_const_iterator _CIt>
      requires __detail::__constant_iterator<_CIt> && convertible_to<_It, _CIt>
    constexpr
    operator _CIt() &&
    { return std::move(_M_current); }

    constexpr bool
    operator<(const basic_const_iterator& __y) const
    noexcept(noexcept(_M_current < __y._M_current))
    requires random_access_iterator<_It>
    { return _M_current < __y._M_current; }

    constexpr bool
    operator>(const basic_const_iterator& __y) const
    noexcept(noexcept(_M_current > __y._M_current))
    requires random_access_iterator<_It>
    { return _M_current > __y._M_current; }

    constexpr bool
    operator<=(const basic_const_iterator& __y) const
    noexcept(noexcept(_M_current <= __y._M_current))
    requires random_access_iterator<_It>
    { return _M_current <= __y._M_current; }

    constexpr bool
    operator>=(const basic_const_iterator& __y) const
    noexcept(noexcept(_M_current >= __y._M_current))
    requires random_access_iterator<_It>
    { return _M_current >= __y._M_current; }

    constexpr auto
    operator<=>(const basic_const_iterator& __y) const
    noexcept(noexcept(_M_current <=> __y._M_current))
    requires random_access_iterator<_It> && three_way_comparable<_It>
    { return _M_current <=> __y._M_current; }

    template<__different_from<basic_const_iterator> _It2>
      constexpr bool
      operator<(const _It2& __y) const
      noexcept(noexcept(_M_current < __y))
      requires random_access_iterator<_It> && totally_ordered_with<_It, _It2>
      { return _M_current < __y; }

    template<__different_from<basic_const_iterator> _It2>
      constexpr bool
      operator>(const _It2& __y) const
      noexcept(noexcept(_M_current > __y))
      requires random_access_iterator<_It> && totally_ordered_with<_It, _It2>
      { return _M_current > __y; }

    template<__different_from<basic_const_iterator> _It2>
      constexpr bool
      operator<=(const _It2& __y) const
      noexcept(noexcept(_M_current <= __y))
      requires random_access_iterator<_It> && totally_ordered_with<_It, _It2>
      { return _M_current <= __y; }

    template<__different_from<basic_const_iterator> _It2>
      constexpr bool
      operator>=(const _It2& __y) const
      noexcept(noexcept(_M_current >= __y))
      requires random_access_iterator<_It> && totally_ordered_with<_It, _It2>
      { return _M_current >= __y; }

    template<__different_from<basic_const_iterator> _It2>
      constexpr auto
      operator<=>(const _It2& __y) const
      noexcept(noexcept(_M_current <=> __y))
      requires random_access_iterator<_It> && totally_ordered_with<_It, _It2>
	&& three_way_comparable_with<_It, _It2>
      { return _M_current <=> __y; }

    template<__detail::__not_a_const_iterator _It2>
      friend constexpr bool
      operator<(const _It2& __x, const basic_const_iterator& __y)
      noexcept(noexcept(__x < __y._M_current))
      requires random_access_iterator<_It> && totally_ordered_with<_It, _It2>
      { return __x < __y._M_current; }

    template<__detail::__not_a_const_iterator _It2>
      friend constexpr bool
      operator>(const _It2& __x, const basic_const_iterator& __y)
      noexcept(noexcept(__x > __y._M_current))
      requires random_access_iterator<_It> && totally_ordered_with<_It, _It2>
      { return __x > __y._M_current; }

    template<__detail::__not_a_const_iterator _It2>
      friend constexpr bool
      operator<=(const _It2& __x, const basic_const_iterator& __y)
      noexcept(noexcept(__x <= __y._M_current))
      requires random_access_iterator<_It> && totally_ordered_with<_It, _It2>
      { return __x <= __y._M_current; }

    template<__detail::__not_a_const_iterator _It2>
      friend constexpr bool
      operator>=(const _It2& __x, const basic_const_iterator& __y)
      noexcept(noexcept(__x >= __y._M_current))
      requires random_access_iterator<_It> && totally_ordered_with<_It, _It2>
      { return __x >= __y._M_current; }

    friend constexpr basic_const_iterator
    operator+(const basic_const_iterator& __i, difference_type __n)
    noexcept(noexcept(basic_const_iterator(__i._M_current + __n)))
    requires random_access_iterator<_It>
    { return basic_const_iterator(__i._M_current + __n); }

    friend constexpr basic_const_iterator
    operator+(difference_type __n, const basic_const_iterator& __i)
    noexcept(noexcept(basic_const_iterator(__i._M_current + __n)))
    requires random_access_iterator<_It>
    { return basic_const_iterator(__i._M_current + __n); }

    friend constexpr basic_const_iterator
    operator-(const basic_const_iterator& __i, difference_type __n)
    noexcept(noexcept(basic_const_iterator(__i._M_current - __n)))
    requires random_access_iterator<_It>
    { return basic_const_iterator(__i._M_current - __n); }

    template<sized_sentinel_for<_It> _Sent>
      constexpr difference_type
      operator-(const _Sent& __y) const
      noexcept(noexcept(_M_current - __y))
      { return _M_current - __y; }

    template<__detail::__not_a_const_iterator _Sent>
      requires sized_sentinel_for<_Sent, _It>
      friend constexpr difference_type
      operator-(const _Sent& __x, const basic_const_iterator& __y)
      noexcept(noexcept(__x - __y._M_current))
      { return __x - __y._M_current; }

    friend constexpr __rvalue_reference
    iter_move(const basic_const_iterator& __i)
    noexcept(noexcept(static_cast<__rvalue_reference>(ranges::iter_move(__i._M_current))))
    { return static_cast<__rvalue_reference>(ranges::iter_move(__i._M_current)); }
  };

  template<typename _Tp, common_with<_Tp> _Up>
    requires input_iterator<common_type_t<_Tp, _Up>>
    struct common_type<basic_const_iterator<_Tp>, _Up>
    { using type = basic_const_iterator<common_type_t<_Tp, _Up>>; };

  template<typename _Tp, common_with<_Tp> _Up>
    requires input_iterator<common_type_t<_Tp, _Up>>
    struct common_type<_Up, basic_const_iterator<_Tp>>
    { using type = basic_const_iterator<common_type_t<_Tp, _Up>>; };

  template<typename _Tp, common_with<_Tp> _Up>
    requires input_iterator<common_type_t<_Tp, _Up>>
    struct common_type<basic_const_iterator<_Tp>, basic_const_iterator<_Up>>
    { using type = basic_const_iterator<common_type_t<_Tp, _Up>>; };

  template<input_iterator _It>
    constexpr const_iterator<_It>
    make_const_iterator(_It __it)
    noexcept(is_nothrow_convertible_v<_It, const_iterator<_It>>)
    { return __it; }

  template<semiregular _Sent>
    constexpr const_sentinel<_Sent>
    make_const_sentinel(_Sent __s)
    noexcept(is_nothrow_convertible_v<_Sent, const_sentinel<_Sent>>)
    { return __s; }

} // namespace std

