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
    let a = array<int>(10);
    print(a);
    print(a.inplace_shape());

    print("==============");

    let b = array<int,2>(3, 4);
    for ( int i in range(b.row()) )
        for ( int j in range(b.column()) )
            b[i][j] = i*10 + j*1;
    print(b);
    print(b.static_shape());

    print("==============");

    let c = array<int,3>(3,4,5);
    for ( int i in range(c.static_shape()[1]) )
        for ( int j in range(c.static_shape()[2]) )
            for ( int k in range(c.static_shape()[3]))
                c[i][j][k] = i*100 + j*10 + k;
    print(c);
    print(c.shape());
};


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