#pragma once

namespace detail
{
    template < class type > std::string  opencl_type_name      ( );
    inline                  std::string& opencl_source_replace ( std::string&, const std::string&, const std::string& );
    
} // namespace detail




constexpr auto opencl_queue_context::forward_progress_guarantee ( )
{
    return std::execution::forward_progress_guarantee::weakly_parallel;;
}

constexpr auto opencl_queue_context::available_parallelism ( )
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

inline const boost::compute::device& opencl_queue_context::device ( )
{
    static let dvc = [] -> std::optional<boost::compute::device> { try { return boost::compute::system::default_device(); } catch ( const boost::compute::no_device_found& ) { return std::nullopt; } } ();
    if ( dvc.has_value() ) [[likely]] 
        return dvc.value();
    else
        throw opencl_error("opencl device not found");
}

inline const boost::compute::context& opencl_queue_context::context ( )
{
    static let ctx = [] -> std::optional<boost::compute::context> { try { return boost::compute::system::default_context(); } catch ( const boost::compute::no_device_found& ) { return std::nullopt; } } ();
    if ( ctx.has_value() ) [[likely]]
        return ctx.value();
    else
        throw opencl_error("opencl device not found");
}

inline boost::compute::command_queue& opencl_queue_context::command_queue ( )
{
    thread_local let que = [] -> std::optional<boost::compute::command_queue> { try { return boost::compute::command_queue(boost::compute::system::default_context(), boost::compute::system::default_device()); } catch ( const boost::compute::no_device_found& ) { return std::nullopt; } } ();
    if ( que.has_value() ) [[likely]]
        return que.value();
    else
        throw opencl_error("opencl device not found");
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

    let prog   = boost::compute::program();
 // let ext    = device().extensions();
 // let align  = std::ranges::max_element(ext, [] (const auto& a, const auto& b) { return a.size() < b.size(); })->size();
 // let pragma = ext
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

inline boost::compute::kernel opencl_queue_context::build_kernel ( const boost::compute::program& prog, std::string kernel_name )
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

inline BOOST_COMPUTE_CL_CALLBACK void opencl_queue_context::enqueue_callback ( void* args )
{
    let ptr = static_cast<task_type*>(args);
    ptr->task->__execute(ptr->task, /*tid=*/ptr->tid);
}





template < class type >
std::string opencl_type_name ( )
{
    if constexpr ( requires { boost::compute::detail::type_name_trait<type>::value(); } )
        return boost::compute::detail::type_name_trait<type>::value();
    else
        return boost::core::demangle(typeid(type).name());
}

inline std::string& detail::opencl_source_replace ( std::string& str, const std::string& from, const std::string& to )
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

