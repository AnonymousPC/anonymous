export module std.feature.aligned_accessor;
import std.compiler;

#ifndef __cpp_lib_aligned_accessor

export namespace std
{
    template < class type, size_t align >
    using aligned_accessor = default_accessor<type>;
}

#endif
