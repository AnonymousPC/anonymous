#pragma once

template < class... types >
constexpr cpu::tuple<types...>::tuple ( types... t )
    extends std::tuple<types...>(std::move(t)...)
{

}

template < class... types >
constexpr int cpu::tuple<types...>::size ( )
{
    return sizeof...(types);
}

template < class... types >
template < int index >
constexpr auto& cpu::tuple<types...>::value ( )
    requires ( index >= -size() and index <= -1 ) or ( index >= 1 and index <= size() )
{
    if constexpr ( index > 0 )
        return std::get<index-1>(static_cast<std::tuple<types...>&>(self));
    else
        return std::get<index+size()>(static_cast<std::tuple<types...>&>(self));
}

template < class... types >
template < int index >
constexpr const auto& cpu::tuple<types...>::value ( ) const
    requires ( index >= -size() and index <= -1 ) or ( index >= 1 and index <= size() )
{
    if constexpr ( index > 0 )
        return std::get<index-1>(static_cast<const std::tuple<types...>&>(self));
    else
        return std::get<index+size()>(static_cast<const std::tuple<types...>&>(self));
}