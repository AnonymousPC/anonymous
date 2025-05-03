#include <cassert>
#include <print>
#include <mdspan>
#include <vector>

int main ( )
{
    auto v = std::vector<int>(2 * 3 * 4);
    auto mds = std::mdspan(v.data(), std::dextents<int,3>(2, 3, 4));
    std::println("{}", "haha");
    std::println("{}", mds.mapping()(1, 2, 3));
}