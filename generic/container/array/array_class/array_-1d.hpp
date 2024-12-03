#pragma once


template < class type >
class array<type,-1>
    extends public array<type,1>,
            public array_algo<array<type,-1>,type>
{
    public: // Core
        using array<type>::array;
        using array<type>::size;
        using array<type>::empty;
        using array<type>::begin;
        using array<type>::end;
        constexpr array ( array<type,1> );
        constexpr static int  dimension ( );

    public: // Typedef ( override )
        using array_algo = array_algo<array<type,-1>,type>;
        using base       = array<type,1>;

    public: // Member ( override )
        constexpr       auto& resize      ( int );
        constexpr       auto& operator [] ( int );
        constexpr const auto& operator [] ( int )                   const;
        constexpr       auto  operator [] ( int, int );
        constexpr const auto  operator [] ( int, int )              const;
        constexpr       auto  operator [] ( int, int, int );
        constexpr const auto  operator [] ( int, int, int )         const;
        constexpr       auto  operator [] ( unary_pred<type> auto );
        constexpr const auto  operator [] ( unary_pred<type> auto ) const;

    public: // Algo
        using array_algo::shape,
              array_algo::static_shape,
              array_algo::inplace_shape,
              array_algo::tuple_shape,
              array_algo::reshape,
              array_algo::flatten,

              array_algo::clear,
              array_algo::erase,
              array_algo::insert,
              array_algo::push,
              array_algo::pop,

              array_algo::average,
              array_algo::adjacent_find,
              array_algo::adjacent_where,
              array_algo::all,
              array_algo::contains,
              array_algo::count,
              array_algo::each,
              array_algo::exist,
              array_algo::fill,
              array_algo::generate,
              array_algo::find,
              array_algo::is_partitioned,
              array_algo::is_sorted,
              array_algo::max,
              array_algo::min,
              array_algo::next_permutation,
              array_algo::none,
              array_algo::partition,
              array_algo::prev_permutation,
              array_algo::product,
              array_algo::remove,
              array_algo::replace,
              array_algo::reverse,
              array_algo::right_adjacent_find,
              array_algo::right_find,
              array_algo::rotate,
              array_algo::sample,
              array_algo::shuffle,
              array_algo::sort,
              array_algo::sum,
              array_algo::transform,
              array_algo::unique,
              array_algo::where;
};


#include "array_-1d.ipp"