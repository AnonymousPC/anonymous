template < class... types >
    requires ( sizeof...(types) >= 2 ) and 
             detail::ints_until_last_type<void,types...> and
             ( not convertible_to<last_type_of<types...>,int> ) // Ambiguous when last_type == int.
struct detail::array_deduction<types...>
{
    using value_type = last_type_of<types...>;
    constexpr static const int dim = sizeof...(types) - 1;
};

template < class... types >
    requires ( sizeof...(types) >= 2 ) and 
             detail::ints_until_last_generator<void,types...>
struct detail::array_deduction<types...>
{
    using value_type = invoke_result<last_type_of<types...>>;
    constexpr static const int dim = sizeof...(types) - 1;
};

template < class... types >
    requires ( sizeof...(types) >= 2 ) and 
             detail::ints_until_last_function<void,types...>
struct detail::array_deduction<types...>
{
    using value_type = detail::invoke_result_by_n_ints<last_type_of<types...>,sizeof...(types)-1>;
    constexpr static const int dim = sizeof...(types) - 1;
};

template < class type >
struct detail::array_deduction<std::initializer_list<type>>
{
    using value_type = type;
    constexpr static const int dim = 1;
};