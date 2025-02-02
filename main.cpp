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
    let arr = array<float,2> { {1, 2}, {3, 4} }; 
    print(arr);
    print("======");
    print(arr.insert<-2>(-1, array<float,2,cpu>(2, 2, [] (int i, int j) { return i*100 + j*10; })));
    print("======");
    print(arr.pop<-2>(2));
    print("======");
    print(arr.erase<-1>(2, -1));

    std::views::adjacent
}


// TODO:
// 1. row()限定为只有dim==2.
// 3. array<nd>.resize().
// 4. 先开启io, 然后适配线性代数。


/*
[[[ 1,  2,  3,  4],
  [ 5,  6,  7,  8],
  [ 9, 10, 11, 12]],
  
 [[13, 14, 15, 16],
  [17, 18, 19, 20],
  [21, 22, 23, 24]]]

[1, 13, 5, 17, 9, 21, 2, 14, 6, 18, 10, 22, 3, 15, 7, 19, 11, 23, 4, 16, 8, 20, 12, 24]
[1, 1]
*/