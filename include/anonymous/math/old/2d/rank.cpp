/// Declaration

constexpr int rank ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> )
{
    auto s = singular_value ( matrix );

    auto s_max  = s.max([] (const auto& a, const auto& b) { return abs(a) < abs(b); });
    auto mn_max = std::max(matrix.row(), matrix.column());
    auto eps    = std::numeric_limits<typename decltype(s)::value_type>::epsilon();

    return s.count([&] (const auto& t) { return abs(t) > s_max * mn_max * eps; });
}