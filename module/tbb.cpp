module;
#undef in
#undef self
#define __TBB_BUILD true
#define _XOPEN_SOURCE
#include <tbb/tbb.h>
#include <tbb/src/tbb/parallel_pipeline.cpp> // Include first
#include <tbb/src/tbb/address_waiter.cpp>
#include <tbb/src/tbb/allocator.cpp>
#include <tbb/src/tbb/arena_slot.cpp>
#include <tbb/src/tbb/arena.cpp>
#include <tbb/src/tbb/concurrent_bounded_queue.cpp>
#include <tbb/src/tbb/dynamic_link.cpp>
#include <tbb/src/tbb/exception.cpp>
#include <tbb/src/tbb/global_control.cpp>
#include <tbb/src/tbb/governor.cpp>
#include <tbb/src/tbb/itt_notify.cpp>
#include <tbb/src/tbb/main.cpp>
#include <tbb/src/tbb/market.cpp>
#include <tbb/src/tbb/misc_ex.cpp>
#include <tbb/src/tbb/observer_proxy.cpp>
#include <tbb/src/tbb/private_server.cpp>
#include <tbb/src/tbb/profiling.cpp>
#include <tbb/src/tbb/queuing_rw_mutex.cpp>
#include <tbb/src/tbb/rml_tbb.cpp>
#include <tbb/src/tbb/rtm_mutex.cpp>
#include <tbb/src/tbb/rtm_rw_mutex.cpp>
#include <tbb/src/tbb/semaphore.cpp>
#include <tbb/src/tbb/small_object_pool.cpp>
#include <tbb/src/tbb/task_dispatcher.cpp>
#include <tbb/src/tbb/task_group_context.cpp>
#include <tbb/src/tbb/task.cpp>
#undef LIBRARY_EXTENSION // from src
#undef LIBRARY_PREFIX // from src
#include <tbb/src/tbb/tcm_adaptor.cpp>
#include <tbb/src/tbb/thread_dispatcher.cpp>
#include <tbb/src/tbb/thread_request_serializer.cpp>
#include <tbb/src/tbb/threading_control.cpp>
#include <tbb/src/tbb/version.cpp>
#include <tbb/src/tbb/misc.cpp> // Include last
// #include <tbb/src/tbbbind/tbb_bind.cpp>
// #include <tbb/src/tbbmalloc/backend.cpp>
// #include <tbb/src/tbbmalloc/backref.cpp>
// #include <tbb/src/tbbmalloc/frontend.cpp>
// #include <tbb/src/tbbmalloc/large_objects.cpp>
// #include <tbb/src/tbbmalloc/tbbmalloc.cpp>
// #include <tbb/src/tbbmalloc_proxy/function_replacement.cpp>
// #include <tbb/src/tbbmalloc_proxy/proxy.cpp>

export module tbb;
import std.compiler; // This library might be depended by std.sender.
import hwloc;

export namespace tbb
{

}