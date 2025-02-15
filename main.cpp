#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
//#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

int main ( )
{
   // http_get("https://www.bilibili.com").for_each(print);
    using type1 = map<int,double>;
    using type2 = vector<pair<int,double>>;

    static_assert(convertible_to<std::ranges::range_reference_t<type2>, std::ranges::range_value_t<type1>>);

}