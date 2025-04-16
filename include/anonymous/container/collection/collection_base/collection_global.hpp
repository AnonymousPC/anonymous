#pragma once

#define left_key_type          typename decay<decltype(left )>::key_type
#define left_value_type        typename decay<decltype(left )>::value_type
#define left_compare_type      typename decay<decltype(left )>::compare_type
#define left_device_type       typename decay<decltype(left )>::device_type
#define right_key_type         typename decay<decltype(right)>::key_type
#define right_value_type       typename decay<decltype(right)>::value_type
#define right_compare_type     typename decay<decltype(right)>::compare_type
#define right_device_type      typename decay<decltype(right)>::device_type

/// Global

constexpr          std::ostream&  operator <<  (       std::ostream&  left, const set_type auto& right ) requires printable    <                right_value_type>;
constexpr          bool           operator ==  ( const set_type auto& left, const set_type auto& right ) requires equalable_to <left_value_type,right_value_type> and                                                   same_as<left_device_type,right_device_type>;
constexpr          auto           operator <=> ( const set_type auto& left, const set_type auto& right ) requires comparable_to<left_value_type,right_value_type> and same_as<left_compare_type,right_compare_type> and same_as<left_device_type,right_device_type>;
constexpr          bool           operator <<  ( const set_type auto& left, const set_type auto& right ) requires equalable_to <left_value_type,right_value_type> and same_as<left_compare_type,right_compare_type> and same_as<left_device_type,right_device_type>;
constexpr          bool           operator >>  ( const set_type auto& left, const set_type auto& right ) requires equalable_to <left_value_type,right_value_type> and same_as<left_compare_type,right_compare_type> and same_as<left_device_type,right_device_type>;
constexpr set_type auto           operator  +  ( const set_type auto& left, const set_type auto& right ) requires same_as      <left_value_type,right_value_type> and same_as<left_compare_type,right_compare_type> and same_as<left_device_type,right_device_type>;
constexpr set_type auto           operator  -  ( const set_type auto& left, const set_type auto& right ) requires same_as      <left_value_type,right_value_type> and same_as<left_compare_type,right_compare_type> and same_as<left_device_type,right_device_type>;
constexpr set_type auto           operator  |  ( const set_type auto& left, const set_type auto& right ) requires same_as      <left_value_type,right_value_type> and same_as<left_compare_type,right_compare_type> and same_as<left_device_type,right_device_type>;
constexpr set_type auto           operator  &  ( const set_type auto& left, const set_type auto& right ) requires same_as      <left_value_type,right_value_type> and same_as<left_compare_type,right_compare_type> and same_as<left_device_type,right_device_type>;
constexpr set_type auto           operator  ^  ( const set_type auto& left, const set_type auto& right ) requires same_as      <left_value_type,right_value_type> and same_as<left_compare_type,right_compare_type> and same_as<left_device_type,right_device_type>;
constexpr set_type auto&          operator  += (       set_type auto& left, const set_type auto& right ) requires requires { left = left + right; };
constexpr set_type auto&          operator  -= (       set_type auto& left, const set_type auto& right ) requires requires { left = left - right; };
constexpr set_type auto&          operator  |= (       set_type auto& left, const set_type auto& right ) requires requires { left = left | right; };
constexpr set_type auto&          operator  &= (       set_type auto& left, const set_type auto& right ) requires requires { left = left & right; };
constexpr set_type auto&          operator  ^= (       set_type auto& left, const set_type auto& right ) requires requires { left = left ^ right; };
 
constexpr          std::ostream&  operator <<  (       std::ostream&  left, const map_type auto& right ) requires printable    <              right_key_type> and printable    <                right_value_type>;
constexpr          bool           operator ==  ( const map_type auto& left, const map_type auto& right ) requires equalable_to <left_key_type,right_key_type> and equalable_to <left_value_type,right_value_type>                                                   and same_as<left_device_type,right_device_type>;
constexpr          auto           operator <=> ( const map_type auto& left, const map_type auto& right ) requires comparable_to<left_key_type,right_key_type> and comparable_to<left_value_type,right_value_type> and same_as<left_compare_type,right_compare_type> and same_as<left_device_type,right_device_type>;


#include "collection_global.cpp"

#undef left_key_type
#undef left_value_type
#undef left_compare_type
#undef left_device_type
#undef right_key_type
#undef right_value_type
#undef right_compare_type
#undef right_device_type