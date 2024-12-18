#pragma once

namespace aux
{
    template < int index = 1 > constexpr decltype(auto) tuplewise_print         (       auto&, const auto& );
    template < int index = 1 > constexpr bool           tuplewise_equal         ( const auto&, const auto& );
    template < int index = 1 > constexpr auto           tuplewise_compare       ( const auto&, const auto& );
    template < int index = 1 > constexpr auto           tuplewise_add           ( const auto&, const auto& );
    template < int index = 1 > constexpr auto           tuplewise_minus         ( const auto&, const auto& );
    template < int index = 1 > constexpr auto           tuplewise_each_multiply ( const auto&, const auto& );
    template < int index = 1 > constexpr auto           tuplewise_multiply_each ( const auto&, const auto& );
    template < int index = 1 > constexpr auto           tuplewise_each_divide   ( const auto&, const auto& );

    template < int index = 1 > constexpr void           tuplewise_add_aux           ( const auto&, const auto&, auto& );
    template < int index = 1 > constexpr void           tuplewise_minus_aux         ( const auto&, const auto&, auto& );
    template < int index = 1 > constexpr void           tuplewise_each_multiply_aux ( const auto&, const auto&, auto& );
    template < int index = 1 > constexpr void           tuplewise_multiply_each_aux ( const auto&, const auto&, auto& );
    template < int index = 1 > constexpr void           tuplewise_each_divide_aux   ( const auto&, const auto&, auto& );

    template < class type1, class type2 > struct        tuplewise_add_result;
    template < class type1, class type2 > struct        tuplewise_minus_result;
    template < class type1, class type2 > struct        tuplewise_each_multiply_result;
    template < class type1, class type2 > struct        tuplewise_multiply_each_result;
    template < class type1, class type2 > struct        tuplewise_each_divide_result;
}


/// Global

constexpr std::ostream& operator << ( std::ostream& left, const pair_type auto& right )
    requires printable<right_key_type> and printable<right_value_type>
{
    return left << '(' << right.key() << ',' << right.value() << ')';
}

constexpr bool operator == ( const pair_type auto& left, const pair_type auto& right )
    requires equalable_to<left_key_type,right_key_type> and equalable_to<left_value_type,right_value_type>
{
    return left.key() == right.key() and left.value() == right.value();
}

constexpr auto operator <=> ( const pair_type auto& left, const pair_type auto& right )
    requires comparable_to<left_key_type,right_key_type> and comparable_to<left_value_type,right_value_type>
{
    using type = common_type<decltype(left.key()<=>right.key()),decltype(left.value()<=>right.value())>;
    let try1 = left.key() <=> right.key();
    if ( try1 != decltype(try1)::equivalent )
        return type(try1);
    else
        return type(left.value() <=> right.value());
}

constexpr pair_type auto operator + ( const pair_type auto& left, const pair_type auto& right )
    requires addable_to<left_key_type,right_key_type> and addable_to<left_value_type,right_value_type>
{
    return pair ( left.key() + right.key(), left.value() + right.value() );
}

constexpr pair_type auto operator - ( const pair_type auto& left, const pair_type auto& right )
    requires minusable_to<left_key_type,right_key_type> and minusable_to<left_value_type,right_value_type>
{
    return pair ( left.key() - right.key(), left.value() - right.value() );
}

constexpr pair_type auto operator * ( const pair_type auto& left, const auto& right )
    requires multipliable_to<left_key_type,right_type> and multipliable_to<left_value_type,right_type> but ( not pair_type<right_type> )
{
    return pair ( left.key() * right, left.value() * right );
}

constexpr pair_type auto operator * ( const pair_type auto& left, const auto& right )
    requires multipliable_to<left_type,right_key_type> and multipliable_to<left_type,right_value_type> but ( not pair_type<left_type> )
{
    return pair ( left * right.value(), left * right.value() );
}

constexpr pair_type auto operator / ( const pair_type auto& left, const auto& right )
    requires dividable_to<left_key_type,right_type> and dividable_to<left_value_type,right_type> but ( not pair_type<right_type> )
{
    return pair ( left.key() / right, left.value() / right );
}





