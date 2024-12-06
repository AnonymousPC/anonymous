#pragma once

#define right_value_type typename decay<decltype(right)>::value_type

constexpr std::ostream& operator << ( std::ostream& left, const array_type auto& right ) requires printable<right_value_type>;

#include "print.ipp"

#undef right_value_type