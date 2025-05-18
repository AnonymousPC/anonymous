constexpr bool operator ==  ( const container auto& left, const container auto& right ) requires equalable_to <left_value_type,right_value_type> and same_as<left_device_type,right_device_type>;
constexpr auto operator <=> ( const container auto& left, const container auto& right ) requires comparable_to<left_value_type,right_value_type> and same_as<left_device_type,right_device_type>;

#include "container_operator.cpp"