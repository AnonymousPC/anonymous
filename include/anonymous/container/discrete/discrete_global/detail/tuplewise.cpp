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

} // namespace detail