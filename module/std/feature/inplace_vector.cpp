export module std.feature.inplace_vector;
import std.compiler;

export namespace std
{
    template < class type, size_t len >
    class inplace_vector
        extends public vector<type>
    {

    };
}
