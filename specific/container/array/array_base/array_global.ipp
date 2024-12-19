#pragma once

namespace aux
{
    template < class type, class... types >
    constexpr bool ints_until_last_func = []
    {
        if constexpr ( std::is_void<type>::value )
            return ap::convertible_until<int,-2,types...> and std::invocable<ap::last_type_of<types...>>;
        else
            return ap::convertible_until<int,-2,types...> and ap::function_type<ap::last_type_of<types...>,type()>;
    } ();

    template < class result_type, class input_type, int count, class... types >
    constexpr bool invocable_r_by_n_ints_helper = []
    {
        if constexpr ( count >= 1 )
            return invocable_r_by_n_ints_helper<result_type,input_type,count-1,int,types...>;
        else
            if constexpr ( std::is_void<result_type>::value )
                return std::invocable<input_type,types...>;
            else
                return ap::function_type<input_type,result_type(types...)>;
    } ();

    template < class result_type, class input_type, int count >
    constexpr bool invocable_r_by_n_ints = invocable_r_by_n_ints_helper<result_type,input_type,count>;

    template < class type, class... types >
    constexpr bool ints_until_last_func_ints = ap::convertible_until<int,-2,types...> and invocable_r_by_n_ints<type,ap::last_type_of<types...>,sizeof...(types)-1>; // No need to check <void,...>, as it forwards to is_invocable_r_by_n_ints.

    template < class type, class... types >
    constexpr bool ints_until_last_type = ap::convertible_until<int,-2,types...> and []
    {
        if constexpr ( std::is_void<type>::value )
            return not ints_until_last_func<type,types...> and not ints_until_last_func_ints<type,types...>;
        else
            return std::convertible_to<ap::last_type_of<types...>,type>;
    } ();

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
    using invoke_result_by_n_ints = invoke_result_by_n_ints_helper<input_type,count>::type;                                                                  // Helper
}