module;
#define _XOPEN_SOURCE
#define __TBB_PREVIEW_PARALLEL_PHASE true
#undef in
#undef self
#include <time.h>
#include <tbb/tbb.h>
#include <git/tbb/src/tbb/parallel_pipeline.cpp> // Include first
#include <git/tbb/src/tbb/address_waiter.cpp>
#include <git/tbb/src/tbb/allocator.cpp>
#include <git/tbb/src/tbb/arena_slot.cpp>
#include <git/tbb/src/tbb/arena.cpp>
#include <git/tbb/src/tbb/concurrent_bounded_queue.cpp>
#include <git/tbb/src/tbb/dynamic_link.cpp>
#include <git/tbb/src/tbb/exception.cpp>
#include <git/tbb/src/tbb/global_control.cpp>
#define system_topology __system_topology__
#include <git/tbb/src/tbb/governor.cpp>
#undef system_topology
#undef LIBRARY_PREFIX
#undef LIBRARY_EXTENSION
#include <git/tbb/src/tbb/itt_notify.cpp>
#include <git/tbb/src/tbb/main.cpp>
#include <git/tbb/src/tbb/market.cpp>
#include <git/tbb/src/tbb/misc_ex.cpp>
#include <git/tbb/src/tbb/observer_proxy.cpp>
#include <git/tbb/src/tbb/private_server.cpp>
#include <git/tbb/src/tbb/profiling.cpp>
#include <git/tbb/src/tbb/queuing_rw_mutex.cpp>
#include <git/tbb/src/tbb/rml_tbb.cpp>
#include <git/tbb/src/tbb/rtm_mutex.cpp>
#include <git/tbb/src/tbb/rtm_rw_mutex.cpp>
#include <git/tbb/src/tbb/semaphore.cpp>
#include <git/tbb/src/tbb/small_object_pool.cpp>
#include <git/tbb/src/tbb/task_dispatcher.cpp>
#include <git/tbb/src/tbb/task_group_context.cpp>
#include <git/tbb/src/tbb/task.cpp>
#include <git/tbb/src/tbb/tcm_adaptor.cpp>
#include <git/tbb/src/tbb/thread_dispatcher.cpp>
#include <git/tbb/src/tbb/thread_request_serializer.cpp>
#include <git/tbb/src/tbb/threading_control.cpp>
#include <git/tbb/src/tbb/version.cpp>
#include <git/tbb/src/tbbbind/tbb_bind.cpp>
#include <git/tbb/src/tbbmalloc_proxy/function_replacement.cpp>
#include <git/tbb/src/tbbmalloc_proxy/proxy.cpp>
#include <git/tbb/src/tbbmalloc/backend.cpp>
#include <git/tbb/src/tbbmalloc/backref.cpp>
#include <git/tbb/src/tbbmalloc/frontend.cpp>
#include <git/tbb/src/tbbmalloc/large_objects.cpp>
#include <git/tbb/src/tbbmalloc/tbbmalloc.cpp>
#include <git/tbb/src/tbb/misc.cpp> // Include last

export module tbb;
import std.compiler; // This library might be depended by stdexec, which might be depended by std.sender.

export namespace tbb
{
    using tbb::concurrent_map;
    using tbb::concurrent_set;
    using tbb::concurrent_unordered_map;
    using tbb::concurrent_unordered_set;
}
