#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;
let engine = std::mt19937();
int n = 100;

int main ( )
{
    let A = array<float,2,cpu>(n, n);
    for ( cpu::template reference<float> val in A.flatten() )
        val = engine();

    let t = std::chrono::system_clock::now();
    A = A * A;
    print(std::chrono::system_clock::now() - t);

}