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
    array<int,1,ap::tbb> arr = range(10000);
    array<int,1,ap::tbb> b = arr;
    let it = b.end();
    it--;
    print(*it);
}

/*

[[1, 2, 3],
 [4, 5, 6]]

[1, 2, 3, 4, 5, 6]
[1, 4, 2, 5, 3, 6]


///////////////////////////

[[[ 1,  2,  3,  4],
  [ 5,  6,  7,  8],
  [ 9, 10, 11, 12]],

 [[13, 14, 15, 16],
  [17, 18, 19, 20],
  [21, 22, 23, 24]]]

[ 1, 2, 3, 4, ..., 24]
[ 1, 13,  5, 17,  9, 21,  2, 14,  6, 18, 10, 22,  3, 15,  7, 19, 11, 23,  4, 16,  8, 20, 12, 24 ]



*/




// array:
// [[row]]      = optimize
// as_flat      = optimize; 强行reinterpret_cast自己。
// as_shape     = 备份法, 列举1-3;
// as_transpose = 备份法
// as_type      = delete; 绝大部分linalg的as_type之后还要传递底层数组指针才能运算, 另外参考specific/audio/mfcc_extractor.cpp:35, 还要手动管理生命周期。


// map:
// keys, values = 备份法

// .reshape(1, 2, 3) = delete;