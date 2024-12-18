#include "generic/basic/interface.hpp"
// #include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/audio/interface.hpp"
#include "specific/container/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
#include <execution>

using namespace ap;

int main () 
{
    let vct = std::vector<int> (10000);
    print(std::ranges::all_of(vct, [] (auto val) { return val == 0; }));
    
}