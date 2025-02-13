#define dll 1
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
    let A = array<double>(range<float>(1, 6));
    print(A);
    let B = fft(A);
    print(B);
    let C = ifft(B);
    print(C);

}