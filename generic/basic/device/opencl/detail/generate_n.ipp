#pragma once

decltype(auto) opencl::generate_n ( auto&&... args )
{
    if constexpr ( sizeof...(args) == 3 )
        if constexpr ( requires { last_value_of(args...).generate(first_value_of(args...), first_value_of(args...) + second_value_of(args...), opencl::execution_context.get_command_queue()); } )
        {
            last_value_of(args...).generate(first_value_of(args...), first_value_of(args...) + second_value_of(args...), opencl::execution_context.get_command_queue());
            opencl::execution_context.get_command_queue().finish();
            return;
        } 

    boost::compute::generate_n(std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue());
    opencl::execution_context.get_command_queue().finish();
    return;
}