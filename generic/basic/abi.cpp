#pragma once

namespace aux
{
    std::string paint ( std::string, const std::array<const char*,4>&, int = 0, int = 0 );
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


#if __cpp_lib_stacktrace
    std::string abi::demangle ( const std::stacktrace& trace )
    {
        return trace | std::views::reverse
                        | std::views::transform ([&] (const auto& e)
                            {
                                return std::format("    {}{} {}{} {}{} {}{}:{}{}",
                                                   yellow, "at", white,  aux::paint(e.description(), grey_scale),
                                                   green,  "in", grey,   e.source_file(), e.source_line(),
                                                   white);
                            })
                        | std::views::join_with('\n')
                        | std::ranges::to<std::string>();
    }
#else
    std::string abi::demangle ( const boost::stacktrace::stacktrace& trace )
    {
        return trace | std::views::reverse
                        | std::views::transform([&] (const auto& e)
                            {
                                return std::format("    {}{} {}{} {}{} {}{}:{}{}",
                                                   yellow, "at", white,  aux::paint(e.name(), grey_scale),
                                                   green,  "in", grey,   e.source_file(), e.source_line(),
                                                   white);
                            })
                        | std::views::join_with('\n')
                        | std::ranges::to<std::string>();
    }
#endif









// Auxiliary

std::string aux::paint ( std::string str, const std::array<const char*,4>& colors, int str_pos, int colors_pos )
{

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
    return paint ( std::move(str), colors, str_pos, colors_pos );
}

















