#pragma once

#define left_type                 decay<decltype(left )>
#define left_key_type    typename decay<decltype(left )>::key_type
#define left_value_type  typename decay<decltype(left )>::value_type
#define right_type                decay<decltype(right)>
#define right_key_type   typename decay<decltype(right)>::key_type
#define right_value_type typename decay<decltype(right)>::value_type

/// Detail

namespace detail
{
    template < class type, int count = 1 >
    constexpr bool tuplewise_printable = []
        {
            if constexpr ( count < tuple_size<type> )
                return printable<tuple_element<count,type>> and tuplewise_printable<type,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_equalable = []
        {
            if constexpr ( tuple_size<type1> == tuple_size<type2> and count < tuple_size<type1> )
                return equalable_to<tuple_element<count,type1>,tuple_element<count,type2>> and tuplewise_equalable<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_comparable = []
        {
            if constexpr ( tuple_size<type1> == tuple_size<type2> and count < tuple_size<type1> )
                return comparable_to<tuple_element<count,type1>,tuple_element<count,type2>> and tuplewise_comparable<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_addable = []
        {
            if constexpr ( tuple_size<type1> == tuple_size<type2> and count < tuple_size<type1> )
                return addable_to<tuple_element<count,type1>,tuple_element<count,type2>> and tuplewise_addable<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_minusable = []
        {
            if constexpr ( tuple_size<type1> == tuple_size<type2> and count < tuple_size<type1> )
                return minusable_to<tuple_element<count,type1>,tuple_element<count,type2>> and tuplewise_minusable<type1,type2,count+1>;
            else
                return true;
        } ();

//  See root/container/interface.h/concept
//  template < class type1, class type2, int count = 1 >
//  constexpr bool tuplewise_convertible =
//      tuple_size<type1> == tuple_size<type2> and
//      std::convertible_to<tuple_element<count,type1>,tuple_element<count,type2>> and []
//      {
//          if constexpr ( count < tuple_size<type1> )
//              return tuplewise_convertible<type1,type2,count+1>;
//          else
//              return true;
//      } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_same =
        tuple_size<type1> == tuple_size<type2> and
        std::same_as<tuple_element<count,type1>,tuple_element<count,type2>> and []
        {
            if constexpr ( count < tuple_size<type1> )
                return tuplewise_same<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_each_multipliable_to =
        multipliable_to<tuple_element<count,type1>,type2> and []
        {
            if constexpr ( count < tuple_size<type1> )
                return tuplewise_each_multipliable_to<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_multipliable_to_each =
        multipliable_to<type1,tuple_element<count,type2>> and []
        {
            if constexpr ( count < tuple_size<type2> )
                return tuplewise_multipliable_to_each<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_each_dividable_to =
        multipliable_to<tuple_element<count,type1>,type2> and []
        {
            if constexpr ( count < tuple_size<type1> )
                return tuplewise_each_dividable_to<type1,type2,count+1>;
            else
                return true;
        } ();

} // namespace detail


/// Global


constexpr            std::ostream& operator <<  ( std::ostream& left,         const pair_type auto& right ) requires printable      <right_key_type>               and printable      <right_value_type>;
constexpr            bool          operator ==  ( const pair_type auto& left, const pair_type auto& right ) requires equalable_to   <left_key_type,right_key_type> and equalable_to   <left_value_type,right_value_type>;
constexpr            auto          operator <=> ( const pair_type auto& left, const pair_type auto& right ) requires comparable_to  <left_key_type,right_key_type> and comparable_to  <left_value_type,right_value_type>;
constexpr pair_type  auto          operator  +  ( const pair_type auto& left, const pair_type auto& right ) requires addable_to     <left_key_type,right_key_type> and addable_to     <left_value_type,right_value_type>;
constexpr pair_type  auto          operator  -  ( const pair_type auto& left, const pair_type auto& right ) requires minusable_to   <left_key_type,right_key_type> and minusable_to   <left_value_type,right_value_type>;
constexpr pair_type  auto          operator  *  ( const pair_type auto& left, const           auto& right ) requires multipliable_to<left_key_type,right_type>     and multipliable_to<left_value_type,right_type>       but ( not pair_type<right_type> );
constexpr pair_type  auto          operator  *  ( const           auto& left, const pair_type auto& right ) requires multipliable_to<left_type,    right_key_type> and multipliable_to<left_type,      right_value_type> but ( not pair_type<left_type>  );
constexpr pair_type  auto          operator  /  ( const pair_type auto& left, const           auto& right ) requires dividable_to   <left_key_type,right_type>     and dividable_to   <left_value_type,right_type>       but ( not pair_type<right_type> );


constexpr            std::ostream& operator <<  ( std::ostream& left,          const tuple_type auto& right ) requires detail::tuplewise_printable           <right_type>;
constexpr            bool          operator ==  ( const tuple_type auto& left, const tuple_type auto& right ) requires detail::tuplewise_equalable           <left_type,right_type>;
constexpr            auto          operator <=> ( const tuple_type auto& left, const tuple_type auto& right ) requires detail::tuplewise_comparable          <left_type,right_type>;
constexpr tuple_type auto          operator  +  ( const tuple_type auto& left, const tuple_type auto& right ) requires detail::tuplewise_addable             <left_type,right_type>;
constexpr tuple_type auto          operator  -  ( const tuple_type auto& left, const tuple_type auto& right ) requires detail::tuplewise_minusable           <left_type,right_type>;
constexpr tuple_type auto          operator  *  ( const tuple_type auto& left, const            auto& right ) requires detail::tuplewise_each_multipliable_to<left_type,right_type> but ( not tuple_type<right_type> );
constexpr tuple_type auto          operator  *  ( const            auto& left, const tuple_type auto& right ) requires detail::tuplewise_multipliable_to_each<left_type,right_type> but ( not tuple_type<left_type > );
constexpr tuple_type auto          operator  /  ( const tuple_type auto& left, const            auto& right ) requires detail::tuplewise_each_dividable_to   <left_type,right_type> but ( not tuple_type<right_type> );


#include "discrete_global.ipp"
#undef left_type
#undef left_key_type
#undef left_value_type
#undef right_type
#undef right_key_type
#undef right_value_type