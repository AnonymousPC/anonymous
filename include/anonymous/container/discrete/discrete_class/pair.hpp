#pragma once

template < class type1, class type2 >
class pair
    extends public std::pair<type1,type2>
{
    public: // Typedef
        using  key_type   = type1;
        using  value_type = type2;
        struct pair_tag { };

    public: // Core
        constexpr pair ( ) = default;         
        constexpr pair ( type1, type2 );

    public: // Conversion
        template < class type3, class type4 > constexpr pair ( const pair<type3,type4>& ) requires convertible_to<type3,type1> and convertible_to<type4,type2>; 

    public: // Member
        constexpr       type1& key   ( );
        constexpr const type1& key   ( ) const;
        constexpr       type2& value ( );
        constexpr const type2& value ( ) const;
};

#include "pair.cpp"