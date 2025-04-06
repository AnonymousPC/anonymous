#pragma once

template < class exception_type >
class exception_interface
{
    public: // Interface
        exception_type& from ( const std::exception& );
};

class exception
    extends public std::exception,
            public exception_interface<exception>
{
    private: // Typedef
        template < class... types > class format_string;

    public: // Core
        exception ( ) = default;

    public: // Constructor
        template < class... types > exception ( format_string<type_identity<types>...>, types&&... );

    public: // Member
        virtual const char*            what       ( ) const noexcept;
        virtual       std::string&     message    ( );
        virtual const std::string&     message    ( ) const;
        virtual       std::stacktrace& stacktrace ( );
        virtual const std::stacktrace& stacktrace ( ) const;

    protected: // Data
        mutable std::string     error_what       = "";
                std::string     error_message    = "";
                std::stacktrace error_stacktrace = std::stacktrace::current();
        const   std::type_info* from_type        = nullptr;
                std::string     from_what        = "";
};

class logic_error
    extends public exception,
            public exception_interface<logic_error>
{
    public:
        using exception::exception;
        using exception_interface<logic_error>::from;
        friend exception_interface<logic_error>;
};

class value_error
    extends public logic_error,
            public exception_interface<value_error>
{
    public:
        using logic_error::logic_error;
        using exception_interface<value_error>::from;
        friend exception_interface<value_error>;
};

class index_error
    extends public value_error,
            public exception_interface<index_error>
{
    public:
        using value_error::value_error;
        using exception_interface<index_error>::from;
        friend exception_interface<index_error>;
};

class key_error
    extends public value_error,
            public exception_interface<key_error>
{
    public:
        using value_error::value_error;
        using exception_interface<key_error>::from;
        friend exception_interface<key_error>;
};

class type_error
    extends public logic_error,
            public exception_interface<type_error>
{
    public:
        using logic_error::logic_error;
        using exception_interface<type_error>::from;
        friend exception_interface<type_error>;
};

class runtime_error
    extends public exception,
            public exception_interface<runtime_error>
{
    public:
        using exception::exception;
        using exception_interface<runtime_error>::from;
        friend exception_interface<runtime_error>;
        runtime_error ( ) = delete; // A runtime error must carry message.
};

class string_error
    extends public runtime_error,
            public exception_interface<string_error>
{
    public:
        using runtime_error::runtime_error;
        using exception_interface<string_error>::from;
        friend exception_interface<string_error>;
};

class encode_error
    extends public string_error,
            public exception_interface<encode_error>
{
    public:
        using string_error::string_error;
        using exception_interface<encode_error>::from;
        friend exception_interface<encode_error>;
};

class format_error
    extends public string_error,
            public exception_interface<format_error>
{
    public:
        using string_error::string_error;
        using exception_interface<format_error>::from;
        friend exception_interface<format_error>;
};

class parse_error
    extends public string_error,
            public exception_interface<parse_error>
{
    public:
        using string_error::string_error;
        using exception_interface<parse_error>::from;
        friend exception_interface<parse_error>;
};

class regex_error
    extends public string_error,
            public exception_interface<regex_error>
{
    public:
        using string_error::string_error;
        using exception_interface<regex_error>::from;
        friend exception_interface<regex_error>;
};

class io_error
    extends public runtime_error,
            public exception_interface<io_error>
{
    public:
        using runtime_error::runtime_error;
        using exception_interface<io_error>::from;
        friend exception_interface<io_error>;
};

class file_error
    extends public io_error,
            public exception_interface<file_error>
{
    public:
        using io_error::io_error;
        using exception_interface<file_error>::from;
        friend exception_interface<file_error>;
};

class pipe_error
    extends public io_error,
            public exception_interface<pipe_error>
{
    public:
        using io_error::io_error;
        using exception_interface<pipe_error>::from;
        friend exception_interface<pipe_error>;
};

class serial_port_error
    extends public io_error,
            public exception_interface<serial_port_error>
{
    public:
        using io_error::io_error;
        using exception_interface<serial_port_error>::from;
        friend exception_interface<serial_port_error>;
};

class network_error
    extends public io_error,
            public exception_interface<network_error>
{
    public:
        using io_error::io_error;
        using exception_interface<network_error>::from;
        friend exception_interface<network_error>;
};

class device_error
    extends public runtime_error,
            public exception_interface<device_error>
{
    public:
        using runtime_error::runtime_error;
        using exception_interface<device_error>::from;
        friend exception_interface<device_error>;
};

