#pragma once

/// Global

constexpr std::istream& operator >> ( std::istream& left, string_type auto& right )
    requires same_as<right_value_type,char> and
             ( right_type::ownership() )
{
    let tmp = right_device_type::template basic_string<char>();
    left >> tmp;
    right = std::move(tmp);
    return left;
}

constexpr std::ostream& operator << ( std::ostream& left, const string_type auto& right )
    requires same_as<right_value_type,char>
{
    using device = right_device_type;
    let right_view = basic_string_view(right);
    device::copy(right_view.begin(), right_view.end(), std::ostream_iterator<char>(left));
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

constexpr auto operator <=> ( const string_type auto& left, const string_type auto& right )
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