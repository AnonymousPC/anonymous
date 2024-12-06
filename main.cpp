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
    let stream = std::ifstream("okk.txt");

    let content = std::views::istream<char>(stream)
        | std::views::lazy_split('\n')
        | std::views::transform ([] (const auto& stream_line)
            {
                return stream_line | std::ranges::to<std::string>();
            })
        | std::ranges::to<std::vector<std::string>>();

    std::ranges::for_each(content, [] (const auto& line) { std::cout << line << '\n'; });
}