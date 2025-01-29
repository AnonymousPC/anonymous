#pragma once

detail::opencl_queue_context::opencl_queue_context ( int )
{
    
}
  
std::uint32_t detail::opencl_queue_context::available_parallelism ( ) const
{
    return boost::compute::system::default_device().compute_units();
}

const boost::compute::device& detail::opencl_queue_context::device ( )
{
    thread_local let dvc = boost::compute::system::default_device();
    return dvc;
}

const boost::compute::context& detail::opencl_queue_context::context ( )
{
    thread_local let ctx = boost::compute::system::default_context();
    return ctx;
}

boost::compute::command_queue& detail::opencl_queue_context::command_queue ( )
{
    thread_local let que = boost::compute::command_queue(boost::compute::system::default_context(), boost::compute::system::default_device());
    return que;
}

void detail::opencl_queue_context::enqueue ( execpools::task_base* task, std::uint32_t tid ) noexcept
{
    if ( boost::compute::system::default_device().get_info<CL_DEVICE_EXECUTION_CAPABILITIES>() & CL_EXEC_NATIVE_KERNEL )
        try
        {
            // TODO: I currently have no environment to check it.
            static let que = boost::compute::command_queue(boost::compute::system::default_context(), boost::compute::system::default_device());
            que.enqueue_native_kernel(enqueue_callback, new task_type(task, tid), sizeof(task_type), 0, 0, 0);
            que.flush();
        }
        catch ( const boost::compute::opencl_error& e )
        {
            throw_opencl_error(e);
        }
    else
        throw_capatability_error();
}

BOOST_COMPUTE_CL_CALLBACK void detail::opencl_queue_context::enqueue_callback ( void* args )
{
    let ptr = static_cast<task_type*>(args);
    ptr->task->__execute(ptr->task, /*tid=*/ptr->tid);
}

void detail::opencl_queue_context::throw_opencl_error ( const boost::compute::opencl_error& e )
{
    throw device_error("failed to enqueue task").from(e);
}

void detail::opencl_queue_context::throw_capatability_error ( )
{
    throw device_error("failed to enqueue task: this opencl device does not supports executing host function (with name = {}, vendor = {}, profile = {}, version = {}, driver_version = {}, capability = {{exec_kernel = {}, exec_native_kernel = {}}})",
                        boost::compute::system::default_device().name(),
                        boost::compute::system::default_device().vendor(),
                        boost::compute::system::default_device().profile(),
                        boost::compute::system::default_device().version(),
                        boost::compute::system::default_device().driver_version(),
                        boost::compute::system::default_device().get_info<CL_DEVICE_EXECUTION_CAPABILITIES>() & CL_EXEC_KERNEL,
                        boost::compute::system::default_device().get_info<CL_DEVICE_EXECUTION_CAPABILITIES>() & CL_EXEC_NATIVE_KERNEL);
}