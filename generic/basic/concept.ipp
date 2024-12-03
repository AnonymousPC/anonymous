#pragma once




/// Function

namespace aux
{
    template < class type, class func_type >
    struct function_type_helper;

    template < class type, class res_type, class... arg_types >
    struct function_type_helper<type,res_type(arg_types...)>
    {
        constexpr static const bool value = std::is_invocable_r<res_type,type,arg_types...>::value;
    };
}

template < class type, class func_type >  concept function_type = aux::function_type_helper<type,func_type>::value;
template < class type, class value_type > concept unary_pred    = function_type<type,bool(value_type)>;
template < class type, class value_type > concept unary_op      = function_type<type,value_type(value_type)>;
template < class type, class value_type > concept binary_pred   = function_type<type,bool(value_type,value_type)>;
template < class type, class value_type > concept binary_op     = function_type<type,value_type(value_type,value_type)>;


/// Argument pack

#define size() (int(1+sizeof...(types))) // Warning: sizeof...(types) returns an unsigned int, which cause error without static_cast<int>

namespace aux
{
    template < class... types >
    struct first_type_of;

    template < class type1, class... types >
    struct first_type_of<type1,types...>
    {
        using type = type1;
    };



    template < class... types >
    struct last_type_of;

    template < class type1 >
    struct last_type_of<type1>
    {
        using type = type1;
    };

    template < class type1, class... types >
        requires ( size() >= 2 )
    struct last_type_of<type1,types...>
    {
        using type = typename last_type_of<types...>::type;
    };



    template < int index, class... types >
    struct index_type_of;

    template < int index, class type1, class... types >
        requires ( index == 1 or index == -size() )
    struct index_type_of<index,type1,types...>
    {
        using type = type1;
    };

    template < int index, class type1, class... types >
        requires ( index >= 2 and index <= size() )
    struct index_type_of<index,type1,types...>
    {
        using type = typename index_type_of<index-1,types...>::type;
    };

    template < int index, class type1, class... types >
        requires ( index >= -size() + 1 and index <= -1 )
    struct index_type_of<index,type1,types...>
    {
        using type = typename index_type_of<index,types...>::type;
    };
}

template <            class... types > using first_type_of = aux::first_type_of<types...>::type;
template <            class... types > using last_type_of  = aux::last_type_of<types...>::type;
template < int index, class... types > using index_type_of = aux::index_type_of<index,types...>::type;





constexpr const auto& first_value_of ( const auto& first, const auto&... )
{
    return first;
}

constexpr const auto& last_value_of ( const auto& first, const auto&... other )
{
    if constexpr ( sizeof...(other) == 0 )
        return first;
    else
        return last_value_of ( other... );
}

template < int index >
constexpr const auto& index_value_of ( const auto& first, const auto&... other )
    requires ( ( index >= - sizeof...(other) - 1 and index <= -1 ) or ( index >= 1 and index <= sizeof...(other) + 1 ) )
{
    if constexpr ( index == 1 or index == - sizeof...(other) - 1 )
        return first;
    else
        if constexpr ( index >= 2 )
            return index_value_of<index-1> ( other... );
        else
            return index_value_of<index>   ( other... );
}






namespace aux
{
    template < class result_type, int index, class... types >
    struct convertible_since;

    template < class result_type, int index, class type1 >
        requires ( index == 1 or index == -1 )
    struct convertible_since<result_type,index,type1>
    {
        constexpr static const bool value = std::is_convertible<type1,result_type>::value;
    };

    template < class result_type, int index, class type1, class... types >
        requires ( index == 1 and size() >= 2 )
    struct convertible_since<result_type,index,type1,types...>
    {
        constexpr static const bool value = std::is_convertible<type1,result_type>::value and convertible_since<result_type,index,types...>::value;
    };

    template < class result_type, int index, class type1, class... types >
        requires ( index >= 2 and index <= size() and size() >= 2 )
    struct convertible_since<result_type,index,type1,types...>
    {
        constexpr static const bool value = convertible_since<result_type,index-1,types...>::value;
    };

    template < class result_type, int index, class type1, class... types >
        requires ( index == -size() and size() >= 2 )
    struct convertible_since<result_type,index,type1,types...>
    {
        constexpr static const bool value = std::is_convertible<type1,result_type>::value and convertible_since<result_type,index+1,types...>::value;
    };

    template < class result_type, int index, class type1, class... types >
        requires ( index >= -size() + 1 and index <= -1 and size() >= 2 )
    struct convertible_since<result_type,index,type1,types...>
    {
        constexpr static const bool value = convertible_since<result_type,index,types...>::value;
    };



    template < class result_type, int index, class... types >
    struct convertible_until;

    template < class result_type, int index, class type1, class... types >
        requires ( index == 1 or index == -size() )
    struct convertible_until<result_type,index,type1,types...>
    {
        constexpr static const bool value = std::is_convertible<type1,result_type>::value;
    };

    template < class result_type, int index, class type1, class... types >
        requires ( index >= 2 and index <= size() )
    struct convertible_until<result_type,index,type1,types...>
    {
        constexpr static const bool value = std::is_convertible<type1,result_type>::value and convertible_until<result_type,index-1,types...>::value;
    };

    template < class result_type, int index, class type1, class... types >
        requires ( index >= -size() + 1 and index <= -1 )
    struct convertible_until<result_type,index,type1,types...>
    {
        constexpr static const bool value = std::is_convertible<type1,result_type>::value and convertible_until<result_type,index,types...>::value;
    };
}


template < class result_type, int index, class... types > constexpr bool convertible_since = aux::convertible_since<result_type,index,types...>::value;
template < class result_type, int index, class... types > constexpr bool convertible_until = aux::convertible_until<result_type,index,types...>::value;


#undef size
