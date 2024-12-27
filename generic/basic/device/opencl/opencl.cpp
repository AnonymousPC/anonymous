#pragma once

std::uint32_t opencl::execution_context_type::available_parallelism ( ) const
{
    return boost::compute::system::default_device().compute_units();
}

boost::compute::command_queue& opencl::execution_context_type::command_queue ( )
{
    thread_local auto cmd_queue = boost::compute::command_queue(boost::compute::system::default_context(), boost::compute::system::default_device());
    return cmd_queue;
}

void opencl::execution_context_type::enqueue ( execpools::task_base* task, std::uint32_t tid )
{
    if ( boost::compute::system::default_device().get_info<CL_DEVICE_EXECUTION_CAPABILITIES>() & CL_EXEC_NATIVE_KERNEL )
        try
        {
            thread_local auto task_queue = boost::compute::command_queue(boost::compute::system::default_context(), boost::compute::system::default_device());
            task_queue.enqueue_native_kernel(enqueue_callback, new task_type(task, tid), sizeof(task_type), 0, 0, 0);
            task_queue.flush();
        }
        catch ( const boost::compute::opencl_error& e )
        {
            throw device_error("failed to enqueue task [[caused by {}: {}]]", typeid(e), e.what());
        }
    else
        throw device_error("failed to enqueue task: opencl device does not supports executing host function (with name = {}, vendor = {}, profile = {}, version = {}, driver_version = {}, capability = {{exec_kernel = {}, exec_native_kernel = {}}})",
                            boost::compute::system::default_device().name(),
                            boost::compute::system::default_device().vendor(),
                            boost::compute::system::default_device().profile(),
                            boost::compute::system::default_device().version(),
                            boost::compute::system::default_device().driver_version(),
                            boost::compute::system::default_device().get_info<CL_DEVICE_EXECUTION_CAPABILITIES>() & CL_EXEC_KERNEL,
                            boost::compute::system::default_device().get_info<CL_DEVICE_EXECUTION_CAPABILITIES>() & CL_EXEC_NATIVE_KERNEL);
}

void BOOST_COMPUTE_CL_CALLBACK opencl::execution_context_type::enqueue_callback ( void* args )
{
    let ptr = static_cast<task_type*>(args);
    ptr->task->__execute(ptr->task, /*tid=*/ptr->tid);
}