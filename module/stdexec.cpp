module;
#undef in
#undef self
#include <stdexec/concepts.hpp>
#include <stdexec/coroutine.hpp>
#include <stdexec/execution.hpp>
#include <stdexec/functional.hpp>
#include <stdexec/stop_token.hpp>

export module stdexec;
import std.compiler; // This library might be depended by std.sender.

namespace stdexec
{
    export using stdexec::receiver;
    export using stdexec::sender;
}