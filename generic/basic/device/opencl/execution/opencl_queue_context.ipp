#pragma once

namespace detail
{
    std::string& opencl_source_replace ( std::string&, const std::string&, const std::string& );

    template < class type >
    std::string opencl_type_name ( )
    {
        if constexpr ( requires { boost::compute::detail::type_name_trait<type>::value(); } )
            return boost::compute::detail::type_name_trait<type>::value();
        else
            return demangle(typeid(type));
    }
    
} // namespace detail


boost::compute::program detail::opencl_queue_context::build_program ( std::string source, const auto&... args )
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
