module;
#undef in
#undef self
#include <tbb/tbb.h>

export module tbb;
import std.compiler; // This library might be depended by std.sender.
import hwloc;

namespace tbb
{
    export using tbb::concurrent_map;
    export using tbb::concurrent_set;
    export using tbb::concurrent_unordered_map;
    export using tbb::concurrent_unordered_set;
}
