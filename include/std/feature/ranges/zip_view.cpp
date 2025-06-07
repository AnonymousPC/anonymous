module;
#include <ranges>

export module std.feature.ranges.zip_view;
import std.compiler;

#ifndef __cpp_lib_ranges_zip

export namespace std
{

namespace ranges
{
    template<typename _Range, bool _Const>
      using __range_iter_cat
	    = typename iterator_traits<iterator_t<__maybe_const<_Const, _Range>>>::iterator_category;

    template <class _Fun, class _Tuple>
    _LIBCPP_HIDE_FROM_ABI constexpr auto __tu_local_tuple_transform(_Fun&& __f, _Tuple&& __tuple) {
    return std::apply(
        [&]<class... _Types>(_Types&&... __elements) {
            return tuple<invoke_result_t<_Fun&, _Types>...>(std::invoke(__f, std::forward<_Types>(__elements))...);
        },
        std::forward<_Tuple>(__tuple));
    }

  template<move_constructible _Fp, input_range... _Vs>
    requires (view<_Vs> && ...) && (sizeof...(_Vs) > 0) && is_object_v<_Fp>
      && regular_invocable<_Fp&, range_reference_t<_Vs>...>
      && std::__can_reference<invoke_result_t<_Fp&, range_reference_t<_Vs>...>>
  class zip_transform_view : public view_interface<zip_transform_view<_Fp, _Vs...>>
  {
    [[no_unique_address]] std::optional<_Fp> _M_fun;
    zip_view<_Vs...> _M_zip;

    using _InnerView = zip_view<_Vs...>;

    template<bool _Const>
      using __ziperator = iterator_t<__maybe_const<_Const, _InnerView>>;

    template<bool _Const>
      using __zentinel = sentinel_t<__maybe_const<_Const, _InnerView>>;

    template<bool _Const>
      using _Base = __maybe_const<_Const, _InnerView>;

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
	  using _Res = invoke_result_t<__maybe_const<_Const, _Fp>&,
				       range_reference_t<__maybe_const<_Const, _Vs>>...>;
	  if constexpr (!is_lvalue_reference_v<_Res>)
	    return input_iterator_tag{};
	  else if constexpr ((derived_from<__range_iter_cat<_Vs, _Const>,
					   random_access_iterator_tag> && ...))
	    return random_access_iterator_tag{};
	  else if constexpr ((derived_from<__range_iter_cat<_Vs, _Const>,
					   bidirectional_iterator_tag> && ...))
	    return bidirectional_iterator_tag{};
	  else if constexpr ((derived_from<__range_iter_cat<_Vs, _Const>,
					   forward_iterator_tag> && ...))
	    return forward_iterator_tag{};
	  else
	    return input_iterator_tag{};
	}
      public:
	using iterator_category = decltype(_S_iter_cat());
      };

    template<bool> class _Iterator;
    template<bool> class _Sentinel;

  public:
    zip_transform_view() = default;

    constexpr explicit
    zip_transform_view(_Fp __fun, _Vs... __views)
      : _M_fun(std::move(__fun)), _M_zip(std::move(__views)...)
    { }

    constexpr auto
    begin()
    { return _Iterator<false>(*this, _M_zip.begin()); }

    constexpr auto
    begin() const
      requires range<const _InnerView>
	&& regular_invocable<const _Fp&, range_reference_t<const _Vs>...>
    { return _Iterator<true>(*this, _M_zip.begin()); }

    constexpr auto
    end()
    {
      if constexpr (common_range<_InnerView>)
	return _Iterator<false>(*this, _M_zip.end());
      else
	return _Sentinel<false>(_M_zip.end());
    }

    constexpr auto
    end() const
      requires range<const _InnerView>
	&& regular_invocable<const _Fp&, range_reference_t<const _Vs>...>
    {
      if constexpr (common_range<const _InnerView>)
	return _Iterator<true>(*this, _M_zip.end());
      else
	return _Sentinel<true>(_M_zip.end());
    }

    constexpr auto
    size() requires sized_range<_InnerView>
    { return _M_zip.size(); }

