#pragma once

namespace detail
{
    struct print_t
    {
        constexpr static void operator() ( );
        constexpr static void operator() ( const printable auto&, const printable auto&... );
    };

    constexpr void print_t::operator() ( )
    {
        std::cout << std::endl;
    }

    constexpr void print_t::operator() ( const printable auto& first, const printable auto&... args )
    {
        std::cout << first;
        if constexpr ( sizeof...(args) >= 1 )
            std::cout << ' ';
        return operator()(args...);
    }
}

constexpr detail::print_t print;