#pragma once

#define left_type        decay<decltype(left )>
#define right_type       decay<decltype(right)>
#define left_value_type  typename decltype(basic_string_view(left ))::value_type
#define right_value_type typename decltype(basic_string_view(right))::value_type


/// Global

constexpr std::istream& operator >> ( std::istream& left,       string_type auto& right );
constexpr std::ostream& operator << ( std::ostream& left, const string_type auto& right );

constexpr             bool          operator ==  ( const general_string_type auto& left, const general_string_type auto& right ) requires ( string_type<left_type> or string_type<right_type> ) and std::same_as<left_value_type,right_value_type>;
constexpr             auto          operator <=> ( const general_string_type auto& left, const general_string_type auto& right ) requires ( string_type<left_type> or string_type<right_type> ) and std::same_as<left_value_type,right_value_type>;
constexpr string_type auto          operator  +  ( const general_string_type auto& left, const general_string_type auto& right ) requires ( string_type<left_type> or string_type<right_type> ) and std::same_as<left_value_type,right_value_type>;
constexpr string_type auto&         operator  += (       general_string_type auto& left, const general_string_type auto& right ) requires std::same_as<left_type,basic_string<left_value_type>> and std::same_as<left_value_type,right_value_type>;

constexpr string_type auto          operator  *  ( const string_type auto&, int_type auto );
constexpr string_type auto          operator  *  ( int_type auto, const string_type auto& );
constexpr string_type auto&         operator  *= (       string_type auto&, int_type auto );

#include "string_global.ipp"

#undef left_type
#undef right_type
#undef left_value_type
#undef right_value_type