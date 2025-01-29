#pragma once

detail::opencl_queue_scope::~opencl_queue_scope ( )
{
    opencl::execution_context.command_queue().finish();
}

boost::compute::command_queue& detail::opencl_queue_scope::command_queue ( )
{
    return opencl::execution_context.command_queue();
}