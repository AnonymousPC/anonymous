#pragma once

template < class... types >
constexpr tuple<types...>::tuple ( types... t )
    extends std::tuple<types...>(std::move(t)...)
{

}

template < class... types >
template < int index >
constexpr auto& tuple<types...>::value ( )
    requires ( index >= -int(sizeof...(types)) and index <= -1 ) or ( index >= 1 and index <= int(sizeof...(types)) )
{
    if constexpr ( index > 0 )
        return std::get<index-1>(static_cast<std::tuple<types...>&>(self));
    else
        return std::get<index+int(sizeof...(types))>(static_cast<std::tuple<types...>&>(self));
}

template < class... types >
template < int index >
constexpr const auto& tuple<types...>::value ( ) const
    requires ( index >= -int(sizeof...(types)) and index <= -1 ) or ( index >= 1 and index <= int(sizeof...(types)) )
{
    if constexpr ( index > 0 )
        return std::get<index-1>(static_cast<const std::tuple<types...>&>(self));
    else
        return std::get<index+int(sizeof...(types))>(static_cast<const std::tuple<types...>&>(self));
}

template < class... types >
constexpr int tuple<types...>::size ( )
{
    return sizeof...(types);
}