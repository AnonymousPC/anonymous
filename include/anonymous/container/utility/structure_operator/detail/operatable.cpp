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

} // namespace detail