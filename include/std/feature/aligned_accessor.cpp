export module std.feature.aligned_accessor;
import std.compiler;

export namespace std
{
    template < class type, size_t align >
    using aligned_accessor = default_accessor<type>;
}
