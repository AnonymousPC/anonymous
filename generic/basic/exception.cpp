#pragma once

/// Class exception

// Core

exception::exception ( )
{
    #if __cpp_lib_stacktrace
    trace = std::stacktrace::current();
    #else
    trace = boost::stacktrace::stacktrace();
    #endif
}

// Member

const char* exception::what ( ) const noexcept
{
    #if __cpp_lib_stacktrace
    if ( not std::ranges::all_of(trace, [] (const auto& e) { return e.description() == ""; }) ) // Not all empty.
    #else
    if ( not std::ranges::all_of(trace, [] (const auto& e) { return e.name() == ""; }) )
    #endif
        msg = abi::red + msg + '\n' + abi::demangle(trace) + abi::white;
    else
        msg = abi::red + msg + abi::white;

    return msg.c_str();
}

