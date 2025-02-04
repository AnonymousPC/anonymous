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
    print("hello");
    throw exception("{}", "oh no");
}

// TODO:
// 1. string_algo. string view should extends, protected array_algo protected string_algo and use part of it.
//  尝试把: ap::is_alnum, operator+都改为string_view接口。
// 4. 先开启io, 然后适配线性代数。
// 5. boost::compute::plus改为, 双重继承std/boost::compute, 然后两个using operator(). 试试加上plus<void>
// 6. Boost.Python