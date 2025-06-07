export module std.feature.execution;
import std.compiler;
export import stdexec;

#ifndef __cpp_lib_sender

export namespace std
{
    namespace execution
    {
        using namespace ::stdexec;
    }
}

#endif
