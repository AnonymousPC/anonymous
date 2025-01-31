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

class network_error
    extends public io_error,
            public exception_interface<network_error>
{
    public:
        using io_error::io_error;
        using exception_interface<network_error>::from;
        friend exception_interface<network_error>;
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

class sql_error
    extends public io_error,
            public exception_interface<sql_error>
{
    public:
        using io_error::io_error;
        using exception_interface<sql_error>::from;
        friend exception_interface<sql_error>;
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
    return std::.make_format_args(make_const_ref(make_formattable(args))...);
}