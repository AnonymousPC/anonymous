#pragma once

#define left_value_type   typename decay<decltype(left )>::value_type
#define right_value_type  typename decay<decltype(right)>::value_type
#define left_dimension             decay<decltype(left )>::dimension()
#define right_dimension            decay<decltype(left )>::dimension()
#define left_device_type  typename decay<decltype(left )>::device_type
#define right_device_type typename decay<decltype(left )>::device_type

constexpr std::ostream& operator << ( std::ostream& left, const array_type auto& right )
    requires printable<right_value_type>
{
    let string_array = detail::stringalize_array(left, right);
    detail::align_array(string_array);
    detail::print_array(left, string_array);
    return left;
}

constexpr bool operator == ( const array_type auto& left, const array_type auto& right )
    requires equalable_to<left_value_type,right_value_type> and
             (left_dimension == right_dimension) and
             same_as<left_device_type,right_device_type>
{
    using device = left_device_type;
    if constexpr ( left_dimension == 1 )
        if ( left.contiguous() and right.contiguous() )
            return device::equal_to(left.data(), left.data() + left.size(), right.data(), right.data() + right.size());
        else
            return device::equal_to(left.begin(), left.end(), right.begin(), right.end());
    else
        if ( left.contiguous() and right.contiguous() )
            return left.shape() == right.shape() and device::equal_to(left.data(), left.data() + left.size(), right.data(), right.data() + right.size()); // Shape should be checked explicitly.
        else
            return device::equal_to(left.begin(), left.end(), right.begin(), right.end());
}

constexpr auto operator <=> ( const array_type auto& left, const array_type auto& right )
    requires comparable_to<left_value_type,right_value_type> and
             (left_dimension == right_dimension) and
             same_as<left_device_type,right_device_type>
{
    using device = left_device_type;
    if constexpr ( left_dimension == 1 )
        if ( left.contiguous() and right.contiguous() )
            return device::lexicographical_compare_three_way(left.data(), left.data() + left.size(), right.data(), right.data() + right.size());
        else
            return device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end());
    else
        if ( same_as<left_device_type::layout_type,std::layout_right> and
             left.contiguous() and right.contiguous() and 
             left.shape() == right.shape() )
            return device::lexicographical_compare_three_way(left.data(), left.data() + left.size(), right.data(), right.data() + right.size()); // Shape should be checked explicitly.
        else
            return device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end()); // Cannot flatten as shape might not equals.
}


#undef left_value_type
#undef right_value_type
#undef left_dimension
#undef right_dimension
#undef left_device_type
#undef right_device_type