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

boost::compute::vector

int main ( )
{
    boost::compute::vector<int> a(1000000);
    boost::compute::vector<int> b(1000000);
    array<int,1,opencl>         c(1000000);
    array<int,1,opencl>         d(1000000);

    let t = std::chrono::system_clock::now();
    for ( int _ in range(100) )
    {
        a = b;
        b = a;
    }
    print(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - t).count());

    t = std::chrono::system_clock::now();
    for ( int _ in range(100) )
    {
        c = d;
        d = c;
    }
    print(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - t).count());


}


// TODO:
// 1. map的keys_view不要自引用,用private继承然后小转大。
// 2. 重写opencl::[[container_base]], 可以不考虑map
// 3. array<nd>.resize().
// 4. 先开启io, 然后适配线性代数。