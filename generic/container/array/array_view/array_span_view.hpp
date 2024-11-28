#pragma once

template < class container_type >
class array_span_view
    extends public array_algo<array_span_view<container_type>,
                              typename container_type::value_type,
                              typename container_type::iterate_type,
                              container_type::dimension()>
{
    private: // Data
        using coor_type = array_coordinate<container_type::dimension(),range<int,true>>;

        container_type& arr;
        coor_type       idx = coor_type();

    public: // Typedef
        using  value_type     = container_type::value_type;
        using  iterate_type   = std::conditional<container_type::dimension()>=2,array_span_view<typename container_type::iterate_type>,value_type>::type;
        class  base;
        using  iterator       = array_view_iterator      <array_span_view>;
        using  const_iterator = array_view_const_iterator<array_span_view>;
        using  array_algo     = array_algo<array_span_view,typename container_type::value_type,typename container_type::iterate_type,container_type::dimension()>;
        struct array_tag { };

    private: // Core
        template < class type2 >
        friend class ap::array_span_view;
        template < class type2, class type3, class type4, int type5 >
        friend class ap::array_algo;
        friend container_type;

    private: // Host
        constexpr       container_type& host ( );
        constexpr const container_type& host ( ) const;

    private: // Constructor. Span_view is the only view which redistribute the line of container_type in every extent, so it should support right_value ones.
        constexpr array_span_view ( container_type&, auto... cn ) requires ( std::convertible_to<decltype(cn),pair<int>> and ... and ( sizeof...(cn) == container_type::dimension() ) );
        constexpr array_span_view ( container_type&, coor_type ); // Only for internal use.

    public: // Core
        constexpr array_span_view& operator = ( const array_span_view&  ) requires std::copyable<value_type>; // Must be written, or the compiler will auto-summon a wrong one.
        constexpr array_span_view& operator = ( const container_type&   ) requires std::copyable<value_type>;
        constexpr array_span_view& operator = (       container_type&&  );

    public: // Member
        constexpr       int            row         ( )     const requires ( container_type::dimension() >= 2 );
        constexpr       int            column      ( )     const requires ( container_type::dimension() == 2 );
        constexpr       int            size        ( )     const;
        constexpr       bool           empty       ( )     const;
        constexpr       iterator       begin       ( );
        constexpr       const_iterator begin       ( )     const;
        constexpr       iterator       end         ( );
        constexpr       const_iterator end         ( )     const;
        constexpr       decltype(auto) operator [] ( int )       requires ( container_type::dimension() == 1 );
        constexpr       decltype(auto) operator [] ( int ) const requires ( container_type::dimension() == 1 );
        constexpr       auto           operator [] ( int )       requires ( container_type::dimension() >= 2 );
        constexpr const auto           operator [] ( int ) const requires ( container_type::dimension() >= 2 );

    public: // Views
        using array_algo::operator[],
              array_algo::reshape,
              array_algo::flatten,
              array_algo::as_type;
        constexpr       auto operator [] ( pair<int>, pair<int> )       requires ( container_type::dimension() == 2 );
        constexpr const auto operator [] ( pair<int>, pair<int> ) const requires ( container_type::dimension() == 2 );
};






template < class container_type >
class array_span_view<container_type>::base // Treat ndarray as 1d*(n-1)d array
    extends public array_span_view<container_type>,
            public ap::array_algo<base,typename container_type::value_type,typename container_type::iterate_type,1> // Dimension == 1.
{
    public: // Algo
        using array_span_view = array_span_view<container_type>;
        using array_algo      = ap::array_algo<base,typename container_type::value_type,typename container_type::iterate_type,1>;

        constexpr int size ( ) const { return array_span_view::row(); }
        constexpr int row  ( ) const = delete;

        using array_span_view::empty,
              array_span_view::begin,
              array_span_view::end,
              array_span_view::operator[],
              array_span_view::reshape,
              array_span_view::flatten,
              array_span_view::as_type;

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
              array_algo::find,
              array_algo::generate,
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


/// Templte deduction

template < class type > array_span_view ( type, auto... ) -> array_span_view<type>;


#include "array_span_view.ipp"