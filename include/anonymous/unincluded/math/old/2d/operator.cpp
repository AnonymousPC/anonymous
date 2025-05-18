/// Declaration

constexpr array_type auto operator * ( const array_type auto& left, const array_type auto& right )
    requires ( left .dimension() == 2 ) and ( numeric<typename decay<decltype(left )>::value_type > or complex_type<typename decay<decltype(left )>::value_type > ) and
             ( right.dimension() == 2 ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> )
{
    #ifdef debug
        if ( left.column() != right.row() )
            throw value_error("cannot multiply matrix of shape {} and matrix of shape {}", left.shape(), right.shape());
    #endif

    try
    {
        using type = std::common_type<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>::type;
        return aux::from_eigen((aux::to_eigen(left.template as_type<type>()) * aux::to_eigen(right.template as_type<type>())).eval());
    }
    catch ( const std::runtime_error& e )
    {
        throw math_error("cannot multiply matrix [[caused by {}: {}]]", "Eigen", e.what());
    }
}

constexpr array_type auto operator * ( const array_type auto& left, const array_type auto& right )
    requires ( left .dimension() == 2 ) and ( numeric<typename decay<decltype(left )>::value_type > or complex_type<typename decay<decltype(left )>::value_type > ) and
             ( right.dimension() == 1 ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> )
{
    #ifdef debug
        if ( left.column() != right.size() )
            throw value_error("cannot multiply matrix of shape {} and vector of size {}", left.shape(), right.size());
    #endif

    return array ( left.row(), [&] ( int i ) { return dot ( left[i], right ); } );
}

constexpr array_type auto operator * ( const array_type auto& left, const array_type auto& right )
    requires ( left .dimension() == -1 ) and ( numeric<typename decay<decltype(left )>::value_type > or complex_type<typename decay<decltype(left )>::value_type > ) and
             ( right.dimension() ==  2 ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> )
{
    #ifdef debug
        if ( left.size() != right.row() )
            throw value_error("cannot multiply transposed-vector of size {} and matrix of shape {}", left.size(), right.shape());
    #endif

    auto tmp_l = transpose(left);
    auto tmp_r = transpose(right);
    return array ( right.column(), [&] ( int i ) { return dot ( tmp_l, tmp_r[i] ); } );
}