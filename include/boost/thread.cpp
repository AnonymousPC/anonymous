module;
#include <boost/thread.hpp>
#include <git/boost/libs/thread/src/future.cpp>
#include <git/boost/libs/thread/src/pthread/once_atomic.cpp>
#include <git/boost/libs/thread/src/pthread/once.cpp>
#include <git/boost/libs/thread/src/pthread/thread.cpp>
#include <git/boost/libs/thread/src/tss_null.cpp>
#include <git/boost/libs/thread/src/win32/thread_primitives.cpp>
#include <git/boost/libs/thread/src/win32/thread.cpp>
#include <git/boost/libs/thread/src/win32/tss_dll.cpp>
#include <git/boost/libs/thread/src/win32/tss_pe.cpp>

export module boost.thread;
export namespace boost::thread
{
    
}
