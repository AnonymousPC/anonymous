// #include <iostream>
// #include <ranges>
// #include <map>
// #include <vector>

// int main ( )
// {
//     auto a = std::vector<int>();
//     auto b = a
//            | std::views::transform([] (const auto& v) { return v; })
//            | std::ranges::to<std::map<int,int>>();   
// }

#define great great
#include <map>
#include <ranges>
#include <vector>


void haha ( )
{
    auto a = std::vector<int>();
    a | std::views::reverse
      | std::ranges::to<std::map<int,int>>();
    great();
    
}