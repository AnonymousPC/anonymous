#include "generic/basic/interface.hpp"
// #include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/audio/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

void test(int t)
{
    if ( t < 10 )
        return test(t+1);
    else
        throw runtime_error("Oh no {:x}", 100);
}

int main ()
{
    test(0);
}