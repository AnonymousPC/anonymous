module;
#ifdef __clang__
    #pragma clang diagnostic ignored "-Wreserved-module-identifier"
#endif
#include <version>

export module std.feature.aligned_accessor;
import std.compiler;
#ifndef __cpp_lib_mdspan
    import std.feature.mdspan;
#endif

export namespace std
{
    template < class type, size_t align >
    using aligned_accessor = default_accessor<type>;
}
