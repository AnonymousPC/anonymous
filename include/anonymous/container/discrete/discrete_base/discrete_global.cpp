constexpr std::ostream& operator << ( std::ostream& left, const pair_type auto& right )
    requires printable<typename remove_cvref<decltype(right)>::key_type  > and 
             printable<typename remove_cvref<decltype(right)>::value_type>
{
    return left << '(' << right.key() << ", " << right.value() << ')';
}

constexpr bool operator == ( const pair_type auto& left, const pair_type auto& right )
    requires equalable_to<typename remove_cvref<decltype(left)>::key_type,  typename remove_cvref<decltype(right)>::key_type  > and 
             equalable_to<typename remove_cvref<decltype(left)>::value_type,typename remove_cvref<decltype(right)>::value_type>
{
    return left.key() == right.key() and left.value() == right.value();
}

constexpr auto operator <=> ( const pair_type auto& left, const pair_type auto& right )
    requires comparable_to<typename remove_cvref<decltype(left)>::key_type,  typename remove_cvref<decltype(right)>::key_type  > and 
             comparable_to<typename remove_cvref<decltype(left)>::value_type,typename remove_cvref<decltype(right)>::value_type>
{
    using type = common_type<decltype(left.key()<=>right.key()),decltype(left.value()<=>right.value())>;
    if ( auto k = left.key() <=> right.key(); k != decltype(k)::equivalent )
        return type(k);
    else
        return type(left.value() <=> right.value());
}

constexpr pair_type auto operator + ( const pair_type auto& left, const pair_type auto& right )
    requires plusable_to<typename remove_cvref<decltype(left)>::key_type,  typename remove_cvref<decltype(right)>::key_type  > and 
             plusable_to<typename remove_cvref<decltype(left)>::value_type,typename remove_cvref<decltype(right)>::value_type>
{
    return pair ( left.key() + right.key(), left.value() + right.value() );
}

constexpr pair_type auto operator - ( const pair_type auto& left, const pair_type auto& right )
    requires minusable_to<typename remove_cvref<decltype(left)>::key_type,  typename remove_cvref<decltype(right)>::key_type  > and 
             minusable_to<typename remove_cvref<decltype(left)>::value_type,typename remove_cvref<decltype(right)>::value_type>
{
    return pair ( left.key() - right.key(), left.value() - right.value() );
}

constexpr pair_type auto operator * ( const pair_type auto& left, const auto& right )
    requires multipliable_to<typename remove_cvref<decltype(left)>::key_type,  remove_cvref<decltype(right)>> and 
             multipliable_to<typename remove_cvref<decltype(left)>::value_type,remove_cvref<decltype(right)>> and 
             ( not pair_type<remove_cvref<decltype(right)>> )
{
    return pair ( left.key() * right, left.value() * right );
}

constexpr pair_type auto operator * ( const pair_type auto& left, const auto& right )
    requires multipliable_to<remove_cvref<decltype(left)>,typename remove_cvref<decltype(right)>::key_type  > and 
             multipliable_to<remove_cvref<decltype(left)>,typename remove_cvref<decltype(right)>::value_type> and 
             ( not pair_type<remove_cvref<decltype(left)>> )
{
    return pair ( left * right.value(), left * right.value() );
}

constexpr pair_type auto operator / ( const pair_type auto& left, const auto& right )
    requires dividable_to<typename remove_cvref<decltype(left)>::key_type,  remove_cvref<decltype(right)>> and 
             dividable_to<typename remove_cvref<decltype(left)>::value_type,remove_cvref<decltype(right)>> and 
             ( not pair_type<remove_cvref<decltype(right)>> )
{
    return pair ( left.key() / right, left.value() / right );
}





// constexpr std::ostream& operator << ( std::ostream& left, const tuple_type auto& right )
//     requires detail::tuplewise_printable<remove_cvref<decltype(right)>>
// {
//     left << '(';
//     for_constexpr<1,tuple_size<remove_cvref<decltype(right)>>-1>([&] <int index> { left << right.template value<index>() << ", "; });
//     if constexpr ( tuple_size<remove_cvref<decltype(right)>> != 0 )
//         left << right.template value<-1>();
//     left << ')';
//     return left;
// }

// constexpr bool operator == ( const tuple_type auto& left, const tuple_type auto& right )
//     requires detail::tuplewise_equalable_to<remove_cvref<decltype(left)>,remove_cvref<decltype(right)>>
// {
//     return all_of_constexpr<1,tuple_size<remove_cvref<decltype(left)>>>([&] <int index> { return left.template value<index>() == right.template value<index>(); });
// }

// constexpr auto operator <=> ( const tuple_type auto& left, const tuple_type auto& right )
//     requires detail::tuplewise_comparable_to<remove_cvref<decltype(left)>,remove_cvref<decltype(right)>>
// {
    
// }

// constexpr tuple_type auto operator + ( const tuple_type auto& left, const tuple_type auto& right )
//     requires detail::tuplewise_plusable_to<remove_cvref<decltype(left)>,remove_cvref<decltype(right)>>
// {
//     return detail::tuplewise_plus ( left, right );
// }

// constexpr tuple_type auto operator - ( const tuple_type auto& left, const tuple_type auto& right )
//     requires detail::tuplewise_minusable_to<remove_cvref<decltype(left)>,remove_cvref<decltype(right)>>
// {
//     return detail::tuplewise_minus ( left, right );
// }

// constexpr tuple_type auto operator * ( const tuple_type auto& left, const auto& right )
//     requires detail::tuplewise_each_multipliable_to<remove_cvref<decltype(left)>,remove_cvref<decltype(right)>> and ( not tuple_type<remove_cvref<decltype(right)>> )
// {
//     return detail::tuplewise_each_multiply ( left, right );
// }

// constexpr tuple_type auto operator * ( const auto& left, const tuple_type auto& right )
//     requires detail::tuplewise_multipliable_to_each<remove_cvref<decltype(left)>,remove_cvref<decltype(right)>> and ( not tuple_type<remove_cvref<decltype(left)>> )
// {
//     return detail::tuplewise_multiply_each ( left, right );
// }

// constexpr tuple_type auto operator / ( const tuple_type auto& left, const auto& right )
//     requires detail::tuplewise_each_dividable_to<remove_cvref<decltype(left)>,remove_cvref<decltype(right)>> and ( not tuple_type<remove_cvref<decltype(right)>> )
// {
//     return detail::tuplewise_each_divide ( left, right );
// }










