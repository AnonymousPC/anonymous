module;
#undef in
#undef self
#include <stdexec/concepts.hpp>
#include <stdexec/coroutine.hpp>
#include <stdexec/execution.hpp>
#include <stdexec/functional.hpp>
#include <stdexec/stop_token.hpp>
#include <exec/static_thread_pool.hpp>
#include <exec/when_any.hpp>
#include <execpools/tbb/tbb_thread_pool.hpp>

export module stdexec;
import std.compiler;  // This library might be depended by std.sender.
import cuda;
import tbb;

namespace stdexec
{
    export using stdexec::receiver;
    export using stdexec::sender;
}