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

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_convertible_to = 
        



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

    template < int index = 1 >
    constexpr void tuplewise_print_impl ( auto& left, const auto& right )
    {
        if constexpr ( tuple_size<decay<decltype(right)>> == 0 )
            left << "()";
        else
        {
            if constexpr ( index == 1 )
                left << '(';
            left << get<index-1>(right);
            if constexpr ( index < tuple_size<decay<decltype(right)>> )
            {
                left << ", ";
                tuplewise_print_impl<index+1> ( left, right );
            }
            else
                left << ')';
        }
    }

    template < int index = 1 >
    constexpr bool tuplewise_equal_impl ( const auto& left, const auto& right )
    {
        if constexpr ( index < tuple_size<decay<decltype(left)>> )
            return get<index-1>(left) == get<index-1>(right) and tuplewise_equal_impl<index+1> ( left, right );
        else if constexpr ( index == tuple_size<decay<decltype(left)>> )
            return get<index-1>(left) == get<index-1>(right);
        else // tuple_size == 0.
            return true;
    }

    template < int index = 1 >
    constexpr auto tuplewise_compare_impl ( const auto& left, const auto& right )
    {
        if constexpr ( index < tuple_size<decay<decltype(left)>> )
        {
            using type = common_type<decltype(get<index-1>(left)<=>get<index-1>(right)),decltype(tuplewise_compare_impl<index+1>(left,right))>;
            auto try1 = get<index-1>(left) <=> get<index-1>(right);
            if ( try1 != decltype(try1)::equivalent )
                return type(try1);
            else
                return type(tuplewise_compare_impl<index+1>(left, right));
        }
        else if constexpr ( index == tuple_size<decay<decltype(left)>> )
            return get<index-1>(left) <=> get<index-1>(right);
        else // tuple_size == 0.
            return std::strong_ordering::equal;
    }





    // Interface

    constexpr auto& tuplewise_print ( auto& left, const auto& right )
    {
        tuplewise_print_impl(left, right);
        return left;
    }

    constexpr bool tuplewise_equal ( const auto& left, const auto& right )
    {
        return tuplewise_equal_impl(left, right);
    }

    constexpr auto tuplewise_compare ( const auto& left, const auto& right )
    {
        return tuplewise_compare_impl(left, right);
    }

    constexpr auto tuplewise_plus ( const auto& left, const auto& right )
    {
        auto t = typename tuplewise_plus_result<decay<decltype(left)>,decay<decltype(right)>>::type();
        if constexpr ( tuple_size<decay<decltype(left)>> > 0 )
            for_constexpr<1,tuple_size<decay<decltype(left)>>>([&] <int index> { get<index-1>(t) = get<index-1>(left) + get<index-1>(right); });
        return t;
    }

    constexpr auto tuplewise_minus ( const auto& left, const auto& right )
    {
        auto t = typename tuplewise_minus_result<decay<decltype(left)>,decay<decltype(right)>>::type();
        if constexpr ( tuple_size<decay<decltype(left)>> > 0 )
            for_constexpr<1,tuple_size<decay<decltype(left)>>>([&] <int index> { get<index-1>(t) = get<index-1>(left) - get<index-1>(right); });
        return t;
    }

    constexpr auto tuplewise_each_multiply ( const auto& left, const auto& right )
    {
        auto t = typename tuplewise_each_multiply_result<decay<decltype(left)>,decay<decltype(right)>>::type();
        if constexpr ( tuple_size<decay<decltype(left)>> > 0 )
            for_constexpr<1,tuple_size<decay<decltype(left)>>>([&] <int index> { get<index-1>(t) = get<index-1>(left) * right; });
        return t;
    }

    constexpr auto tuplewise_multiply_each ( const auto& left, const auto& right )
    {
        auto t = typename tuplewise_multiply_each_result<decay<decltype(left)>,decay<decltype(right)>>::type();
        if constexpr ( tuple_size<decay<decltype(right)>> > 0 )
            for_constexpr<1,tuple_size<decay<decltype(left)>>>([&] <int index> { get<index-1>(t) = left * get<index-1>(right); });
        return t;
    }

    constexpr auto tuplewise_each_divide ( const auto& left, const auto& right )
    {
        auto t = typename tuplewise_each_divide_result<decay<decltype(left)>,decay<decltype(right)>>::type();
        if constexpr ( tuple_size<decay<decltype(left)>> > 0 )
            for_constexpr<1,tuple_size<decay<decltype(left)>>>([&] <int index> { get<index-1>(t) = get<index-1>(left) / right; });
        return t;
    }

} // namespace detail