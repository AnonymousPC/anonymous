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
    
    enum { implicit_mode, explicit_mode, default_mode };

              std::string    format_stacktrace        ( const std::stacktrace& );
              std::string    format_nested_exception  ( const std::type_info&, const std::string& );
              std::string    format_stacktrace_color  ( std::string, int = 0, int = 0 );
              std::string    format_stacktrace_module ( std::string );
    constexpr int            get_format_mode         ( const char* );
    constexpr decltype(auto) make_formattable        ( auto&& );
}






template < class exception_type >
exception_type& exception_interface<exception_type>::from ( const std::exception& e )
{
    static_cast<exception_type&>(self).from_type = &typeid(e);
    static_cast<exception_type&>(self).from_what = e.what();
    return static_cast<exception_type&>(self);
}

template < class... types >
exception::exception ( format_string<type_identity<types>...> str, types&&... args )
    extends error_message ( str.format(std::forward<decltype(args)>(args)...) )
{
    
}

const char* exception::what ( ) const noexcept
{
    if ( from_type == nullptr )
        error_what = detail::red   + error_message + '\n' +
                     detail::white + detail::format_stacktrace(error_stacktrace);

    else
        error_what = detail::red   + error_message + '\n' + 
                     detail::white + detail::format_stacktrace(error_stacktrace) + '\n' + 
                     '\n' +
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

template < class... types >
class exception::format_string
{
    private: // Data
        const char* str = nullptr;

    public: // Core
        consteval format_string ( const char* );
        constexpr std::string format ( types&&... ) const;
};

template < class... types >
consteval exception::format_string<types...>::format_string ( const char* init_str )
    extends str ( init_str )
{
    if ( detail::get_format_mode(str) == detail::explicit_mode )
        /*check-only*/ (void) std::format_string<const char*,conditional<std::formattable<types,char>,types,std::string>...>(std::string("{0}") + str);
    else
        /*check-only*/ (void) std::format_string<const char*,conditional<std::formattable<types,char>,types,std::string>...>(std::string("{}" ) + str);
}

template < class... types >
constexpr std::string exception::format_string<types...>::format ( types&&... args ) const
{
    switch ( detail::get_format_mode(str) )
    {
        case detail::explicit_mode:
            return std::format(std::runtime_format(std::string("{0}") + str), "", detail::make_formattable(args)...);
        case detail::implicit_mode:
            return std::format(std::runtime_format(                     str),     detail::make_formattable(args)...);
        case detail::default_mode:
            return str;
        default:
            return str;
    }
}






std::string detail::format_stacktrace ( const std::stacktrace& trace )
{
    return trace | std::views::reverse
                 | std::views::transform([&] (const auto& entry)
                     {
                         if ( entry.source_file() != "" and entry.source_line() != 0 )
                             return std::format("    {}{} {}{} {}{} {}{}:{}{}",
                                                yellow, "at", white, format_stacktrace_color(format_stacktrace_module(entry.description())),
                                                green,  "in", grey,  entry.source_file(), entry.source_line(),
                                                white);
                         else
                             return std::format("    {}{} {}{}{}",
                                                yellow, "at", white, format_stacktrace_color(format_stacktrace_module(entry.description())),
                                                white);
                     })
                 | std::views::join_with('\n')
                 | std::ranges::to<std::string>();
}

std::string detail::format_nested_exception ( const std::type_info& from_type, const std::string& from_what )
{
    #if defined(__GNUC__) and not defined(__clang__) // terminate called after throwing an instance of '{typeid}'\n  what():  {what}
        return std::format("after throwing an instance of '{}'\n  what(): {}", boost::core::demangle(from_type.name()), from_what);
    #elifdef __clang__ // libc++abi: terminating due to uncaught exception of type {typeid}: {what}
        return std::format("due to uncaught exception of type {}: {}", boost::core::demangle(from_type.name()), from_what);
    #else
        return std::format("catch {}: {}", boost::core::demangle(from_type.name()), from_what);
    #endif
}

std::string detail::format_stacktrace_color ( std::string str, int str_pos, int colors_pos )
{
    constexpr std::array<const char*,4> colors = { white, light_grey, grey, dark_grey };

    // Locate brackets
    auto p1 = str.find('<', str_pos);
    auto p2 = str.find('>', str_pos);

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

std::string detail::format_stacktrace_module ( std::string str )
{
    return std::regex_replace(str, std::regex(R"(@[\w\.]+)"), "");
}

constexpr int detail::get_format_mode ( const char* str )
{
    auto b = str;
    auto e = str;
    while ( *e != '\0' )
        e++;

    while ( true )
    {
        auto p = std::find(b, e, '{');

        if ( p == e )
            return default_mode;
        else if ( *(p+1) >= '0' and *(p+1) <= '9' )
            return explicit_mode;
        else if ( p+1 < e and *(p+1) != '{' )
            return implicit_mode;
        else
            { b = p + 2; continue; }
    }
}

constexpr decltype(auto) detail::make_formattable ( auto&& f )
{
    if constexpr ( formattable<remove_cvref<decltype(f)>> )
        return f;
    else
        return std::format("[[{} object at {}]]", boost::core::demangle(typeid(f).name()), static_cast<const void*>(&f));
} 



