module;
#ifdef __clang__
    #pragma clang diagnostic ignored "-Wreserved-module-identifier"
#endif

export module std.feature.sender;
import std.compiler;
export import stdexec;

export namespace std
{
    namespace execution
    {
        using namespace ::stdexec;
    }
}
