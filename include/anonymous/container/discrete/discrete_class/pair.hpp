template < class type1, class type2>
class pair
    extends public std::pair<type1,type2>,
            public structure_interface<pair<type1,type2>,type1,type2>
{
    private: // Base
        using base = std::pair<type1,type2>;

    public: // Typedef
        using key_type              =       type1;
        using key_reference         =       type1&;
        using const_key_reference   = const type1&;
        using value_type            =       type2;
        using value_reference       =       type2&;
        using const_value_reference = const type2&;

    public: // Core
        constexpr pair ( ) = default;         
        constexpr pair ( type1, type2 );

    public: // Conversion 
        template < class type3, class type4 >          constexpr pair ( const pair<type3,type4>& ) requires convertible_to  <type3,type1> and convertible_to  <type4,type2>;
        template < class type3, class type4 > explicit constexpr pair ( const pair<type3,type4>& ) requires constructible_to<type3,type1> and constructible_to<type4,type2>;

    public: // Member
        constexpr key_reference         key   ( );
        constexpr const_key_reference   key   ( ) const;
        constexpr value_reference       value ( );
        constexpr const_value_reference value ( ) const;
};

#include "pair.cpp"
