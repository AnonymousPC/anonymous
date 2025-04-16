#pragma once

namespace detail
{
    std::string& opencl_source_replace ( std::string&, const std::string&, const std::string& );

    template < class type >
    std::string opencl_type_name ( );
    
} // namespace detail



constexpr auto opencl_queue_context::forward_progress_guarantee ( ) const
{
    return std::execution::forward_progress_guarantee::weakly_parallel;
}

constexpr auto opencl_queue_context::available_parallelism ( ) const
{
    return device().compute_units();
}

const boost::compute::context& opencl_queue_context::context ( )
{
    try
    {
        return boost::compute::system::default_context();
    }
    catch ( const boost::compute::no_device_found& e )
    {
        
    }
}

const boost::compute::device& opencl_queue_context::device ( )
{
    static auto ctx = boost::compute::system::default_device();
    return ctx;
}

boost::compute::command_queue& opencl_queue_context::command_queue ( )
{
    thread_local auto que = boost::compute::command_queue(context(), device());
    return que;
}

boost::compute::program opencl_queue_context::build_program ( std::string source, const auto&... args )
{
    // Build
    if constexpr ( sizeof...(args) > 0 )
    {
        static_assert(sizeof...(args) % 2 == 0, "arguments should be like: type1(), 'type1', type2(), 'type2', , ...");
        for_constexpr<1,sizeof...(args),2>([&] <int index>
        {
            source = detail::opencl_source_replace(source, index_value_of<index+1>(args...), detail::opencl_type_name<index_type_of<index,decltype(args)...>>());
        });
    }

    auto prog   = boost::compute::program();
 // auto ext    = device().extensions();
 // auto align  = std::ranges::max_element(ext, [] (const auto& a, const auto& b) { return a.size() < b.size(); })->size();
 // auto pragma = ext
 //            | std::views::filter   ([ ] (const auto& opt) { return opt != ""; })
 //            | std::views::transform([&] (const auto& opt) { return std::format("#pragma OPENCL EXTENSION {:{}} : enable", opt, align); })
 //            | std::views::join_with('\n')
 //            | std::ranges::to<std::string>();

    try
    {
     // prog = boost::compute::program::create_with_source(pragma + '\n' + source, context());
        prog = boost::compute::program::create_with_source(source, context());
    }
    catch ( const boost::compute::opencl_error& e )
    {
        throw opencl_error("failed to create opencl program").from(e);
    }

    try
    {
        prog.build();
    }
    catch ( const boost::compute::opencl_error& e )
    {
        throw opencl_error("failed to build opencl program\n"
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

    return prog;
}



boost::compute::kernel opencl_queue_context::build_kernel ( const boost::compute::program& prog, std::string kernel_name )
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

void opencl_queue_context::enqueue ( execpools::task_base* task, std::uint32_t tid )
{
    if ( boost::compute::system::default_device().get_info<CL_DEVICE_EXECUTION_CAPABILITIES>() & CL_EXEC_NATIVE_KERNEL )
        try
        {
            // TODO: I currently have no environment to check it.
            static auto que = boost::compute::command_queue(boost::compute::system::default_context(), boost::compute::system::default_device());
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

void opencl_queue_context::enqueue_callback ( void* args )
{
    auto ptr = static_cast<task_type*>(args);
    ptr->task->__execute(ptr->task, /*tid=*/ptr->tid);
}









std::string& detail::opencl_source_replace ( std::string& str, const std::string& from, const std::string& to )
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

template < class type >
std::string detail::opencl_type_name ( )
{
    if constexpr ( requires { boost::compute::detail::type_name_trait<type>::value(); } )
        return boost::compute::detail::type_name_trait<type>::value();
    else
        return boost::core::demangle(typeid(type).name());
}