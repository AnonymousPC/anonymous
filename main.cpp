#include "generic/basic/interface.hpp"
// #include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/audio/interface.hpp"
#include "specific/container/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

int main ( )
{
    set<int,opencl::template less<int>,opencl> s;
    for ( int i in range(100) )
        s.push(i);

    for ( int i in s )
        print(i);
}


// TODO:
// 1. map的keys_view不要自引用,用private继承然后小转大。
// 2. 重写opencl::[[container_base]], 可以不考虑map
// 3. array<nd>.resize().
// 4. 先开启io, 然后适配线性代数。