#pragma once
#define size() (int(1+sizeof...(types))) // Warning: sizeof...(types) returns an unsigned int, which cause error without static_cast<int>

namespace detail
{
    template < class result_type, int index, class... types >
    struct convertible_since_helper;

    template < class result_type, int index, class type1 >
        requires ( index == 1 or index == -1 )
    struct convertible_since_helper<result_type,index,type1>
    {
        constexpr static const bool value = std::convertible_to<type1,result_type>;
    };

    template < class result_type, int index, class type1, class... types >
        requires ( index == 1 and size() >= 2 )
    struct convertible_since_helper<result_type,index,type1,types...>
    {
        constexpr static const bool value = std::convertible_to<type1,result_type> and convertible_since_helper<result_type,index,types...>::value;
    };

    template < class result_type, int index, class type1, class... types >
        requires ( index >= 2 and index <= size() and size() >= 2 )
    struct convertible_since_helper<result_type,index,type1,types...>
    {
        constexpr static const bool value = convertible_since_helper<result_type,index-1,types...>::value;
    };

    template < class result_type, int index, class type1, class... types >
        requires ( index == -size() and size() >= 2 )
    struct convertible_since_helper<result_type,index,type1,types...>
    {
        constexpr static const bool value = std::convertible_to<type1,result_type> and convertible_since_helper<result_type,index+1,types...>::value;
    };

    template < class result_type, int index, class type1, class... types >
        requires ( index >= -size() + 1 and index <= -1 and size() >= 2 )
    struct convertible_since_helper<result_type,index,type1,types...>
    {
        constexpr static const bool value = convertible_since_helper<result_type,index,types...>::value;
    };



    template < class result_type, int index, class... types >
    struct convertible_until_helper;

    template < class result_type, int index, class type1, class... types >
        requires ( index == 1 or index == -size() )
    struct convertible_until_helper<result_type,index,type1,types...>
    {
        constexpr static const bool value = std::convertible_to<type1,result_type>;
    };

    template < class result_type, int index, class type1, class... types >
        requires ( index >= 2 and index <= size() )
    struct convertible_until_helper<result_type,index,type1,types...>
    {
        constexpr static const bool value = std::convertible_to<type1,result_type> and convertible_until_helper<result_type,index-1,types...>::value;
    };

    template < class result_type, int index, class type1, class... types >
        requires ( index >= -size() + 1 and index <= -1 )
    struct convertible_until_helper<result_type,index,type1,types...>
    {
        constexpr static const bool value = std::convertible_to<type1,result_type> and convertible_until_helper<result_type,index,types...>::value;
    };



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
        requires ( size() >= 2 )
    struct last_type_of_helper<type1,types...>
    {
        using type = last_type_of_helper<types...>::type;
    };

    template < int index, class... types >
    struct index_type_of_helper;

    template < int index, class type1, class... types >
        requires ( index == 1 or index == -size() )
    struct index_type_of_helper<index,type1,types...>
    {
        using type = type1;
    };

    template < int index, class type1, class... types >
        requires ( index >= 2 and index <= size() )
    struct index_type_of_helper<index,type1,types...>
    {
        using type = index_type_of_helper<index-1,types...>::type;
    };

    template < int index, class type1, class... types >
        requires ( index >= -size() + 1 and index <= -1 )
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



    // Additional

    template < int from, int to, int add, int index >
    constexpr void for_constexpr_impl ( auto&& op )
    {
        if constexpr ( ( add > 0 and index <= to ) or
                       ( add < 0 and index >= to ) )
        {
            op.template operator()<index>();
            for_constexpr_impl<from,to,add,index+add>(std::forward<decltype(op)>(op));
        }
    }

    template < int from, int to, int add = 1 >
    constexpr void for_constexpr ( auto&& op )
    {
        static_assert(add != 0, "this for-clause is infinite");
        if constexpr ( ( add > 0 and from <= to ) or
                       ( add < 0 and from >= to ) )
            for_constexpr_impl<from,to,add,from>(op);
        else
            static_assert(false, "this for-clause does not do anything");
    }
}

#undef size
