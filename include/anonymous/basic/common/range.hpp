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

#include "range.cpp"
