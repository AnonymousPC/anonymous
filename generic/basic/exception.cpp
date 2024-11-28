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
    if ( std::ranges::any_of(trace, [] (const auto& e) { return not e.description().empty(); }) )
        msg = abi::red + msg + '\n' + abi::demangle(trace) + abi::white;
    else
        msg = abi::red + msg + abi::white;

    return msg.c_str();
}

