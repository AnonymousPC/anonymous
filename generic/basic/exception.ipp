#pragma once

/// Exceptions list

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














/// Class exception

// Constructor

template < class... arg_types >
exception::exception ( format_string<std::type_identity_t<arg_types>...> str, arg_types&&... args )
{
    msg   = exception::format ( str, std::forward<decltype(args)>(args)... );
    trace = std::stacktrace::current();
}


// Auxiliary

constexpr std::string exception::format ( auto&& fmt, auto&&... args )
{
    // Tools.
    [[maybe_unused]] let make_const_ref   = [] ( const auto& item ) -> decltype(auto) { return item; };
    [[maybe_unused]] let make_formattable = [] ( const auto& item ) -> decltype(auto)
    {
        if constexpr ( std::formattable<decay<decltype(item)>,char> ) // std::formattable
            return item;
        else if constexpr ( printable<decltype(item)> )
            return (std::stringstream()<<item).str();
        else if constexpr ( std::same_as<decltype(item),const std::type_info&> )
            return abi::demangle(item.name());
        else
            return std::format("[[{} object at {}]]", abi::demangle(typeid(item).name()), static_cast<const void*>(&item));
    };

    // Format.
    using mode = decltype(fmt.parse());
    switch ( fmt.parse() )
    {
        case mode::implicit_mode:
            return std::vformat(fmt.string(), std::make_format_args(make_const_ref(make_formattable(args))...)); break;
        case mode::explicit_mode:
            return std::vformat(std::string("{0}") + fmt.string(), std::make_format_args("", make_const_ref(make_formattable(args))...)); break;
        case mode::default_mode:
            return fmt.string(); break;
        default:
            return fmt.string(); break;
    }
}










/// Class exception::format_string

template < class... arg_types >
class exception::format_string
{
    public: // Mode
        enum class mode { implicit_mode, explicit_mode, default_mode };

    private: // Data
        const char* data = nullptr;
        mode        m    = mode::default_mode;

    public: // Core
        consteval format_string ( const char* );

    public: // Access
        constexpr std::string string ( ) const;
        constexpr mode        parse  ( ) const;
};

template < class... arg_types >
consteval exception::format_string<arg_types...>::format_string ( const char* init_data )
    extends data ( init_data )
{
    // Tools.
    let make_formattable = [] ( const auto& item ) -> decltype(auto)
    {
        if constexpr ( std::formattable<decay<decltype(item)>,char> ) // std::formattable
            return item;
        else if constexpr ( printable<decltype(item)> )
            return (std::stringstream()<<item).str();
        else if constexpr ( std::same_as<decltype(item),const std::type_info&> )
            return abi::demangle(item.name());
        else
            return static_cast<const void*>(&item);
    };

    // Set mode. [[std::string is not always consteval]]
    let b = data;
    let e = data + strlen(data);

    while ( true )
    {
        let p = std::find(b, e, '{');

        if ( p == e )
            m = mode::default_mode;
        else if ( std::isdigit(*(p+1)) )
            m = mode::explicit_mode;
        else if ( p+1 < e and *(p+1) != '{' )
            m = mode::implicit_mode;
        else
            { b = p + 2; continue; }
        break;
    }

    // Check if formattable.
    using string_type = std::format_string<const char*, decltype(make_formattable(std::declval<arg_types>()))...>;
    if ( mode() == mode::explicit_mode )
        string_type(std::string("{0}") + data);
    else
        string_type(std::string("{}")  + data);
}

// Access

template < class... arg_types >
constexpr std::string exception::format_string<arg_types...>::string ( ) const
{
    return std::string(data);
}

template < class... arg_types >
constexpr exception::format_string<arg_types...>::mode exception::format_string<arg_types...>::parse ( ) const
{
    return m;
}