class cuda_error
    extends public device_error,
            public exception_interface<cuda_error>
{
    public:
        using device_error::device_error;
        using exception_interface<cuda_error>::from;
        friend exception_interface<cuda_error>;
};

class opencl_error
    extends public device_error,
            public exception_interface<opencl_error>
{
    public:
        using device_error::device_error;
        using exception_interface<opencl_error>::from;
        friend exception_interface<opencl_error>;
};

class tbb_error
    extends public device_error,
            public exception_interface<tbb_error>
{
    public:
        using device_error::device_error;
        using exception_interface<tbb_error>::from;
        friend exception_interface<tbb_error>;
};

class math_error
    extends public runtime_error,
            public exception_interface<math_error>
{
    public:
        using runtime_error::runtime_error;
        using exception_interface<math_error>::from;
        friend exception_interface<math_error>;
};

class linalg_error
    extends public math_error,
            public exception_interface<linalg_error>
{
    public:
        using math_error::math_error;
        using exception_interface<linalg_error>::from;
        friend exception_interface<linalg_error>;
};

class signal
    extends public exception
{
    using exception::exception;
};

class abort_signal
    extends public signal
{
    using signal::signal;  
};

class floating_point_exception_signal
    extends public signal
{
    using signal::signal;
};

class illegal_instruction_signal
    extends public signal
{
    using signal::signal;
};

class interrupt_signal
    extends public signal
{
    using signal::signal;
};

class segmentation_violation_signal
    extends public signal
{
    using signal::signal;
};

class terminate_signal
    extends public signal
{
    using signal::signal;
};



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

    inline    std::string    format_stacktrace       ( const std::stacktrace& );
    inline    std::string    format_nested_exception ( const std::type_info&, const std::string& );
    inline    std::string    format_stacktrace_color ( std::string, int = 0, int = 0 );
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

inline const char* exception::what ( ) const noexcept
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

inline std::string& exception::message ( )
{
    return error_message;
}

inline const std::string& exception::message ( ) const
{
    return error_message;
}

inline std::stacktrace& exception::stacktrace ( )
{
    return error_stacktrace;
}

inline const std::stacktrace& exception::stacktrace ( ) const
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






inline std::string detail::format_stacktrace ( const std::stacktrace& trace )
{
    return trace | std::views::reverse
                 | std::views::transform([&] (const auto& entry)
                     {
                         if ( entry.source_file() != "" and entry.source_line() != 0 )
                             return std::format("    {}{} {}{} {}{} {}{}:{}{}",
                                                yellow, "at", white, format_stacktrace_color(entry.description()),
                                                green,  "in", grey,  entry.source_file(), entry.source_line(),
                                                white);
                         else
                             return std::format("    {}{} {}{}{}",
                                                yellow, "at", white, format_stacktrace_color(entry.description()),
                                                white);
                     })
                 | std::views::join_with('\n')
                 | std::ranges::to<std::string>();
}

inline std::string detail::format_nested_exception ( const std::type_info& from_type, const std::string& from_what )
{
    #if defined(__GNUC__) but not defined(__clang__) // terminate called after throwing an instance of '{typeid}'\n  what():  {what}
        return std::format("after throwing another instance of '{}'\n  what(): {}", boost::core::demangle(from_type.name()), from_what);
    #elifdef __clang__ // libc++abi: terminating due to uncaught exception of type {typeid}: {what}
        return std::format("due to another exception of type {}: {}", boost::core::demangle(from_type.name()), from_what);
    #else
        return std::format("catch {}: {}", boost::core::demangle(from_type.name()), from_what);
    #endif
}

inline std::string detail::format_stacktrace_color ( std::string str, int str_pos, int colors_pos )
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

constexpr int detail::get_format_mode ( const char* str )
{
    let b = str;
    let e = str;
    while ( *e != '\0' )
        e++;

    while ( true )
    {
        let p = std::find(b, e, '{');

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
    if constexpr ( std::formattable<decay<decltype(f)>,char> )
        return f;
    else if constexpr ( printable<decltype(f)> )
        return (std::stringstream()<<f).str();
    else if constexpr ( same_as<decltype(f),const std::type_info&> )
        return boost::core::demangle(f.name());
    else
        return std::format("[[{} object at {}]]", boost::core::demangle(typeid(f).name()), static_cast<const void*>(&f));
} 

