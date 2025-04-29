template < class... types >
constexpr tuple<types...>::tuple ( types... t )
    requires ( sizeof...(types) >= 1 )
    extends std::tuple<types...> ( std::move(t)... )
{

}

template < class... types >
template < class... types2 >
constexpr tuple<types...>::tuple ( const tuple<types2...>& cvt )
    requires ( convertible_to<types2,types> and ... )
    extends std::tuple<types...> ( static_cast<const std::tuple<types2...>&>(cvt) )
{

}

template < class... types >
template < class... types2 >
constexpr tuple<types...>::tuple ( const tuple<types2...>& cvt )
    requires ( constructible_to<types2,types> and ... )
    extends std::tuple<types...> ( static_cast<const std::tuple<types2...>&>(cvt) )
{

}

template < class... types >
template < int index >
constexpr tuple<types...>::template reference<index> tuple<types...>::value ( )
    requires ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) )
{
    if constexpr ( index > 0 )
        return std::get<index-1>(static_cast<std::tuple<types...>&>(self));
    else
        return std::get<index+sizeof...(types)>(static_cast<std::tuple<types...>&>(self));
}

template < class... types >
template < int index >
constexpr tuple<types...>::template const_reference<index> tuple<types...>::value ( ) const
    requires ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) )
{
    if constexpr ( index > 0 )
        return std::get<index-1>(static_cast<const std::tuple<types...>&>(self));
    else
        return std::get<index+sizeof...(types)>(static_cast<const std::tuple<types...>&>(self));
}