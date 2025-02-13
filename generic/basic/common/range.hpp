#pragma once

/** Some notes:
  * Category 2 types of range by minusable<type> instead of
  * initializer ways avoids crashes below:
  *
  * for ( float i in range ( 1.0, 2.5 ) ) ...;
  *
  * In initializer category mode, here decltype(range::step) == int, and
  * second scope in ( auto iter = range.begin(), "iter != range.end()" )
  * calls iter -> data != range.end() -> data instead of operator <=. Thus,
  * an unexpected infinity for scope occured.
  */


template < class type >
class range
{
    private: // Precondition    
        static_assert ( number_type<type> );

    public: // Typedef
        using value_type     = type;
        class const_iterator;
        using iterator       = const_iterator;

    private: // Range
        value_type low  = type();
        value_type high = type();
        value_type step = 1;

    public: // Constructor
        constexpr range ( value_type )                             requires int_type<type>;
        constexpr range ( value_type, value_type, value_type = 1 );

    public: // Conversion
        template < class type2 > constexpr range ( range<type2> )  requires ( int_type<type> and int_type<type2> ) or ( float_type<type> and float_type<type2> );

    public: // Member
        constexpr const_iterator begin ( ) const;
        constexpr const_iterator end   ( ) const;
        constexpr int            size  ( ) const;

    public: // Friend
        template < class type2 > friend class range;
};

#include "range.ipp"
