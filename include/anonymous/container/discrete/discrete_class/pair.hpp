template < class type1, class type2, class device >
class pair
    extends public device::template pair<type1,type2>
{
    public: // Typedef
        using  key_type              = device::template value_type     <type1>;
        using  key_reference         = device::template reference      <type1>;
        using  const_key_reference   = device::template const_reference<type1>;
        using  value_type            = device::template value_type     <type2>;
        using  value_reference       = device::template reference      <type2>;
        using  const_value_reference = device::template const_reference<type2>;
        using  device_type           = device;
        struct pair_concept { };

    public: // Core
        constexpr pair ( ) = default;         
        constexpr pair ( type1, type2 );

    public: // Conversion 
        template < class type3, class type4, class device2 >          constexpr pair ( const pair<type3,type4,device2>& ) requires convertible_to  <type3,type1> and convertible_to  <type4,type2>;
        template < class type3, class type4, class device2 > explicit constexpr pair ( const pair<type3,type4,device2>& ) requires constructible_to<type3,type1> and constructible_to<type4,type2>;

    public: // Member
        constexpr key_reference         key   ( );
        constexpr const_key_reference   key   ( ) const;
        constexpr value_reference       value ( );
        constexpr const_value_reference value ( ) const;
};

#include "pair.cpp"
