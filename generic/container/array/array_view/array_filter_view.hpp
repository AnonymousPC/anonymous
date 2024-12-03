#pragma once

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
class array_filter_view
    extends public array_algo<array_filter_view<container_type,filter>,
                              typename container_type::value_type,
                              typename container_type::iterate_type,
                              container_type::dimension()>
{
    private: // Data
        container_type& arr;
        filter          filt = filter();

    public: // Typedef
        using  value_type     = container_type::value_type;
        using  iterate_type   = container_type::iterate_type;
        class  base;
        class  iterator;
        class  const_iterator;
        using  array_algo     = array_algo<array_filter_view<container_type,filter>,typename container_type::value_type,typename container_type::iterate_type,container_type::dimension()>;
        struct array_tag { };

    public: // Friend
        template < class type2, unary_pred<typename container_type::iterate_type> type3 >
        friend class ap::array_filter_view;
        template < class type2, class type3, class type4, int type5 >
        friend class ap::array_algo;
        friend container_type;

    private: // Host
        constexpr       container_type& host ( );
        constexpr const container_type& host ( ) const;

    private: // Constructor
        constexpr array_filter_view ( container_type&, filter );

    public: // Core
        constexpr array_filter_view             ( const array_filter_view& ) = default;
        constexpr array_filter_view& operator = ( const array_filter_view& ) requires std::copyable<value_type>; // Must be written, otherwise the compilter will summon one wrong.
        constexpr array_filter_view& operator = ( const container_type&  )   requires std::copyable<value_type>;
        constexpr array_filter_view& operator = (       container_type&& );

    public: // Interface
        constexpr int            row         ( )     const requires ( container_type::dimension() >= 2 ); // O(N).
        constexpr int            size        ( )     const;                                               // O(N).
        constexpr bool           empty       ( )     const;                                               // O(N).
        constexpr iterator       begin       ( );                                                         // O(N), but usually smaller.
        constexpr const_iterator begin       ( )     const;                                               // O(N), but usually smaller.
        constexpr iterator       end         ( );                                                         // O(1).
        constexpr const_iterator end         ( )     const;                                               // O(1).
        constexpr decltype(auto) operator [] ( int );                                                     // O(N).
        constexpr decltype(auto) operator [] ( int ) const;                                               // O(N).

    public: // Views
        using array_algo::operator[],
              array_algo::reshape,
              array_algo::flatten,
              array_algo::as_type;
        constexpr       auto           operator [] ( unary_pred<iterate_type> auto );        // Lazy.
        constexpr const auto           operator [] ( unary_pred<iterate_type> auto )  const; // Lazy.
};


template < class container_type, unary_pred<typename container_type::iterate_type> filter >
class array_filter_view<container_type,filter>::base // Treat ndarray as 1d*(n-1)d array
    extends public array_filter_view<container_type,filter>,
            public ap::array_algo<base,typename container_type::value_type,typename container_type::iterate_type,1> // Dimension == 1.
{
    public: // Algo
        using array_filter_view = array_filter_view<container_type,filter>;
        using array_algo        = ap::array_algo<base,typename container_type::value_type,typename container_type::iterate_type,1>;

        constexpr int size ( ) const { return array_filter_view::row(); }
        constexpr int row  ( ) const = delete;

        using array_filter_view::empty,
              array_filter_view::begin,
              array_filter_view::end,
              array_filter_view::operator[],
              array_filter_view::reshape,
              array_filter_view::flatten,
              array_filter_view::as_type;

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




/// Iterator

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
class array_filter_view<container_type,filter>::iterator
{
    private: // Data
        container_type* arr_ptr  = nullptr;
        const filter*   filt_ptr = nullptr;
        int             pos      = 0;

    private: // Host
        constexpr container_type& host     ( ) const;
        constexpr const filter&   function ( ) const;

    public: // Typedef
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = std::iterator_traits<typename container_type::iterator>::value_type;
        using difference_type   = std::iterator_traits<typename container_type::iterator>::difference_type;
        using pointer           = std::iterator_traits<typename container_type::iterator>::pointer;
        using reference         = std::iterator_traits<typename container_type::iterator>::reference;

    public: // Core
        constexpr iterator ( ) = default;
        constexpr iterator ( container_type&, const filter&, int );

    public: // Operator
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





/// Const_iterator

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
class array_filter_view<container_type,filter>::const_iterator
{
    private: // Data
        const container_type* arr_ptr  = nullptr;
        const filter*         filt_ptr = nullptr;
        int                   pos      = 0;

    private: // Host
        constexpr const container_type& host     ( ) const;
        constexpr const filter&         function ( ) const;

    public: // Typedef
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = std::iterator_traits<typename container_type::const_iterator>::value_type;
        using difference_type   = std::iterator_traits<typename container_type::const_iterator>::difference_type;
        using pointer           = std::iterator_traits<typename container_type::const_iterator>::pointer;
        using reference         = std::iterator_traits<typename container_type::const_iterator>::reference;

    public: // Core
        constexpr const_iterator ( ) = default;
        constexpr const_iterator ( const container_type&, const filter&, int );

    public: // Operator
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




/// Template deduction

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
array_filter_view ( container_type, filter ) -> array_filter_view<container_type,filter>;



#include "array_filter_view.ipp"