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
        class device_error;
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
        template < class... types > class format_string;

    public: // Core
        exception ( ) = default;

    public: // Constructor
        template < class... types >
        exception ( format_string<type_identity<types>...>, types&&... );

    public: // Factory
        exception& from ( const std::exception& );

    public: // Member
        virtual const char*            what       ( ) const noexcept;
        virtual       std::string&     message    ( );
        virtual const std::string&     message    ( ) const;
        virtual       std::stacktrace& stacktrace ( );
        virtual const std::stacktrace& stacktrace ( ) const;

    private: // Data
        mutable std::string     error_what       = "";
                std::string     error_message    = "";
                std::stacktrace error_stacktrace = std::stacktrace::current();
        const   std::type_info* from_type        = nullptr;
                std::string     from_what        = "";
};









#include "exception.ipp"
//#if dll
    #include "exception.cpp"
//#endif