constexpr std::ostream& operator << ( std::ostream& left, const tuple_type auto& right )
    requires aux::tuplewise_printable<right_type>
{
    return aux::tuplewise_print ( left, right );
}

constexpr bool operator == ( const tuple_type auto& left, const tuple_type auto& right )
    requires aux::tuplewise_equalable<left_type,right_type>
{
    return aux::tuplewise_equal ( left, right );
}

constexpr auto operator <=> ( const tuple_type auto& left, const tuple_type auto& right )
    requires aux::tuplewise_comparable<left_type,right_type>
{
    return aux::tuplewise_compare ( left, right );
}

constexpr tuple_type auto operator + ( const tuple_type auto& left, const tuple_type auto& right )
    requires aux::tuplewise_addable<left_type,right_type>
{
    return aux::tuplewise_add ( left, right );
}

constexpr tuple_type auto operator - ( const tuple_type auto& left, const tuple_type auto& right )
    requires aux::tuplewise_minusable<left_type,right_type>
{
    return aux::tuplewise_minus ( left, right );
}

constexpr tuple_type auto operator * ( const tuple_type auto& left, const auto& right )
    requires aux::tuplewise_each_multipliable_to<left_type,right_type> but ( not tuple_type<right_type> )
{
    return aux::tuplewise_each_multiply ( left, right );
}

constexpr tuple_type auto operator * ( const auto& left, const tuple_type auto& right )
    requires aux::tuplewise_multipliable_to_each<left_type,right_type> but ( not tuple_type<left_type> )
{
    return aux::tuplewise_multiply_each ( left, right );
}

constexpr tuple_type auto operator / ( const tuple_type auto& left, const auto& right )
    requires aux::tuplewise_each_dividable_to<left_type,right_type> but ( not tuple_type<right_type> )
{
    return aux::tuplewise_each_divide ( left, right );
}






/// Auxiliary (function)

template < int index >
constexpr decltype(auto) aux::tuplewise_print ( auto& left, const auto& right )
{
    if constexpr ( index == 1 )
        left << '(';

    left << get<index-1>(right);

    if constexpr ( index != tuple_size<right_type> )
    {
        left << ", ";
        tuplewise_print<index+1> ( left, right );
    }
    else
        left << ')';

    return left;
}

template < int index >
constexpr bool aux::tuplewise_equal ( const auto& left, const auto& right )
{
    if constexpr ( index < tuple_size<left_type> )
        return get<index-1>(left) == get<index-1>(right) and aux::tuplewise_equal<index+1> ( left, right );
    else
        return get<index-1>(left) == get<index-1>(right);
}

template < int index >
constexpr auto aux::tuplewise_compare ( const auto& left, const auto& right )
{
    if constexpr ( index < tuple_size<left_type> )
    {
        using type = common_type<decltype(get<index-1>(left)<=>get<index-1>(right)),decltype(tuplewise_compare<index+1>(left,right))>;

        let try1 = get<index-1>(left) <=> get<index-1>(right);
        if ( try1 != decltype(try1)::equivalent )
            return type(try1);
        else
            return type(tuplewise_compare<index+1>(left, right));
    }

    else
        return get<index-1>(left) <=> get<index-1>(right);
}

template < int index >
constexpr auto aux::tuplewise_add ( const auto& left, const auto& right )
{
    let t = typename tuplewise_add_result<left_type,right_type>::type();
    tuplewise_add_aux ( left, right, t );
    return t;
}

template < int index >
constexpr auto aux::tuplewise_minus ( const auto& left, const auto& right )
{
    let t = typename tuplewise_minus_result<left_type,right_type>::type();
    tuplewise_minus_aux ( left, right, t );
    return t;
}

template < int index >
constexpr auto aux::tuplewise_each_multiply ( const auto& left, const auto& right )
{
    let t = typename tuplewise_each_multiply_result<left_type,right_type>::type();
    tuplewise_each_multiply_aux ( left, right, t );
    return t;
}

template < int index >
constexpr auto aux::tuplewise_multiply_each ( const auto& left, const auto& right )
{
    let t = typename tuplewise_multiply_each_result<left_type,right_type>::type();
    tuplewise_multiply_each_aux ( left, right, t );
    return t;
}

