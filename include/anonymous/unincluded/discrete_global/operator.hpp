#include "detail/tuplewise.cpp"

constexpr            bool          operator ==  ( const pair_type  auto& left, const pair_type  auto& right ) requires equalable_to   <left_key_type,right_key_type> and equalable_to   <left_value_type,right_value_type>;
constexpr            auto          operator <=> ( const pair_type  auto& left, const pair_type  auto& right ) requires comparable_to  <left_key_type,right_key_type> and comparable_to  <left_value_type,right_value_type>;
constexpr pair_type  auto          operator  +  ( const pair_type  auto& left, const pair_type  auto& right ) requires plusable_to    <left_key_type,right_key_type> and plusable_to    <left_value_type,right_value_type>;
constexpr pair_type  auto          operator  -  ( const pair_type  auto& left, const pair_type  auto& right ) requires minusable_to   <left_key_type,right_key_type> and minusable_to   <left_value_type,right_value_type>;
constexpr pair_type  auto          operator  *  ( const pair_type  auto& left, const            auto& right ) requires multipliable_to<left_key_type,right_type    > and multipliable_to<left_value_type,right_type      > and ( not pair_type<right_type> );
constexpr pair_type  auto          operator  *  ( const            auto& left, const pair_type  auto& right ) requires multipliable_to<left_type,    right_key_type> and multipliable_to<left_type,      right_value_type> and ( not pair_type<left_type > );
constexpr pair_type  auto          operator  /  ( const pair_type  auto& left, const            auto& right ) requires dividable_to   <left_key_type,right_type    > and dividable_to   <left_value_type,right_type      > and ( not pair_type<right_type> );

constexpr            bool          operator ==  ( const tuple_type auto& left, const tuple_type auto& right ) requires detail::tuplewise_equalable_to        <left_type,right_type>;
constexpr            auto          operator <=> ( const tuple_type auto& left, const tuple_type auto& right ) requires detail::tuplewise_comparable_to       <left_type,right_type>;
constexpr tuple_type auto          operator  +  ( const tuple_type auto& left, const tuple_type auto& right ) requires detail::tuplewise_plusable_to         <left_type,right_type>;
constexpr tuple_type auto          operator  -  ( const tuple_type auto& left, const tuple_type auto& right ) requires detail::tuplewise_minusable_to        <left_type,right_type>;
constexpr tuple_type auto          operator  *  ( const tuple_type auto& left, const            auto& right ) requires detail::tuplewise_each_multipliable_to<left_type,right_type> and ( not tuple_type<right_type> );
constexpr tuple_type auto          operator  *  ( const            auto& left, const tuple_type auto& right ) requires detail::tuplewise_multipliable_to_each<left_type,right_type> and ( not tuple_type<left_type > );
constexpr tuple_type auto          operator  /  ( const tuple_type auto& left, const            auto& right ) requires detail::tuplewise_each_dividable_to   <left_type,right_type> and ( not tuple_type<right_type> );

#include "operator.cpp"