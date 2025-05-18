constexpr array_type auto tensor ( const array_type auto& left, const array_type auto& right )
    requires ( left .dimension() == 1 ) and ( numeric<typename decay<decltype(left )>::value_type > or complex_type<typename decay<decltype(left )>::value_type > ) and
             ( right.dimension() == 1 ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> )
{
    return matrix ( left.size(), right.size(), [&] ( int i, int j ) { return left[i] * right[j]; } );
}