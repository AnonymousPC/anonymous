#pragma once

template < class array_view_type >
class array_view_iterator
{
    private: // Data
        array_view_type* arr_ptr = nullptr;
        int              pos     = 0;

    public: // Typedef. Does not use std::iterator_traits, as the array_view does not defined iterator itself.
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = array_view_type::iterate_type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = value_type*;
        using reference         = value_type&;

    private: // Host
        constexpr array_view_type& host ( ) const;

    public: // Core
        constexpr array_view_iterator ( ) = default;
        constexpr array_view_iterator ( array_view_type&, int );
        constexpr array_view_iterator ( const array_view_iterator& ) = default;
        constexpr array_view_iterator& operator = ( const array_view_iterator& ); // Checks arr must be same in debug mode.

    public: // Operator
        constexpr decltype(auto)       operator *   ( )                            const;
        constexpr decltype(auto)       operator ->  ( )                            const;
        constexpr decltype(auto)       operator []  ( int )                        const;

        constexpr bool                 operator ==  ( const array_view_iterator& ) const;
        constexpr std::strong_ordering operator <=> ( const array_view_iterator& ) const;

        constexpr array_view_iterator  operator  +  ( int )                        const;
        constexpr array_view_iterator  operator  -  ( int )                        const;
        constexpr difference_type      operator  -  ( const array_view_iterator& ) const;

        constexpr array_view_iterator& operator ++  ( );
        constexpr array_view_iterator  operator ++  ( int );
        constexpr array_view_iterator& operator --  ( );
        constexpr array_view_iterator  operator --  ( int );
};

template < class array_view_type >
class array_view_const_iterator
{
    private: // Data
        const array_view_type* arr_ptr = nullptr;
        int                    pos     = 0;

    public: // Typedef. Does not use std::iterator_traits, as the array_view does not defined const_iterator itself.
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = array_view_type::iterate_type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const value_type*;
        using reference         = const value_type&;

    private: // Host
        constexpr const array_view_type& host ( ) const;

    public: // Core
        constexpr array_view_const_iterator ( ) = default;
        constexpr array_view_const_iterator ( const array_view_type&, int );
        constexpr array_view_const_iterator ( const array_view_const_iterator& ) = default;
        constexpr array_view_const_iterator& operator = ( const array_view_const_iterator& ); // Checks arr must be same in debug mode.

    public: // Operator
        constexpr decltype(auto)             operator *   ( )                                  const;
        constexpr decltype(auto)             operator ->  ( )                                  const;
        constexpr decltype(auto)             operator []  ( int )                              const;

        constexpr bool                       operator ==  ( const array_view_const_iterator& ) const;
        constexpr std::strong_ordering       operator <=> ( const array_view_const_iterator& ) const;

        constexpr array_view_const_iterator  operator  +  ( int )                              const;
        constexpr array_view_const_iterator  operator  -  ( int )                              const;
        constexpr difference_type            operator  -  ( const array_view_const_iterator& ) const;

        constexpr array_view_const_iterator& operator ++  ( );
        constexpr array_view_const_iterator  operator ++  ( int );
        constexpr array_view_const_iterator& operator --  ( );
        constexpr array_view_const_iterator  operator --  ( int );
};



#include "array_view_iterator.ipp"