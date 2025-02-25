#pragma once

constexpr tuple_type auto svd ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> )
{
    let [vals, l_vcts, r_vcts] = singular ( matrix );
    let u = transpose(l_vcts);
    let s = array<typename decltype(vals)::value_type,2>(vals.size(), vals.size());
    for ( int i in range(vals.size()) )
        s[i][i] = vals[i];
    let v = transpose(r_vcts);

    return tuple ( u, s, v );
}