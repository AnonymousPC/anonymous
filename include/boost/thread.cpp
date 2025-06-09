module;
#undef in
#undef self
#include <boost/thread.hpp>
#include <boost/thread/future.cpp>
#include <boost/thread/tss_null.cpp>
#ifdef _WIN32
    #include <boost/thread/win32/thread_primitives.cpp>
    #include <boost/thread/win32/thread.cpp>
    #include <boost/thread/win32/tss_dll.cpp>
    #include <boost/thread/win32/tss_pe.cpp>
#elif defined(__linux__) or defined(__MACH__)
    #include <boost/thread/pthread/once_atomic.cpp>
    #include <boost/thread/pthread/once.cpp>
    #include <boost/thread/pthread/thread.cpp>
#endif

export module boost.thread;
import std;
export namespace boost
{

}
