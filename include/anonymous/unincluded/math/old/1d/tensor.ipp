#pragma once

constexpr array_type auto tensor ( const array_type auto& left, const array_type auto& right )
    requires ( left .dimension() == 1 ) and ( number_type<left_value_type > or complex_type<left_value_type > ) and
             ( right.dimension() == 1 ) and ( number_type<right_value_type> or complex_type<right_value_type> )
{
    return matrix ( left.size(), right.size(), [&] ( int i, int j ) { return left[i] * right[j]; } );
}