#pragma once

constexpr std::ostream& operator << ( std::ostream& left, const set_type auto& right )
    requires printable<right_value_type>
{
    left << '{';
    auto it = right.begin();
    while ( it != right.end() )
        it == right.begin() ? left         << *it++ otherwise
                              left << ", " << *it++;
    left << '}';
    return left;
}

constexpr bool operator == ( const set_type auto& left, const set_type auto& right )
    requires equalable_to<left_value_type, right_value_type > and 
             same_as     <left_device_type,right_device_type>
{
    if constexpr ( same_as<left_compare_type,right_compare_type> )
        return left_device_type::equal ( left.begin(), left.end(), right.begin(), right.end() );
    else
        return left_device_type::is_permutation ( left.begin(), left.end(), right.begin(), right.end() );
}

constexpr auto operator <=> ( const set_type auto& left, const set_type auto& right )
    requires comparable_to<left_value_type,  right_value_type  > and
             same_as      <left_compare_type,right_compare_type> and 
             same_as      <left_device_type, right_device_type >
{
    return left_device_type::lexicographical_compare_three_way ( left.begin(), left.end(), right.begin(), right.end() );
}

constexpr bool operator << ( const set_type auto& left, const set_type auto& right )
    requires equalable_to<left_value_type,  right_value_type  > and
             same_as     <left_compare_type,right_compare_type> and
             same_as     <left_device_type, right_device_type >
{
    return left_device_type::includes ( right.begin(), right.end(), left.begin(), left.end(), left_compare_type() );
}

constexpr bool operator >> ( const set_type auto& left, const set_type auto& right )
    requires equalable_to<left_value_type,  right_value_type  > and
             same_as     <left_compare_type,right_compare_type> and
             same_as     <left_device_type, right_device_type >
{
    return left_device_type::includes ( left.begin(), left.end(), right.begin(), right.end(), left_compare_type() );
}

constexpr std::ostream& operator << ( std::ostream& left, const map_type auto& right )
    requires printable<right_key_type> and printable<right_value_type>
{
    left << '{';
    for ( let it = right.begin(); it != right.end(); ++it )
        it == right.begin() ? left         << it->key() << ": " << it->value() otherwise
                              left << ", " << it->key() << ": " << it->value();
    left << '}';
    return left;
}

constexpr bool operator == ( const map_type auto& left, const map_type auto& right )
    requires equalable_to<left_key_type,   right_key_type   > and
             equalable_to<left_value_type, right_value_type > and 
             same_as     <left_device_type,right_device_type>
{
    if constexpr ( same_as<left_compare_type,right_compare_type> )
        return left_device_type::equal ( left.begin(), left.end(), right.begin(), right.end() );
    else
        return left_device_type::is_permutation ( left.begin(), left.end(), right.begin(), right.end() );
}

constexpr auto operator <=> ( const map_type auto& left, const map_type auto& right )
    requires comparable_to<left_key_type,    right_key_type    > and
             comparable_to<left_value_type,  right_value_type  > and
             same_as      <left_compare_type,right_compare_type> and 
             same_as      <left_device_type, right_device_type >
{
    return left_device_type::lexicographical_compare_three_way ( left.begin(), left.end(), right.begin(), right.end() );
}