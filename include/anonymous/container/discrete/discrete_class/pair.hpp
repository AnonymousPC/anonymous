template < class type1, class type2, class device >
class pair
    extends public device::template pair<type1,type2>
{
    private: // Typedef
        using base = device::template pair<type1,type2>;

    public: // Typedef
        using key_type              = device::template value_type     <type1>;
        using key_reference         = device::template reference      <type1>;
        using const_key_reference   = device::template const_reference<type1>;
        using value_type            = device::template value_type     <type2>;
        using value_reference       = device::template reference      <type2>;
        using const_value_reference = device::template const_reference<type2>;

    public: // Core
        constexpr pair ( ) = default;         
        constexpr pair ( type1, type2 );

    public: // Conversion 
        template < class type3, class type4 > constexpr pair ( const pair<type3,type4,device>& ) requires convertible_to<type3,type1> and convertible_to<type4,type2>;
        constexpr pair ( const pair_type auto )

    public: // Member
        constexpr key_reference         key   ( );
        constexpr const_key_reference   key   ( ) const;
        constexpr value_reference       value ( );
        constexpr const_value_reference value ( ) const;
};

template < class type1, class type2, class device >                           constexpr            std::ostream& operator <<  (       std::ostream&    left, const pair<type1,type2,device>& ) requires printable      <right_key_type>               and printable      <right_value_type>;
template < class type1, class type2, class type3, class type4, class device > constexpr            bool          operator ==  ( const pair<type1,type2,device>&, const pair<type3,type4,device>& ) requires equalable_to   <left_key_type,right_key_type> and equalable_to   <left_value_type,right_value_type>;
template < class type1, class type2, class type3, class type4, class device > constexpr            auto          operator <=> ( const pair<type1,type2,device>&, const pair<type3,type4,device>& ) requires comparable_to  <left_key_type,right_key_type> and comparable_to  <left_value_type,right_value_type>;
template < class type1, class type2, class type3, class type4, class device > constexpr pair_type  auto          operator  +  ( const pair<type1,type2,device>&, const pair_type  auto& right ) requires plusable_to    <left_key_type,right_key_type> and plusable_to    <left_value_type,right_value_type>;
template < class type1, class type2, class type3, class type4, class device > constexpr pair_type  auto          operator  -  ( const pair<type1,type2,device>&, const pair_type  auto& right ) requires minusable_to   <left_key_type,right_key_type> and minusable_to   <left_value_type,right_value_type>;
template < class type1, class type2, class type, class device >               constexpr pair_type  auto          operator  *  ( const pair<type1,type2,device>&, const            auto& right ) requires multipliable_to<left_key_type,right_type    > and multipliable_to<left_value_type,right_type      >;
template < class type, class type1, class type2, class device >               constexpr pair_type  auto          operator  *  ( const type&,                     const pair_type  auto& right ) requires multipliable_to<left_type,    right_key_type> and multipliable_to<left_type,      right_value_type>;
template < class type1, class type2, class type, class device >               constexpr pair_type  auto          operator  /  ( const pair<type1,type2,device>&, const            auto& right ) requires dividable_to   <left_key_type,right_type    > and dividable_to   <left_value_type,right_type      >;


#include "pair.cpp"