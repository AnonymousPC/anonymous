import anonymous;
import std;

int main ( )
{
    auto m = std::vector<int>(10) 
           | std::views::transform([] (const auto& val) { return std::pair(val, val); })
           | std::views::elements<3>
           | std::ranges::to<std::map<int,std::string>>();

    auto n = std::map<int,std::string>();
    n = n + n;
}