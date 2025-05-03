constexpr std::ostream& operator << ( std::ostream& left, const array_type auto& right )
    requires printable<typename decay<decltype(right)>::value_type>
{
    auto string_array = detail::stringalize_array(left, right);
    detail::align_array(string_array);
    detail::print_array(left, string_array);
    return left;
}

constexpr bool operator == ( const array_type auto& left, const array_type auto& right )
    requires equalable_to<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type> and
             (decay<decltype(left)>::dimension() == decay<decltype(right)>::dimension()) and
             same_as<typename decay<decltype(left)>::device_type,typename decay<decltype(right)>::device_type>
{
    using device = typename decay<decltype(left)>::device_type;
    if constexpr ( decay<decltype(left)>::dimension() == 1 )
        if ( left.contiguous() and right.contiguous() )
            return device::equal(left.data(), left.data() + left.size(), right.data(), right.data() + right.size());
        else
            return device::equal(left.begin(), left.end(), right.begin(), right.end());
    else
        if ( left.contiguous() and right.contiguous() )
            return left.shape() == right.shape() and device::equal(left.data(), left.data() + left.size(), right.data(), right.data() + right.size()); // Shape should be checked explicitly.
        else
            return device::equal(left.begin(), left.end(), right.begin(), right.end());
}

constexpr auto operator <=> ( const array_type auto& left, const array_type auto& right )
    requires comparable_to<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type> and
             (decay<decltype(left)>::dimension() == decay<decltype(right)>::dimension()) and
             same_as<typename decay<decltype(left)>::device_type,typename decay<decltype(right)>::device_type>
{
    using device = typename decay<decltype(left)>::device_type;
    if constexpr ( decay<decltype(left)>::dimension() == 1 )
        if ( left.contiguous() and right.contiguous() )
            return device::lexicographical_compare_three_way(left.data(), left.data() + left.size(), right.data(), right.data() + right.size());
        else
            return device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end());
    else
        if ( same_as<typename decay<decltype(left)>::device_type::layout_type,std::layout_right> and
             left.contiguous() and right.contiguous() and 
             left.shape() == right.shape() )
            return device::lexicographical_compare_three_way(left.data(), left.data() + left.size(), right.data(), right.data() + right.size()); // Shape should be checked explicitly.
        else
            return device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end()); // Cannot flatten as shape might not equals.
}