namespace detail
{
    template < class input_type, int count, class... int_types >
    constexpr bool invocable_by_n_ints_helper = []
        {
            if constexpr ( count >= 1 )
                return invocable_by_n_ints_helper<input_type,count-1,int_types...,int>;
            else
                return invocable<input_type,int_types...>;
        } ();

    template < class input_type, int count >
    concept invocable_by_n_ints = invocable_by_n_ints_helper<input_type,count>; // Concept cannot be recursive.

    template < class input_type, class result_type, int count, class... int_types >
    constexpr bool invocable_r_by_n_ints_helper = []
        {
            if constexpr ( count >= 1 )
                return invocable_r_by_n_ints_helper<input_type,result_type,count-1,int_types...,int>;
            else
                return invocable_r<input_type,result_type,int_types...>;
        } ();

    template < class input_type, class result_type, int count >
    concept invocable_r_by_n_ints = invocable_r_by_n_ints_helper<input_type,result_type,count>; // Concept cannot be recursive

    template < class input_type, int count, class... types >
    struct invoke_result_by_n_ints_helper;

    template < class input_type, int count, class... types >
        requires ( count >= 1 )
    struct invoke_result_by_n_ints_helper<input_type,count,types...>
    {
        using type = invoke_result_by_n_ints_helper<input_type,count-1,int,types...>::type;
    };

    template < class input_type, int count, class... types >
        requires ( count == 0 )
    struct invoke_result_by_n_ints_helper<input_type,count,types...>
    {
        using type = invoke_result<input_type,types...>;
    };

    template < class input_type, int count >
    using invoke_result_by_n_ints = invoke_result_by_n_ints_helper<input_type,count>::type;



    template < class value_type, class... types >
    constexpr bool ints_until_last_type =
        all_of_constexpr<1,sizeof...(types)-1>([] <int index> { return convertible_to<index_type_of<index,types...>,int>; }) and
        ( (     is_void<value_type> and not invocable<last_type_of<types...>> and not invocable_by_n_ints<last_type_of<types...>,sizeof...(types)> ) or
          ( not is_void<value_type> and convertible_to<last_type_of<types...>,value_type> ) );

    template < class value_type, class... types >
    constexpr bool ints_until_last_generator =
        all_of_constexpr<1,sizeof...(types)-1>([] <int index> { return convertible_to<index_type_of<index,types...>,int>; }) and
        ( (     is_void<value_type> and invocable  <last_type_of<types...>>            ) or 
          ( not is_void<value_type> and invocable_r<last_type_of<types...>,value_type> ) );

    template < class value_type, class... types >
    constexpr bool ints_until_last_function =  
        all_of_constexpr<1,sizeof...(types)-1>([] <int index> { return convertible_to<index_type_of<index,types...>,int>; }) and 
        ( (     is_void<value_type> and invocable_by_n_ints  <last_type_of<types...>,           sizeof...(types)> ) or
          ( not is_void<value_type> and invocable_r_by_n_ints<last_type_of<types...>,value_type,sizeof...(types)> ) );
}