    constexpr auto
    size() const requires sized_range<const _InnerView>
    { return _M_zip.size(); }
  };

  template<class _Fp, class... Rs>
    zip_transform_view(_Fp, Rs&&...) -> zip_transform_view<_Fp, views::all_t<Rs>...>;

  template<move_constructible _Fp, input_range... _Vs>
    requires (view<_Vs> && ...) && (sizeof...(_Vs) > 0) && is_object_v<_Fp>
      && regular_invocable<_Fp&, range_reference_t<_Vs>...>
      && std::__can_reference<invoke_result_t<_Fp&, range_reference_t<_Vs>...>>
  template<bool _Const>
  class zip_transform_view<_Fp, _Vs...>::_Iterator : public __iter_cat<_Const>
  {
    using _Parent = __maybe_const<_Const, zip_transform_view>;

    _Parent* _M_parent = nullptr;
    __ziperator<_Const> _M_inner;

    constexpr
    _Iterator(_Parent& __parent, __ziperator<_Const> __inner)
      : _M_parent(std::addressof(__parent)), _M_inner(std::move(__inner))
    { }

    friend class zip_transform_view;

  public:
    // iterator_category defined in zip_transform_view::__iter_cat
    using iterator_concept = typename __ziperator<_Const>::iterator_concept;
    using value_type
      = remove_cvref_t<invoke_result_t<__maybe_const<_Const, _Fp>&,
				       range_reference_t<__maybe_const<_Const, _Vs>>...>>;
    using difference_type = range_difference_t<_Base<_Const>>;

    _Iterator() = default;

    constexpr
    _Iterator(_Iterator<!_Const> __i)
      requires _Const && convertible_to<__ziperator<false>, __ziperator<_Const>>
      : _M_parent(__i._M_parent), _M_inner(std::move(__i._M_inner))
    { }

    constexpr decltype(auto)
    operator*() const
    {
      return std::apply([&](const auto&... __iters) -> decltype(auto) {
        return std::__invoke(*_M_parent->_M_fun, *__iters...);
      }, _M_inner._M_current);
    }

    constexpr _Iterator&
    operator++()
    {
      ++_M_inner;
      return *this;
    }

    constexpr void
    operator++(int)
    { ++*this; }

    constexpr _Iterator
    operator++(int) requires forward_range<_Base<_Const>>
    {
      auto __tmp = *this;
      ++*this;
      return __tmp;
    }

    constexpr _Iterator&
    operator--() requires bidirectional_range<_Base<_Const>>
    {
      --_M_inner;
      return *this;
    }

    constexpr _Iterator
    operator--(int) requires bidirectional_range<_Base<_Const>>
    {
      auto __tmp = *this;
      --*this;
      return __tmp;
    }

    constexpr _Iterator&
    operator+=(difference_type __x) requires random_access_range<_Base<_Const>>
    {
      _M_inner += __x;
      return *this;
    }

    constexpr _Iterator&
    operator-=(difference_type __x) requires random_access_range<_Base<_Const>>
    {
      _M_inner -= __x;
      return *this;
    }

    constexpr decltype(auto)
    operator[](difference_type __n) const requires random_access_range<_Base<_Const>>
    {
      return std::apply([&]<typename... _Is>(const _Is&... __iters) -> decltype(auto) {
        return std::__invoke(*_M_parent->_M_fun, __iters[iter_difference_t<_Is>(__n)]...);
      }, _M_inner._M_current);
    }

    friend constexpr bool
    operator==(const _Iterator& __x, const _Iterator& __y)
      requires equality_comparable<__ziperator<_Const>>
    { return __x._M_inner == __y._M_inner; }

    friend constexpr auto
    operator<=>(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base<_Const>>
    { return __x._M_inner <=> __y._M_inner; }

    friend constexpr _Iterator
    operator+(const _Iterator& __i, difference_type __n)
      requires random_access_range<_Base<_Const>>
    { return _Iterator(*__i._M_parent, __i._M_inner + __n); }

    friend constexpr _Iterator
    operator+(difference_type __n, const _Iterator& __i)
      requires random_access_range<_Base<_Const>>
    { return _Iterator(*__i._M_parent, __i._M_inner + __n); }

    friend constexpr _Iterator
    operator-(const _Iterator& __i, difference_type __n)
      requires random_access_range<_Base<_Const>>
    { return _Iterator(*__i._M_parent, __i._M_inner - __n); }

    friend constexpr difference_type
    operator-(const _Iterator& __x, const _Iterator& __y)
      requires sized_sentinel_for<__ziperator<_Const>, __ziperator<_Const>>
    { return __x._M_inner - __y._M_inner; }
  };

  template<move_constructible _Fp, input_range... _Vs>
    requires (view<_Vs> && ...) && (sizeof...(_Vs) > 0) && is_object_v<_Fp>
      && regular_invocable<_Fp&, range_reference_t<_Vs>...>
      && std::__can_reference<invoke_result_t<_Fp&, range_reference_t<_Vs>...>>
  template<bool _Const>
  class zip_transform_view<_Fp, _Vs...>::_Sentinel
  {
    __zentinel<_Const> _M_inner;

    constexpr explicit
    _Sentinel(__zentinel<_Const> __inner)
      : _M_inner(__inner)
    { }

    friend class zip_transform_view;

  public:
    _Sentinel() = default;

    constexpr
    _Sentinel(_Sentinel<!_Const> __i)
      requires _Const && convertible_to<__zentinel<false>, __zentinel<_Const>>
      : _M_inner(std::move(__i._M_inner))
    { }

    template<bool _OtherConst>
      requires sentinel_for<__zentinel<_Const>, __ziperator<_OtherConst>>
    friend constexpr bool
    operator==(const _Iterator<_OtherConst>& __x, const _Sentinel& __y)
    { return __x._M_inner == __y._M_inner; }

    template<bool _OtherConst>
      requires sized_sentinel_for<__zentinel<_Const>, __ziperator<_OtherConst>>
    friend constexpr range_difference_t<__maybe_const<_OtherConst, _InnerView>>
    operator-(const _Iterator<_OtherConst>& __x, const _Sentinel& __y)
    { return __x._M_inner - __y._M_inner; }

    template<bool _OtherConst>
      requires sized_sentinel_for<__zentinel<_Const>, __ziperator<_OtherConst>>
    friend constexpr range_difference_t<__maybe_const<_OtherConst, _InnerView>>
    operator-(const _Sentinel& __x, const _Iterator<_OtherConst>& __y)
    { return __x._M_inner - __y._M_inner; }
  };

  namespace views
  {
      template<typename _Fp, typename... _Ts>
	concept __can_zip_transform_view
	  = requires { zip_transform_view(std::declval<_Fp>(), std::declval<_Ts>()...); };

    struct _ZipTransform
    {
      template<typename _Fp, typename... _Ts>
	requires (sizeof...(_Ts) == 0) || __can_zip_transform_view<_Fp, _Ts...>
	constexpr auto
	operator() [[nodiscard]] (_Fp&& __f, _Ts&&... __ts) const
	{
	  if constexpr (sizeof...(_Ts) == 0)
	    return views::empty<remove_cvref_t<invoke_result_t<remove_cvref_t<_Fp>&>>>;
	  else
	    return zip_transform_view(std::forward<_Fp>(__f), std::forward<_Ts>(__ts)...);
	}
    };

    inline constexpr _ZipTransform zip_transform;
  }

  template<forward_range _Vp, size_t _Nm>
    requires view<_Vp> && (_Nm > 0)
  class adjacent_view : public view_interface<adjacent_view<_Vp, _Nm>>
  {
    _Vp _M_base = _Vp();

    template<bool> class _Iterator;
    template<bool> class _Sentinel;

    struct __as_sentinel
    { };

  public:
    adjacent_view() requires default_initializable<_Vp> = default;

    constexpr explicit
    adjacent_view(_Vp __base)
      : _M_base(std::move(__base))
    { }

    constexpr auto
    begin() requires (!__simple_view<_Vp>)
    { return _Iterator<false>(ranges::begin(_M_base), ranges::end(_M_base)); }

    constexpr auto
    begin() const requires range<const _Vp>
    { return _Iterator<true>(ranges::begin(_M_base), ranges::end(_M_base)); }

    constexpr auto
    end() requires (!__simple_view<_Vp>)
    {
      if constexpr (common_range<_Vp>)
	return _Iterator<false>(__as_sentinel{}, ranges::begin(_M_base), ranges::end(_M_base));
      else
	return _Sentinel<false>(ranges::end(_M_base));
    }

    constexpr auto
    end() const requires range<const _Vp>
    {
      if constexpr (common_range<const _Vp>)
	return _Iterator<true>(__as_sentinel{}, ranges::begin(_M_base), ranges::end(_M_base));
      else
	return _Sentinel<true>(ranges::end(_M_base));
    }

    constexpr auto
    size() requires sized_range<_Vp>
    {
      using _ST = decltype(ranges::size(_M_base));
      using _CT = common_type_t<_ST, size_t>;
      auto __sz = static_cast<_CT>(ranges::size(_M_base));
      __sz -= std::min<_CT>(__sz, _Nm - 1);
      return static_cast<_ST>(__sz);
    }

    constexpr auto
    size() const requires sized_range<const _Vp>
    {
      using _ST = decltype(ranges::size(_M_base));
      using _CT = common_type_t<_ST, size_t>;
      auto __sz = static_cast<_CT>(ranges::size(_M_base));
      __sz -= std::min<_CT>(__sz, _Nm - 1);
      return static_cast<_ST>(__sz);
    }
  };

  template<typename _Vp, size_t _Nm>
    inline constexpr bool enable_borrowed_range<adjacent_view<_Vp, _Nm>>
      = enable_borrowed_range<_Vp>;

    // Yields tuple<_Tp, ..., _Tp> with _Nm elements.
    template<typename _Tp, size_t _Nm>
      using __repeated_tuple = decltype(std::tuple_cat(std::declval<array<_Tp, _Nm>>()));

    // For a functor F that is callable with N arguments, the expression
    // declval<__unarize<F, N>>(x) is equivalent to declval<F>(x, ..., x).
    template<typename _Fp, size_t _Nm>
      struct __unarize
      {
	template<typename... _Ts>
	  static invoke_result_t<_Fp, _Ts...>
	  __tuple_apply(const tuple<_Ts...>&); // not defined

	template<typename _Tp>
	  decltype(__tuple_apply(std::declval<__repeated_tuple<_Tp, _Nm>>()))
	  operator()(_Tp&&); // not defined
      };

  template<forward_range _Vp, size_t _Nm>
    requires view<_Vp> && (_Nm > 0)
  template<bool _Const>
  class adjacent_view<_Vp, _Nm>::_Iterator
  {
#ifdef __clang__ // LLVM-61763 workaround
  public:
#endif
    using _Base = __maybe_const<_Const, _Vp>;
    array<iterator_t<_Base>, _Nm> _M_current = array<iterator_t<_Base>, _Nm>();

    constexpr
    _Iterator(iterator_t<_Base> __first, sentinel_t<_Base> __last)
    {
      for (auto& __i : _M_current)
	{
	  __i = __first;
	  ranges::advance(__first, 1, __last);
	}
    }

    constexpr
    _Iterator(__as_sentinel, iterator_t<_Base> __first, iterator_t<_Base> __last)
    {
      if constexpr (!bidirectional_range<_Base>)
	for (auto& __it : _M_current)
	  __it = __last;
      else
	for (size_t __i = 0; __i < _Nm; ++__i)
	  {
	    _M_current[_Nm - 1 - __i] = __last;
	    ranges::advance(__last, -1, __first);
	  }
    }

    static auto
    _S_iter_concept()
    {
      if constexpr (random_access_range<_Base>)
	return random_access_iterator_tag{};
      else if constexpr (bidirectional_range<_Base>)
	return bidirectional_iterator_tag{};
      else
	return forward_iterator_tag{};
    }

    friend class adjacent_view;

#ifndef __clang__ // LLVM-61763 workaround
    template<forward_range _Wp, move_constructible _Fp, size_t _Mm>
      requires view<_Wp> && (_Mm > 0) && is_object_v<_Fp>
        && regular_invocable<__unarize<_Fp&, _Mm>, range_reference_t<_Wp>>
        && std::__can_reference<invoke_result_t<__unarize<_Fp&, _Mm>,
							 range_reference_t<_Wp>>>
      friend class adjacent_transform_view;
#endif

  public:
    using iterator_category = input_iterator_tag;
    using iterator_concept = decltype(_S_iter_concept());
    // using value_type = conditional_t<_Nm == 2,
	// 			     pair<range_value_t<_Base>, range_value_t<_Base>>,
	// 			     __repeated_tuple<range_value_t<_Base>, _Nm>>;
    using value_type = __repeated_tuple<range_value_t<_Base>, _Nm>; // I changed it.
    using difference_type = range_difference_t<_Base>;

    _Iterator() = default;

    constexpr
    _Iterator(_Iterator<!_Const> __i)
      requires _Const && convertible_to<iterator_t<_Vp>, iterator_t<_Base>>
    {
      for (size_t __j = 0; __j < _Nm; ++__j)
	_M_current[__j] = std::move(__i._M_current[__j]);
    }

    constexpr auto
    operator*() const
    {
      auto __f = [](auto& __i) -> decltype(auto) { return *__i; };
      return __tu_local_tuple_transform(__f, _M_current);
    }

    constexpr _Iterator&
    operator++()
    {
      for (auto& __i : _M_current)
	++__i;
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
      for (auto& __i : _M_current)
	--__i;
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
      for (auto& __i : _M_current)
	__i += __x;
      return *this;
    }

    constexpr _Iterator&
    operator-=(difference_type __x)
      requires random_access_range<_Base>
    {
      for (auto& __i : _M_current)
	__i -= __x;
      return *this;
    }

    constexpr auto
    operator[](difference_type __n) const
      requires random_access_range<_Base>
    {
      auto __f = [&](auto& __i) -> decltype(auto) { return __i[__n]; };
      return __tu_local_tuple_transform(__f, _M_current);
    }

    friend constexpr bool
    operator==(const _Iterator& __x, const _Iterator& __y)
    { return __x._M_current.back() == __y._M_current.back(); }

    friend constexpr bool
    operator<(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base>
    { return __x._M_current.back() < __y._M_current.back(); }

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
    { return __x._M_current.back() <=> __y._M_current.back(); }

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
    {
      auto __r = __i;
      __r += __n;
      return __r;
    }

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
    { return __x._M_current.back() - __y._M_current.back(); }

    friend constexpr auto
    iter_move(const _Iterator& __i)
    { return __tu_local_tuple_transform(ranges::iter_move, __i._M_current); }

    friend constexpr void
    iter_swap(const _Iterator& __l, const _Iterator& __r)
      requires indirectly_swappable<iterator_t<_Base>>
    {
      for (size_t __i = 0; __i < _Nm; __i++)
	ranges::iter_swap(__l._M_current[__i], __r._M_current[__i]);
    }
  };

  template<forward_range _Vp, size_t _Nm>
    requires view<_Vp> && (_Nm > 0)
  template<bool _Const>
  class adjacent_view<_Vp, _Nm>::_Sentinel
  {
    using _Base = __maybe_const<_Const, _Vp>;

    sentinel_t<_Base> _M_end = sentinel_t<_Base>();

    constexpr explicit
    _Sentinel(sentinel_t<_Base> __end)
      : _M_end(__end)
    { }

    friend class adjacent_view;

  public:
    _Sentinel() = default;

    constexpr
    _Sentinel(_Sentinel<!_Const> __i)
      requires _Const && convertible_to<sentinel_t<_Vp>, sentinel_t<_Base>>
      : _M_end(std::move(__i._M_end))
    { }

    template<bool _OtherConst>
      requires sentinel_for<sentinel_t<_Base>,
			    iterator_t<__maybe_const<_OtherConst, _Vp>>>
    friend constexpr bool
    operator==(const _Iterator<_OtherConst>& __x, const _Sentinel& __y)
    { return __x._M_current.back() == __y._M_end; }

    template<bool _OtherConst>
      requires sized_sentinel_for<sentinel_t<_Base>,
				  iterator_t<__maybe_const<_OtherConst, _Vp>>>
    friend constexpr range_difference_t<__maybe_const<_OtherConst, _Vp>>
    operator-(const _Iterator<_OtherConst>& __x, const _Sentinel& __y)
    { return __x._M_current.back() - __y._M_end; }

    template<bool _OtherConst>
      requires sized_sentinel_for<sentinel_t<_Base>,
				  iterator_t<__maybe_const<_OtherConst, _Vp>>>
    friend constexpr range_difference_t<__maybe_const<_OtherConst, _Vp>>
    operator-(const _Sentinel& __y, const _Iterator<_OtherConst>& __x)
    { return __y._M_end - __x._M_current.back(); }
  };

  namespace views
  {
      template<size_t _Nm, typename _Range>
	concept __can_adjacent_view
	  = requires { adjacent_view<all_t<_Range>, _Nm>(std::declval<_Range>()); };

    template<size_t _Nm>
      struct _Adjacent : range_adaptor_closure<_Adjacent<_Nm>>
      {
	template<viewable_range _Range>
	  requires (_Nm == 0) || __can_adjacent_view<_Nm, _Range>
	  constexpr auto
	  operator() [[nodiscard]] (_Range&& __r) const
	  {
	    if constexpr (_Nm == 0)
	      return views::empty<tuple<>>;
	    else
	      return adjacent_view<all_t<_Range>, _Nm>(std::forward<_Range>(__r));
	  }
      };

    template<size_t _Nm>
      inline constexpr _Adjacent<_Nm> adjacent;

    inline constexpr auto pairwise = adjacent<2>;
  }

  template<forward_range _Vp, move_constructible _Fp, size_t _Nm>
   requires view<_Vp> && (_Nm > 0) && is_object_v<_Fp>
     && regular_invocable<__unarize<_Fp&, _Nm>, range_reference_t<_Vp>>
     && std::__can_reference<invoke_result_t<__unarize<_Fp&, _Nm>,
						       range_reference_t<_Vp>>>
  class adjacent_transform_view : public view_interface<adjacent_transform_view<_Vp, _Fp, _Nm>>
  {
    [[no_unique_address]] std::optional<_Fp> _M_fun;
    adjacent_view<_Vp, _Nm> _M_inner;

    using _InnerView = adjacent_view<_Vp, _Nm>;

    template<bool _Const>
      using _InnerIter = iterator_t<__maybe_const<_Const, _InnerView>>;

    template<bool _Const>
      using _InnerSent = sentinel_t<__maybe_const<_Const, _InnerView>>;

    template<bool> class _Iterator;
    template<bool> class _Sentinel;

  public:
    adjacent_transform_view() = default;

    constexpr explicit
    adjacent_transform_view(_Vp __base, _Fp __fun)
      : _M_fun(std::move(__fun)), _M_inner(std::move(__base))
    { }

    constexpr auto
    begin()
    { return _Iterator<false>(*this, _M_inner.begin()); }

    constexpr auto
    begin() const
      requires range<const _InnerView>
	&& regular_invocable<__unarize<const _Fp&, _Nm>,
			     range_reference_t<const _Vp>>
    { return _Iterator<true>(*this, _M_inner.begin()); }

    constexpr auto
    end()
    {
      if constexpr (common_range<_InnerView>)
        return _Iterator<false>(*this, _M_inner.end());
      else
        return _Sentinel<false>(_M_inner.end());
    }

    constexpr auto
    end() const
      requires range<const _InnerView>
	&& regular_invocable<__unarize<const _Fp&, _Nm>,
			     range_reference_t<const _Vp>>
    {
      if constexpr (common_range<const _InnerView>)
        return _Iterator<true>(*this, _M_inner.end());
      else
        return _Sentinel<true>(_M_inner.end());
    }

    constexpr auto
    size() requires sized_range<_InnerView>
    { return _M_inner.size(); }

    constexpr auto
    size() const requires sized_range<const _InnerView>
    { return _M_inner.size(); }
  };

  template<forward_range _Vp, move_constructible _Fp, size_t _Nm>
   requires view<_Vp> && (_Nm > 0) && is_object_v<_Fp>
     && regular_invocable<__unarize<_Fp&, _Nm>, range_reference_t<_Vp>>
     && std::__can_reference<invoke_result_t<__unarize<_Fp&, _Nm>,
						       range_reference_t<_Vp>>>
  template<bool _Const>
  class adjacent_transform_view<_Vp, _Fp, _Nm>::_Iterator
  {
    using _Parent = __maybe_const<_Const, adjacent_transform_view>;
    using _Base = __maybe_const<_Const, _Vp>;

    _Parent* _M_parent = nullptr;
    _InnerIter<_Const> _M_inner;

    constexpr
    _Iterator(_Parent& __parent, _InnerIter<_Const> __inner)
      : _M_parent(std::addressof(__parent)), _M_inner(std::move(__inner))
    { }

    static auto
    _S_iter_cat()
    {
      using _Res = invoke_result_t<__unarize<__maybe_const<_Const, _Fp>&, _Nm>,
				   range_reference_t<_Base>>;
      using _Cat = typename iterator_traits<iterator_t<_Base>>::iterator_category;
      if constexpr (!is_lvalue_reference_v<_Res>)
	return input_iterator_tag{};
      else if constexpr (derived_from<_Cat, random_access_iterator_tag>)
	return random_access_iterator_tag{};
      else if constexpr (derived_from<_Cat, bidirectional_iterator_tag>)
	return bidirectional_iterator_tag{};
      else if constexpr (derived_from<_Cat, forward_iterator_tag>)
	return forward_iterator_tag{};
      else
	return input_iterator_tag{};
    }

    friend class adjacent_transform_view;

  public:
    using iterator_category = decltype(_S_iter_cat());
    using iterator_concept = typename _InnerIter<_Const>::iterator_concept;
    using value_type
      = remove_cvref_t<invoke_result_t
		       <__unarize<__maybe_const<_Const, _Fp>&, _Nm>,
			range_reference_t<_Base>>>;
    using difference_type = range_difference_t<_Base>;

    _Iterator() = default;

    constexpr
    _Iterator(_Iterator<!_Const> __i)
      requires _Const && convertible_to<_InnerIter<false>, _InnerIter<_Const>>
      : _M_parent(__i._M_parent), _M_inner(std::move(__i._M_inner))
    { }

    constexpr decltype(auto)
    operator*() const
    {
      return std::apply([&](const auto&... __iters) -> decltype(auto) {
        return std::__invoke(*_M_parent->_M_fun, *__iters...);
      }, _M_inner._M_current);
    }

    constexpr _Iterator&
    operator++()
    {
      ++_M_inner;
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
      --_M_inner;
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
    operator+=(difference_type __x) requires random_access_range<_Base>
    {
      _M_inner += __x;
      return *this;
    }

    constexpr _Iterator&
    operator-=(difference_type __x) requires random_access_range<_Base>
    {
      _M_inner -= __x;
      return *this;
    }

    constexpr decltype(auto)
    operator[](difference_type __n) const requires random_access_range<_Base>
    {
      return std::apply([&](const auto&... __iters) -> decltype(auto) {
        return std::__invoke(*_M_parent->_M_fun, __iters[__n]...);
      }, _M_inner._M_current);
    }

    friend constexpr bool
    operator==(const _Iterator& __x, const _Iterator& __y)
    { return __x._M_inner == __y._M_inner; }

    friend constexpr bool
    operator<(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base>
    { return __x._M_inner < __y._M_inner; }

    friend constexpr bool
    operator>(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base>
    { return __x._M_inner > __y._M_inner; }

    friend constexpr bool
    operator<=(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base>
    { return __x._M_inner <= __y._M_inner; }

    friend constexpr bool
    operator>=(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base>
    { return __x._M_inner >= __y._M_inner; }

    friend constexpr auto
    operator<=>(const _Iterator& __x, const _Iterator& __y)
      requires random_access_range<_Base> &&
      three_way_comparable<_InnerIter<_Const>>
    { return __x._M_inner <=> __y._M_inner; }

    friend constexpr _Iterator
    operator+(const _Iterator& __i, difference_type __n)
      requires random_access_range<_Base>
    { return _Iterator(*__i._M_parent, __i._M_inner + __n); }

    friend constexpr _Iterator
    operator+(difference_type __n, const _Iterator& __i)
      requires random_access_range<_Base>
    { return _Iterator(*__i._M_parent, __i._M_inner + __n); }

    friend constexpr _Iterator
    operator-(const _Iterator& __i, difference_type __n)
      requires random_access_range<_Base>
    { return _Iterator(*__i._M_parent, __i._M_inner - __n); }

    friend constexpr difference_type
    operator-(const _Iterator& __x, const _Iterator& __y)
      requires sized_sentinel_for<_InnerIter<_Const>, _InnerIter<_Const>>
    { return __x._M_inner - __y._M_inner; }
  };

  template<forward_range _Vp, move_constructible _Fp, size_t _Nm>
   requires view<_Vp> && (_Nm > 0) && is_object_v<_Fp>
     && regular_invocable<__unarize<_Fp&, _Nm>, range_reference_t<_Vp>>
     && std::__can_reference<invoke_result_t<__unarize<_Fp&, _Nm>,
						       range_reference_t<_Vp>>>
  template<bool _Const>
  class adjacent_transform_view<_Vp, _Fp, _Nm>::_Sentinel
  {
    _InnerSent<_Const> _M_inner;

    constexpr explicit
    _Sentinel(_InnerSent<_Const> __inner)
      : _M_inner(__inner)
    { }

    friend class adjacent_transform_view;

  public:
    _Sentinel() = default;

    constexpr
    _Sentinel(_Sentinel<!_Const> __i)
      requires _Const && convertible_to<_InnerSent<false>, _InnerSent<_Const>>
      : _M_inner(std::move(__i._M_inner))
    { }

    template<bool _OtherConst>
      requires sentinel_for<_InnerSent<_Const>, _InnerIter<_OtherConst>>
    friend constexpr bool
    operator==(const _Iterator<_OtherConst>& __x, const _Sentinel& __y)
    { return __x._M_inner == __y._M_inner; }

    template<bool _OtherConst>
      requires sized_sentinel_for<_InnerSent<_Const>, _InnerIter<_OtherConst>>
    friend constexpr range_difference_t<__maybe_const<_OtherConst, _InnerView>>
    operator-(const _Iterator<_OtherConst>& __x, const _Sentinel& __y)
    { return __x._M_inner - __y._M_inner; }

    template<bool _OtherConst>
      requires sized_sentinel_for<_InnerSent<_Const>, _InnerIter<_OtherConst>>
    friend constexpr range_difference_t<__maybe_const<_OtherConst, _InnerView>>
    operator-(const _Sentinel& __x, const _Iterator<_OtherConst>& __y)
    { return __x._M_inner - __y._M_inner; }
  };

  namespace views
  {
      template<size_t _Nm, typename _Range, typename _Fp>
	concept __can_adjacent_transform_view
	  = requires { adjacent_transform_view<all_t<_Range>, remove_cvref_t<_Fp>, _Nm>
		         (std::declval<_Range>(), std::declval<_Fp>()); };

    template<size_t _Nm>
      struct _AdjacentTransform : range_adaptor_closure<_AdjacentTransform<_Nm>>
      {
	template<viewable_range _Range, typename _Fp>
	  requires (_Nm == 0) || __can_adjacent_transform_view<_Nm, _Range, _Fp>
	  constexpr auto
	  operator() [[nodiscard]] (_Range&& __r, _Fp&& __f) const
	  {
	    if constexpr (_Nm == 0)
	      return zip_transform(std::forward<_Fp>(__f));
	    else
	      return adjacent_transform_view<all_t<_Range>, remove_cvref_t<_Fp>, _Nm>
		(std::forward<_Range>(__r), std::forward<_Fp>(__f));
	  }

    template<typename _Pattern>
      constexpr auto
      operator() [[nodiscard]] (_Pattern&& __f) const
      {
        return __pipeable(std::bind_back(*this, std::forward<_Pattern>(__f)));
      }

	static constexpr int _S_arity = 2;
	static constexpr bool _S_has_simple_extra_args = true;
      };

    template<size_t _Nm>
      inline constexpr _AdjacentTransform<_Nm> adjacent_transform;

    inline constexpr auto pairwise_transform = adjacent_transform<2>;
  }


}

}

#endif