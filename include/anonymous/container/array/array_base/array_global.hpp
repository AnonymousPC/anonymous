#pragma once

#define left_value_type   typename decay<decltype(left )>::value_type
#define right_value_type  typename decay<decltype(right)>::value_type
#define left_dimension             decay<decltype(left )>::dimension()
#define right_dimension            decay<decltype(left )>::dimension()
#define left_device_type  typename decay<decltype(left )>::device_type
#define right_device_type typename decay<decltype(left )>::device_type

constexpr std::ostream& operator <<  (       std::ostream&    left, const array_type auto& right ) requires printable    <                right_value_type>;
constexpr bool          operator ==  ( const array_type auto& left, const array_type auto& right ) requires equalable_to <left_value_type,right_value_type> and (left_dimension == right_dimension) and same_as<left_device_type,right_device_type>;
constexpr auto          operator <=> ( const array_type auto& left, const array_type auto& right ) requires comparable_to<left_value_type,right_value_type> and (left_dimension == right_dimension) and same_as<left_device_type,right_device_type>;

#undef left_value_type
#undef right_value_type
#undef left_dimension
#undef right_dimension
#undef left_device_type
#undef right_device_type