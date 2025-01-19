#include "generic/basic/interface.hpp"
// #include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/audio/interface.hpp"
#include "specific/container/interface.hpp"
// #include "specific/neural/interface.hpp"*
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
#include <boost/compute/container/basic_string.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/system.hpp>
using namespace ap;

int main ( )
{
    let execution_context = std::execution::static_thread_pool(10);

    let task = std::execution::schedule(execution_context.get_scheduler())
             | std::execution::bulk(200, [] (int i)
                 {
                     let str = basic_string<char,opencl>(10000, 'a');
                     str = str[1,5000];
                     str = str[1,2500];
                     let str2 = basic_string<char,cpu>(str);
                     print(std::this_thread::get_id(), str2.size());
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