#pragma once

namespace detail
{
    template < class type, class... types >
    constexpr bool ints_until_last_func = []
    {
        if constexpr ( is_void<type> )
            return convertible_until<int,-2,types...> and std::invocable<last_type_of<types...>>;
        else
            return convertible_until<int,-2,types...> and function_type<last_type_of<types...>,type()>;
    } ();

    template < class result_type, class input_type, int count, class... types >
    constexpr bool invocable_r_by_n_ints_helper = []
    {
        if constexpr ( count >= 1 )
            return invocable_r_by_n_ints_helper<result_type,input_type,count-1,int,types...>;
        else
            if constexpr ( is_void<result_type> )
                return std::invocable<input_type,types...>;
            else
                return function_type<input_type,result_type(types...)>;
    } ();

    template < class result_type, class input_type, int count >
    constexpr bool invocable_r_by_n_ints = invocable_r_by_n_ints_helper<result_type,input_type,count>;

    template < class type, class... types >
    constexpr bool ints_until_last_func_ints = convertible_until<int,-2,types...> and invocable_r_by_n_ints<type,last_type_of<types...>,sizeof...(types)-1>; // No need to check <void,...>, as it forwards to invocable_r_by_n_ints_helper.

    template < class type, class... types >
    constexpr bool ints_until_last_type = convertible_until<int,-2,types...> and []
    {
        if constexpr ( is_void<type> )
            return not ints_until_last_func<type,types...> and not ints_until_last_func_ints<type,types...>;
        else
            return std::convertible_to<last_type_of<types...>,type>;
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
    using invoke_result_by_n_ints = invoke_result_by_n_ints_helper<input_type,count>::type;

    constexpr auto multiply_first_to_second_last ( const auto& arg1, const auto& arg2, [[maybe_unused]] const auto&... args )
    {
        if constexpr ( sizeof...(args) >= 1 )
            return multiply_first_to_second_last(arg1 * arg2, args...);
        else 
            return arg1 * arg2;
    }

    constexpr int multiply_first_until_last ( const auto&... args )
    {
        return ( args * ... );
    }

    constexpr int multiply_first_until_second_last ( const auto& arg1, const auto&... args )
    {
        if constexpr ( sizeof...(args) >= 1 )
            return arg1 * multiply_first_until_second_last(args...);
        else
            return 1;
    }

    constexpr bool check_first_until_last_as_positive ( const auto&... args )
    {
        return ( [] (const auto& v) { return v >= 0; } ( args ) and ... );
    }

    constexpr bool check_first_until_second_last_as_positive ( const auto& arg1, const auto&... args )
    {
        if constexpr ( sizeof...(args) >= 1 )
            return arg1 > 0 and check_first_until_second_last_as_positive(args...);
        else
            return true;
    }

    constexpr void device_generate_mdspan ( const auto&, const auto& )
    {
        static_assert(false, "not coded yet");
    }

    template < int from, int to >
    constexpr int partial_size_of ( const auto& arr )
    {
        // TODO: optimize.

        let shp = arr.static_shape();

        if constexpr ( from == 2 and to == -1 )
            return std::accumulate(++shp.begin(), shp.end(), 1, std::multiplies<>());
        else if constexpr ( from == 1 and to == -2 )
            return std::accumulate(shp.begin(), --shp.end(), 1, std::multiplies<>());
        else
            static_assert(false, "only accepts partial_size_of<2,-1> or partial_size_of<1,-2>");
    }

    template < int from, int to >
    constexpr auto partial_shape_of ( const auto& arr )
    {
        // TODO: optimize.

        let shp = arr.static_shape();
        let partial = static_array<int,arr.size()-1>();

        if constexpr ( from == 2 and to == -1 )
            std::copy(++shp.begin(), shp.end(), partial.begin());
        else if constexpr ( from == 1 and to == -2 )
            std::copy(shp.begin(), --shp.end(), partial.begin());
        else
            static_assert(false, "only accepts partial_shape_of<2,-1> or partial_shape_of<1,-2>");

        return partial;
    }


    
    
}