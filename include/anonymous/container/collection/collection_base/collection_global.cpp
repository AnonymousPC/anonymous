constexpr std::ostream& operator << ( std::ostream& left, const set_type auto& right )
    requires printable<typename decay<decltype(right)>::value_type>
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
    requires equalable_to<typename decay<decltype(left)>::value_type, typename decay<decltype(right)>::value_type > and 
             same_as     <typename decay<decltype(left)>::device_type,typename decay<decltype(right)>::device_type>
{
    using device = typename decay<decltype(left)>::device_type;
    if constexpr ( same_as<typename decay<decltype(left)>::compare_type,typename decay<decltype(right)>::compare_type> )
        return device::equal(left.begin(), left.end(), right.begin(), right.end());
    else
        return device::is_permutation(left.begin(), left.end(), right.begin(), right.end());
}

constexpr auto operator <=> ( const set_type auto& left, const set_type auto& right )
    requires comparable_to<typename decay<decltype(left)>::value_type,  typename decay<decltype(right)>::value_type  > and
             same_as      <typename decay<decltype(left)>::compare_type,typename decay<decltype(right)>::compare_type> and 
             same_as      <typename decay<decltype(left)>::device_type, typename decay<decltype(right)>::device_type >
{
    using device = typename decay<decltype(left)>::device_type;
    if constexpr ( requires { device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end()); } )
        return device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end());
    else
        if constexpr ( not same_as<compare_result<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type>,std::partial_ordering> )
            return left == right                                                                         ? compare_result<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type>::equivalent : 
                   device::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()) ? compare_result<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type>::less       :
                                                                                                           compare_result<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type>::greater;  
        else
            return left == right                                                                             ? std::partial_ordering::equivalent : 
                   device::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end())     ? std::partial_ordering::less       :
                   not device::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()) ? std::partial_ordering::greater    :
                                                                                                               std::partial_ordering::unordered; 
}

constexpr bool operator << ( const set_type auto& left, const set_type auto& right )
    requires equalable_to<typename decay<decltype(left)>::value_type,  typename decay<decltype(right)>::value_type  > and
             same_as     <typename decay<decltype(left)>::compare_type,typename decay<decltype(right)>::compare_type> and
             same_as     <typename decay<decltype(left)>::device_type, typename decay<decltype(right)>::device_type >
{
    using device = typename decay<decltype(left)>::device_type;
    return device::includes(right.begin(), right.end(), left.begin(), left.end(), typename decay<decltype(left)>::compare_type());
}

constexpr bool operator >> ( const set_type auto& left, const set_type auto& right )
    requires equalable_to<typename decay<decltype(left)>::value_type,  typename decay<decltype(right)>::value_type  > and
             same_as     <typename decay<decltype(left)>::compare_type,typename decay<decltype(right)>::compare_type> and
             same_as     <typename decay<decltype(left)>::device_type, typename decay<decltype(right)>::device_type >
{
    using device = typename decay<decltype(left)>::device_type;
    return device::includes(left.begin(), left.end(), right.begin(), right.end(), typename decay<decltype(left)>::compare_type());
}

constexpr std::ostream& operator << ( std::ostream& left, const map_type auto& right )
    requires printable<typename decay<decltype(right)>::key_type> and printable<typename decay<decltype(right)>::value_type>
{
    left << '{';
    for ( auto it = right.begin(); it != right.end(); ++it )
        it == right.begin() ? left         << it->key() << ": " << it->value() :
                              left << ", " << it->key() << ": " << it->value();
    left << '}';
    return left;
}

constexpr bool operator == ( const map_type auto& left, const map_type auto& right )
    requires equalable_to<typename decay<decltype(left)>::key_type,   typename decay<decltype(right)>::key_type   > and
             equalable_to<typename decay<decltype(left)>::value_type, typename decay<decltype(right)>::value_type > and 
             same_as     <typename decay<decltype(left)>::device_type,typename decay<decltype(right)>::device_type>
{
    using device = typename decay<decltype(left)>::device_type;
    if constexpr ( same_as<typename decay<decltype(left)>::compare_type,typename decay<decltype(right)>::compare_type> )
        return device::equal ( left.begin(), left.end(), right.begin(), right.end() );
    else
        return device::is_permutation(left.begin(), left.end(), right.begin(), right.end());
}

constexpr auto operator <=> ( const map_type auto& left, const map_type auto& right )
    requires comparable_to<typename decay<decltype(left)>::key_type,    typename decay<decltype(right)>::key_type    > and
             comparable_to<typename decay<decltype(left)>::value_type,  typename decay<decltype(right)>::value_type  > and
             same_as      <typename decay<decltype(left)>::compare_type,typename decay<decltype(right)>::compare_type> and 
             same_as      <typename decay<decltype(left)>::device_type, typename decay<decltype(right)>::device_type >
{
    using device = typename decay<decltype(left)>::device_type;
    if constexpr ( requires { device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end()); } )
        return device::lexicographical_compare_three_way(left.begin(), left.end(), right.begin(), right.end());
    else
        if constexpr ( not same_as<compare_result<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type>,std::partial_ordering> )
            return left == right                                                                         ? compare_result<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type>::equivalent : 
                   device::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()) ? compare_result<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type>::less       :
                                                                                                           compare_result<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type>::greater;  
        else
            return left == right                                                                             ? std::partial_ordering::equivalent : 
                   device::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end())     ? std::partial_ordering::less       :
                   not device::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()) ? std::partial_ordering::greater    :
                                                                                                               std::partial_ordering::unordered; 
}