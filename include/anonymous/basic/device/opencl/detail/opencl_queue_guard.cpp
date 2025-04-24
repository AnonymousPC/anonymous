detail::opencl_queue_guard::~opencl_queue_guard ( )
{
    opencl_queue_context::command_queue().finish();
}

boost::compute::command_queue& detail::opencl_queue_guard::command_queue ( )
{
    return opencl_queue_context::command_queue();
}