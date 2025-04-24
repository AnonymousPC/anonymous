struct input_t
{
    constexpr string operator() ( )                       const;
    constexpr string operator() ( const printable auto& ) const;
};

constexpr string input_t::operator() ( ) const
{
    auto str = std::string();
    std::getline(std::cin, str, '\n');
    return string(str);
}

constexpr string input_t::operator() ( const printable auto& prompt ) const
{
    std::cout << prompt;
    return self();
}  