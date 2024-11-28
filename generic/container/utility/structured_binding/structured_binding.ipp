#pragma once

/// Pair

template < ap::pair_type pair >
struct std::tuple_size<pair>
{
    constexpr static const int value = 2;
};

template < size_t index,ap::pair_type pair >
    requires ( index == 0 or index == 1 )
struct std::tuple_element<index,pair>
{
    using type = std::conditional<index==0,typename pair::key_type,typename pair::value_type>::type;
};

template < int index, ap::pair_type pair >
    requires ( index == 0 or index == 1 )
constexpr decltype(auto) ap::get ( pair& p )
{
    if constexpr ( index == 0 )
        return p.key();
    else
        return p.value();
}

template < int index, ap::pair_type pair >
    requires ( index == 0 or index == 1 )
constexpr decltype(auto) ap::get ( const pair& p )
{
    if constexpr ( index == 0 )
        return p.key();
    else
        return p.value();
}

template < int index, ap::pair_type pair >
    requires ( index == 0 or index == 1 )
constexpr decltype(auto) ap::get ( pair&& p )
{
    if constexpr ( index == 0 )
        return std::move ( p.key() );
    else
        return std::move ( p.value() );
}




/// Tuple

template < ap::tuple_type tuple >
struct std::tuple_size<tuple>
{
    constexpr static const int value = tuple::size();
};

template < size_t index, ap::tuple_type tuple >
    requires ( index >= 0 and index <= tuple::size() - 1 )
struct std::tuple_element<index,tuple>
{
    using type = typename tuple::value_type<index+1>;
};

template < int index, ap::tuple_type tuple >
    requires ( index >= 0 and index <= tuple::size() - 1 )
constexpr decltype(auto) ap::get ( tuple& t )
{
    return t[ap::constexpr_index<index+1>()];
}

template < int index, ap::tuple_type tuple >
    requires ( index >= 0 and index <= tuple::size() - 1 )
constexpr decltype(auto) ap::get ( const tuple& t )
{
    return t[ap::constexpr_index<index+1>()];
}

template < int index, ap::tuple_type tuple >
    requires ( index >= 0 and index <= tuple::size() - 1 )
constexpr decltype(auto) ap::get ( tuple&& t )
{
    return std::move ( t[ap::constexpr_index<index+1>()] );
}