#pragma once

namespace detail
{
    std::string demangle_rethrown_exception ( const std::type_info& /*type*/, const std::string& /*what*/ );
    std::string demangle_rethrown_exception ( const std::type_info& /*type*/, const std::string& /*message*/, const std::stacktrace& /*stacktrace*/, const std::stacktrace& /*compare_stacktrace*/ );
}


const char* exception::what ( ) const noexcept
{
    if ( error_from_typeid == nullptr ) // Inpendent exception.
        error_what = abi::red   + error_message + '\n' +
                     abi::white + abi::demangle(error_stacktrace);

    else if ( error_from_message == "" ) // Exception.from(std::exception)
        error_what = abi::red   + error_message + '\n' + 
                     abi::white + abi::demangle(error_stacktrace) + '\n' + 
                     abi::white + detail::demangle_rethrown_exception(error_from_typeid, error_from_what);

    else // Exception.from(ap::exception).
        error_what = abi::red   + error_message + '\n' +
                     abi::white + abi::demangle(error_stacktrace) + '\n' + 
                     abi::white + detail::demangle_rethrown_exception(error_from_typeid, error_from_what)
        
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

