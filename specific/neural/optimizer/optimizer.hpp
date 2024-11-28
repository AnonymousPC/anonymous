#pragma once

namespace aux
{
    template < class type1, class type2 >
    constexpr bool same_as_one_of_tuple_value_type = false;

    template < class type, class... types >
    constexpr bool same_as_one_of_tuple_value_type<type,tuple<types...>> = ( std::same_as<type,types> or ... );

    template < class type1, tuple_type type2 >
    constexpr bool same_as_one_of_tuple_value_type<type1,type2> = same_as_one_of_tuple_value_type<type1,decltype(tuple(std::declval<type2>()))>;


    template < class type1, class type2 >
    constexpr int index_of_same_type_in_tuple_value_types = [] { static_assert(tuple_type<type2>, "type2 is not tuple_type"); static_assert(false, "type1 is not same as any of type2::value_type"); return 0; } ();

    template < class type, class type1, class... types >
    constexpr int index_of_same_type_in_tuple_value_types<type,tuple<type1,types...>> = [] { if constexpr ( std::same_as<type,type1> ) return 1; else return 1 + index_of_same_type_in_tuple_value_types<type,tuple<types...>>; } ();

    template < class type1, tuple_type type2 >
    constexpr int index_of_same_type_in_tuple_value_types<type1,type2> = index_of_same_type_in_tuple_value_types<type1,decltype(tuple(std::declval<type2>()))>;
}

#include "adaptive_moment_estimation_optmizer.hpp"
#include "root_mean_square_propagation_optimizer.hpp"
#include "stochastic_gradient_descent_optimizer.hpp"