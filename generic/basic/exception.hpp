#pragma once
#include "abi.hpp"
#include "concept.hpp"

/// Exceptions list

class exception;
    class logic_error;
        class value_error;
        class index_error;
        class key_error;
        class nullptr_error;

    class runtime_error;
        class type_error;
        class encode_error;
        class format_error;
        class parse_error;
        class regex_error;
        class file_error;
        class network_error;
        class pipe_error;
        class math_error;

    class signal;
        class abort_signal;
        class floating_point_exception_signal;
        class illegal_instruction_signal;
        class interrupt_signal;
        class segmentation_violation_signal;
        class terminate_signal;



/// Class exception

class exception
    extends public std::exception
{
    private: // Typedef
        template < class... arg_types > class format_string;

    private: // Data
        mutable std::string                   msg   = std::string();
        #if __cpp_lib_stacktrace
        mutable std::stacktrace               trace = std::stacktrace();
        #else
        mutable boost::stacktrace::stacktrace trace = boost::stacktrace::stacktrace();
        #endif

    public: // Core
                 exception ( );
        virtual ~exception ( ) = default;

    public: // Constructor
        template < class... arg_types >
        exception ( format_string<std::type_identity_t<arg_types>...>, arg_types&&... );

    public: // Member
        virtual const char* what ( ) const noexcept;

    private: // Auxiliary
        constexpr static std::string format ( auto&&, auto&&... );
};









#include "exception.ipp"
#if dll
    #include "exception.cpp"
#endif