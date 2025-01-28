#include "generic/basic/interface.hpp"
// #include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/audio/interface.hpp"
// #include "specific/container/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

using reference = opencl::template reference<int>;
using reference2 = opencl::template reference<float>;

int main ( )
{
    boost::compute::vector<int> vct(10);
    reference a = vct[1];
    a = 100;

    boost::compute::vector<float> vct2(10);
    reference2 b = vct2[1];
    b = 2.2;

    print(a > b);
    print(a < b);



    
    // let arr = array<int,2,opencl>(4, 4);
    // for ( int i in range(4) )
    //     for ( int j in range(4) )
    //         arr[i][j] = (i-1)*4 + j;
    // print(array<int>(arr.as_flat()));

    // let arr1= array<int,3,opencl>(2, 3, 4);
    // for ( int i in range(2) )
    //     for ( int j in range(3) )
    //         for ( int k in range(4) )
    // print(array<int>(arr1.as_flat()));

    // let arr2 = array<int,3,cpu>(2, 3, 4);
    // for ( int i in range(2) )
    //     for ( int j in range(3) )
    //         for ( int k in range(4) )
    //             arr2[i][j][k] = (i-1)*12 + (j-1)*4 + (k-1) + 1;
    // print(arr2.as_flat());


}


// TODO:
// 1. 把array_upper的&self[0]想办法去掉。
// 2. 试试array<opencl>
// 3. map的keys_view不要自引用,用private继承然后小转大。
// 4. 

// DONTDO:
// 1. 考虑[i][j][k]性能。注意auto&遍历比mdspan快一倍。

// /*

// (2, 3, 4)

// [[[ 1,  2,  3,  4],
//   [ 5,  6,  7,  8],
//   [ 9, 10, 11, 12]],

//  [[13, 14, 15, 16],
//   [17, 18, 19, 20],
//   [21, 22, 23, 24]]]

// [  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 ]
// columns<2>: offset=1, shape=(2, 3)
//  [[ 2,  6, 10],
//   [14, 18, 22]]
// columns<1>: offset=2, shape=(2)
//  [10, 22]

  
// [  1, 13,  5, 17,  9, 21,  2, 14,  6, 18, 10, 22,  3, 15,  7, 19, 11, 23,  4, 16,  8, 20, 12, 24 ]


// */