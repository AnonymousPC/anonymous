#pragma once

namespace aux
{
    template < class container_type, class type2 >
    struct array_type_view_iterate_type;

    template < class >
    struct is_array_type_view;
}

template < class container_type, class type2 >
class array_type_view
    extends public array_algo<array_type_view<container_type,type2>,
                              type2,
                              typename aux::array_type_view_iterate_type<container_type,type2>::type, // What??
                              container_type::dimension()>
{
    private: // Precondition
        static_assert ( std::is_convertible<typename container_type::value_type,type2>::value );
        static_assert ( not aux::is_array_type_view<container_type>::value, "chained as_type is deprecated. e.x. float->int->float == float brings unexpected results" );

    private: // Data
        container_type& arr;

    public: // Typedef
        using  value_type = type2;
        using  iterate_type = aux::array_type_view_iterate_type<container_type,type2>::type;
     // class  base;
        class  iterator;
        class  const_iterator;
        using  array_algo = array_algo<array_type_view,type2,typename aux::array_type_view_iterate_type<container_type,type2>::type,container_type::dimension()>;
        struct array_tag { };

    public: // Friend
        template < class type3, class type4 >
        friend class ap::array_type_view;
        template < class type3, class type4, class type5, int type6 >
        friend class ap::array_algo;
        friend container_type;

    private: // Host
        constexpr       container_type& host ( );
        constexpr const container_type& host ( ) const;

    private: // Constructor
        constexpr array_type_view ( container_type& );

    public: // Core
        constexpr array_type_view             ( const array_type_view& ) = default;
        constexpr array_type_view& operator = ( const array_type_view& ) = delete;

    public: // Interface
        constexpr int            row         ( )     const requires ( container_type::dimension() >= 2 );
        constexpr int            column      ( )     const requires ( container_type::dimension() == 2 );
        constexpr int            size        ( )     const;
        constexpr bool           empty       ( )     const;
        constexpr iterator       begin       ( );
        constexpr const_iterator begin       ( )     const;
        constexpr iterator       end         ( );
        constexpr const_iterator end         ( )     const;
        constexpr auto           operator [] ( int );
        constexpr const auto     operator [] ( int ) const;

    public: // Views
        using array_algo::operator[],
              array_algo::reshape,
              array_algo::flatten;
};


template < class container_type, class type2 >
class array_type_view<container_type,type2>::iterator
{
    public: // Typedef
        using iterator_category = std::iterator_traits<typename container_type::iterator>::iterator_category;
        using value_type        = array_type_view<container_type,type2>::iterate_type;
        using difference_type   = std::iterator_traits<typename container_type::iterator>::difference_type;
     // using pointer           = what;
     // using reference         = what;

    private: // Data
        container_type::iterator ptr;

    public: // Interface
        constexpr iterator ( container_type::iterator );

        constexpr auto                 operator *   ( )                 const;
     // constexpr auto                 operator ->  ( )                 const;

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

template < class container_type, class type2 >
class array_type_view<container_type,type2>::const_iterator
{
    public: // Typedef
        using iterator_category = std::iterator_traits<typename container_type::const_iterator>::iterator_category;
        using value_type        = array_type_view<container_type,type2>::iterate_type;
        using difference_type   = std::iterator_traits<typename container_type::const_iterator>::difference_type;
     // using pointer           = what;
     // using reference         = what;

    private: // Data
        container_type::const_iterator ptr;

    public: // Interface
        constexpr const_iterator ( container_type::const_iterator );

        constexpr const auto           operator *   ( )                 const;
     // constexpr const auto           operator ->  ( )                 const;

        constexpr bool                 operator ==  ( const const_iterator& ) const;
        constexpr std::strong_ordering operator <=> ( const const_iterator& ) const;

        constexpr const_iterator       operator  +  ( int )             const;
        constexpr const_iterator       operator  -  ( int )             const;
        constexpr difference_type      operator  -  ( const const_iterator& ) const;

        constexpr const_iterator&      operator ++  ( );
        constexpr const_iterator       operator ++  ( int );
        constexpr const_iterator&      operator --  ( );
        constexpr const_iterator       operator --  ( int );
};

#include "array_type_view.ipp"