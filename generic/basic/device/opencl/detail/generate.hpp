#pragma once

namespace detail
{
    template < class type > concept opencl_random_engine_type =
        requires ( type engine, opencl::template pointer<type> it, boost::compute::command_queue& cmd_queue ) { engine.generate(it, it, cmd_queue); };
}

decltype(auto) opencl::generate ( auto&& first, auto&& last, detail::opencl_random_engine_type auto&& engine )
{
    engine.generate(first, last, opencl::execution_context.get_command_queue());
    opencl::execution_context.get_command_queue().finish();
    return;
}
