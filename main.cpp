#include "generic/basic/interface.hpp"
// #include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/audio/interface.hpp"
#include "specific/container/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
#include <boost/compute/iterator/buffer_iterator.hpp>
using namespace ap;

int main ( )
{
    let task = std::execution::just()
             | std::execution::bulk(10, [] (int i)
                 {
                     let str = basic_string<char,cpu>(1000, 'a');
                     let str2 = str[1,500];
                     let str3 = str2 * 1;
                     let str4 = str2[1,10];
                     let str5 = string(str4);
                     print(str5);
                 });
        
    std::execution::sync_wait(task);

};


/*

(2, 3, 4)

[[[ 1,  2,  3,  4],
  [ 5,  6,  7,  8],
  [ 9, 10, 11, 12]],

 [[13, 14, 15, 16],
  [17, 18, 19, 20],
  [21, 22, 23, 24]]]

[  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 ]
[  1, 13,  5, 17,  9, 21,  2, 14,  6, 18, 10, 22,  3, 15,  7, 19, 11, 23,  4, 16,  8, 20, 12, 24 ]


*/