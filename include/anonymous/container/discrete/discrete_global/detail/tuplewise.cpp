namespace detail
{
    // Concept
    template < class type, int count = 1 >
    constexpr bool tuplewise_printable = 
        all_of_constexpr<1,tuple_size<type>>([] <int index> { return printable<tuple_element<index,type>>; });

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_equalable_to =
        tuple_size<type1> == tuple_size<type2> and 
        all_of_constexpr<1,tuple_size<type1>>([] <int index> { return equalable_to<tuple_element<index,type1>,tuple_element<index,type2>>; });

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_comparable_to = 
        tuple_size<type1> == tuple_size<type2> and
        all_of_constexpr<1,tuple_size<type1>>([] <int index> { return comparable_to<tuple_element<index,type1>,tuple_element<index,type2>>; });

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_plusable_to = 
        tuple_size<type1> == tuple_size<type2> and
        all_of_constexpr<1,tuple_size<type1>>([] <int index> { return plusable_to<tuple_element<index,type1>,tuple_element<index,type2>>; });

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_minusable_to = 
        tuple_size<type1> == tuple_size<type2> and
        all_of_constexpr<1,tuple_size<type1>>([] <int index> { return minusable_to<tuple_element<index,type1>,tuple_element<index,type2>>; });

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_each_multipliable_to =
        all_of_constexpr<1,tuple_size<type1>>([] <int index> { return multipliable_to<tuple_element<index,type1>,type2>; });

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_multipliable_to_each =
        all_of_constexpr<1,tuple_size<type2>>([] <int index> { return multipliable_to<type1,tuple_element<index,type2>>; });

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_each_dividable_to =
        all_of_constexpr<1,tuple_size<type1>>([] <int index> { return dividable_to<tuple_element<index,type1>,type2>; });




    // Operation
    template < class... types1, class... types2 >
    constexpr tuple<types1...,types2...> tuple_cat ( tuple<types1...>&& left, tuple<types2...>&& right )
    {
        return tuple<types1...,types2...>(
                   static_cast<tuple<types1...,types2...>&&>(
                       std::tuple_cat(
                           static_cast<std::tuple<types1...>&&>(left),
                           static_cast<std::tuple<types2...>&&>(right)
                       )
                   )
               );
    }

    template < int count = 1 >
    constexpr auto tuplewise_compare ( const tuple_type auto& left, const tuple_type auto& right )
    {
        if constexpr ( tuple_size<left_type> == 0 )
            return std::strong_ordering::equal;
        else if constexpr ( count < tuple_size<left_type> )
        {
            using result_type1 = compare_result<tuple_element<1,left_type>,tuple_element<1,right_type>>;
            using result_types = decltype(tuplewise_compare<count+1>(left, right));
            using result_type  = common_type<result_type1,result_types>;
            
            auto result = (get<count-1>(left) <=> get<count-1>(right));
            if ( result == decltype(result)::equivalent )
                return result_type(result);
            else
                return result_type(tuplewise_compare<count+1>(left, right));
        }
        else
            return get<count-1>(left) <=> get<count-1>(right);
    }

    template < int count = 1 >
    constexpr auto tuplewise_plus ( const tuple_type auto& left, const tuple_type auto& right )
    {
        if constexpr ( tuple_size<left_type> == 0 )
            return tuple();
        else if constexpr ( count < tuple_size<left_type> )
            return tuple_cat(tuple(get<count-1>(left) + get<count-1>(right)), tuplewise_plus<count+1>(left, right));
        else
            return tuple(get<count-1>(left) + get<count-1>(right));
    }

    template < int count = 1 >
    constexpr auto tuplewise_minus ( const tuple_type auto& left, const tuple_type auto& right )
    {
        if constexpr ( tuple_size<left_type> == 0 )
            return tuple();
        else if constexpr ( count < tuple_size<left_type> )
            return tuple_cat(tuple(get<count-1>(left) - get<count-1>(right)), tuplewise_minus<count+1>(left, right));
        else
            return tuple(get<count-1>(left) - get<count-1>(right));
    }

    template < int count = 1 >
    constexpr auto tuplewise_each_multiply ( const tuple_type auto& left, const auto& right )
    {
        if constexpr ( tuple_size<left_type> == 0 )
            return tuple();
        else if constexpr ( count < tuple_size<left_type> )
            return tuple_cat(tuple(get<count-1>(left) * right), tuplewise_each_multiply<count+1>(left, right));
        else
            return tuple(get<count-1>(left) * right);
    }

    template < int count = 1 >
    constexpr auto tuplewise_multiply_each ( const auto& left, const tuple_type auto& right )
    {
        if constexpr ( tuple_size<right_type> == 0 )
            return tuple();
        else if constexpr ( count < tuple_size<left_type> )
            return tuple_cat(tuple(left * get<count-1>(right)), tuplewise_multiply_each<count+1>(left, right));
        else
            return tuple(left * get<count-1>(right));
    }

    template < int count = 1 >
    constexpr auto tuplewise_each_divide ( const tuple_type auto& left, const auto& right )
    {
        if constexpr ( tuple_size<left_type> == 0 )
            return tuple();
        else if constexpr ( count < tuple_size<left_type> )
            return tuple_cat(tuple(get<count-1>(left) / right), tuplewise_each_divide<count+1>(left, right));
        else
            return tuple(get<count-1>(left) / right);
    }















    // template < tuple_type type1, tuple_type type2 >
    // struct tuplewise_plus_result_helper
    // {
    //     using type = tuplewise_plus_result_helper<to_base_tuple<type1>,to_base_tuple<type2>>::type;
    // };

    // template < class... types1, class... types2 >
    // struct tuplewise_plus_result_helper<tuple<types1...>,tuple<types2...>>
    // {
    //     using type = tuple<plus_result<types1,types2>...>;
    // };

    // template < tuple_type type1, tuple_type type2 >
    // using tuplewise_plus_result = tuplewise_plus_result_helper<type1,type2>::type;




    // template < tuple_type type1, tuple_type type2 >
    // struct tuplewise_minus_result_helper
    // {
    //     using type = tuplewise_minus_result_helper<to_base_tuple<type1>,to_base_tuple<type2>>::type;
    // };

    // template < class... types1, class... types2 >
    // struct tuplewise_minus_result_helper<tuple<types1...>,tuple<types2...>>
    // {
    //     using type = tuple<minus_result<types1,types2>...>;
    // };

    // template < tuple_type type1, tuple_type type2 >
    // using tuplewise_minus_result = tuplewise_minus_result_helper<type1,type2>::type;



    // template < tuple_type type1, tuple_type type2 >
    // struct tuplewise_each_multiply_result_helper
    // {
    //     using type = tuplewise_each_multiply_result_helper<to_base_tuple<type1>,to_base_tuple<type2>>::type;
    // };

    // template < class... types1, class... types2 >
    // struct tuplewise_minus_result_helper<tuple<types1...>,tuple<types2...>>
    // {
    //     using type = tuple<minus_result<types1,types2>...>;
    // };

    // template < tuple_type type1, tuple_type type2 >
    // using tuplewise_minus_result = tuplewise_minus_result_helper<type1,type2>::type;




    // template < tuple_type type1, class type2 >
    // struct tuplewise_each_multiply_result_helper
    // {
    //     using type = tuplewise_each_multiply_result_helper<to_base_tuple<type1>,type2>::type;
    // }

    // template < class... types1, class type2 >
    // struct tuplewise_each_multiply_result_helper<tuple<types1...>,type2>
    // {
    //     using type = tuple<multiply_result<types1,type2>...>;
    // };

    // template < tuple_type type1, class type2 >
    // using tuplewise_each_mutliply_result = tuplewise_each_multiply_result_helper<type1,type2>::type;

    

    // template < class type1, class types2 >
    // struct tuplewise_multiply_each_result;

    // template < class type1, class... types2 >
    // struct tuplewise_multiply_each_result<type1,tuple<types2...>>
    // {
    //     using type = tuple<multiply_result<type1,types2>...>;
    // };

    // template < class type1, tuple_type type2 >
    // struct tuplewise_multiply_each_result<type1,type2>
    // {
    //     using type = tuplewise_multiply_each_result<type1,decltype(tuple(std::declval<type2>()))>::type;
    // };

    // template < class types1, class type2 >
    // struct tuplewise_each_divide_result;

    // template < class... types1, class type2 >
    // struct tuplewise_each_divide_result<tuple<types1...>,type2>
    // {
    //     using type = tuple<divide_result<types1,type2>...>;
    // };

    // template < tuple_type type1, class type2 >
    // struct tuplewise_each_divide_result<type1,type2>
    // {
    //     using type = tuplewise_each_divide_result<decltype(tuple(std::declval<type1>())),type2>::type;
    // };





    // Implemention

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

} // namespace detail