class exception;
    class logic_error;
        class value_error;
            class index_error;
            class key_error;
        class type_error;

    class runtime_error;
        class text_error;
            class encode_error;
            class format_error;
            class parse_error;
            class regex_error;
        class io_error;
            class file_error;
            class pipe_error;
            class serial_port_error;
            class network_error;
            class mysql_error;
        class device_error;
            class cuda_error;
            class opencl_error;
            class tbb_error;
        class math_error;
            class linalg_error;

    class internal_error;

    class signal;
        class abort_signal;
        class floating_point_exception_signal;
        class illegal_instruction_signal;
        class interrupt_signal;
        class segmentation_violation_signal;
        class terminate_signal;




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

class text_error
    extends public runtime_error,
            public exception_interface<text_error>
{
    public:
        using runtime_error::runtime_error;
        using exception_interface<text_error>::from;
        friend exception_interface<text_error>;
};

class encode_error
    extends public text_error,
            public exception_interface<encode_error>
{
    public:
        using text_error::text_error;
        using exception_interface<encode_error>::from;
        friend exception_interface<encode_error>;
};

class format_error
    extends public text_error,
            public exception_interface<format_error>
{
    public:
        using text_error::text_error;
        using exception_interface<format_error>::from;
        friend exception_interface<format_error>;
};

class parse_error
    extends public text_error,
            public exception_interface<parse_error>
{
    public:
        using text_error::text_error;
        using exception_interface<parse_error>::from;
        friend exception_interface<parse_error>;
};

class regex_error
    extends public text_error,
            public exception_interface<regex_error>
{
    public:
        using text_error::text_error;
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

class internal_error
    extends public exception
{
    public:
        internal_error ( ) = default; // An internal error must not carry message.
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


#include "exception.cpp"