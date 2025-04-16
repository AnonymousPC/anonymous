#pragma once

constexpr void detail::print_t::operator() ( )
{
    std::cout << std::endl;
}

constexpr void detail::print_t::operator() ( const printable auto& first, const printable auto&... args )
{
    std::cout << first;
    if constexpr ( sizeof...(args) >= 1 )
        std::cout << ' ';
    return operator()(args...);
}