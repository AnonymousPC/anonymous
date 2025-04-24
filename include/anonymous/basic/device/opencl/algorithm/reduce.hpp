decltype(auto) opencl::reduce ( auto&&... args )
{
    static_assert(sizeof...(args) == 3 or sizeof...(args) == 4, "boost::compute::reduce() accepts 3 or 4 args");

    using type = remove_cvref<index_type_of<3,decltype(args)...>>;
    auto result = type();
    if constexpr ( sizeof...(args) == 3 )
        boost::compute::reduce(first_value_of(args...), second_value_of(args...), &result, opencl::execution_context.command_queue());
    else
        boost::compute::reduce(first_value_of(args...), second_value_of(args...), &result, last_value_of(args...), opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
    return result;
}