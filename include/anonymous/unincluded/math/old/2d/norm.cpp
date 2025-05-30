template < numeric auto num >
constexpr /*value_type*/ auto norm ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> )
{
    if constexpr ( num == 1 )
    {
        using numeric = decltype(complex(matrix_value_type()))::value_type;
        return array<numeric>(matrix.column(), [&] (int j) { auto s = numeric(0); for ( int i in range(matrix.row()) ) s += abs(matrix[i][j]); return s; }) .max();
    }

    else if constexpr ( num == 2 )
        return singular_value(matrix).max();

    else if constexpr ( num == std::numeric_limits<decltype(num)>::infinity() )
        return array<matrix_value_type>(matrix.row(), [&] (int i) { return matrix[i].sum([] (const auto& n) { return abs(n); }); }) .max();

    else
        static_assert(false, "unsolvable, currently norm 1, 2 and inf is defined");
}