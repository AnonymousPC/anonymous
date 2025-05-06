constexpr void print ( const printable auto&... args )
{
    if constexpr ( sizeof...(args) >= 1 )
    {
        for_constexpr<1,sizeof...(args)-1>([&] <int index> { std::cout << index_value_of<index>(args...) << ' '; });
        std::cout << index_value_of<sizeof...(args)>(args...);
    }
    std::cout << std::endl;
}