module;
#undef in
#undef self
#include <boost/thread.hpp>
#include <boost/thread/src/future.cpp>
#include <boost/thread/src/tss_null.cpp>
#ifdef _WIN32
    #include <boost/thread/src/win32/thread_primitives.cpp>
    #include <boost/thread/src/win32/thread.cpp>
    #include <boost/thread/src/win32/tss_dll.cpp>
    #include <boost/thread/src/win32/tss_pe.cpp>
#elif defined(__linux__) or defined(__MACH__)
 // #include <boost/thread/src/pthread/once_atomic.cpp>
    #include <boost/thread/src/pthread/once.cpp>
    #include <boost/thread/src/pthread/thread.cpp>
#endif

export module boost.thread;
import std;

export namespace boost
{

}
