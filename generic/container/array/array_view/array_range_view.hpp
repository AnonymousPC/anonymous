#pragma once

template < class container_type, bool continuous >
class array_range_view
    extends public array_algo<array_range_view<container_type,continuous>,
                              typename container_type::value_type,
                              typename container_type::iterate_type,
                              container_type::dimension()>
{
    private: // Data
        container_type&       arr;
        range<int,continuous> idx = range<int,continuous>();

    private: // Typedef
        class iterator_base;
        class const_iterator_base;

    public: // Typedef
        using  value_type     = container_type::value_type;
        using  iterate_type   = container_type::iterate_type;
        class  base;
        using  iterator       = iterator_base::type;
        using  const_iterator = const_iterator_base::type;
        using  array_algo     = array_algo<array_range_view,typename container_type::value_type,typename container_type::iterate_type,container_type::dimension()>;
        struct array_tag { };

    public: // Friend
        template < class type2, bool type3 >
        friend class ap::array_range_view;
        template < class type2, class type3, class type4, int type5 >
        friend class ap::array_algo;
        friend container_type;

    private: // Host
        constexpr       container_type& host ( );
        constexpr const container_type& host ( ) const;

    private: // Constructor
        constexpr array_range_view ( container_type&, int, int )      requires continuous;
        constexpr array_range_view ( container_type&, int, int, int ) requires ( not continuous );

    public: // Core
        constexpr array_range_view             ( const array_range_view& ) = default;
        constexpr array_range_view& operator = ( const array_range_view& ) requires std::copyable<value_type>; // Must be written, or the compiler will auto-summon a wrong one.
        constexpr array_range_view& operator = ( const container_type&   ) requires std::copyable<value_type>;
        constexpr array_range_view& operator = (       container_type&&  );

    public: // Interface
        constexpr int            row         ( )     const requires ( container_type::dimension() >= 2 );
        constexpr int            size        ( )     const;
        constexpr bool           empty       ( )     const;
        constexpr iterator       begin       ( );
        constexpr const_iterator begin       ( )     const;
        constexpr iterator       end         ( );
        constexpr const_iterator end         ( )     const;
        constexpr decltype(auto) operator [] ( int );
        constexpr decltype(auto) operator [] ( int ) const;

    public: // Views
        using array_algo::operator[],
              array_algo::reshape,
              array_algo::flatten,
              array_algo::as_type;
        constexpr       auto operator [] ( int, int );
        constexpr const auto operator [] ( int, int )      const;
        constexpr       auto operator [] ( int, int, int );
        constexpr const auto operator [] ( int, int, int ) const;
};

template < class container_type, bool continuous >
class array_range_view<container_type,continuous>::base // Treat ndarray as 1d*(n-1)d array
    extends public array_range_view<container_type,continuous>,
            public ap::array_algo<base,typename container_type::value_type,typename container_type::iterate_type,1> // Dimension == 1.
{
    public: // Algo
        using array_range_view = array_range_view<container_type,continuous>;
        using array_algo       = ap::array_algo<base,typename container_type::value_type,typename container_type::iterate_type,1>;

        constexpr int size ( ) const { return array_range_view::row(); }
        constexpr int row  ( ) const = delete;

        using array_range_view::empty,
              array_range_view::begin,
              array_range_view::end,
              array_range_view::operator[],
              array_range_view::reshape,
              array_range_view::flatten,
              array_range_view::as_type;

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




/// Class array_range_view::iterator

template < class container_type, bool continuous >
struct array_range_view<container_type,continuous>::iterator_base
{
    class iterator // Candicate.
    {
        public: // Typedef
            using iterator_category = std::conditional<continuous,typename std::iterator_traits<typename container_type::iterator>::iterator_category,std::random_access_iterator_tag>::type;
            using value_type        = std::iterator_traits<typename container_type::iterator>::value_type;
            using difference_type   = std::iterator_traits<typename container_type::iterator>::difference_type;
            using pointer           = std::iterator_traits<typename container_type::iterator>::pointer;
            using reference         = std::iterator_traits<typename container_type::iterator>::reference;

        private: // Data
            container_type::iterator ptr  = typename container_type::iterator();
            int                      step = 0;

        public: // Interface
            constexpr iterator ( );
            constexpr iterator ( container_type::iterator, int );

            constexpr decltype(auto)       operator *   ( )                 const;
            constexpr decltype(auto)       operator ->  ( )                 const;

            constexpr bool                 operator ==  ( const iterator& ) const;
            constexpr std::strong_ordering operator <=> ( const iterator& ) const;

            constexpr iterator             operator  +  ( int )             const;
            constexpr iterator             operator  -  ( int )             const;
            constexpr difference_type      operator  -  ( const iterator& ) const;

            constexpr iterator&            operator ++  ( );
            constexpr iterator             operator ++  ( int );
            constexpr iterator&            operator --  ( );
            constexpr iterator             operator --  ( int );
    };

    using type = std::conditional<continuous,typename container_type::iterator,iterator>::type;
};




/// Class array_range_view::const_iterator

template < class container_type, bool continuous >
struct array_range_view<container_type,continuous>::const_iterator_base
{
    class const_iterator // Candicate
    {
        public: // Typedef
            using iterator_category = std::conditional<continuous,typename std::iterator_traits<typename container_type::const_iterator>::iterator_category,std::random_access_iterator_tag>::type;
            using value_type        = std::iterator_traits<typename container_type::const_iterator>::value_type;
            using difference_type   = std::iterator_traits<typename container_type::const_iterator>::difference_type;
            using pointer           = std::iterator_traits<typename container_type::const_iterator>::pointer;
            using reference         = std::iterator_traits<typename container_type::const_iterator>::reference;

        private: // Data
            container_type::const_iterator ptr  = typename container_type::const_iterator();
            int                            step = 0;

        public: // Interface
            constexpr const_iterator ( );
            constexpr const_iterator ( container_type::const_iterator, int );

            constexpr decltype(auto)       operator *   ( )                       const;
            constexpr decltype(auto)       operator ->  ( )                       const;

            constexpr bool                 operator ==  ( const const_iterator& ) const;
            constexpr std::strong_ordering operator <=> ( const const_iterator& ) const;

            constexpr const_iterator       operator  +  ( int )                   const;
            constexpr const_iterator       operator  -  ( int )                   const;
            constexpr difference_type      operator  -  ( const const_iterator& ) const;

            constexpr const_iterator&      operator ++  ( );
            constexpr const_iterator       operator ++  ( int );
            constexpr const_iterator&      operator --  ( );
            constexpr const_iterator       operator --  ( int );
    };

    using type = std::conditional<continuous,typename container_type::const_iterator,const_iterator>::type;
};



/// Template deduction

template < class container_type >
array_range_view ( container_type, auto, auto ) -> array_range_view<container_type,true>;

template < class container_type >
array_range_view ( container_type, auto, auto, auto ) -> array_range_view<container_type>;


#include "array_range_view.ipp"