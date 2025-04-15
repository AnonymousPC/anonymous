#pragma once

/// Declaration

constexpr int rank ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> )
{
    let s = singular_value ( matrix );

    let s_max  = s.max([] (const auto& a, const auto& b) { return abs(a) < abs(b); });
    let mn_max = std::max(matrix.row(), matrix.column());
    let eps    = std::numeric_limits<typename decltype(s)::value_type>::epsilon();

    return s.count([&] (const auto& t) { return abs(t) > s_max * mn_max * eps; });
}