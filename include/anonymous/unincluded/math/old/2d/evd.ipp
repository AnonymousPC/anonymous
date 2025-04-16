#pragma once

constexpr tuple_type auto evd ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> )
{
    #ifdef debug
        if ( matrix.row() != matrix.column() )
            throw value_error("cannot evd-decompose matrix of shape {}: matrix must be square", matrix.shape());
    #endif

    auto [vals, vcts] = eigen(matrix);
    auto u = transpose(vcts);
    auto e = array<typename decltype(vals)::value_type,2>(vals.size(), vals.size());
    for ( int i in range(vals.size()) )
        e[i][i] = vals[i];
    auto v = inverse(u);

    return tuple ( u, e, v );
}