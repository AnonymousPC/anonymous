module;
#undef in
#undef self
#include <boost/thread.hpp>
#include <git/boost/libs/thread/src/future.cpp>
#include <git/boost/libs/thread/src/tss_null.cpp>
#ifdef _WIN32
    #include <git/boost/libs/thread/src/win32/thread_primitives.cpp>
    #include <git/boost/libs/thread/src/win32/thread.cpp>
    #include <git/boost/libs/thread/src/win32/tss_dll.cpp>
    #include <git/boost/libs/thread/src/win32/tss_pe.cpp>
#elif defined(__linux__) or defined(__MACH__)
    #include <git/boost/libs/thread/src/pthread/once_atomic.cpp>
    #include <git/boost/libs/thread/src/pthread/once.cpp>
    #include <git/boost/libs/thread/src/pthread/thread.cpp>
#endif

export module boost.thread;
import std;
export namespace boost
{

}
