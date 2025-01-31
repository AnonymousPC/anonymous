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
    array<float,3,opencl> arr(2, 3, 4, [] (int i, int j, int k) { return (i-1)*12 + (j-1) * 4 + (k-1) + 1; });
    arr[1][1][1] += 100;
    print(arr);
}


// TODO:
// 3. array<nd>.resize().
// 4. 先开启io, 然后适配线性代数。
