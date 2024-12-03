#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/audio/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

void test ( int t )
{
    if ( t == 0 )
        throw exception("Oh NO {}", std::this_thread::get_id());
    else
        test(t-1);
}

int main ( )
{
    let task = std::execution::schedule(global_cpu_context.get_scheduler())
             | std::execution::then([] { test(10); });
        
    std::execution::sync_wait(task);

    
}