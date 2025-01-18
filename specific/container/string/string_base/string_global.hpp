#pragma once

#define left_type         decay<decltype(left )>
#define right_type        decay<decltype(right)>
#define left_value_type   typename decltype(basic_string_view(left ))::value_type
#define right_value_type  typename decltype(basic_string_view(right))::value_type
#define left_device_type  typename decltype(basic_string_view(left ))::device_type
#define right_device_type typename decltype(basic_string_view(right))::device_type


/// Global

constexpr std::istream&     operator >>  (       std::istream&     left,       string_type auto& right ) requires same_as<right_value_type,char> and ( right_type::ownership() );
constexpr std::ostream&     operator <<  (       std::ostream&     left, const string_type auto& right ) requires same_as<right_value_type,char>;
constexpr             bool  operator ==  ( const string_type auto& left, const string_type auto& right ) requires same_as<left_value_type,right_value_type> and same_as<left_device_type,right_device_type>;
constexpr             auto  operator <=> ( const string_type auto& left, const string_type auto& right ) requires same_as<left_value_type,right_value_type> and same_as<left_device_type,right_device_type>;
constexpr string_type auto  operator  +  ( const string_type auto& left, const string_type auto& right ) requires same_as<left_value_type,right_value_type> and same_as<left_device_type,right_device_type>;
constexpr string_type auto& operator  += (       string_type auto& left, const string_type auto& right ) requires same_as<left_value_type,right_value_type> and same_as<left_device_type,right_device_type> and ( left_type::ownership() );
constexpr string_type auto  operator  *  ( const string_type auto& left,       int_type    auto  right );
constexpr string_type auto  operator  *  (       int_type    auto  left, const string_type auto& right );
constexpr string_type auto& operator  *= (       string_type auto& left,       int_type    auto  right )  requires ( left_type::ownership() );

#include "string_global.ipp"

#undef left_type
#undef right_type
#undef left_value_type
#undef right_value_type
#undef left_device_type
#undef right_device_type