#pragma once

std::ostream& operator << ( std::ostream& left, const array_type auto& right )
{
    if constexpr ( decay<decltype(right)>::dimension() == 1 )
        std::ranges::for_each(right, [&] (const auto& val) { left << val << ' '; });
    else
        std::ranges::for_each(right, [&] (const auto& line) { left << line << '\n'; });
    return left;
}

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



    enum array_attribute
    {
        no_attribute,
        rows_attribute,
        columns_attribute,
        transpose_attribute 
    };

    constexpr auto multiply_first_to_second_last ( const auto& arg1, const auto& arg2, [[maybe_unused]] const auto&... args )
    {
        if constexpr ( sizeof...(args) >= 1 )
            return multiply_first_to_second_last(arg1 * arg2, args...);
        else 
            return arg1;
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
            return arg1 >= 0 and check_first_until_second_last_as_positive(args...);
        else
            return true;
    }

    constexpr decltype(auto) md_access ( auto& arr, int_type auto idx1, int_type auto... idxs )
    {
        if constexpr ( sizeof...(idxs) >= 1 )
            return md_access(arr[idx1], idxs...);
        else
            return arr[idx1];
    }

    constexpr decltype(auto) md_access ( const auto& arr, int_type auto idx1, int_type auto... idxs )
    {
        if constexpr ( sizeof...(idxs) >= 1 )
            return md_access(arr[idx1], idxs...);
        else
            return arr[idx1];
    }

    constexpr void md_generate ( auto& arr, const auto& shp, const auto& func, int_type auto... idx )
    {
        if constexpr ( sizeof...(idx) <= decay<decltype(arr)>::dimension() - 2 )
            for ( int i in range(shp[sizeof...(idx)+1]) )
                md_generate(arr, shp, func, idx..., i);
        else
            for ( int i in range(shp[-1]) )
                md_access(arr, idx..., i) = func(idx..., i);
    }

    template < auto attr >
    constexpr int view_offset_begin ( const auto& shp, int_type auto... offsets )
    {
        if constexpr ( sizeof...(offsets) == 0 )
            return 0;
        else
            if constexpr ( attr == rows_attribute )
            { 
                int ofs = 0;
                for_constexpr<1,sizeof...(offsets)>([&] <int index>
                    {
                        let p = 1;
                        for_constexpr<1+index,1+sizeof...(offsets)>([&] <int index2> { p *= shp[index2]; });
                        p *= index_value_of<index>(offsets...);
                        ofs += p;
                    });
                return ofs;
            }
            else if constexpr ( attr == columns_attribute )
            {
                int ofs = 0;
                for_constexpr<1,sizeof...(offsets)>([&] <int index>
                    {
                        let p = 1;
                        for_constexpr<decay<decltype(shp)>::size()-sizeof...(offsets),decay<decltype(shp)>::size()-sizeof...(offsets)+index-1>([&] <int index2> { p *= shp[index2]; });
                        p *= index_value_of<index>(offsets...);
                        ofs += p;
                    });
                return ofs;
            }
            else
                static_assert(false, "unknown attribute");
    }

    template < auto attr >
    constexpr int view_offset_end ( const auto& shp, int_type auto... offsets )
    {
        if constexpr ( attr == rows_attribute )
            return view_offset_begin<attr>(shp, offsets...) + shp[1+sizeof...(offsets)];
        else if constexpr ( attr == columns_attribute )
            return view_offset_begin<attr>(shp, offsets...) + shp[decay<decltype(shp)>::size()-sizeof...(offsets)];
        else
            static_assert(false, "unknown attribute");
    }


    
    
}