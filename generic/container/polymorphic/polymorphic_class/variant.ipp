#pragma once

/// Auxiliary

namespace detail
{
    template < class type >
    constexpr bool all_different<type> = true;

    template < class type, class... types >
    constexpr bool all_different<type,types...> = not ( same_as<type,types> or ... ) and all_different<types...>;

    template < class input_type, class type >
    constexpr bool all_invocable_and_returns_same_type<input_type,type> = invocable<input_type,type>;

    template < class input_type, class type, class... types >
    constexpr bool all_invocable_and_returns_same_type<input_type,type,types...> = []
    {
        if constexpr ( ( invocable<input_type,type > and ... and invocable<input_type,types> ) )
            return ( same_as<invoke_result<input_type,type>,invoke_result<input_type,types>> and ... );
        else
            return false;
    } ();

    template < class input_type, class... types >
    constexpr int index_of_unique_same_type = [] { static_assert(false, "you need to specialize it"); return false; } ();

    template < class input_type, class type >
    constexpr int index_of_unique_same_type<input_type,type> = same_as<input_type,type> ? 1 otherwise 0;

    template < class input_type, class type, class... types >
    constexpr int index_of_unique_same_type<input_type,type,types...> = same_as<input_type,type>                            ? 1 otherwise
                                                                        index_of_unique_same_type<input_type,types...> == 0 ? 0 otherwise
                                                                                                                              1 + index_of_unique_same_type<input_type,types...>;
    template < class input_type, class... types >
    constexpr int index_of_unique_convertible_type = [] { static_assert(false, "you need to specialize it"); return false; } ();

    template < class input_type, class type >
    constexpr int index_of_unique_convertible_type<input_type,type> = convertible_to<input_type,type> ? 1 otherwise 0;

    template < class input_type, class type, class... types >
    constexpr int index_of_unique_convertible_type<input_type,type,types...> = convertible_to<input_type,type>                            ? 1 otherwise
                                                                               index_of_unique_convertible_type<input_type,types...> == 0 ? 0 otherwise
                                                                                                                                            1 + index_of_unique_convertible_type<input_type,types...>;
    template < class input_type, class... types >
    constexpr int index_of_unique_constructible_type = [] { static_assert(false, "you need to specialize it"); return false; } ();
    
    template < class input_type, class type >
    constexpr int index_of_unique_constructible_type<input_type,type> = constructible_from<type,input_type> ? 1 otherwise 0;

    template < class input_type, class type, class... types >
    constexpr int index_of_unique_constructible_type<input_type,type,types...> = constructible_from<type,input_type>                          ? 1 otherwise
                                                                                 index_of_unique_constructible_type<input_type,types...> == 0 ? 0 otherwise
                                                                                                                                                1 + index_of_unique_constructible_type<input_type,types...>;
}

template < class... types >
constexpr variant<types...>::variant ( auto v )
    requires ( same_as<types,decltype(v)> or ... )
{
    base::template emplace<detail::index_of_unique_same_type<decltype(v),types...>-1>(std::move(v));
}

template < class... types >
constexpr variant<types...>::variant ( auto v )
    requires ( convertible_to<decltype(v),types> or ... ) but ( not ( same_as<types,decltype(v)> or ... ) )
{
    base::template emplace<detail::index_of_unique_convertible_type<decltype(v),types...>-1>(std::move(v));
}

template < class... types >
constexpr variant<types...>::variant ( auto v )
    requires ( constructible_from<types,decltype(v)> or ... ) but ( not ( convertible_to<decltype(v),types> or ... ) )
{
    base::template emplace<detail::index_of_unique_constructible_type<decltype(v),types...>-1>(std::move(v));
}

template < class... types >
constexpr int variant<types...>::index ( ) const
{
    if ( not base::valueless_by_exception() ) [[likely]]
        return base::index() + 1;
    else
        return 0;
}

template < class... types >
constexpr const std::type_info& variant<types...>::type ( ) const
{
    if ( not base::valueless_by_exception() ) [[likely]]
        return *(std::array<const std::type_info*,sizeof...(types)>{&typeid(types)...}[index()-1]);
    else
        return typeid(void);
}

template < class... types >
template < class value_type >
constexpr value_type& variant<types...>::value ( )
    requires ( same_as<types,value_type> or ... )
{
    if ( index() == detail::index_of_unique_same_type<value_type,types...> )
        return std::get<value_type>(static_cast<base&>(self));
    else
        throw type_error("bad variant access: cannot access {}-th type {} in {} (whose type = {}, index = {})", detail::index_of_unique_same_type<value_type,types...>, typeid(value_type), typeid(self), type(), index());
}

template < class... types >
template < class value_type >
constexpr const value_type& variant<types...>::value ( ) const
    requires ( same_as<types,value_type> or ... )
{
    if ( index() == detail::index_of_unique_same_type<value_type,types...> )
        return std::get<value_type>(static_cast<const base&>(self));
    else
        throw type_error("bad variant access: cannot access {}-th type {} in {} (whose type = {}, index = {})", detail::index_of_unique_same_type<value_type,types...>, typeid(value_type), typeid(self), type(), index());
}

template < class... types >
template < int value_index >
constexpr index_type_of<value_index,types...>& variant<types...>::value ( )
    requires ( ( value_index >= -sizeof...(types) and value_index <= -1 ) or ( value_index >= 1 and value_index <= sizeof...(types) ) )
{
    if ( index() == value_index )
        return std::get<value_index-1>(static_cast<base&>(self));
    else
        throw type_error("bad variant access: cannot access {}-th type {} in {} (whose type = {}, index = {})", value_index, typeid(index_type_of<value_index,types...>), typeid(self), type(), index());
}

template < class... types >
template < int value_index >
constexpr const index_type_of<value_index,types...>& variant<types...>::value ( ) const
    requires ( ( value_index >= -sizeof...(types) and value_index <= -1 ) or ( value_index >= 1 and value_index <= sizeof...(types) ) )
{
    if ( index() == value_index )
        return std::get<value_index-1>(static_cast<const base&>(self));
    else
        throw type_error("bad variant access: cannot access {}-th type {} in {} (whose type = {}, index = {})", value_index, typeid(index_type_of<value_index,types...>), typeid(self), type(), index());
}

template < class... types >
constexpr decltype(auto) variant<types...>::visit ( auto&& v )
    requires detail::all_invocable_and_returns_same_type<decltype(v),types...>
{
    return std::visit(std::forward<decltype(v)>(v), static_cast<base&>(self));
}

template < class... types >
constexpr decltype(auto) variant<types...>::visit ( auto&& v ) const
    requires detail::all_invocable_and_returns_same_type<decltype(v),types...>
{
    return std::visit(std::forward<decltype(v)>(v), static_cast<const base&>(self));
}

template < class... types >
constexpr int variant<types...>::size ( )
{
    return sizeof...(types);
}