export module std.compiler;

#if defined(__GNUC__) and not defined(__clang__)
    export import std.compiler.gcc;
#elifdef __clang__
    export import std.compiler.clang;
#elifdef _MSC_VER
    export import std.compiler.msvc;
#endif