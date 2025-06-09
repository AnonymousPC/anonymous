module;
#define _XOPEN_SOURCE
#define __TBB_PREVIEW_PARALLEL_PHASE true
#undef in
#undef self
#include <time.h>
#include <tbb/tbb.h>
#include <tbb/parallel_pipeline.cpp> // Include first
#include <tbb/address_waiter.cpp>
#include <tbb/allocator.cpp>
#include <tbb/arena_slot.cpp>
#include <tbb/arena.cpp>
#include <tbb/concurrent_bounded_queue.cpp>
#include <tbb/dynamic_link.cpp>
#include <tbb/exception.cpp>
#include <tbb/global_control.cpp>
#define system_topology system_topology_2
#include <tbb/governor.cpp>
#undef system_topology
#undef LIBRARY_PREFIX
#undef LIBRARY_EXTENSION
#include <tbb/itt_notify.cpp>
#include <tbb/main.cpp>
#include <tbb/market.cpp>
#include <tbb/misc_ex.cpp>
#include <tbb/observer_proxy.cpp>
#include <tbb/private_server.cpp>
#include <tbb/profiling.cpp>
#include <tbb/queuing_rw_mutex.cpp>
#include <tbb/rml_tbb.cpp>
#include <tbb/rtm_mutex.cpp>
#include <tbb/rtm_rw_mutex.cpp>
#include <tbb/semaphore.cpp>
#include <tbb/small_object_pool.cpp>
#include <tbb/task_dispatcher.cpp>
#include <tbb/task_group_context.cpp>
#include <tbb/task.cpp>
#include <tbb/tcm_adaptor.cpp>
#include <tbb/thread_dispatcher.cpp>
#include <tbb/thread_request_serializer.cpp>
#include <tbb/threading_control.cpp>
#include <tbb/version.cpp>
// #include <tbbbind/tbb_bind.cpp> fixme
#include <tbbmalloc_proxy/function_replacement.cpp>
#include <tbbmalloc_proxy/proxy.cpp>
#define notify_type notify_type_2
#define prepare prepare_2
#define cancel cancel_2
#define acquired acquired_2
#define releasing releasing_2
#define call_itt_notify call_itt_notify_2
#include <tbbmalloc/backend.cpp>
#include <tbbmalloc/backref.cpp>
#include <tbbmalloc/frontend.cpp>
// #include <tbbmalloc/large_objects.cpp> fixme
#include <tbbmalloc/tbbmalloc.cpp>
#include <tbb/misc.cpp> // Include last

export module tbb;
import std.compiler; // This library might be depended by stdexec, which might be depended by std.sender.
import hwloc;

namespace tbb
{
    export using tbb::concurrent_map;
    export using tbb::concurrent_set;
    export using tbb::concurrent_unordered_map;
    export using tbb::concurrent_unordered_set;
}
