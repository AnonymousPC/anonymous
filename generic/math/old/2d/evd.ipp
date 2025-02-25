#pragma once

constexpr tuple_type auto evd ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> )
{
    #if debug
        if ( matrix.row() != matrix.column() )
            throw value_error("cannot evd-decompose matrix of shape {}: matrix must be square", matrix.shape());
    #endif

    let [vals, vcts] = eigen(matrix);
    let u = transpose(vcts);
    let e = array<typename decltype(vals)::value_type,2>(vals.size(), vals.size());
    for ( int i in range(vals.size()) )
        e[i][i] = vals[i];
    let v = inverse(u);

    return tuple ( u, e, v );
}