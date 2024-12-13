#include "generic/basic/interface.hpp"
// #include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/audio/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"

using namespace ap;

void test(int i)
{
    if( i == 0)
        throw exception("OHOH");
    else
        test(i-1);
}

int main ( )
{
    test(10);
}
