namespace detail
{
    template < class type >
    std::string  opencl_type_name      ( );
    std::string& opencl_source_replace ( std::string&, const std::string&, const std::string& );

} // namespace detail

constexpr auto opencl_queue_context::forward_progress_guarantee ( )
{
    return std::execution::forward_progress_guarantee::weakly_parallel;
}

constexpr auto opencl_queue_context::available_parallelism ( )
{
    return device().compute_units();
}

boost::compute::context& opencl_queue_context::context ( )
{
    return ctx;
}

boost::compute::device& opencl_queue_context::device ( )
{
    return dvc;
}

boost::compute::command_queue& opencl_queue_context::command_queue ( )
{
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
    auto ext    = device().extensions();
    auto align  = std::ranges::max_element(ext, [] (const auto& a, const auto& b) { return a.size() < b.size(); })->size();
    auto pragma = ext
                | std::views::filter   ([ ] (const auto& opt) { return opt != ""; })
                | std::views::transform([&] (const auto& opt) { return std::format("#pragma OPENCL EXTENSION {:{}} : enable", opt, align); })
                | std::views::join_with('\n')
                | std::ranges::to<std::string>();

    try
    {
        prog = boost::compute::program::create_with_source(pragma + '\n' + source, context());
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
    try
    {
        command_queue().enqueue_native_kernel(enqueue_callback, new task_type(task, tid), sizeof(task_type), 0, 0, 0);
        command_queue().flush();
    }
    catch ( const boost::compute::opencl_error& e )
    {
        throw opencl_error("failed to enqueue task").from(e);
        }
}

void opencl_queue_context::enqueue_callback ( void* args )
{
    auto ptr = static_cast<task_type*>(args);
    ptr->task->__execute(ptr->task, /*tid=*/ptr->tid);
    delete ptr;
}









template < class type >
std::string detail::opencl_type_name ( )
{
    if constexpr ( requires { boost::compute::detail::type_name_trait<type>::value(); } )
        return boost::compute::detail::type_name_trait<type>::value();
    else
        return boost::core::demangle(typeid(type).name());
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