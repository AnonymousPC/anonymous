#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
#include <clblast.h>
using namespace ap;
int main ( )
{
    array<float,1,opencl> arr;
    arr.resize(6);
    for ( int i in range(6) )
        arr[i] = i;
    print(arr + arr);
}
// TODO
// 1. array里声明using vector = array<self> 因为file_scv extents matrix<string> extends cpu::vector extents ... 