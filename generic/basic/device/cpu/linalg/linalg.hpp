#pragma once

#define left_type                     decay<decltype(left  )>
#define left_value_type      typename decay<decltype(left  )>::value_type
#define left_extents_type    typename decay<decltype(left  )>::extents_type
#define left_layout_type     typename decay<decltype(left  )>::layout_type
#define left_accessor_type   typename decay<decltype(left  )>::accessor_type
#define left_rank                     decay<decltype(left  )>::extents_type::rank()
#define right_type                    decay<decltype(right )>
#define right_value_type     typename decay<decltype(right )>::value_type
#define right_extents_type   typename decay<decltype(right )>::extents_type
#define right_layout_type    typename decay<decltype(right )>::layout_type
#define right_accessor_type  typename decay<decltype(right )>::accessor_type
#define right_rank                    decay<decltype(right )>::rank()
#define output_type                   decay<decltype(output)>
#define output_value_type    typename decay<decltype(output)>::value_type
#define output_layout_type   typename decay<decltype(output)>::layout_type
#define output_extents_type  typename decay<decltype(output)>::extents_type
#define output_rank                   decay<decltype(output)>::rank()
#define output_accessor_type typename decay<decltype(output)>::accessor_type

#include "detail.hpp"

constexpr void cpu::linalg::unary_plus ( const auto& right, auto& output )
{
    detail::eigen_map(output).noalias() = + detail::eigen_map<output_value_type>(right);
}

constexpr void cpu::linalg::unary_minus ( const auto& right, auto& output )
{
    detail::eigen_map(output).noalias() = - detail::eigen_map<output_value_type>(right);
}

constexpr void cpu::linalg::plus ( const auto& left, const auto& right, auto& output )
{
    detail::eigen_map(output).noalias() = detail::eigen_map<output_value_type>(left) + detail::eigen_map<output_value_type>(right);
}

constexpr void cpu::linalg::minus ( const auto& left, const auto& right, auto& output )
{
    detail::eigen_map(output).noalias() = detail::eigen_map<output_value_type>(left) - detail::eigen_map<output_value_type>(right);
}

constexpr void cpu::linalg::left_scale ( const auto& left, const auto& right, auto& output )
{
    detail::eigen_map(output).noalias() = left * detail::eigen_map(right);
}

constexpr void cpu::linalg::right_scale ( const auto& left, const auto& right, auto& output )
{
    detail::eigen_map(output).noalias() = detail::eigen_map<output_value_type>(left) * right;
}

constexpr void cpu::linalg::multiply ( const auto& left, const auto& right, auto& output )
{
    detail::eigen_map(output).noalias() = detail::eigen_map<output_value_type>(left) * detail::eigen_map<output_value_type>(right);
}

constexpr void cpu::linalg::divide ( const auto& left, const auto& right, auto& output )
{
    detail::eigen_map(output).noalias() = detail::eigen_map<output_value_type>(left) / right;
}

constexpr void cpu::linalg::plus_equal ( auto& left, const auto& right, auto& /*output*/ )
{
    detail::eigen_map(left) += detail::eigen_map<left_value_type>(right);
}

constexpr void cpu::linalg::minus_equal ( auto& left, const auto& right, auto& /*output*/ )
{
    detail::eigen_map(left) -= detail::eigen_map<left_value_type>(right);
}

constexpr void cpu::linalg::right_scale_equal ( auto& left, const auto& right, auto& /*output*/ )
{
    detail::eigen_map(left) *= right;
}

constexpr void cpu::linalg::multiply_equal ( auto& left, const auto& right, auto& /*output*/ )
{
    detail::eigen_map(left) *= detail::eigen_map<left_value_type>(right);
}

constexpr void cpu::linalg::divide_equal ( auto& left, const auto& right, auto& /*output*/ )
{
    detail::eigen_map(left) /= right;
}

constexpr void cpu::linalg::dot ( const auto& left, const auto& right, auto& output )
{
    output = detail::eigen_map<output_value_type>(left).dot(detail::eigen_map<output_value_type>(right));
}

constexpr void cpu::linalg::cross ( const auto& left, const auto& right, auto& output )
{
    detail::eigen_map(output).noalias() = detail::eigen_map<output_value_type>(left).cross(detail::eigen_map<output_value_type>(right));
}

constexpr void cpu::linalg::convolve ( const auto& left, const auto& right, auto& output )
{
    static_assert(not true, "not coded yet");
}

#undef left_type
#undef left_value_type
#undef left_extents_type
#undef left_layout_type
#undef left_accessor_type
#undef left_rank
#undef right_type
#undef right_value_type
#undef right_extents_type
#undef right_layout_type
#undef right_accessor_type
#undef right_rank
#undef output_type
#undef output_value_type
#undef output_extents_type
#undef output_layout_type
#undef output_accessor_type
#undef output_rank