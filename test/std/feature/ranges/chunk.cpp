import std;

int main ( )
{
    auto str = std::string("abc123def");
    auto chunked = str
                 | std::views::chunk(3)
                 | std::views::transform([] (const auto& segment)
                     {
                         return segment | std::ranges::to<std::string>();
                     })
                 | std::ranges::to<std::vector<std::string>>();

    if ( chunked != std::vector<std::string>{"abc", "123", "def"} )
        throw std::runtime_error("test failed");
}
    