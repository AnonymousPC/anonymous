#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
#include "specific/audio/interface.hpp"
#include "specific/neural/interface.hpp"
#include "specific/spirit/interface.hpp"
#include "specific/stock/interface.hpp"
#include "specific/vscode/interface.hpp"
using namespace ap;

void task1 ( )
{
    print("will execute");
    sleep(100s);
    print("will not execute");
}

void task2 ( )
{
    print("task2");
    return;
}

int main ( )
{
    print(std::thread::hardware_concurrency());
    let a = std::execution::schedule(cpu_context.get_scheduler()) | std::execution::then(task1);
    let b = std::execution::schedule(cpu_context.get_scheduler()) | std::execution::then(task2);
    std::execution::start_detached(std::execution::when_any(a, b));
}
