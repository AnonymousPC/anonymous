#pragma once

/// Core

namespace detail
{
    template < int index, class input_type > struct tuple_element_helper;
    template < int index, class input_type > requires ( index > 0 ) struct tuple_element_helper<index,input_type> { using type = std::tuple_element<std::size_t(index-1),input_type>::type; };
    template < int index, class input_type > requires ( index < 0 ) struct tuple_element_helper<index,input_type> { using type = std::tuple_element<std::size_t(int(std::tuple_size<input_type>::value)+index),input_type>::type; };
}

template < class type1, class type2 >                 using          common_type         = std::common_type<type1,type2>::type;
template < bool condition, class type1, class type2 > using          conditional         = std::conditional<condition,type1,type2>::type;
template < class type >                               using          decay               = std::decay<type>::type;
template < class func_type, class... arg_types >      using          invoke_result       = std::invoke_result<func_type,arg_types...>::type;
template < class type >                               using          remove_const        = std::remove_const<type>::type;
template < class type >                               using          remove_cv           = std::remove_cv<type>::type;
template < class type >                               using          remove_volatile     = std::remove_volatile<type>::type;
template < class type >                               using          remove_extent       = std::remove_extent<type>::type;
template < class type >                               using          remove_pointer      = std::remove_pointer<type>::type;
template < class type >                               using          remove_reference    = std::remove_reference<type>::type;
template < int index, class type >                    using          tuple_element       = detail::tuple_element_helper<index,type>::type;
template < class type >                               constexpr int  tuple_size          = std::tuple_size<type>::value;

template < class type >                               constexpr bool is_class            = std::is_class<type>::value;
template < class type >                               constexpr bool is_const            = std::is_const<type>::value;
template < class type >                               constexpr bool is_lvalue_reference = std::is_lvalue_reference<type>::value;
template < class type >                               constexpr bool is_pointer          = std::is_pointer<type>::value;
template < class type >                               constexpr bool is_reference        = std::is_reference<type>::value;
template < class type >                               constexpr bool is_rvalue_reference = std::is_rvalue_reference<type>::value;
template < class type >                               constexpr bool is_void             = std::is_void<type>::value;
template < class type >                               constexpr bool is_volatile         = std::is_volatile<type>::value;


/// Operator

template < class type >               concept addable         = requires { std::declval<type >() + std::declval<type >(); };
template < class type1, class type2 > concept addable_to      = requires { std::declval<type1>() + std::declval<type2>(); };
template < class type1, class type2 > using   add_result      = decltype ( std::declval<type1>() + std::declval<type2>() );

template < class type >               concept minusable       = requires { std::declval<type >() - std::declval<type >(); };
template < class type1, class type2 > concept minusable_to    = requires { std::declval<type1>() - std::declval<type2>(); };
template < class type1, class type2 > using   minus_result    = decltype ( std::declval<type1>() - std::declval<type2>() );

template < class type >               concept multipliable    = requires { std::declval<type >() * std::declval<type >(); };
template < class type1, class type2 > concept multipliable_to = requires { std::declval<type1>() * std::declval<type2>(); };
template < class type1, class type2 > using   multiply_result = decltype ( std::declval<type1>() * std::declval<type2>() );

template < class type >               concept dividable       = requires { std::declval<type >() / std::declval<type >(); };
template < class type1, class type2 > concept dividable_to    = requires { std::declval<type1>() / std::declval<type2>(); };
template < class type1, class type2 > using   divide_result   = decltype ( std::declval<type1>() / std::declval<type2>() );

template < class type >               concept equalable       = requires { std::declval<type >() == std::declval<type >(); };
template < class type1, class type2 > concept equalable_to    = requires { std::declval<type1>() == std::declval<type2>(); };

template < class type >               concept comparable      = requires { std::declval<type >() <=> std::declval<type >(); };
template < class type1, class type2 > concept comparable_to   = requires { std::declval<type1>() <=> std::declval<type2>(); };

template < class type >               concept printable       = requires ( type obj ) { std::cout << obj; };
template < class type >               concept inputable       = requires ( type obj ) { std::cin  >> obj; };






/// Is...type

template < class type > concept char_type   = std::same_as<remove_cv<type>,char> or std::same_as<remove_cv<type>,wchar_t> or std::same_as<remove_cv<type>,char8_t> or std::same_as<remove_cv<type>,char16_t> or std::same_as<remove_cv<type>,char32_t> or requires { typename type::char_tag; };
template < class type > concept int_type    = ( std::signed_integral<type> and ( not char_type<type> ) ) or requires { typename type::int_tag;    };
template < class type > concept float_type  = std::floating_point<type>                                  or requires { typename type::float_tag;  };
template < class type > concept number_type = int_type<type> or float_type<type>                         or requires { typename type::number_tag; };






/// Function

// template < class type, class res_type, class.. arg_types > concept function_type = ...;
// template < class type, class value_type >                  concept unary_pred    = ...;
// template < class type, class value_type >                  concept unary_op      = ...;
// template < class type, class value_type >                  concept binary_pred   = ...;
// template < class type, class value_type >                  concept binary_op     = ...;




/// Argument pack

// template <            class... types > using first_type_of = ...;
// template <            class... types > using last_type_of  = ...;
// template < int index, class... types > using index_type_of = ...;

//                        constexpr const auto& first_value_of ( const auto&, const auto&... );
//                        constexpr const auto& last_value_of  ( const auto&, const auto&... );
// template < int index > constexpr const auto& index_value_of ( const auto&, const auto&... );

// template < class result_type, int index, class... types > constexpr bool same_since        = ...;
// template < class result_type, int index, class... types > constexpr bool same_until        = ...;
// template < class result_type, int index, class... types > constexpr bool convertible_since = ...;
// template < class result_type, int index, class... types > constexpr bool convertible_until = ...;


#include "concept.ipp"