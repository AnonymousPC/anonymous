



constexpr            std::ostream& operator <<  (       std::ostream&    left, const pair_type  auto& right ) requires printable      <right_key_type>               and printable      <right_value_type>;
constexpr            bool          operator ==  ( const pair_type  auto& left, const pair_type  auto& right ) requires equalable_to   <left_key_type,right_key_type> and equalable_to   <left_value_type,right_value_type>;
constexpr            auto          operator <=> ( const pair_type  auto& left, const pair_type  auto& right ) requires comparable_to  <left_key_type,right_key_type> and comparable_to  <left_value_type,right_value_type>;
constexpr pair_type  auto          operator  +  ( const pair_type  auto& left, const pair_type  auto& right ) requires plusable_to    <left_key_type,right_key_type> and plusable_to    <left_value_type,right_value_type>;
constexpr pair_type  auto          operator  -  ( const pair_type  auto& left, const pair_type  auto& right ) requires minusable_to   <left_key_type,right_key_type> and minusable_to   <left_value_type,right_value_type>;
constexpr pair_type  auto          operator  *  ( const pair_type  auto& left, const            auto& right ) requires multipliable_to<left_key_type,right_type    > and multipliable_to<left_value_type,right_type      >;
constexpr pair_type  auto          operator  *  ( const            auto& left, const pair_type  auto& right ) requires multipliable_to<left_type,    right_key_type> and multipliable_to<left_type,      right_value_type>;
constexpr pair_type  auto          operator  /  ( const pair_type  auto& left, const            auto& right ) requires dividable_to   <left_key_type,right_type    > and dividable_to   <left_value_type,right_type      >;


// constexpr            std::ostream& operator <<  (       std::ostream&    left, const tuple_type auto& right ) requires detail::tuplewise_printable                                        <remove_cvref<decltype(right)>>;
// constexpr            bool          operator ==  ( const tuple_type auto& left, const tuple_type auto& right ) requires detail::tuplewise_equalable_to        <remove_cvref<decltype(left)>,remove_cvref<decltype(right)>>;
// constexpr            auto          operator <=> ( const tuple_type auto& left, const tuple_type auto& right ) requires detail::tuplewise_comparable_to       <remove_cvref<decltype(left)>,remove_cvref<decltype(right)>>;
// constexpr tuple_type auto          operator  +  ( const tuple_type auto& left, const tuple_type auto& right ) requires detail::tuplewise_plusable_to         <remove_cvref<decltype(left)>,remove_cvref<decltype(right)>>;
// constexpr tuple_type auto          operator  -  ( const tuple_type auto& left, const tuple_type auto& right ) requires detail::tuplewise_minusable_to        <remove_cvref<decltype(left)>,remove_cvref<decltype(right)>>;
// constexpr tuple_type auto          operator  *  ( const tuple_type auto& left, const            auto& right ) requires detail::tuplewise_each_multipliable_to<remove_cvref<decltype(left)>,remove_cvref<decltype(right)>> and ( not tuple_type<remove_cvref<decltype(right)>> );
// constexpr tuple_type auto          operator  *  ( const            auto& left, const tuple_type auto& right ) requires detail::tuplewise_multipliable_to_each<remove_cvref<decltype(left)>,remove_cvref<decltype(right)>> and ( not tuple_type<remove_cvref<decltype(left )>> );
// constexpr tuple_type auto          operator  /  ( const tuple_type auto& left, const            auto& right ) requires detail::tuplewise_each_dividable_to   <remove_cvref<decltype(left)>,remove_cvref<decltype(right)>> and ( not tuple_type<remove_cvref<decltype(right)>> );

#include "discrete_global.cpp"