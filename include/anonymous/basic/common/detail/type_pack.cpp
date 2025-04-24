namespace detail
{
    template < class... types >
    struct first_type_of_helper;

    template < class type1, class... types >
    struct first_type_of_helper<type1,types...>
    {
        using type = type1;
    };
    
    template < class... types > 
    struct second_type_of_helper;

    template < class type1, class type2, class... types >
    struct second_type_of_helper<type1,type2,types...>
    {
        using type = type2;
    };

    template < class... types >
    struct last_type_of_helper;

    template < class type1 >
    struct last_type_of_helper<type1>
    {
        using type = type1;
    };

    template < class type1, class... types >
        requires ( 1 + sizeof...(types) >= 2 )
    struct last_type_of_helper<type1,types...>
    {
        using type = last_type_of_helper<types...>::type;
    };

    template < int index, class... types >
    struct index_type_of_helper;

    template < int index, class type1, class... types >
        requires ( index == 1 or index == - 1 - sizeof...(types) )
    struct index_type_of_helper<index,type1,types...>
    {
        using type = type1;
    };

    template < int index, class type1, class... types >
        requires ( index >= 2 and index <= 1 + sizeof...(types) )
    struct index_type_of_helper<index,type1,types...>
    {
        using type = index_type_of_helper<index-1,types...>::type;
    };

    template < int index, class type1, class... types >
        requires ( index >= - 1 - sizeof...(types) + 1 and index <= -1 )
    struct index_type_of_helper<index,type1,types...>
    {
        using type = index_type_of_helper<index,types...>::type;
    };

    constexpr decltype(auto) first_value_of_helper ( auto&& first, auto&&... )
    {
        return first;
    }

    constexpr decltype(auto) second_value_of_helper ( auto&& first, auto&& second, auto&&... )
    {
        return second;
    }

    constexpr decltype(auto) last_value_of_helper ( auto&& first, auto&&... other )
    {
        if constexpr ( sizeof...(other) == 0 )
            return first;
        else
            return last_value_of_helper(std::forward<decltype(other)>(other)...);
    }

    template < int index >
    constexpr decltype(auto) index_value_of_helper ( auto&& first, auto&&... other )
    {
        static_assert ( ( index >= - sizeof...(other) - 1 and index <= -1 ) or ( index >= 1 and index <= sizeof...(other) + 1 ), "index out of range" );

        if constexpr ( index == 1 or index == - sizeof...(other) - 1 )
            return first;
        else
            if constexpr ( index >= 2 )
                return index_value_of_helper<index-1>(std::forward<decltype(other)>(other)...);
            else
                return index_value_of_helper<index>  (std::forward<decltype(other)>(other)...);
    }
}