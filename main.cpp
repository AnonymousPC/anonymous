#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

class my_vector
{
    void emplace_back(auto&&...) { /*assume we do something here*/; }
};

int main ( )
{
    auto my_vec = std::vector<int>() | std::ranges::to<my_vector>();

}