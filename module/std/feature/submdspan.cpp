module;
#ifdef __clang__
    #pragma clang diagnostic ignored "-Wreserved-module-identifier"
#endif

export module std.feature.submdspan;
import std.compiler;

export namespace std
{
    template < size_t padding >
    class layout_right_padded;

    template < size_t padding >
    class layout_left_padded;
}