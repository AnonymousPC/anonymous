#pragma once

class logic_error
    extends public exception
{
    using exception::exception;
};

class value_error
    extends public logic_error
{
    using logic_error::logic_error;
};

class index_error
    extends public logic_error
{
    public:
        using logic_error::logic_error;
};

class key_error
    extends public logic_error
{
    public:
        using logic_error::logic_error;
};

class nullptr_error
    extends public logic_error
{
    public:
        using logic_error::logic_error;
};

class runtime_error
    extends public exception
{
    using exception::exception;
    runtime_error ( ) = delete; // A runtime error must carry message.
};

class type_error
    extends public runtime_error
{
    public:
        using runtime_error::runtime_error;
};

class encode_error
    extends public runtime_error
{
    public:
        using runtime_error::runtime_error;
};

class format_error
    extends public runtime_error
{
    public:
        using runtime_error::runtime_error;
};

class parse_error
    extends public runtime_error
{
    public:
        using runtime_error::runtime_error;
};

class regex_error
    extends public runtime_error
{
    public:
        using runtime_error::runtime_error;
};

class file_error
    extends public runtime_error
{
    using runtime_error::runtime_error;
};

class network_error
    extends public runtime_error
{
    using runtime_error::runtime_error;
};

class pipe_error
    extends public runtime_error
{
    using runtime_error::runtime_error;
};

class device_error
    extends public runtime_error
{
    using runtime_error::runtime_error;
};

class math_error
    extends public runtime_error
{
    using runtime_error::runtime_error;
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

template < class... types >
exception::exception ( format_string<type_identity<types>...> str, types&&... args )
    extends error_message ( str.format(std::forward<decltype(args)>(args)...) )
{

}   

template < class... types >
class exception::format_string
{
    private: // Mode
        enum class mode { implicit_mode, explicit_mode, default_mode };

    private: // Data
        const char* str = nullptr;

    public: // Core
        consteval format_string ( const char* );

    public: // Member
        constexpr std::string format ( types&&... ) const;
        constexpr mode        parse  ( )            const;

    private: // Detail
        constexpr static decltype(auto) make_const_ref   ( const auto& );
        constexpr static decltype(auto) make_formattable ( const auto& );
        constexpr static decltype(auto) make_format_args ( const auto&... );
};

template < class... types >
consteval exception::format_string<types...>::format_string ( const char* init_str )
    extends str ( init_str )
{
    if ( parse() == mode::explicit_mode )
        /*check-only*/ (void) std::format_string<const char*,conditional<std::formattable<types,char>,types,std::string>...>(std::string("{0}") + str);
    else
        /*check-only*/ (void) std::format_string<const char*,conditional<std::formattable<types,char>,types,std::string>...>(std::string("{}" ) + str);
}

template < class... types >
constexpr std::string exception::format_string<types...>::format ( types&&... args ) const
{
    switch ( parse() )
    {
        case mode::implicit_mode:
            return std::vformat(str, make_format_args(args...));
        case mode::explicit_mode:
            return std::vformat(std::string("{0}") + str, make_format_args("", args...));
        case mode::default_mode:
            return str;
        default:
            return str;
    }
}

template < class... types >
constexpr exception::format_string<types...>::mode exception::format_string<types...>::parse ( ) const
{
    let b = str;
    let e = str;
    while ( *e != '\0' )
        e++;

    while ( true )
    {
        let p = std::find(b, e, '{');

        if ( p == e )
            return mode::default_mode;
        else if ( *(p+1) >= '0' and *(p+1) <= '9' )
            return mode::explicit_mode;
        else if ( p+1 < e and *(p+1) != '{' )
            return mode::implicit_mode;
        else
            { b = p + 2; continue; }
    }
}

template < class... types >
constexpr decltype(auto) exception::format_string<types...>::make_const_ref ( const auto& args )
{
    return args;
}

template < class... types >
constexpr decltype(auto) exception::format_string<types...>::make_formattable ( const auto& args )
{
    if constexpr ( std::formattable<decay<decltype(args)>,char> ) // std::formattable
        return args;
    else if constexpr ( printable<decltype(args)> )
        return (std::stringstream()<<args).str();
    else if constexpr ( same_as<decltype(args),const std::type_info&> )
        return demangle(args);
    else
        return std::format("[[{} object at {}]]", demangle(typeid(args)), static_cast<const void*>(&args));
} 

template < class... types >
constexpr decltype(auto) exception::format_string<types...>::make_format_args ( const auto&... args )
{
    return std::make_format_args(make_const_ref(make_formattable(args))...);
}