#pragma once

#define left_type         decay<decltype(left )>
#define right_type        decay<decltype(right)>
#define left_value_type   typename decltype(basic_string_view(left ))::value_type
#define right_value_type  typename decltype(basic_string_view(right))::value_type
#define left_device_type  typename decltype(basic_string_view(left ))::device_type
#define right_device_type typename decltype(basic_string_view(right))::device_type

/// Global

constexpr std::istream& operator >> ( std::istream& left, string_type auto& right )
    requires ( right_type::ownership() )
{
    right.clear();
    [[maybe_unused]] let entry = std::istream::sentry(left, false);
    while ( true )
    {
        let buf = right_value_type(left.get());
        if ( not std::isspace(buf) and not left.eof() )
            right.push(buf);
        else
        {
            left.unget();
            break;
        }
    }
    return left;
}

constexpr std::ostream& operator << ( std::ostream& left, const string_type auto& right )
{
    using device = right_device_type;
    [[maybe_unused]] let entry = std::ostream::sentry(left);
    device::copy(right.begin(), right.end(), std::ostream_iterator<right_value_type>(left));
    return left;
}

constexpr bool operator == ( const string_type auto& left, const string_type auto& right )
    requires same_as<left_value_type, right_value_type > and
             same_as<left_device_type,right_device_type>
{
    using device = left_device_type;
    let left_view  = basic_string_view(left);
    let right_view = basic_string_view(right);
    return device::equal(left_view.begin(), left_view.end(), right_view.begin(), right_view.end());
}

constexpr std::strong_ordering operator <=> ( const string_type auto& left, const string_type auto& right )
    requires same_as<left_value_type, right_value_type > and
             same_as<left_device_type,right_device_type>
{
    using device = left_device_type;
    let left_view  = basic_string_view(left);
    let right_view = basic_string_view(right);
    if constexpr ( requires { device::lexicographical_compare_three_way(left_view.begin(), left_view.end(), right_view.begin(), right_view.end()); } )
        return device::lexicographical_compare_three_way(left_view.begin(), left_view.end(), right_view.begin(), right_view.end());
    else   
        return left_view == right_view                                                                                   ? std::strong_ordering::equal otherwise
               device::lexicographical_compare(left_view.begin(), left_view.end(), right_view.begin(), right_view.end()) ? std::strong_ordering::less  otherwise
                                                                                                                           std::strong_ordering::greater;
}

constexpr string_type auto operator + ( const string_type auto& left, const string_type auto& right )
    requires same_as<left_value_type, right_value_type > and 
             same_as<left_device_type,right_device_type>
{
    using device = left_device_type;
    let left_view  = basic_string_view(left);
    let right_view = basic_string_view(right);
    let str        = basic_string<left_value_type,left_device_type>(left_view.size() + right_view.size(), left_value_type('\0'));
    device::copy(left_view .begin(), left_view .end(), str.begin());
    device::copy(right_view.begin(), right_view.end(), str.begin() + left_view.size());
    return str;
}

constexpr string_type auto& operator += ( string_type auto& left, const string_type auto& right )
    requires same_as<left_value_type, right_value_type > and 
             same_as<left_device_type,right_device_type> and 
             ( left_type::ownership() )
{
    using device = left_device_type;
    let right_view = basic_string_view(right);
    let old_size   = left.size();
    left.resize(left.size() + right_view.size());
    device::copy(right_view.begin(), right_view.end(), left.begin() + old_size);
    return left;
}

constexpr string_type auto operator * ( const string_type auto& left, int_type auto right )
{
    #if debug
        if ( right < 0 )
            throw value_error("multiply string with negative times {}", right);
    #endif
    using device = left_device_type;
    let left_view = basic_string_view(left);
    let str       = basic_string<left_value_type,left_device_type>(left.size() * right, left_value_type('\0'));
    for ( int i in range(right) )
        device::copy(left_view.begin(), left_view.end(), str.begin() + left_view.size() * (i - 1));
    return str;
}

constexpr string_type auto operator * ( int_type auto left, const string_type auto& right )
{
    #if debug
        if ( left < 0 )
            throw value_error("multiply string with negative times {}", left);
    #endif
    using device = right_device_type;
    let right_view = basic_string_view(right);
    let str        = basic_string<right_value_type,right_device_type>(left * right.size(), right_value_type('\0'));
    for ( int i in range(left) )
        device::copy(right_view.begin(), right_view.end(), str.begin() + right_view.size() * (i - 1));
    return str;
}

constexpr string_type auto& operator *= ( string_type auto& left, int_type auto right )
    requires ( left_type::ownership() )
{    
    #if debug
        if ( right < 0 )
            throw value_error("multiply string with negative times {}", right);
    #endif
    using device = left_device_type;
    let old_size = left.size();
    left.resize(left.size() * right);
    for ( int i in range(2, right) )
        device::copy(left.begin(), left.begin() + old_size, left.begin() + old_size * (i - 1));
    return left;
}

#undef left_type
#undef right_type
#undef left_value_type
#undef right_value_type
#undef left_device_type
#undef right_device_type