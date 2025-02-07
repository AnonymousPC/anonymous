#pragma once

#include "detail.hpp"

#define left_value_type   typename decltype(left  )::value_type
#define right_value_type  typename decltype(right )::value_type
#define output_value_type typename decltype(output)::value_type


constexpr void cpu::linalg::multiply ( const auto left, const auto right, auto output )
{
    detail::eigen_map(output) = detail::eigen_map<output_value_type>(left) * detail::eigen_map<output_value_type>(right);
}


#undef left_value_type
#undef right_value_type
#undef output_value_type



