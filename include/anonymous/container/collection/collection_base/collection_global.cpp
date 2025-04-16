#pragma once

constexpr std::ostream& operator << ( std::ostream& left, const set_type auto& right )
    requires printable<right_value_type>
{
    left << '{';
    auto it = right.begin();
    while ( it != right.end() )
        it == right.begin() ? left         << *it++ :
                              left << ", " << *it++;
    left << '}';
    return left;
}

constexpr bool operator == ( const set_type auto& left, const set_type auto& right )
    requires equalable_to<left_value_type, right_value_type > and 
             same_as     <left_device_type,right_device_type>
{
    using device = left_device_type;
    if constexpr ( same_as<left_compare_type,right_compare_type> )
        return device::equal(left.begin(), left.end(), right.begin(), right.end());
    else
        return device::is_permutation(left.begin(), left.end(), right.begin(), right.end());
}

constexpr auto operator <=> ( const set_type auto& left, const set_type auto& right )
    requires comparable_to<left_value_type,  right_value_type  > and
             same_as      <left_compare_type,right_compare_type> and 
             same_as      <left_device_type, right_device_type >
{
    using device = left_device_type;
    if constexpr ( requires { device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end()); } )
        return device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end());
    else
        if constexpr ( not same_as<compare_result<left_value_type,right_value_type>,std::partial_ordering> )
            return left == right                                                                         ? compare_result<left_value_type,right_value_type>::equivalent : 
                   device::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()) ? compare_result<left_value_type,right_value_type>::less       :
                                                                                                           compare_result<left_value_type,right_value_type>::greater;  
        else
            return left == right                                                                             ? std::partial_ordering::equivalent : 
                   device::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end())     ? std::partial_ordering::less       :
                   not device::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()) ? std::partial_ordering::greater    :
                                                                                                               std::partial_ordering::unordered; 
}

constexpr bool operator << ( const set_type auto& left, const set_type auto& right )
    requires equalable_to<left_value_type,  right_value_type  > and
             same_as     <left_compare_type,right_compare_type> and
             same_as     <left_device_type, right_device_type >
{
    using device = left_device_type;
    return device::includes(right.begin(), right.end(), left.begin(), left.end(), left_compare_type());
}

constexpr bool operator >> ( const set_type auto& left, const set_type auto& right )
    requires equalable_to<left_value_type,  right_value_type  > and
             same_as     <left_compare_type,right_compare_type> and
             same_as     <left_device_type, right_device_type >
{
    using device = left_device_type;
    return device::includes(left.begin(), left.end(), right.begin(), right.end(), left_compare_type());
}

constexpr std::ostream& operator << ( std::ostream& left, const map_type auto& right )
    requires printable<right_key_type> and printable<right_value_type>
{
    left << '{';
    for ( auto it = right.begin(); it != right.end(); ++it )
        it == right.begin() ? left         << it->key() << ": " << it->value() :
                              left << ", " << it->key() << ": " << it->value();
    left << '}';
    return left;
}

constexpr bool operator == ( const map_type auto& left, const map_type auto& right )
    requires equalable_to<left_key_type,   right_key_type   > and
             equalable_to<left_value_type, right_value_type > and 
             same_as     <left_device_type,right_device_type>
{
    using device = left_device_type;
    if constexpr ( same_as<left_compare_type,right_compare_type> )
        return device::equal ( left.begin(), left.end(), right.begin(), right.end() );
    else
        return device::is_permutation(left.begin(), left.end(), right.begin(), right.end());
}

constexpr auto operator <=> ( const map_type auto& left, const map_type auto& right )
    requires comparable_to<left_key_type,    right_key_type    > and
             comparable_to<left_value_type,  right_value_type  > and
             same_as      <left_compare_type,right_compare_type> and 
             same_as      <left_device_type, right_device_type >
{
    using device = left_device_type;
    if constexpr ( requires { device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end()); } )
        return device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end());
    else
        if constexpr ( not same_as<compare_result<left_value_type,right_value_type>,std::partial_ordering> )
            return left == right                                                                         ? compare_result<left_value_type,right_value_type>::equivalent : 
                   device::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()) ? compare_result<left_value_type,right_value_type>::less       :
                                                                                                           compare_result<left_value_type,right_value_type>::greater;  
        else
            return left == right                                                                             ? std::partial_ordering::equivalent : 
                   device::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end())     ? std::partial_ordering::less       :
                   not device::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()) ? std::partial_ordering::greater    :
                                                                                                               std::partial_ordering::unordered; 
}