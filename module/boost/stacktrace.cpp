module;
#undef in
#undef self
#ifdef __GNUC__
    #define _GNU_SOURCE
#else
    #define BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED
#endif
#include <boost/stacktrace.hpp>

export module boost.stacktrace;
import std.compiler; // This library might be depended by std.stacktrace.

export namespace boost::stacktrace
{
    using boost::stacktrace::frame;
    using boost::stacktrace::stacktrace;
}