#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;
int main ( )
{
    array<float,2,cpu> arr;
    arr.resize(10, 10);
    for ( int i in range(arr.size()) )
        arr.flatten()[i] = i;
    array<int,2,cpu> arr2 = arr;
    print(arr + arr2);

    // Eigen::TensorSlicingOp

   // Eigen::TensorBase::slice
}
// TODO
// 1. array里声明using vector = array<self> 因为file_scv extents matrix<string> extends cpu::vector extents ... 