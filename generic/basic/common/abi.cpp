#pragma once

namespace detail
{
    std::string paint ( std::string, int = 0, int = 0 );
}

std::string abi::demangle ( const char* mangled_name )
{
    let ok             = 0;
    let damangled_name = ::abi::__cxa_demangle ( mangled_name, nullptr, nullptr, &ok );

    let demangled_str  = ok == 0 ? std::string(damangled_name) otherwise
                                    std::format("demangle failed {}: {}", ok, std::string(mangled_name));
    free ( damangled_name );
    return demangled_str;
} 

std::string abi::demangle ( const std::stacktrace& trace )
{
    return trace | std::views::reverse
                 | std::views::transform ([&] (const auto& e)
                     {
                         return std::format("    {}{} {}{} {}{} {}{}:{}{}",
                                            yellow, "at", white,  detail::paint(e.description()),
                                            green,  "in", grey,   e.source_file(), e.source_line(),
                                            white);
                     })
                 | std::views::join_with('\n')
                 | std::ranges::to<std::string>();
}

std::string abi::demangle ( const std::vector<std::stacktrace_entry>& trace )
{
    return trace | std::views::reverse
                 | std::views::transform ([&] (const auto& e)
                     {
                         return std::format("    {}{} {}{} {}{} {}{}:{}{}",
                                            yellow, "at", white,  detail::paint(e.description()),
                                            green,  "in", grey,   e.source_file(), e.source_line(),
                                            white);
                     })
                 | std::views::join_with('\n')
                 | std::ranges::to<std::string>();
}

std::string detail::paint ( std::string str, int str_pos, int colors_pos )
{
    constexpr std::array<const char*,4> colors = { abi::white, abi::light_grey, abi::grey, abi::dark_grey };

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
    return paint ( std::move(str), str_pos, colors_pos );
}

















