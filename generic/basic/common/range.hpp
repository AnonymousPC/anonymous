#pragma once
#include "concept.hpp"

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


/// Range (raw: no definition)

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
        constexpr explicit range ( value_type );
        constexpr explicit range ( value_type, value_type, value_type = 1 );

    public: // Member
        constexpr const_iterator begin ( ) const;
        constexpr const_iterator end   ( ) const;
};

#include "range.ipp"
