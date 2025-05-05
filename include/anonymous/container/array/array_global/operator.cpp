#include "detail/stringalize.cpp"

constexpr std::ostream& operator << ( std::ostream& left, const array_type auto& right )
    requires printable<right_value_type>
{
    auto string_array = detail::stringalize_array(left, right);
    detail::align_array(string_array);
    detail::print_array(left, string_array);
    return left;
}

constexpr bool operator == ( const array_type auto& left, const array_type auto& right )
    requires equalable_to<left_value_type,right_value_type> and
             (left.dimension() == right.dimension()) and
             same_as<left_device_type,right_device_type>
{
    constexpr int dim = left.dimension();
    using device = left_device_type;

    if constexpr ( dim == 1 )
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
    requires comparable_to<left_value_type,right_value_type> and
             (left.dimension() == right.dimension()) and
             same_as<left_device_type,right_device_type>
{
    constexpr int dim = left.dimension();
    using device = left_device_type;

    if constexpr ( dim == 1 )
        if ( left.contiguous() and right.contiguous() )
            return device::lexicographical_compare_three_way(left.data(), left.data() + left.size(), right.data(), right.data() + right.size());
        else
            return device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end());
    else
        if ( same_as<typename device::layout_type,std::layout_right> and left.contiguous() and right.contiguous() and left.shape() == right.shape() )
            return device::lexicographical_compare_three_way(left.data(), left.data() + left.size(), right.data(), right.data() + right.size()); // Shape should be checked explicitly.
        else
            return device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end()); // Cannot flatten as shape might not equals.
}