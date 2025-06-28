constexpr /*value_type*/ auto operator * ( const array_type auto& left, const array_type auto& right )
    requires ( left .dimension() == -1 ) and ( numeric<typename decay<decltype(left )>::value_type > or complex_type<typename decay<decltype(left )>::value_type > ) and
             ( right.dimension() ==  1 ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> )
{
    #ifdef debug
        if ( left.size() != right.size() )
            throw value_error("cannot multiply transposed-vector of size {} and vector of size {}: size must be equal", left.size(), right.size());
    #endif

    using type = common_type<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>;

    if constexpr ( numeric<typename decay<decltype(left )>::value_type> )
        return std::inner_product ( left.begin(), left.end(), right.begin(), type(0) );

    else if constexpr ( complex_type<typename decay<decltype(left )>::value_type> ) // Needs conj the right array if complex_type<typename decay<decltype(left )>::value_type>
        return std::inner_product ( left.begin(), left.end(), right.begin(), type(0),
                                    [] ( const auto& a, const auto& b ) { return a + b; },
                                    [] ( const auto& a, const auto& b ) { return conj(a) * b; } );
}

constexpr array_type auto operator * ( const array_type auto& left, const array_type auto& right )
    requires ( left .dimension() ==  1 ) and ( numeric<typename decay<decltype(left )>::value_type > or complex_type<typename decay<decltype(left )>::value_type > ) and
             ( right.dimension() == -1 ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> )
{
    return matrix ( left.size(), right.size(), [&] ( int i, int j ) { return left[i] * right[j]; } );
}