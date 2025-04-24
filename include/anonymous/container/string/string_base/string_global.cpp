constexpr std::istream& operator >> ( std::istream& left, string_type auto& right )
    requires is_class<decay<decltype(right)>> and ( decay<decltype(right)>::ownership() )
{
    return left >> static_cast<typename decay<decltype(right)>::device_type::basic_string<typename decay<decltype(right)>::value_type>&>(right);
}

constexpr std::ostream& operator << ( std::ostream& left, const string_type auto& right )
    requires is_class<decay<decltype(right)>>
{
    return left << static_cast<typename decay<decltype(right)>::device_type::basic_string<typename decay<decltype(right)>::value_type>&>(right);
}

constexpr bool operator == ( const string_type auto& left, const string_type auto& right )
    requires same_as<typename decay<decltype(left )>::value_type, typename decay<decltype(right)>::value_type > and
             same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>
{
    using device = typename decay<decltype(left )>::device_type;
    auto left_view  = basic_string_view(left);
    auto right_view = basic_string_view(right);
    return device::equal(left_view.begin(), left_view.end(), right_view.begin(), right_view.end());
}

constexpr std::strong_ordering operator <=> ( const string_type auto& left, const string_type auto& right )
    requires same_as<typename decay<decltype(left )>::value_type, typename decay<decltype(right)>::value_type > and
             same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>
{
    using device = typename decay<decltype(left )>::device_type;
    auto left_view  = basic_string_view(left);
    auto right_view = basic_string_view(right);
    if constexpr ( requires { device::lexicographical_compare_three_way(left_view.begin(), left_view.end(), right_view.begin(), right_view.end()); } )
        return device::lexicographical_compare_three_way(left_view.begin(), left_view.end(), right_view.begin(), right_view.end());
    else   
        return left_view == right_view                                                                                   ? std::strong_ordering::equal :
               device::lexicographical_compare(left_view.begin(), left_view.end(), right_view.begin(), right_view.end()) ? std::strong_ordering::less  :
                                                                                                                           std::strong_ordering::greater;
}

constexpr string_type auto operator + ( const string_type auto& left, const string_type auto& right )
    requires same_as<typename decay<decltype(left )>::value_type, typename decay<decltype(right)>::value_type > and 
             same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>
{
    using device = typename decay<decltype(left )>::device_type;
    auto left_view  = basic_string_view(left);
    auto right_view = basic_string_view(right);
    auto str        = basic_string<typename decay<decltype(left )>::value_type,typename decay<decltype(left )>::device_type>(left_view.size() + right_view.size(), typename decay<decltype(left )>::value_type('\0'));
    device::copy(left_view .begin(), left_view .end(), str.begin());
    device::copy(right_view.begin(), right_view.end(), str.begin() + left_view.size());
    return str;
}

constexpr string_type auto& operator += ( string_type auto& left, const string_type auto& right )
    requires same_as<typename decay<decltype(left )>::value_type, typename decay<decltype(right)>::value_type > and 
             same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type> and 
             ( decay<decltype(left)>::ownership() )
{
    using device = typename decay<decltype(left )>::device_type;
    auto right_view = basic_string_view(right);
    auto old_size   = left.size();
    left.resize(left.size() + right_view.size());
    device::copy(right_view.begin(), right_view.end(), left.begin() + old_size);
    return left;
}

constexpr string_type auto operator * ( const string_type auto& left, int_type auto right )
{
    #ifdef debug
        if ( right < 0 )
            throw value_error("multiply string with negative times {}", right);
    #endif
    using device = typename decay<decltype(left )>::device_type;
    auto left_view = basic_string_view(left);
    auto str       = basic_string<typename decay<decltype(left )>::value_type,typename decay<decltype(left )>::device_type>(left.size() * right, typename decay<decltype(left )>::value_type('\0'));
    for ( int i in range(right) )
        device::copy(left_view.begin(), left_view.end(), str.begin() + left_view.size() * (i - 1));
    return str;
}

constexpr string_type auto operator * ( int_type auto left, const string_type auto& right )
{
    #ifdef debug
        if ( left < 0 )
            throw value_error("multiply string with negative times {}", left);
    #endif
    using device = typename decay<decltype(right)>::device_type;
    auto right_view = basic_string_view(right);
    auto str        = basic_string<typename decay<decltype(right)>::value_type,typename decay<decltype(right)>::device_type>(left * right.size(), typename decay<decltype(right)>::value_type('\0'));
    for ( int i in range(left) )
        device::copy(right_view.begin(), right_view.end(), str.begin() + right_view.size() * (i - 1));
    return str;
}

constexpr string_type auto& operator *= ( string_type auto& left, int_type auto right )
    requires ( decay<decltype(left)>::ownership() )
{    
    #ifdef debug
        if ( right < 0 )
            throw value_error("multiply string with negative times {}", right);
    #endif
    using device = typename decay<decltype(left )>::device_type;
    auto old_size = left.size();
    left.resize(left.size() * right);
    for ( int i in range(2, right) )
        device::copy(left.begin(), left.begin() + old_size, left.begin() + old_size * (i - 1));
    return left;
}