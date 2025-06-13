module;
#define _XOPEN_SOURCE
#define __TBB_PREVIEW_PARALLEL_PHASE true
#undef in
#undef self
#include <time.h>
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
#define system_topology system_topology_2
#include <tbb/src/tbb/governor.cpp>
#undef system_topology
#undef LIBRARY_PREFIX
#undef LIBRARY_EXTENSION
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
#include <tbb/src/tbb/tcm_adaptor.cpp>
#include <tbb/src/tbb/thread_dispatcher.cpp>
#include <tbb/src/tbb/thread_request_serializer.cpp>
#include <tbb/src/tbb/threading_control.cpp>
#include <tbb/src/tbb/version.cpp>
// #include <tbb/src/tbbbind/tbb_bind.cpp> fixme
#include <tbb/src/tbbmalloc_proxy/function_replacement.cpp>
#include <tbb/src/tbbmalloc_proxy/proxy.cpp>
#define notify_type notify_type_2
#define prepare prepare_2
#define cancel cancel_2
#define acquired acquired_2
#define releasing releasing_2
#define call_itt_notify call_itt_notify_2
#include <tbb/src/tbbmalloc/backend.cpp>
#include <tbb/src/tbbmalloc/backref.cpp>
#include <tbb/src/tbbmalloc/frontend.cpp>
// #include <tbb/src/tbbmalloc/large_objects.cpp> fixme
#include <tbb/src/tbbmalloc/tbbmalloc.cpp>
#include <tbb/src/tbb/misc.cpp> // Include last

export module tbb;
import std;
import hwloc;

namespace tbb
{
    export using tbb::concurrent_map;
    export using tbb::concurrent_set;
    export using tbb::concurrent_unordered_map;
    export using tbb::concurrent_unordered_set;
}
