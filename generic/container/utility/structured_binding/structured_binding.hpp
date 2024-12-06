#pragma once

} // Out from namespace ap


/// Declaration

namespace ap
{
    template < class type > auto get ( type );
}



/// Pair

template < ap::pair_type pair >
struct std::tuple_size<pair>;

template < size_t index, ap::pair_type pair >
    requires ( index == 0 or index == 1 )
struct std::tuple_element<index,pair>;

template < int index, ap::pair_type pair >
    requires ( index == 0 or index == 1 )
constexpr decltype(auto) ap::get ( pair& );

template < int index, ap::pair_type pair >
    requires ( index == 0 or index == 1 )
constexpr decltype(auto) ap::get ( const pair& );

template < int index, ap::pair_type pair >
    requires ( index == 0 or index == 1 )
constexpr decltype(auto) ap::get ( pair&& );




/// Tuple

template < ap::tuple_type tuple >
struct std::tuple_size<tuple>;

template < size_t index, ap::tuple_type tuple >
    requires ( index >= 0 and index <= tuple::size() - 1 )
struct std::tuple_element<index,tuple>;

template < int index, ap::tuple_type tuple >
    requires ( index >= 0 and index <= tuple::size() - 1 )
constexpr decltype(auto) ap::get ( tuple& );

template < int index, ap::tuple_type tuple >
    requires ( index >= 0 and index <= tuple::size() - 1 )
constexpr decltype(auto) ap::get ( const tuple& );

template < int index, ap::tuple_type tuple >
    requires ( index >= 0 and index <= tuple::size() - 1 )
constexpr decltype(auto) ap::get ( tuple&& );


#include "structured_binding.ipp"

namespace ap { // Back into namespace ap
