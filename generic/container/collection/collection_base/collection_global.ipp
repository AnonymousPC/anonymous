#pragma once

/// Adaptor

template < class type, class original_less >
struct as_compares
{
    constexpr static const auto less     = original_less();
    constexpr static const auto equal_to = std::equal_to<>();
};

template < class type1, class type2, class original_key_less >
struct as_key_compares
{
    constexpr static const auto less = [] ( const auto& a, const auto& b )
    {
        if constexpr ( std::convertible_to<decay<decltype(a)>,map_pair<type1,type2>> and
                       std::convertible_to<decay<decltype(b)>,map_pair<type1,type2>> )
            return original_key_less() ( a.key(), b.key() );
        else if constexpr ( std::convertible_to<decay<decltype(a)>,map_pair<type1,type2>> )
            return original_key_less() ( a.key(), b );
        else
            return original_key_less() ( a, b.key() );
    };

    constexpr static const auto equal_to = [] ( const auto& a, const auto& b )
    {
        if constexpr ( std::convertible_to<decay<decltype(a)>,map_pair<type1,type2>> and
                       std::convertible_to<decay<decltype(b)>,map_pair<type1,type2>> )
            return std::equal_to<>() ( a.key(), b.key() );
        else if constexpr ( std::convertible_to<decay<decltype(a)>,map_pair<type1,type2>> )
            return std::equal_to<>() ( a.key(), b );
        else
            return std::equal_to<>() ( a, b.key() );
    };
};

template < class type1, class type2, class original_value_less >
struct as_value_pointer_compares
{
    constexpr static const auto less = [] ( const auto& a, const auto& b )
    {
        if constexpr ( std::convertible_to<decay<decltype(a)>,pair<const type1,const type2>> and // Tip: the above as_key_compares turns pair<const key,value> into map_pair<key,value>, and then std::convertible_to is ok.
                       std::convertible_to<decay<decltype(b)>,pair<const type1,const type2>> )   // I wonder how to change this :)
            return original_value_less() ( *a.value(), *b.value() );
        else if constexpr ( std::convertible_to<decay<decltype(a)>,pair<const type1,type2>> )
            return original_value_less() ( *a.value(), *b );
        else
            return original_value_less() ( *a, *b.value() );
    };

    constexpr static const auto equal_to = [] ( const auto& a, const auto& b )
    {
        if constexpr ( std::convertible_to<decay<decltype(a)>,pair<const type1,const type2>> and
                       std::convertible_to<decay<decltype(b)>,pair<const type1,const type2>> )
            return std::equal_to<>() ( *a.value(), *b.value() );
        else if constexpr ( std::convertible_to<decay<decltype(a)>,pair<const type1,type2>> )
            return std::equal_to<>() ( *a.value(), *b );
        else
            return std::equal_to<>() ( *a, *b.value() );
    };
};




/// Global

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
    requires equalable_to<left_value_type,right_value_type>
{
    if constexpr ( std::same_as<left_compare_type,right_compare_type> )
        return std::equal ( left.begin(), left.end(), right.begin(), right.end() );
    else
        return std::is_permutation ( left.begin(), left.end(), right.begin(), right.end() );
}

constexpr auto operator <=> ( const set_type auto& left, const set_type auto& right )
    requires comparable_to<left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>
{
    return std::lexicographical_compare_three_way ( left.begin(), left.end(), right.begin(), right.end() );
}

constexpr bool operator << ( const set_type auto& left, const set_type auto& right )
    requires equalable_to<left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>
{
    using compare_type = right_compare_type;
    return std::includes ( right.begin(), right.end(), left.begin(), left.end(), compare_type() );
}

constexpr bool operator >> ( const set_type auto& left, const set_type auto& right )
    requires equalable_to<left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>
{
    using compare_type = left_compare_type;
    return std::includes ( left.begin(), left.end(), right.begin(), right.end(), compare_type() );
}

