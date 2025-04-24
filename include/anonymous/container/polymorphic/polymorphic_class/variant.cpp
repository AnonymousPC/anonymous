template < class... types >
constexpr variant<types...>::variant ( auto v )
    requires ( same_as<types,decltype(v)> or ... )
{
    base::template emplace<detail::find_same_type<decltype(v),types...>-1>(std::move(v));
}

template < class... types >
constexpr variant<types...>::variant ( auto v )
    requires ( convertible_to<decltype(v),types> or ... ) and ( not ( same_as<types,decltype(v)> or ... ) )
{
    base::template emplace<detail::find_convertible_type<decltype(v),types...>-1>(std::move(v));
}

template < class... types >
constexpr variant<types...>::variant ( auto v )
    requires ( constructible_from<types,decltype(v)> or ... ) and ( not ( convertible_to<decltype(v),types> or ... ) )
{
    base::template emplace<detail::find_constructible_type<decltype(v),types...>-1>(std::move(v));
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
        return *(static_array<const std::type_info*,sizeof...(types)>{&typeid(types)...}[index()]);
    else
        return typeid(void);
}

template < class... types >
template < class value_type >
constexpr value_type& variant<types...>::value ( )
    requires ( same_as<types,value_type> or ... )
{
    if ( index() == detail::find_same_type<value_type,types...> ) [[likely]]
        return std::get<value_type>(static_cast<base&>(self));
    else
        throw type_error("bad variant access (with type() = {}, access = {})", type(), typeid(value_type));
}

template < class... types >
template < class value_type >
constexpr const value_type& variant<types...>::value ( ) const
    requires ( same_as<types,value_type> or ... )
{
    if ( index() == detail::find_same_type<value_type,types...> ) [[likely]]
        return std::get<value_type>(static_cast<const base&>(self));
    else
        throw type_error("bad variant access (with type() = {}, access = {})", type(), typeid(value_type));
}

template < class... types >
template < int value_index >
constexpr index_type_of<value_index,types...>& variant<types...>::value ( )
    requires ( ( value_index >= -sizeof...(types) and value_index <= -1 ) or ( value_index >= 1 and value_index <= sizeof...(types) ) )
{
    if ( index() == value_index ) [[likely]]
        return std::get<value_index-1>(static_cast<base&>(self));
    else
        throw type_error("bad variant access (with index() = {}, access = {})", index(), value_index);
}

template < class... types >
template < int value_index >
constexpr const index_type_of<value_index,types...>& variant<types...>::value ( ) const
    requires ( ( value_index >= -sizeof...(types) and value_index <= -1 ) or ( value_index >= 1 and value_index <= sizeof...(types) ) )
{
    if ( index() == value_index )
        return std::get<value_index-1>(static_cast<const base&>(self));
    else
        throw type_error("bad variant access (with index() = {}, access = {})", index(), value_index);
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

template < class... types >
std::ostream& operator << ( std::ostream& left, const variant<types...>& right )
    requires ( printable<types> and ... ) and ( sizeof...(types) >= 1 )
{
    return right.visit([&] (const auto& val) -> std::ostream& { return left << val; });
} 