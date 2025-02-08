#pragma once

#include "detail.hpp"

#define left_value_type     typename decltype(left  )::value_type
#define left_extents_type   typename decltype(left  )::extents_type
#define left_layout_type    typename decltype(left  )::layout_type
#define right_value_type    typename decltype(right )::value_type
#define right_extents_type  typename decltype(right )::extents_type
#define right_layout_type   typename decltype(right )::layout_type
#define output_value_type   typename decltype(output)::value_type
#define output_layout_type  typename decltype(output)::layout_type
#define output_extents_type typename decltype(output)::extents_type

constexpr void cpu::linalg::unary_plus ( const auto right, auto output )
{
    detail::eigen_map(output) = + detail::eigen_map<output_value_type>(right);
}

constexpr void cpu::linalg::unary_minus ( const auto right, auto output )
{
    detail::eigen_map(output) = - detail::eigen_map<output_value_type>(right);
}

constexpr void cpu::linalg::multiply ( const auto left, const auto right, auto output )
{
    detail::eigen_map(output) = detail::eigen_map<output_value_type>(left) * detail::eigen_map<output_value_type>(right);
}


#undef left_value_type
#undef left_extents_type
#undef left_layout_type
#undef right_value_type
#undef right_extents_type
#undef right_layout_type
#undef output_value_type
#undef output_extents_type
#undef output_layout_type



