#pragma once

namespace detail
{
    struct print_t
    {
        constexpr static void operator() ( );
        constexpr static void operator() ( const printable auto&, const printable auto&... );
        static std::recursive_mutex print_mutex;
    };
}

constexpr detail::print_t print;

constexpr void detail::print_t::operator() ( )
{
    let guard = std::lock_guard<std::recursive_mutex>(print_mutex);

    std::cout << std::endl;
}

constexpr void detail::print_t::operator() ( const printable auto& first, const printable auto&... args )
{
    let guard = std::lock_guard<std::recursive_mutex>(print_mutex);

    std::cout << first;
    if constexpr ( sizeof...(args) >= 1 )
        std::cout << ' ';
    return operator()(args...);
}