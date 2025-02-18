#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

int main ( )
{    
    string str = "hello,world!";

    let str1 = detail::encode_base64(str);
    let str2 = str | views::encode_base64 | std::ranges::to<string>();

    std::ranges::take_while_view

    std::ranges::
}