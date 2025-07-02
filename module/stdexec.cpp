module;
#undef in
#undef self
#define __cpp_lib_execution false
#include <stdexec/concepts.hpp>
#include <stdexec/coroutine.hpp>
#include <stdexec/execution.hpp>
#include <stdexec/functional.hpp>
#include <stdexec/stop_token.hpp>

export module stdexec;
import std.compiler; // This library might be depended by std.sender.

namespace stdexec
{
    export using stdexec::schedule;
}