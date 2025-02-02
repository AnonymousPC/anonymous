#pragma once

namespace detail
{
    template < class... types >
    struct array_deduction;

    template < class... types >
        requires ( sizeof...(types) >= 2 ) and 
                 detail::ints_until_last_type<void,types...> and
                 ( not convertible_to<last_type_of<types...>,int> ) // Ambiguous when last_type == int.
    struct array_deduction<types...>
    {
        using value_type = last_type_of<types...>;
        constexpr static const int dim = sizeof...(types) - 1;
    };

    template < class... types >
        requires ( sizeof...(types) >= 2 ) and 
                 detail::ints_until_last_func<void,types...>
    struct array_deduction<types...>
    {
        using value_type = invoke_result<last_type_of<types...>>;
        constexpr static const int dim = sizeof...(types) - 1;
    };

    template < class... types >
        requires ( sizeof...(types) >= 2 ) and 
                 detail::ints_until_last_func_ints<void,types...>
    struct array_deduction<types...>
    {
        using value_type = detail::invoke_result_by_n_ints<last_type_of<types...>,sizeof...(types)-1>;
        constexpr static const int dim = sizeof...(types) - 1;
    };

    template < class type >
    struct array_deduction<std::initializer_list<type>>
    {
        using value_type = type;
        constexpr static const int dim = 1;
    };

    template < class type >
    struct array_deduction<range<type>>
    {
        using value_type = type;
        constexpr static const int dim = 1;
    };
    
} // namespace detail


array ( auto... args ) -> array<typename detail::array_deduction<decltype(args)...>::value_type,
                                         detail::array_deduction<decltype(args)...>::dim>;