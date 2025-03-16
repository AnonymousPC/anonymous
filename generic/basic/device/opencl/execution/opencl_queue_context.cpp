#pragma once

namespace detail
{
    std::string& opencl_source_replace ( std::string& str, const std::string& from, const std::string& to )
    {
        size_t pos = 0;
        while ( true )
        {
            pos = str.find(from, pos);
            if ( pos != std::string::npos )
            {
                str.replace(pos, from.size(), to);
                pos += to.size() + 1;
            }
            else 
                break;
        }
        return str;
    }
}

detail::opencl_queue_context::opencl_queue_context ( int )
{
    
}

std::uint32_t detail::opencl_queue_context::available_parallelism ( ) const
{
    try
    {
        return boost::compute::system::default_device().compute_units();
    }
    catch ( const boost::compute::no_device_found& e )
    {
        throw opencl_error("no opencl device found").from(e);
    }
}

const boost::compute::device& detail::opencl_queue_context::device ( )
{
    thread_local let dvc = [] -> std::optional<boost::compute::device> { try { return boost::compute::system::default_device(); } catch ( const boost::compute::no_device_found& ) { return std::nullopt; } } ();
    if ( dvc.has_value() ) [[likely]] 
        return dvc.value();
    else
        throw opencl_error("opencl device not found");
}

const boost::compute::context& detail::opencl_queue_context::context ( )
{
    thread_local let ctx = [] -> std::optional<boost::compute::context> { try { return boost::compute::system::default_context(); } catch ( const boost::compute::no_device_found& ) { return std::nullopt; } } ();
    if ( ctx.has_value() ) [[likely]]
        return ctx.value();
    else
        throw opencl_error("opencl device not found");
}

boost::compute::command_queue& detail::opencl_queue_context::command_queue ( )
{
    thread_local let que = [] -> std::optional<boost::compute::command_queue> { try { return boost::compute::command_queue(boost::compute::system::default_context(), boost::compute::system::default_device()); } catch ( const boost::compute::no_device_found& ) { return std::nullopt; } } ();
    if ( que.has_value() ) [[likely]]
        return que.value();
    else
        throw opencl_error("opencl device not found");
}

boost::compute::kernel detail::opencl_queue_context::build_kernel ( const boost::compute::program& prog, std::string kernel_name )
{
    try
    {
        return boost::compute::kernel(prog, kernel_name);
    }
    catch ( const boost::compute::opencl_error& e )
    {
        throw opencl_error("failed to build opencl kernel\n"
                           "    ===== source =====\n"
                           "{}\n"
                           "\n"
                           "    ===== build log =====\n"
                           "{}", // build log ends with "\n" itself.
                           prog.source()    | std::views::split     ('\n')
                                            | std::views::drop_while([] (const auto& line) { return std::ranges::starts_with(line, std::string_view("#pragma")); })
                                            | std::views::transform ([] (const auto& line) { return "      " + (line | std::ranges::to<std::string>()); })
                                            | std::views::join_with ('\n')
                                            | std::ranges::to<std::string>(),
                           prog.build_log() | std::views::split     ('\n')
                                            | std::views::transform ([] (const auto& line) { return "      " + (line | std::ranges::to<std::string>()); })
                                            | std::views::join_with ('\n')
                                            | std::ranges::to<std::string>()
                          ).from(e);
    }
}

void detail::opencl_queue_context::enqueue ( execpools::task_base* task, std::uint32_t tid )
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
            throw opencl_error("failed to enqueue task").from(e);
        }
    else
        throw opencl_error("failed to enqueue task: this opencl device does not supports executing host function (with name = {}, vendor = {}, profile = {}, version = {}, driver_version = {}, capability.exec_kernel = {}, capability.exec_native_kernel = {})",
                           boost::compute::system::default_device().name(),
                           boost::compute::system::default_device().vendor(),
                           boost::compute::system::default_device().profile(),
                           boost::compute::system::default_device().version(),
                           boost::compute::system::default_device().driver_version(),
                           boost::compute::system::default_device().get_info<CL_DEVICE_EXECUTION_CAPABILITIES>() & CL_EXEC_KERNEL,
                           boost::compute::system::default_device().get_info<CL_DEVICE_EXECUTION_CAPABILITIES>() & CL_EXEC_NATIVE_KERNEL);
}

BOOST_COMPUTE_CL_CALLBACK void detail::opencl_queue_context::enqueue_callback ( void* args )
{
    let ptr = static_cast<task_type*>(args);
    ptr->task->__execute(ptr->task, /*tid=*/ptr->tid);
}