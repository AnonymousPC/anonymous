#include <ranges>
#include <vector>
#include <map>

int main()
{
    std::vector<int> a;
    auto b = a
           | std::views::reverse
           | std::ranges::to<std::map<int,int>>();
}