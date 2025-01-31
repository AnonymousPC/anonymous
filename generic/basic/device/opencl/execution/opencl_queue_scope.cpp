#pragma once

detail::opencl_queue_scope::~opencl_queue_scope ( )
{
    detail::opencl_queue_context::command_queue().finish();
}

boost::compute::command_queue& detail::opencl_queue_scope::command_queue ( )
{
    return detail::opencl_queue_context::command_queue();
}