template < class... types >
constexpr tuple<types...>::tuple ( types... t )
    requires ( sizeof...(types) >= 1 )
    extends std::tuple<types...>(std::move(t)...)
{

}

template < class... types >
constexpr tuple<types...>::tuple ( const tuple_type auto& cvt )
    requires ( sizeof...(types) >= 1 ) and 
             detail::tuplewise_convertible_to<cvt_type,tuple>
{
    for_constexpr<1,sizeof...(types)>([&] <int index> { self.template value<index>() = cvt.template value<index>(); });
}

template < class... types >
template < int index >
constexpr tuple<types...>::reference<index> tuple<types...>::value ( )
    requires ( index >= -int(sizeof...(types)) and index <= -1 ) or ( index >= 1 and index <= int(sizeof...(types)) )
{
    if constexpr ( index > 0 )
        return std::get<index-1>(static_cast<std::tuple<types...>&>(self));
    else
        return std::get<index+int(sizeof...(types))>(static_cast<std::tuple<types...>&>(self));
}

template < class... types >
template < int index >
constexpr tuple<types...>::const_reference<index> tuple<types...>::value ( ) const
    requires ( index >= -int(sizeof...(types)) and index <= -1 ) or ( index >= 1 and index <= int(sizeof...(types)) )
{
    if constexpr ( index > 0 )
        return std::get<index-1>(static_cast<const std::tuple<types...>&>(self));
    else
        return std::get<index+int(sizeof...(types))>(static_cast<const std::tuple<types...>&>(self));
}