#include "generic/basic/interface.hpp"
// #include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/audio/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;
int main ( )
{
    let a = std::vector<std::string>{"hello", "world", "good"};
    let b = a
          | std::views::join_with('|')
          | std::views::chunk(4)
          | std::views::join_with(std::string("__"))
          | std::ranges::to<std::string>();
    print(b);
}