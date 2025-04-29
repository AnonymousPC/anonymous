constexpr std::ostream& operator << ( std::ostream& left, const pair_type auto& right )
    requires printable<right_key_type  > and 
             printable<right_value_type>
{
    return left << '(' << right.key() << ", " << right.value() << ')';
}

constexpr bool operator == ( const pair_type auto& left, const pair_type auto& right )
    requires equalable_to<left_key_type,  right_key_type  > and 
             equalable_to<left_value_type,right_value_type>
{
    return left.key() == right.key() and left.value() == right.value();
}

constexpr auto operator <=> ( const pair_type auto& left, const pair_type auto& right )
    requires comparable_to<left_key_type,  right_key_type  > and 
             comparable_to<left_value_type,right_value_type>
{
    using type = common_type<decltype(left.key()<=>right.key()),decltype(left.value()<=>right.value())>;
    if ( auto k = (left.key() <=> right.key()); k != decltype(k)::equivalent )
        return type(k);
    else
        return type(left.value() <=> right.value());
}

constexpr pair_type auto operator + ( const pair_type auto& left, const pair_type auto& right )
    requires plusable_to<left_key_type,  right_key_type  > and 
             plusable_to<left_value_type,right_value_type>
{
    return pair ( left.key() + right.key(), left.value() + right.value() );
}

constexpr pair_type auto operator - ( const pair_type auto& left, const pair_type auto& right )
    requires minusable_to<left_key_type,  right_key_type  > and 
             minusable_to<left_value_type,right_value_type>
{
    return pair ( left.key() - right.key(), left.value() - right.value() );
}

constexpr pair_type auto operator * ( const pair_type auto& left, const auto& right )
    requires multipliable_to<left_key_type,  right_type> and 
             multipliable_to<left_value_type,right_type> and 
             ( not pair_type<right_type> )
{
    return pair ( left.key() * right, left.value() * right );
}

constexpr pair_type auto operator * ( const pair_type auto& left, const auto& right )
    requires multipliable_to<left_type,right_key_type  > and 
             multipliable_to<left_type,right_value_type> and 
             ( not pair_type<left_type> )
{
    return pair ( left * right.value(), left * right.value() );
}

constexpr pair_type auto operator / ( const pair_type auto& left, const auto& right )
    requires dividable_to<left_key_type,  right_type> and 
             dividable_to<left_value_type,right_type> and 
             ( not pair_type<right_type> )
{
    return pair ( left.key() / right, left.value() / right );
}





constexpr std::ostream& operator << ( std::ostream& left, const tuple_type auto& right )
    requires detail::tuplewise_printable<right_type>
{
    left << '(';
    for_constexpr<1,tuple_size<right_type>-1>([&] <int index> { left << get<index-1>(right) << ", "; });
    if constexpr ( tuple_size<right_type> != 0 )
        left << get<tuple_size<right_type>-1>(right);
    left << ')';
    return left;
}

constexpr bool operator == ( const tuple_type auto& left, const tuple_type auto& right )
    requires detail::tuplewise_equalable_to<left_type,right_type>
{
    return all_of_constexpr<1,tuple_size<left_type>>([&] <int index> { return get<index-1>(left) == get<index-1>(right); });
}

constexpr auto operator <=> ( const tuple_type auto& left, const tuple_type auto& right )
    requires detail::tuplewise_comparable_to<left_type,right_type>
{
    return detail::tuplewise_compare(left, right);
}

constexpr tuple_type auto operator + ( const tuple_type auto& left, const tuple_type auto& right )
    requires detail::tuplewise_plusable_to<left_type,right_type>
{
    return detail::tuplewise_plus(left, right);
}

constexpr tuple_type auto operator - ( const tuple_type auto& left, const tuple_type auto& right )
    requires detail::tuplewise_minusable_to<left_type,right_type>
{
    return detail::tuplewise_minus ( left, right );
}

constexpr tuple_type auto operator * ( const tuple_type auto& left, const auto& right )
    requires detail::tuplewise_each_multipliable_to<left_type,right_type> and ( not tuple_type<right_type> )
{
    return detail::tuplewise_each_multiply ( left, right );
}

constexpr tuple_type auto operator * ( const auto& left, const tuple_type auto& right )
    requires detail::tuplewise_multipliable_to_each<left_type,right_type> and ( not tuple_type<left_type> )
{
    return detail::tuplewise_multiply_each ( left, right );
}

constexpr tuple_type auto operator / ( const tuple_type auto& left, const auto& right )
    requires detail::tuplewise_each_dividable_to<left_type,right_type> and ( not tuple_type<right_type> )
{
    return detail::tuplewise_each_divide ( left, right );
}










