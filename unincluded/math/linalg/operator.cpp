
constexpr array_type auto operator + ( const array_type auto& right )
    requires numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type>
{
    using device     = typename decay<decltype(right)>::device_type;
    using value_type = decltype(+std::declval<typename decay<decltype(right)>::value_type>());
    auto output = array<value_type,right_dimension,device>([&] { if constexpr ( right_dimension == 1 ) return right.size(); else return right.shape(); } ());
    device_linalg_1_1(unary_plus, right, output);    
    return output;
}

constexpr array_type auto operator - ( const array_type auto& right )
    requires numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type>
{
    using device     = typename decay<decltype(right)>::device_type;
    using value_type = decltype(-std::declval<typename decay<decltype(right)>::value_type>());
    auto output = array<value_type,right_dimension,device>([&] { if constexpr ( right_dimension == 1 ) return right.size(); else return right.shape(); } ());
    device_linalg_1_1(unary_minus, right, output);
    return output;
}

constexpr array_type auto operator + ( const array_type auto& left, const array_type auto& right )
    requires ( ( numeric<typename decay<decltype(left )>::value_type> or complex_type<typename decay<decltype(left )>::value_type> ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and
             ( left_dimension == right_dimension ) and 
             same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>
{
    #ifdef debug
    if ( left.shape() != right.shape() )
        throw linalg_error("plus array with inconsistent shape (with left_shape = {}, right_shape = {})", left.shape(), right.shape());
    #endif
    
    using device     = typename decay<decltype(left )>::device_type;
    using value_type = decltype(std::declval<typename decay<decltype(left )>::value_type>() + std::declval<typename decay<decltype(right)>::value_type>());
    auto output = array<value_type,left_dimension,device>([&] { if constexpr ( left_dimension == 1 ) return left.size(); else return left.shape(); } ());
    left.mdspan().visit([&] (const auto& lspan) { return right.mdspan().visit([&] (const auto& rspan) { return device::linalg::plus(lspan, rspan, output.mdspan().template value<1>()); }); });
    return output;
}

constexpr array_type auto operator - ( const array_type auto& left, const array_type auto& right )
    requires ( ( numeric<typename decay<decltype(left )>::value_type> or complex_type<typename decay<decltype(left )>::value_type> ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and
             ( left_dimension == right_dimension ) and 
             same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>
{
    #ifdef debug
    if ( left.shape() != right.shape() )
        throw linalg_error("minus array with inconsistent shape (with left_shape = {}, right_shape = {})", left.shape(), right.shape());
    #endif
    
    using device     = typename decay<decltype(left )>::device_type;
    using value_type = decltype(std::declval<typename decay<decltype(left )>::value_type>() - std::declval<typename decay<decltype(right)>::value_type>());
    auto output = array<value_type,left_dimension,device>([&] { if constexpr ( left_dimension == 1 ) return left.size(); else return left.shape(); } ());
    device_linalg_2_1(minus, left, right, output);
    return output;
}

constexpr array_type auto operator * ( const auto& left, const array_type auto& right )
    requires ( numeric<decay<decltype(left)>> or complex_type<decay<decltype(left)>> ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> )
{    
    using device     = typename decay<decltype(right)>::device_type;
    using value_type = decltype(std::declval<decay<decltype(left)>>() * std::declval<typename decay<decltype(right)>::value_type>());
    auto output = array<value_type,right_dimension,device>([&] { if constexpr ( right_dimension == 1 ) return right.size(); else return right.shape(); } ());
    device_linalg_c1_1(left_scale, left, right, output);
    return output;
}

constexpr array_type auto operator * ( const array_type auto& left, const auto& right )
    requires ( numeric<typename decay<decltype(left )>::value_type> or complex_type<typename decay<decltype(left )>::value_type> ) and ( numeric<decay<decltype(right)>> or complex_type<decay<decltype(right)>> )
{    
    using device     = typename decay<decltype(left )>::device_type;
    using value_type = decltype(std::declval<typename decay<decltype(left )>::value_type>() * std::declval<decay<decltype(right)>>());
    auto output = array<value_type,left_dimension,device>([&] { if constexpr ( left_dimension == 1 ) return left.size(); else return left.shape(); } ());
    device_linalg_1c_1(right_scale, left, right, output);
    return output;
}

constexpr array_type auto operator * ( const array_type auto& left, const array_type auto& right )
    requires ( ( numeric<typename decay<decltype(left )>::value_type> or complex_type<typename decay<decltype(left )>::value_type> ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and
             ( left_dimension == 2 and right_dimension == 2 ) and
             same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>
{
    #ifdef debug
    if ( left.column() != right.row() )
        throw linalg_error("multiply matrix with inconsistent column and row (with left_shape = {}, right_shape = {})", left.shape(), right.shape());
    #endif
    
    using device     = typename decay<decltype(left )>::device_type;
    using value_type = decltype(std::declval<typename decay<decltype(left )>::value_type>() * std::declval<typename decay<decltype(right)>::value_type>());
    auto output = array<value_type,2,device>(left.row(), right.column());
    device_linalg_2_1(multiply, left, right, output);
    return output;
}

constexpr array_type auto operator / ( const array_type auto& left, const auto& right )
    requires ( numeric<typename decay<decltype(left )>::value_type> or complex_type<typename decay<decltype(left )>::value_type> ) and ( numeric<decay<decltype(right)>> or complex_type<decay<decltype(right)>> )
{    
    using device     = typename decay<decltype(left )>::device_type;
    using value_type = decltype(std::declval<typename decay<decltype(left )>::value_type>() / std::declval<decay<decltype(right)>>());
    auto output = array<value_type,left_dimension,device>([&] { if constexpr ( left_dimension == 1 ) return left.size(); else return left.shape(); } ());
    device_linalg_1c_1(divide, left, right, output);
    return output;
}

constexpr array_type auto& operator += ( array_type auto& left, const array_type auto& right )
    requires ( ( numeric<typename decay<decltype(left )>::value_type> or complex_type<typename decay<decltype(left )>::value_type> ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and
             ( left_dimension == right_dimension ) and 
             same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>
{
    #ifdef debug
    if ( left.shape() != right.shape() )
        throw linalg_error("plus array with inconsistent shape (with left_shape = {}, right_shape = {})", left.shape(), right.shape());
    #endif

    using device = typename decay<decltype(left )>::device_type;
    auto& output = left;
    device_linalg_2_1(plus_equal, left, right, output);
    return left;
}

constexpr array_type auto& operator -= ( array_type auto& left, const array_type auto& right )
    requires ( ( numeric<typename decay<decltype(left )>::value_type> or complex_type<typename decay<decltype(left )>::value_type> ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and
             ( left_dimension == right_dimension ) and 
             same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>
{
    #ifdef debug
    if ( left.shape() != right.shape() )
        throw linalg_error("minus array with inconsistent shape (with left_shape = {}, right_shape = {})", left.shape(), right.shape());
    #endif
    
    using device = typename decay<decltype(left )>::device_type;
    auto& output = left;
    device_linalg_2_1(minus_equal, left, right, output);
    return left;
}

constexpr array_type auto& operator *= ( array_type auto& left, const auto& right )
    requires ( numeric<typename decay<decltype(left )>::value_type> or complex_type<typename decay<decltype(left )>::value_type> ) and ( numeric<decay<decltype(right)>> or complex_type<decay<decltype(right)>> )
{   
    using device = typename decay<decltype(left )>::device_type;
    auto& output = left;
    device_linalg_1c_1(right_scale_equal, left, right, output);
    return left;
}

constexpr array_type auto& operator *= ( array_type auto& left, const array_type auto& right )
    requires ( ( numeric<typename decay<decltype(left )>::value_type> or complex_type<typename decay<decltype(left )>::value_type> ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and
             ( left_dimension == 2 and right_dimension == 2 ) and
             same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>
{
    #ifdef debug
    if ( left.column() != right.row() )
        throw linalg_error("multiply matrix with inconsistent column and row (with left_shape = {}, right_shape = {})", left.shape(), right.shape());
    #endif
    
    using device = typename decay<decltype(left )>::device_type;
    auto& output = left;
    device_linalg_2_1(multiply_equal, left, right, output);
    return left;
}

constexpr array_type auto& operator /= ( array_type auto& left, const auto& right )
    requires ( numeric<typename decay<decltype(left )>::value_type> or complex_type<typename decay<decltype(left )>::value_type> ) and ( numeric<decay<decltype(right)>> or complex_type<decay<decltype(right)>> )
{   
    using device = typename decay<decltype(left )>::device_type;
    auto& output = left;
    device_linalg_1c_1(divide_equal, left, right, output);
    return left;
}
