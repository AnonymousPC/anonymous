#pragma once


template < class type, int dim >
class array_line
    extends public array     <type,dim>,
            public array_algo<array_line<type,dim>,type,typename array<type,dim>::iterate_type,dim>
{
    public: // Typedef
        using  value_type     = typename array<type,dim>::value_type;
        using  iterate_type   = typename array<type,dim>::iterate_type;
        using  iterator       = typename array<type,dim>::iterator;
        using  const_iterator = typename array<type,dim>::const_iterator;
        using  base           = array<type,dim>;
        using  array_algo     = array_algo<array_line<type,dim>,type,typename array<type,dim>::iterate_type,dim>;
        struct array_tag { };

    public: // Core
        using array<type,dim>::array;
        constexpr array_line ( ) = default;
        constexpr array_line ( const array<type,dim>&  );
        constexpr array_line (       array<type,dim>&& );
        constexpr array_line& operator = ( const array<type,dim>&  );
        constexpr array_line& operator = (       array<type,dim>&& );

    public: // Interface
        using array<type,dim>::row,
              array<type,dim>::size,
              array<type,dim>::empty,
              array<type,dim>::begin,
              array<type,dim>::end,
              array<type,dim>::operator[],
              array<type,dim>::reshape,
              array<type,dim>::flatten,
              array<type,dim>::as_type;
        constexpr void resize ( ) = delete;

    public: // Algo
        using array_algo::dimension,
              array_algo::shape,
              array_algo::static_shape,
              array_algo::inplace_shape,
              array_algo::tuple_shape,

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

#include "array_line.ipp"