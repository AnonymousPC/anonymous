module;
#undef in
#undef self
#include <tbb/tbb.h>

export module tbb;
import std.compiler; // This library might be depended by std.sender.
import hwloc;