constexpr set_type auto operator + ( const set_type auto& left, const set_type auto& right )
    requires std::same_as<left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>
{
    using value_type   = left_value_type;
    using compare_type = left_compare_type;

    let s = flat_set<value_type,compare_type>();
    s.data_handle().resize ( left.size() + right.size() );
    let it = std::set_union ( left.begin(), left.end(), right.begin(), right.end(), s.data_handle().begin(), compare_type() );
    s.data_handle().resize ( it - s.data_handle().begin() );

    return s;
}

constexpr set_type auto operator - ( const set_type auto& left, const set_type auto& right )
    requires std::same_as<left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>
{
    using value_type   = left_value_type;
    using compare_type = left_compare_type;

    let s = flat_set<value_type,compare_type>();
    s.data_handle().resize ( left.size() );
    let it = std::set_difference ( left.begin(), left.end(), right.begin(), right.end(), s.data_handle().begin(), compare_type() );
    s.data_handle().resize ( it - s.data_handle().begin() );

    return s;
}

constexpr set_type auto operator | ( const set_type auto& left, const set_type auto& right )
    requires std::same_as<left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>
{
    return left + right;
}

constexpr set_type auto operator & ( const set_type auto& left, const set_type auto& right )
    requires std::same_as<left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>
{
    using value_type   = left_value_type;
    using compare_type = left_compare_type;

    let s = flat_set<value_type,compare_type>();
    s.data_handle().resize ( std::max ( left.size(), right.size() ) );
    let it = std::set_intersection ( left.begin(), left.end(), right.begin(), right.end(), s.data_handle().begin(), compare_type() );
    s.data_handle().resize ( it - s.data_handle().begin() );

    return s;
}

constexpr set_type auto operator ^ ( const set_type auto& left, const set_type auto& right )
    requires std::same_as<left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>
{
    using value_type   = left_value_type;
    using compare_type = left_compare_type;

    let s = flat_set<value_type,compare_type>();
    s.data_handle().resize ( left.size() + right.size() );
    let it = std::set_symmetric_difference ( left.begin(), left.end(), right.begin(), right.end(), s.data_handle().begin(), compare_type() );
    s.data_handle().resize ( it - s.data_handle().begin() );

    return s;
}

constexpr set_type auto& operator += ( set_type auto& left, const set_type auto& right )
    requires requires { left = left + right; }
{
    if constexpr ( requires { left.data_handle().resize(0); } ) // If it can resize directly.
    {
        let sz = left.size();
        left.data_handle().resize ( left.size() + right.size() );
        std::copy ( right.begin(), right.end(), left.begin() + sz );
        std::inplace_merge ( left.begin(), left.begin() + sz, left.end() );
        return left;
    }

    else
        return left = left + right;
}

constexpr set_type auto& operator -= ( set_type auto& left, const set_type auto& right )
    requires requires { left = left + right; }
{
    return left = left - right;
}

constexpr set_type auto& operator |= ( set_type auto& left, const set_type auto& right )
    requires requires { left = left + right; }
{
    return left += right;
}

constexpr set_type auto& operator &= ( set_type auto& left, const set_type auto& right )
    requires requires { left = left + right; }
{
    return left = left & right;
}

constexpr set_type auto& operator ^= ( set_type auto& left, const set_type auto& right )
    requires requires { left = left + right; }
{
    return left = left ^ right;
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
    requires equalable_to<left_key_type,right_key_type> and equalable_to<left_value_type,right_value_type>
{
    if constexpr ( std::same_as<left_key_compare_type,right_key_compare_type> )
        return std::equal ( left.begin(), left.end(), right.begin(), right.end() );
    else
        return std::is_permutation ( left.begin(), left.end(), right.begin(), right.end() );
}

constexpr auto operator <=> ( const map_type auto& left, const map_type auto& right )
    requires comparable_to<left_key_type,right_key_type> and comparable_to<left_value_type,right_value_type> and std::same_as<left_key_compare_type,right_key_compare_type>
{
    return std::lexicographical_compare_three_way ( left.begin(), left.end(), right.begin(), right.end() );
}