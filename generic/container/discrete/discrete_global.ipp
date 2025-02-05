#pragma once

namespace detail
{
    // Concept

    template < class type, int count = 1 >
    constexpr bool tuplewise_printable = []
        {
            if constexpr ( count < tuple_size<type> )
                return printable<tuple_element<count,type>> and tuplewise_printable<type,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_equalable_to = []
        {
            if constexpr ( tuple_size<type1> == tuple_size<type2> and count < tuple_size<type1> )
                return equalable_to<tuple_element<count,type1>,tuple_element<count,type2>> and tuplewise_equalable_to<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_comparable_to = []
        {
            if constexpr ( tuple_size<type1> == tuple_size<type2> and count < tuple_size<type1> )
                return comparable_to<tuple_element<count,type1>,tuple_element<count,type2>> and tuplewise_comparable_to<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_plusable_to = []
        {
            if constexpr ( tuple_size<type1> == tuple_size<type2> and count < tuple_size<type1> )
                return plusable_to<tuple_element<count,type1>,tuple_element<count,type2>> and tuplewise_plusable_to<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_minusable_to = []
        {
            if constexpr ( tuple_size<type1> == tuple_size<type2> and count < tuple_size<type1> )
                return minusable_to<tuple_element<count,type1>,tuple_element<count,type2>> and tuplewise_minusable_to<type1,type2,count+1>;
            else
                return true;
        } ();

//  See root/container/interface.h/concept
//  template < class type1, class type2, int count = 1 >
//  constexpr bool tuplewise_convertible_to =
//      tuple_size<type1> == tuple_size<type2> and
//      std::convertible_to<tuple_element<count,type1>,tuple_element<count,type2>> and []
//      {
//          if constexpr ( count < tuple_size<type1> )
//              return tuplewise_convertible<type1,type2,count+1>;
//          else
//              return true;
//      } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_same_as =
        tuple_size<type1> == tuple_size<type2> and
        std::same_as<tuple_element<count,type1>,tuple_element<count,type2>> and []
        {
            if constexpr ( count < tuple_size<type1> )
                return tuplewise_same_as<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_each_multipliable_to =
        multipliable_to<tuple_element<count,type1>,type2> and []
        {
            if constexpr ( count < tuple_size<type1> )
                return tuplewise_each_multipliable_to<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_multipliable_to_each =
        multipliable_to<type1,tuple_element<count,type2>> and []
        {
            if constexpr ( count < tuple_size<type2> )
                return tuplewise_multipliable_to_each<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_each_dividable_to =
        multipliable_to<tuple_element<count,type1>,type2> and []
        {
            if constexpr ( count < tuple_size<type1> )
                return tuplewise_each_dividable_to<type1,type2,count+1>;
            else
                return true;
        } ();

    // Operation result

    template < class type1, class type2 >
    struct tuplewise_plus_result;

    template < class... types1, class... types2 >
    struct tuplewise_plus_result<tuple<types1...>,tuple<types2...>>
    {
        using type = tuple<plus_result<types1,types2>...>;
    };

    template < tuple_type type1, tuple_type type2 >
    struct tuplewise_plus_result<type1,type2>
    {
        using type = tuplewise_plus_result<decltype(tuple(std::declval<type1>())),decltype(tuple(std::declval<type2>()))>::type;
    };

    template < class type1, class type2 >
    struct tuplewise_minus_result;

    template < class... types1, class... types2 >
    struct tuplewise_minus_result<tuple<types1...>,tuple<types2...>>
    {
        using type = tuple<minus_result<types1,types2>...>;
    };

    template < tuple_type type1, tuple_type type2 >
    struct tuplewise_minus_result<type1,type2>
    {
        using type = tuplewise_minus_result<decltype(tuple(std::declval<type1>())),decltype(tuple(std::declval<type2>()))>::type;
    };

    template < class types1, class type2 >
    struct tuplewise_each_multiply_result;

    template < class... types1, class type2 >
    struct tuplewise_each_multiply_result<tuple<types1...>,type2>
    {
        using type = tuple<multiply_result<types1,type2>...>;
    };

    template < tuple_type type1, class type2 >
    struct tuplewise_each_multiply_result<type1,type2>
    {
        using type = tuplewise_each_multiply_result<decltype(tuple(std::declval<type1>())),type2>::type;
    };

    template < class type1, class types2 >
    struct tuplewise_multiply_each_result;

    template < class type1, class... types2 >
    struct tuplewise_multiply_each_result<type1,tuple<types2...>>
    {
        using type = tuple<multiply_result<type1,types2>...>;
    };

    template < class type1, tuple_type type2 >
    struct tuplewise_multiply_each_result<type1,type2>
    {
        using type = tuplewise_multiply_each_result<type1,decltype(tuple(std::declval<type2>()))>::type;
    };

    template < class types1, class type2 >
    struct tuplewise_each_divide_result;

    template < class... types1, class type2 >
    struct tuplewise_each_divide_result<tuple<types1...>,type2>
    {
        using type = tuple<divide_result<types1,type2>...>;
    };

    template < tuple_type type1, class type2 >
    struct tuplewise_each_divide_result<type1,type2>
    {
        using type = tuplewise_each_divide_result<decltype(tuple(std::declval<type1>())),type2>::type;
    };

    // Implemention

    template < int index >
    constexpr void tuplewise_print_impl ( auto& left, const auto& right )
    {
        if constexpr ( index == 1 )
            left << '(';
        left << get<index-1>(right);
        if constexpr ( index != tuple_size<right_type> )
        {
            left << ", ";
            tuplewise_print_impl<index+1> ( left, right );
        }
        else
            left << ')';
    }

    template < int index >
    constexpr bool tuplewise_equal_impl ( const auto& left, const auto& right )
    {
        if constexpr ( index < tuple_size<left_type> )
            return get<index-1>(left) == get<index-1>(right) and tuplewise_equal_impl<index+1> ( left, right );
        else
            return get<index-1>(left) == get<index-1>(right);
    }

    template < int index >
    constexpr auto tuplewise_compare_impl ( const auto& left, const auto& right )
    {
        if constexpr ( index < tuple_size<left_type> )
        {
            using type = common_type<decltype(get<index-1>(left)<=>get<index-1>(right)),decltype(tuplewise_compare_impl<index+1>(left,right))>;
            let try1 = get<index-1>(left) <=> get<index-1>(right);
            if ( try1 != decltype(try1)::equivalent )
                return type(try1);
            else
                return type(tuplewise_compare_impl<index+1>(left, right));
        }

        else
            return get<index-1>(left) <=> get<index-1>(right);
    }

    template < int index >
    constexpr void tuplewise_plus_impl ( const auto& left, const auto& right, auto& t )
    {
        get<index-1>(t) = get<index-1>(left) + get<index-1>(right);

        if constexpr ( index < tuple_size<left_type > and
                       index < tuple_size<right_type> )
            tuplewise_plus_impl<index+1> ( left, right, t );
    }

    template < int index >
    constexpr void tuplewise_minus_impl ( const auto& left, const auto& right, auto& t )
    {
        get<index-1>(t) = get<index-1>(left) - get<index-1>(right);

        if constexpr ( index < tuple_size<left_type > and
                       index < tuple_size<right_type> )
            tuplewise_minus_impl<index+1> ( left, right, t );
    }

    template < int index >
    constexpr void tuplewise_each_multiply_impl ( const auto& left, const auto& right, auto& t )
    {
        get<index-1>(t) = get<index-1>(left) * right;

        if constexpr ( index < tuple_size<left_type> )
            tuplewise_each_multiply_impl<index+1> ( left, right, t );
    }

    template < int index >
    constexpr void tuplewise_multiply_each_impl ( const auto& left, const auto& right, auto& t )
    {
        get<index-1>(t) = left * get<index-1>(right);

        if constexpr ( index < tuple_size<right_type> )
            tuplewise_multiply_each_impl<index+1> ( left, right, t );
    }

    template < int index >
    constexpr void tuplewise_each_divide_impl ( const auto& left, const auto& right, auto& t )
    {
        get<index-1>(t) = get<index-1>(left) / right;

        if constexpr ( index < tuple_size<left_type> )
            tuplewise_each_divide_impl<index+1> ( left, right, t );
    }

    // Interface

    constexpr auto& tuplewise_print ( auto& left, const auto& right )
    {
        tuplewise_print_impl<1>(left, right);
        return left;
    }

    constexpr bool tuplewise_equal ( const auto& left, const auto& right )
    {
        return tuplewise_equal_impl<1>(left, right);
    }

    constexpr auto tuplewise_compare ( const auto& left, const auto& right )
    {
        return tuplesize_compare_impl<1>(left, right);
    }

    constexpr auto tuplewise_plus ( const auto& left, const auto& right )
    {
        let t = typename tuplewise_plus_result<left_type,right_type>::type();
        tuplewise_plus_impl ( left, right, t );
        return t;
    }

    constexpr auto tuplewise_minus ( const auto& left, const auto& right )
    {
        let t = typename tuplewise_minus_result<left_type,right_type>::type();
        tuplewise_minus_impl ( left, right, t );
        return t;
    }

    constexpr auto tuplewise_each_multiply ( const auto& left, const auto& right )
    {
        let t = typename tuplewise_each_multiply_result<left_type,right_type>::type();
        tuplewise_each_multiply_impl ( left, right, t );
        return t;
    }

    constexpr auto tuplewise_multiply_each ( const auto& left, const auto& right )
    {
        let t = typename tuplewise_multiply_each_result<left_type,right_type>::type();
        tuplewise_multiply_each_impl ( left, right, t );
        return t;
    }

    constexpr auto tuplewise_each_divide ( const auto& left, const auto& right )
    {
        let t = typename tuplewise_each_divide_result<left_type,right_type>::type();
        tuplewise_each_divide_impl ( left, right, t );
        return t;
    }

} // namespace detail






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
    requires plusable_to<left_key_type,right_key_type> and plusable_to<left_value_type,right_value_type>
{
    return cpu::pair ( left.key() + right.key(), left.value() + right.value() );
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
    requires detail::tuplewise_printable<right_type>
{
    return detail::tuplewise_print ( left, right );
}

constexpr bool operator == ( const tuple_type auto& left, const tuple_type auto& right )
    requires detail::tuplewise_equalable_to<left_type,right_type>
{
    return detail::tuplewise_equal ( left, right );
}

constexpr auto operator <=> ( const tuple_type auto& left, const tuple_type auto& right )
    requires detail::tuplewise_comparable_to<left_type,right_type>
{
    return detail::tuplewise_compare ( left, right );
}

constexpr tuple_type auto operator + ( const tuple_type auto& left, const tuple_type auto& right )
    requires detail::tuplewise_plusable_to<left_type,right_type>
{
    return detail::tuplewise_plus ( left, right );
}

constexpr tuple_type auto operator - ( const tuple_type auto& left, const tuple_type auto& right )
    requires detail::tuplewise_minusable_to<left_type,right_type>
{
    return detail::tuplewise_minus ( left, right );
}

constexpr tuple_type auto operator * ( const tuple_type auto& left, const auto& right )
    requires detail::tuplewise_each_multipliable_to<left_type,right_type> but ( not tuple_type<right_type> )
{
    return detail::tuplewise_each_multiply ( left, right );
}

constexpr tuple_type auto operator * ( const auto& left, const tuple_type auto& right )
    requires detail::tuplewise_multipliable_to_each<left_type,right_type> but ( not tuple_type<left_type> )
{
    return detail::tuplewise_multiply_each ( left, right );
}

constexpr tuple_type auto operator / ( const tuple_type auto& left, const auto& right )
    requires detail::tuplewise_each_dividable_to<left_type,right_type> but ( not tuple_type<right_type> )
{
    return detail::tuplewise_each_divide ( left, right );
}














