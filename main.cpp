#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

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