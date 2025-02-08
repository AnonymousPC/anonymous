#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

/* 每个ndarray(assume shape = [2, 3, 4])
   能分解出2个matrix, 2个T->matrix
   能分解出6个vector, 6个matrix->T->vector, 6个T->matrix->vector, 6个T->matrix->T->vector

   考察下列矩阵
   [[[1, 2, 3, 4]
     [5, 6, 7, 8]
     [9,10,11,12]],
     
     [13,14,15,16],
     [17,18,19,20],
     [21,22,23,24]]]
    
    每个matrix不仅有transpose(), 还会有对应的flatten()
    其变化无穷无尽。故：
    1. 当前view需要new时, 只有ownership()才能transpose(), flatten(), reshape().
    2. 直到可以栈变量&引用(每个ndarray唯一对应一个mdspan)。

auto& test(std::string&& val)
{
    val = "hello, world! out of bound";
    return static_cast<std::string&>(val);
}

int main ( )
{
    let str = std::string("Hello");
    auto& result = test("hello");
    print(result);
}

// ndarray<int,3> | ndarray<int,3>::transpose()
// matrix1,       | matrix1::transpose()
// matrix2,       | matrix2::transpose()
// vector11
// vector12
// vector13


// (2*3*4)
// 2*matrix,



// TODO
// 1. array里声明using vector = array<self> 因为file_scv extents matrix<string> extends cpu::vector extents ... 