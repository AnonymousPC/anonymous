#pragma once

template < class type1, class type2 >
class pair
    extends public std::pair<type1,type2>
{
    public: // Traits
        constexpr static int size ( );

    public: // Typedef
        using  key_type   = type1;
        using  value_type = type2;
        struct pair_tag { };

    public: // Core
        constexpr pair ( )                                                                         requires default_initializable<remove_cv<type1>> and default_initializable<remove_cv<type2>> = default; // Remove_cv is essential, as default_initializable<const int> == false (requires "new const int()").
        constexpr pair ( type1, type2 );

    public: // Conversion
        template < class type3, class type4 > constexpr          pair ( const pair<type3,type4>& ) requires convertible_to    <type3,type1> and convertible_to    <type4,type2> but ( not same_as       <type1,type3> or not same_as       <type2,type4> );
        template < class type3, class type4 > constexpr explicit pair ( const pair<type3,type4>& ) requires constructible_from<type1,type3> and constructible_from<type2,type4> but ( not convertible_to<type3,type1> or not convertible_to<type4,type2> );

    public: // Member
        constexpr  decltype(auto) key   ( );
        constexpr  decltype(auto) key   ( ) const;
        constexpr  decltype(auto) value ( );
        constexpr  decltype(auto) value ( ) const;
};

#include "pair.ipp"