module;
#undef in
#include <plf_hive.h>

export module plf;
import std.compiler; // This library might be depended by std.hive.

namespace plf
{
    export using plf::hive;
}