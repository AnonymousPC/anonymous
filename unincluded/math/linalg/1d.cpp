constexpr array_type auto convolve ( const array_type auto& left, const array_type auto& right )
    requires ( ( numeric<typename decay<decltype(left )>::value_type> or complex_type<typename decay<decltype(left )>::value_type> ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and
             ( left_dimension == 1 and right_dimension == 1 ) and 
             same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>
{
    using device     = typename decay<decltype(left )>::device_type;
    using value_type = common_type<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>;
    auto output = array<value_type,1,device>(left.size() + right.size() - 1);
    device_linalg_2_1(convolve, left, right, output);
    return output;
}

constexpr array_type auto cross ( const array_type auto& left, const array_type auto& right )
    requires ( ( numeric<typename decay<decltype(left )>::value_type> or complex_type<typename decay<decltype(left )>::value_type> ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and
             ( left_dimension == 1 and right_dimension == 1 ) and 
             same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>
{
    #ifdef debug
    if ( left.size() != 3 or right.size() != 3 )
        throw linalg_error("cross vector whose size is not 3 (with left_size = {}, right_size = {})", left.size(), right.size());
    #endif
    
    using device     = typename decay<decltype(left )>::device_type;
    using value_type = common_type<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>;
    auto output = array<value_type,1,device>(3);
    device_linalg_2_1(cross, left, right, output);
    return output;
}

constexpr auto dot ( const array_type auto& left, const array_type auto& right )
    requires ( ( numeric<typename decay<decltype(left )>::value_type> or complex_type<typename decay<decltype(left )>::value_type> ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and
             ( left_dimension == 1 and right_dimension == 1 ) and 
             same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>
{
    #ifdef debug
    if ( left.size() != right.size() )
        throw linalg_error("dot vector with inconsistent size (with left_size = {}, right_size = {})", left.size(), right.size());
    #endif
    
    using device     = typename decay<decltype(left )>::device_type;
    using value_type = common_type<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>;
    auto output = value_type();
    device_linalg_2_c(dot, left, right, output);
    return output;
}

constexpr array_type auto fft ( const array_type auto& vector )
    requires ( numeric<vector_value_type> or complex_type<vector_value_type> ) and
             ( vector_dimension == 1 )
{
    using device = vector_device_type;
    using value_type = decltype(complex(vector_value_type()));
    auto output = array<value_type,1,device>(vector.size());
    device_linalg_1_1(fft, vector, output);
    return output;
} 

constexpr array_type auto ifft ( const array_type auto& vector )
    requires complex_type<vector_value_type> and
             ( vector_dimension == 1 )
{
    using device = vector_device_type;
    using value_type = decltype(complex(vector_value_type()));
    auto output = array<value_type,1,device>(vector.size());
    device_linalg_1_1(ifft, vector, output);
    return output;
} 

constexpr array_type auto tensor ( const array_type auto& left, const array_type auto& right )
    requires ( ( numeric<typename decay<decltype(left )>::value_type> or complex_type<typename decay<decltype(left )>::value_type> ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and
             ( left_dimension == 1 and right_dimension == 1 ) and 
             same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>
{    
    using device     = typename decay<decltype(left )>::device_type;
    using value_type = common_type<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>;
    auto output = array<value_type,2,device>(left.size(), right.size());
    device_linalg_2_1(tensor, left, right, output);
    return output;
}
