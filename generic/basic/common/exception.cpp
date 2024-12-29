#pragma once

exception::exception ( )
{
    trace = std::stacktrace::current();
}

const char* exception::what ( ) const noexcept
{
    if ( not std::ranges::all_of(trace, [] (const auto& e) { return e.description() == ""; }) ) // Not all empty.
        wt = abi::red + msg + '\n' + abi::white + abi::demangle(trace);
    else
        wt = abi::red + msg + abi::white;

    return wt.c_str();
}

std::string& exception::message ( )
{
    return msg;
}

const std::string& exception::message ( ) const
{
    return msg;
}

std::stacktrace& exception::stacktrace ( )
{
    return trace;
}

const std::stacktrace& exception::stacktrace ( ) const
{
    return trace;
}

