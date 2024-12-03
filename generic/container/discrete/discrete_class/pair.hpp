#pragma once

template < class type1, class type2 >
class pair
{
    public: // Typedef
        using  key_type   = type1;
        using  value_type = type2;
        struct pair_tag { };

    private: // Data
        type1 x = type1();
        type2 y = type2();

    public: // Core
        constexpr  pair ( )                            requires std::default_initializable<remove_cv<type1>> and std::default_initializable<remove_cv<type2>> = default; // Remove_cv is essential, as std::default_initializable<const int> == false (require "new const int()").
        constexpr  pair ( type1, type2 );
        constexpr  pair ( const pair&  )             = default;
        constexpr  pair (       pair&& )             = default;
        constexpr ~pair ( )                          = default;
        constexpr  pair& operator = ( const pair&  ) = default;
        constexpr  pair& operator = (       pair&& ) = default;
        constexpr        type1& key   ( );
        constexpr  const type1& key   ( ) const;
        constexpr        type2& value ( );
        constexpr  const type2& value ( ) const;

    public: // Conversion
        template < class type3, class type4 > constexpr          pair ( const pair<type3,type4>& ) requires std::convertible_to    <type3,type1> and std::convertible_to    <type4,type2> but ( not std::same_as       <type1,type3> or not std::same_as       <type2,type4> );
        template < class type3, class type4 > constexpr explicit pair ( const pair<type3,type4>& ) requires std::constructible_from<type1,type3> and std::constructible_from<type2,type4> but ( not std::convertible_to<type3,type1> or not std::convertible_to<type4,type2> );

    protected: // For map_pair
        struct map_pair_tag { };
        template < class type3, class type4 > constexpr explicit pair ( map_pair_tag, pair<type3,type4>&& ) requires std::same_as<decay<type1>,decay<type3>> and std::same_as<decay<type2>,decay<type4>>;
};


/// Template deduction

template < class type1, class type2 > pair ( type1, type2 ) -> pair<type1,type2>;



#include "pair.ipp"