module;
#undef in
#if defined(__GNUC__) and not defined(__clang__)
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <plf_hive.h>

export module plf;
import std.compiler; // This library might be depended by std.hive.

export namespace plf
{
    using plf::hive;
}