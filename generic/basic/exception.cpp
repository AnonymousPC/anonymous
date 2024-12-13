#pragma once

/// Class exception

// Core

exception::exception ( )
{
    trace = std::stacktrace::current();
}

// Member

const char* exception::what ( ) const noexcept
{
    if ( not std::ranges::all_of(trace, [] (const auto& e) { return e.description() == ""; }) ) // Not all empty.
        wt = abi::red + msg + '\n' + abi::demangle(trace) + abi::white;
    else
        wt = abi::red + msg + abi::white;

    return wt.c_str();
}

