#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
using namespace ap;

int main ( )
{
    let str = string("hello, world");
    let com = str | views::encode_gzip | std::ranges::to<string>();
    print(com);
}