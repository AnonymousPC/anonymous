#pragma once

namespace detail
{    
    constexpr const char* red        = "\033[38;2;240;0;0m";
    constexpr const char* yellow     = "\033[38;2;240;240;0m";
    constexpr const char* green      = "\033[38;2;0;240;0m";
    constexpr const char* blue       = "\033[38;2;0;120;240m";
    constexpr const char* white      = "\033[38;2;192;192;192m";
    constexpr const char* light_grey = "\033[38;2;144;144;144m";
    constexpr const char* grey       = "\033[38;2;96;96;96m";
    constexpr const char* dark_grey  = "\033[38;2;48;48;48m";

    std::string format_stacktrace       ( const std::stacktrace& );
    std::string format_nested_exception ( const std::type_info&, const std::string& );
    std::string format_stacktrace_color ( std::string, int = 0, int = 0 );
}

exception& exception::from ( const std::exception& e )
{
    from_type = &typeid(e);
    from_what = e.what();
    return self;

}

const char* exception::what ( ) const noexcept
{
    if ( from_type == nullptr )
        error_what = detail::red   + error_message + '\n' +
                     detail::white + detail::format_stacktrace(error_stacktrace);

    else
        error_what = detail::red   + error_message + '\n' + 
                     detail::white + detail::format_stacktrace(error_stacktrace) + '\n' + 
                     detail::white + detail::format_nested_exception(*from_type, from_what);
        
    return error_what.c_str();
}

std::string& exception::message ( )
{
    return error_message;
}

const std::string& exception::message ( ) const
{
    return error_message;
}

std::stacktrace& exception::stacktrace ( )
{
    return error_stacktrace;
}

const std::stacktrace& exception::stacktrace ( ) const
{
    return error_stacktrace;
}

std::string detail::format_stacktrace ( const std::stacktrace& trace )
{
    return trace | std::views::drop_while([&] (const auto& entry)
                     {
                         return entry.description().contains("ap::exception");
                     })
                 | std::views::reverse
                 | std::views::transform([&] (const auto& entry)
                     {
                         return std::format("    {}{} {}{} {}{} {}{}:{}{}",
                                            yellow, "at", white, format_stacktrace_color(entry.description()),
                                            green,  "in", grey,  entry.source_file(), entry.source_line(),
                                            white);
                     })
                 | std::views::join_with('\n')
                 | std::ranges::to<std::string>();
}

std::string detail::format_nested_exception ( const std::type_info& from_type, const std::string& from_what )
{
    #if defined(__GNUC__) but not defined(__clang__) // terminate called after throwing an instance of '{typeid}'\n  what():  {what}
        return std::format("after throwing an instance of '{}'\n  what(): {}", demangle(from_type), from_what);
    #elifdef __clang__ // libc++abi: terminating due to uncaught exception of type {typeid}: {what}
        return std::format("due to exception of type {}: {}", demangle(from_type), from_what);
    #else
        return std::format("catch {}: {}", demangle(from_type), from_what);
    #endif
}

std::string detail::format_stacktrace_color ( std::string str, int str_pos, int colors_pos )
{
    constexpr std::array<const char*,4> colors = { white, light_grey, grey, dark_grey };

    // Locate brackets
    let p1 = str.find('<', str_pos);
    let p2 = str.find('>', str_pos);

    // Find end.
    if ( p1 == str.npos and p2 == str.npos )
        return str;

    // '<' is first.
    if ( p1 != str.npos and p1 < p2 )
    {
        int p = std::clamp(++colors_pos, 0, int(colors.size()-1));
        str.insert(p1, colors[p]);
        str_pos = p1 + std::string_view(colors[p]).size() + 1;
    }

    // '>' is first.
    else if ( p2 != str.npos and p2 < p1 )
    {
        int p = std::clamp(--colors_pos, 0, int(colors.size()-1));
        str.insert(p2 + 1, colors[p]);
        str_pos = p2 + 1 + std::string_view(colors[p]).size();
    }

    // Continue.
    return format_stacktrace_color ( std::move(str), str_pos, colors_pos );
}