module;
#ifdef __linux__
    #define _GNU_SOURCE
#elifdef __MACH__
    #define BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED
#endif
#undef in
#undef self
#include <boost/stacktrace.hpp>

export module boost.stacktrace;
import std.compiler; // This library might be depended by std.stacktrace.

export namespace boost::stacktrace
{
    using boost::stacktrace::frame;
    using boost::stacktrace::stacktrace;
}