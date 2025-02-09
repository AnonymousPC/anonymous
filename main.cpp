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
    array<float,2,opencl> arr;
    arr.resize(2, 2);
    for ( int i in range(4) )
        arr.flatten()[i] = i;
    print(arr * 10);
}
// TODO
// 1. array里声明using vector = array<self> 因为file_scv extents matrix<string> extends cpu::vector extents ... 