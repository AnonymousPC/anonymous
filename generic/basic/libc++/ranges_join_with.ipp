#pragma once

namespace std {
inline namespace __1 { 
namespace ranges {

  template<typename _Range, typename _Pattern>
    concept __compatible_joinable_ranges
	= common_with<range_value_t<_Range>, range_value_t<_Pattern>>
	  && common_reference_with<range_reference_t<_Range>,
				   range_reference_t<_Pattern>>
	  && common_reference_with<range_rvalue_reference_t<_Range>,
				   range_rvalue_reference_t<_Pattern>>;

  template<typename _Range>
    concept __bidirectional_common = bidirectional_range<_Range> && common_range<_Range>;

  template<typename _Tp, int _Disc>
    struct _Absent { };

  template<bool _Present, typename _Tp, int _Disc = 0>
    using __maybe_present = __conditional_t<_Present, _Tp, _Absent<_Tp, _Disc>>;

  template<input_range _Vp, forward_range _Pattern>
    requires view<_Vp> && view<_Pattern>
      && input_range<range_reference_t<_Vp>>
      && __compatible_joinable_ranges<range_reference_t<_Vp>, _Pattern>
  class join_with_view : public view_interface<join_with_view<_Vp, _Pattern>>
  {
    using _InnerRange = range_reference_t<_Vp>;

    _Vp _M_base = _Vp();
    [[no_unique_address]]
      __maybe_present<!forward_range<_Vp>,
	__my_non_propagating_cache<iterator_t<_Vp>>> _M_outer_it; // See libcpp_ranges_chunk.ipp
    __my_non_propagating_cache<remove_cv_t<_InnerRange>> _M_inner; // See libcpp_ranges_chunk.ipp
    _Pattern _M_pattern = _Pattern();

    template<bool _Const> using _Base = __maybe_const<_Const, _Vp>;
    template<bool _Const> using _InnerBase = range_reference_t<_Base<_Const>>;
    template<bool _Const> using _PatternBase = __maybe_const<_Const, _Pattern>;

    template<bool _Const> using _OuterIter = iterator_t<_Base<_Const>>;
    template<bool _Const> using _InnerIter = iterator_t<_InnerBase<_Const>>;
    template<bool _Const> using _PatternIter = iterator_t<_PatternBase<_Const>>;

    template<bool _Const>
      static constexpr bool _S_ref_is_glvalue = is_reference_v<_InnerBase<_Const>>;

    template<bool _Const>
    struct __iter_cat
    { };

    template<bool _Const>
      requires _S_ref_is_glvalue<_Const>
	&& forward_range<_Base<_Const>>
	&& forward_range<_InnerBase<_Const>>
    struct __iter_cat<_Const>
    {
      private:
	static auto
	_S_iter_cat()
	{
	  using _OuterIter = join_with_view::_OuterIter<_Const>;
	  using _InnerIter = join_with_view::_InnerIter<_Const>;
	  using _PatternIter = join_with_view::_PatternIter<_Const>;
	  using _OuterCat = typename iterator_traits<_OuterIter>::iterator_category;
	  using _InnerCat = typename iterator_traits<_InnerIter>::iterator_category;
	  using _PatternCat = typename iterator_traits<_PatternIter>::iterator_category;
	  if constexpr (!is_lvalue_reference_v<common_reference_t<iter_reference_t<_InnerIter>,
								  iter_reference_t<_PatternIter>>>)
	    return input_iterator_tag{};
	  else if constexpr (derived_from<_OuterCat, bidirectional_iterator_tag>
			     && derived_from<_InnerCat, bidirectional_iterator_tag>
			     && derived_from<_PatternCat, bidirectional_iterator_tag>
			     && common_range<_InnerBase<_Const>>
			     && common_range<_PatternBase<_Const>>)
	    return bidirectional_iterator_tag{};
	  else if constexpr (derived_from<_OuterCat, forward_iterator_tag>
			     && derived_from<_InnerCat, forward_iterator_tag>
			     && derived_from<_PatternCat, forward_iterator_tag>)
	    return forward_iterator_tag{};
	  else
	    return input_iterator_tag{};
	}
      public:
	using iterator_category = decltype(_S_iter_cat());
    };

    template<bool> struct _Iterator;
    template<bool> struct _Sentinel;

  public:
    join_with_view() requires (default_initializable<_Vp>
			       && default_initializable<_Pattern>)
      = default;

    constexpr
    join_with_view(_Vp __base, _Pattern __pattern)
    : _M_base(std::move(__base)), _M_pattern(std::move(__pattern))
    { }

    template<input_range _Range>
      requires constructible_from<_Vp, views::all_t<_Range>>
	&& constructible_from<_Pattern, single_view<range_value_t<_InnerRange>>>
    constexpr
    join_with_view(_Range&& __r, range_value_t<_InnerRange> __e)
    : _M_base(views::all(std::forward<_Range>(__r))),
      _M_pattern(views::single(std::move(__e)))
    { }

    constexpr _Vp
    base() const& requires copy_constructible<_Vp>
    { return _M_base; }

    constexpr _Vp
    base() &&
    { return std::move(_M_base); }

    constexpr auto
    begin()
    {
      if constexpr (forward_range<_Vp>)
	{
	  constexpr bool __use_const = is_reference_v<_InnerRange>
	    && __simple_view<_Vp> && __simple_view<_Pattern>;
	  return _Iterator<__use_const>{*this, ranges::begin(_M_base)};
	}
      else
	{
	  _M_outer_it.__emplace(ranges::begin(_M_base));
	  return _Iterator<false>{*this};
	}
    }

    constexpr auto
    begin() const
      requires forward_range<const _Vp>
	&& forward_range<const _Pattern>
	&& is_reference_v<range_reference_t<const _Vp>>
	&& input_range<range_reference_t<const _Vp>>
    { return _Iterator<true>{*this, ranges::begin(_M_base)}; }

    constexpr auto
    end()
    {
      constexpr bool __use_const
	= __simple_view<_Vp> && __simple_view<_Pattern>;
      if constexpr (is_reference_v<_InnerRange>
		    && forward_range<_Vp> && common_range<_Vp>
		    && forward_range<_InnerRange> && common_range<_InnerRange>)
        return _Iterator<__use_const>{*this, ranges::end(_M_base)};
      else
        return _Sentinel<__use_const>{*this};
    }

    constexpr auto
    end() const
      requires forward_range<const _Vp>
	&& forward_range<const _Pattern>
	&& is_reference_v<range_reference_t<const _Vp>>
	&& input_range<range_reference_t<const _Vp>>
    {
      using _InnerConstRange = range_reference_t<const _Vp>;
      if constexpr (forward_range<_InnerConstRange>
		    && common_range<const _Vp>
		    && common_range<_InnerConstRange>)
        return _Iterator<true>{*this, ranges::end(_M_base)};
      else
        return _Sentinel<true>{*this};
    }
  };

  template<typename _Range, typename _Pattern>
    join_with_view(_Range&&, _Pattern&&)
      -> join_with_view<views::all_t<_Range>, views::all_t<_Pattern>>;

  template<input_range _Range>
    join_with_view(_Range&&, range_value_t<range_reference_t<_Range>>)
      -> join_with_view<views::all_t<_Range>,
			single_view<range_value_t<range_reference_t<_Range>>>>;

  template<input_range _Vp, forward_range _Pattern>
    requires view<_Vp> && view<_Pattern>
      && input_range<range_reference_t<_Vp>>
      && __compatible_joinable_ranges<range_reference_t<_Vp>, _Pattern>
  template<bool _Const>
  class join_with_view<_Vp, _Pattern>::_Iterator : public __iter_cat<_Const>
  {
    using _Parent = __maybe_const<_Const, join_with_view>;
    using _Base = join_with_view::_Base<_Const>;
    using _InnerBase = join_with_view::_InnerBase<_Const>;
    using _PatternBase = join_with_view::_PatternBase<_Const>;

    using _OuterIter = join_with_view::_OuterIter<_Const>;
    using _InnerIter = join_with_view::_InnerIter<_Const>;
    using _PatternIter = join_with_view::_PatternIter<_Const>;

    static constexpr bool _S_ref_is_glvalue = join_with_view::_S_ref_is_glvalue<_Const>;

    _Parent* _M_parent = nullptr;
    [[no_unique_address]]
      __maybe_present<forward_range<_Base>, _OuterIter> _M_outer_it;
    variant<_PatternIter, _InnerIter> _M_inner_it;

    constexpr _OuterIter&
    _M_get_outer()
    {
      if constexpr (forward_range<_Base>)
	return _M_outer_it;
      else
	return *_M_parent->_M_outer_it;
    }

    constexpr const _OuterIter&
    _M_get_outer() const
    {
      if constexpr (forward_range<_Base>)
	return _M_outer_it;
      else
	return *_M_parent->_M_outer_it;
    }

    constexpr
    _Iterator(_Parent& __parent, _OuterIter __outer)
      requires forward_range<_Base>
    : _M_parent(std::addressof(__parent)), _M_outer_it(std::move(__outer))
    {
      if (_M_get_outer() != ranges::end(_M_parent->_M_base))
	{
	  auto&& __inner = _M_update_inner();
	  _M_inner_it.template emplace<1>(ranges::begin(__inner));
	  _M_satisfy();
	}
    }

    constexpr
    _Iterator(_Parent& __parent)
      requires (!forward_range<_Base>)
    : _M_parent(std::addressof(__parent))
    {
      if (_M_get_outer() != ranges::end(_M_parent->_M_base))
	{
	  auto&& __inner = _M_update_inner();
	  _M_inner_it.template emplace<1>(ranges::begin(__inner));
	  _M_satisfy();
	}
    }

    constexpr auto&
    _M_update_inner()
    {
      _OuterIter& __outer = _M_get_outer();
      if constexpr (_S_ref_is_glvalue)
	return __as_lvalue(*__outer);
      else
	return _M_parent->_M_inner.__emplace_from([&] { return *__outer; });
    }

    constexpr auto&
    _M_get_inner()
    {
      if constexpr (_S_ref_is_glvalue)
	return __as_lvalue(*_M_get_outer());
      else
	return *_M_parent->_M_inner;
    }

    constexpr void
    _M_satisfy()
    {
      while (true)
	{
	  if (_M_inner_it.index() == 0)
	    {
	      if (std::get<0>(_M_inner_it) != ranges::end(_M_parent->_M_pattern))
		break;

	      auto&& __inner = _M_update_inner();
	      _M_inner_it.template emplace<1>(ranges::begin(__inner));
	    }
	  else
	    {
	      auto&& __inner = _M_get_inner();
	      if (std::get<1>(_M_inner_it) != ranges::end(__inner))
		break;

	      if (++_M_get_outer() == ranges::end(_M_parent->_M_base))
		{
		  if constexpr (_S_ref_is_glvalue)
		    _M_inner_it.template emplace<0>();
		  break;
		}

	      _M_inner_it.template emplace<0>(ranges::begin(_M_parent->_M_pattern));
	    }
	}
    }

    static auto
    _S_iter_concept()
    {
      if constexpr (_S_ref_is_glvalue
		    && bidirectional_range<_Base>
		    && __bidirectional_common<_InnerBase>
		    && __bidirectional_common<_PatternBase>)
	return bidirectional_iterator_tag{};
      else if constexpr (_S_ref_is_glvalue
			 && forward_range<_Base>
			 && forward_range<_InnerBase>)
	return forward_iterator_tag{};
      else
	return input_iterator_tag{};
    }

    friend join_with_view;

  public:
    using iterator_concept = decltype(_S_iter_concept());
    // iterator_category defined in join_with_view::__iter_cat
    using value_type = common_type_t<iter_value_t<_InnerIter>,
				     iter_value_t<_PatternIter>>;
    using difference_type = common_type_t<iter_difference_t<_OuterIter>,
					  iter_difference_t<_InnerIter>,
					  iter_difference_t<_PatternIter>>;

    _Iterator() = default;

    constexpr
    _Iterator(_Iterator<!_Const> __i)
      requires _Const
	&& convertible_to<iterator_t<_Vp>, _OuterIter>
	&& convertible_to<iterator_t<_InnerRange>, _InnerIter>
	&& convertible_to<iterator_t<_Pattern>, _PatternIter>
    : _M_parent(__i._M_parent),
      _M_outer_it(std::move(__i._M_outer_it))
    {
      if (__i._M_inner_it.index() == 0)
	_M_inner_it.template emplace<0>(std::get<0>(std::move(__i._M_inner_it)));
      else
	_M_inner_it.template emplace<1>(std::get<1>(std::move(__i._M_inner_it)));
    }

    constexpr common_reference_t<iter_reference_t<_InnerIter>,
			         iter_reference_t<_PatternIter>>
    operator*() const
    {
      if (_M_inner_it.index() == 0)
	return *std::get<0>(_M_inner_it);
      else
	return *std::get<1>(_M_inner_it);
    }

    constexpr _Iterator&
    operator++()
    {
      if (_M_inner_it.index() == 0)
	++std::get<0>(_M_inner_it);
      else
	++std::get<1>(_M_inner_it);
      _M_satisfy();
      return *this;
    }

    constexpr void
    operator++(int)
    { ++*this; }

    constexpr _Iterator
    operator++(int)
      requires _S_ref_is_glvalue
	&& forward_iterator<_OuterIter> && forward_iterator<_InnerIter>
    {
      _Iterator __tmp = *this;
      ++*this;
      return __tmp;
    }

    constexpr _Iterator&
    operator--()
      requires _S_ref_is_glvalue
	&& bidirectional_range<_Base>
	&& __bidirectional_common<_InnerBase>
	&& __bidirectional_common<_PatternBase>
    {
      if (_M_outer_it == ranges::end(_M_parent->_M_base))
	{
	  auto&& __inner = *--_M_outer_it;
	  _M_inner_it.template emplace<1>(ranges::end(__inner));
	}

      while (true)
	{
	  if (_M_inner_it.index() == 0)
	    {
	      auto& __it = std::get<0>(_M_inner_it);
	      if (__it == ranges::begin(_M_parent->_M_pattern))
		{
		  auto&& __inner = *--_M_outer_it;
		  _M_inner_it.template emplace<1>(ranges::end(__inner));
		}
	      else
		break;
	    }
	  else
	    {
	      auto& __it = std::get<1>(_M_inner_it);
	      auto&& __inner = *_M_outer_it;
	      if (__it == ranges::begin(__inner))
		_M_inner_it.template emplace<0>(ranges::end(_M_parent->_M_pattern));
	      else
		break;
	    }
	}

      if (_M_inner_it.index() == 0)
	--std::get<0>(_M_inner_it);
      else
	--std::get<1>(_M_inner_it);
      return *this;
    }

    constexpr _Iterator
    operator--(int)
      requires _S_ref_is_glvalue && bidirectional_range<_Base>
	&& __bidirectional_common<_InnerBase>
	&& __bidirectional_common<_PatternBase>
    {
      _Iterator __tmp = *this;
      --*this;
      return __tmp;
    }

    friend constexpr bool
    operator==(const _Iterator& __x, const _Iterator& __y)
      requires _S_ref_is_glvalue
	&& forward_range<_Base> && equality_comparable<_InnerIter>
    { return __x._M_outer_it == __y._M_outer_it && __x._M_inner_it ==__y._M_inner_it; }

    friend constexpr common_reference_t<iter_rvalue_reference_t<_InnerIter>,
					iter_rvalue_reference_t<_PatternIter>>
    iter_move(const _Iterator& __x)
    {
      if (__x._M_inner_it.index() == 0)
	return ranges::iter_move(std::get<0>(__x._M_inner_it));
      else
	return ranges::iter_move(std::get<1>(__x._M_inner_it));
    }

    friend constexpr void
    iter_swap(const _Iterator& __x, const _Iterator& __y)
      requires indirectly_swappable<_InnerIter, _PatternIter>
    {
      if (__x._M_inner_it.index() == 0)
	{
	  if (__y._M_inner_it.index() == 0)
	    ranges::iter_swap(std::get<0>(__x._M_inner_it), std::get<0>(__y._M_inner_it));
	  else
	    ranges::iter_swap(std::get<0>(__x._M_inner_it), std::get<1>(__y._M_inner_it));
	}
      else
	{
	  if (__y._M_inner_it.index() == 0)
	    ranges::iter_swap(std::get<1>(__x._M_inner_it), std::get<0>(__y._M_inner_it));
	  else
	    ranges::iter_swap(std::get<1>(__x._M_inner_it), std::get<1>(__y._M_inner_it));
	}
    }
  };

  template<input_range _Vp, forward_range _Pattern>
    requires view<_Vp> && view<_Pattern>
      && input_range<range_reference_t<_Vp>>
      && __compatible_joinable_ranges<range_reference_t<_Vp>, _Pattern>
  template<bool _Const>
  class join_with_view<_Vp, _Pattern>::_Sentinel
  {
    using _Parent = __maybe_const<_Const, join_with_view>;
    using _Base = join_with_view::_Base<_Const>;

    sentinel_t<_Base> _M_end = sentinel_t<_Base>();

    constexpr explicit
    _Sentinel(_Parent& __parent)
    : _M_end(ranges::end(__parent._M_base))
    { }

    friend join_with_view;

  public:
    _Sentinel() = default;

    constexpr
    _Sentinel(_Sentinel<!_Const> __s)
      requires _Const && convertible_to<sentinel_t<_Vp>, sentinel_t<_Base>>
    : _M_end(std::move(__s._M_end))
    { }

    template<bool _OtherConst>
      requires sentinel_for<sentinel_t<_Base>,
			    iterator_t<__maybe_const<_OtherConst, _Vp>>>
    friend constexpr bool
    operator==(const _Iterator<_OtherConst>& __x, const _Sentinel& __y)
    { return __x._M_get_outer() == __y._M_end; }
  };

  namespace views
  {
      template<typename _Range, typename _Pattern>
	concept __can_join_with_view
	  = requires { join_with_view(std::declval<_Range>(), std::declval<_Pattern>()); };

    struct _JoinWith : __range_adaptor_closure<_JoinWith>
    {
      template<viewable_range _Range, typename _Pattern>
	requires __can_join_with_view<_Range, _Pattern>
	constexpr auto
	operator() [[nodiscard]] (_Range&& __r, _Pattern&& __f) const
	{
	  return join_with_view(std::forward<_Range>(__r), std::forward<_Pattern>(__f));
	}

      template<typename _Pattern>
  constexpr auto
  operator() [[nodiscard]] (_Pattern&& __f) const
  {
    return __range_adaptor_closure_t(std::__bind_back(*this, std::forward<_Pattern>(__f)));
  }


      static constexpr int _S_arity = 2;
      template<typename _Pattern>
	static constexpr bool _S_has_simple_extra_args
	 // = _LazySplit::_S_has_simple_extra_args<_Pattern>;
      = true;
    };

    inline constexpr _JoinWith join_with;
  } // namespace views
    


} // namespace range
} // namespace __1
} // namespace std