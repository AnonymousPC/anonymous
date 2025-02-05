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
    let arr = array<float,2,opencl>(10, 10, [] (int i, int j) { return i * 0.125 + j *  0.50; });
    print(std::format("{:.6f}", arr));
}