template < int index >
constexpr auto aux::tuplewise_each_divide ( const auto& left, const auto& right )
{
    let t = typename tuplewise_each_divide_result<left_type,right_type>::type();
    tuplewise_each_divide_aux ( left, right, t );
    return t;
}






template < int index >
constexpr void aux::tuplewise_add_aux ( const auto& left, const auto& right, auto& t )
{
    get<index-1>(t) = get<index-1>(left) + get<index-1>(right);

    if constexpr ( index < tuple_size<left_type > and
                   index < tuple_size<right_type> )
        tuplewise_add_aux<index+1> ( left, right, t );
}

template < int index >
constexpr void aux::tuplewise_minus_aux ( const auto& left, const auto& right, auto& t )
{
    get<index-1>(t) = get<index-1>(left) - get<index-1>(right);

    if constexpr ( index < tuple_size<left_type > and
                   index < tuple_size<right_type> )
        tuplewise_minus_aux<index+1> ( left, right, t );
}

template < int index >
constexpr void aux::tuplewise_each_multiply_aux ( const auto& left, const auto& right, auto& t )
{
    get<index-1>(t) = get<index-1>(left) * right;

    if constexpr ( index < tuple_size<left_type> )
        tuplewise_each_multiply_aux<index+1> ( left, right, t );
}

template < int index >
constexpr void aux::tuplewise_multiply_each_aux ( const auto& left, const auto& right, auto& t )
{
    get<index-1>(t) = left * get<index-1>(right);

    if constexpr ( index < tuple_size<right_type> )
        tuplewise_multiply_each_aux<index+1> ( left, right, t );
}

template < int index >
constexpr void aux::tuplewise_each_divide_aux ( const auto& left, const auto& right, auto& t )
{
    get<index-1>(t) = get<index-1>(left) / right;

    if constexpr ( index < tuple_size<left_type> )
        tuplewise_each_divide_aux<index+1> ( left, right, t );
}





template < class... types1, class... types2 >
struct aux::tuplewise_add_result<tuple<types1...>,tuple<types2...>>
{
    using type = tuple<add_result<types1,types2>...>;
};

template < tuple_type type1, tuple_type type2 >
struct aux::tuplewise_add_result<type1,type2>
{
    using type = tuplewise_add_result<decltype(tuple(std::declval<type1>())),decltype(tuple(std::declval<type2>()))>::type;
};

template < class... types1, class... types2 >
struct aux::tuplewise_minus_result<tuple<types1...>,tuple<types2...>>
{
    using type = tuple<minus_result<types1,types2>...>;
};

template < tuple_type type1, tuple_type type2 >
struct aux::tuplewise_minus_result<type1,type2>
{
    using type = tuplewise_minus_result<decltype(tuple(std::declval<type1>())),decltype(tuple(std::declval<type2>()))>::type;
};

template < class... types1, class type2 >
struct aux::tuplewise_each_multiply_result<tuple<types1...>,type2>
{
    using type = tuple<multiply_result<types1,type2>...>;
};

template < tuple_type type1, class type2 >
struct aux::tuplewise_each_multiply_result<type1,type2>
{
    using type = tuplewise_each_multiply_result<decltype(tuple(std::declval<type1>())),type2>::type;
};

template < class type1, class... types2 >
struct aux::tuplewise_multiply_each_result<type1,tuple<types2...>>
{
    using type = tuple<multiply_result<type1,types2>...>;
};

template < class type1, tuple_type type2 >
struct aux::tuplewise_multiply_each_result<type1,type2>
{
    using type = tuplewise_multiply_each_result<type1,decltype(tuple(std::declval<type2>()))>::type;
};

template < class... types1, class type2 >
struct aux::tuplewise_each_divide_result<tuple<types1...>,type2>
{
    using type = tuple<divide_result<types1,type2>...>;
};

template < tuple_type type1, class type2 >
struct aux::tuplewise_each_divide_result<type1,type2>
{
    using type = tuplewise_each_divide_result<decltype(tuple(std::declval<type1>())),type2>::type;
};