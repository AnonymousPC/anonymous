constexpr bool operator == ( const container auto& left, const container auto& right ) 
    requires equalable_to<left_value_type, right_value_type > and 
             same_as     <left_device_type,right_device_type>
{
    using device = left_device_type;
    return device::equal(left.begin(), left.end(), right.begin(), right.end());
}

constexpr auto operator <=> ( const container auto& left, const container auto& right ) 
    requires comparable_to<left_value_type, right_value_type > and 
             same_as      <left_device_type,right_device_type>
{
    using device = left_device_type;
    return device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end());
}
