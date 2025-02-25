#pragma once

namespace detail
{
    struct print_t
    {
        static std::recursive_mutex mutex;
        static void operator() ( );
        static void operator() ( const printable auto&, const printable auto&... );
    };

    void print_t::operator() ( )
    {
        let scope = std::lock_guard<std::recursive_mutex>(mutex);
        std::cout << std::endl;
    }

    void print_t::operator() ( const printable auto& first, const printable auto&... args )
    {
        let scope = std::lock_guard<std::recursive_mutex>(mutex);
        std::cout << first;
        if constexpr ( sizeof...(args) >= 1 )
            std::cout << ' ';
        return operator()(args...);
    }

    std::recursive_mutex print_t::mutex = std::recursive_mutex();
}

detail::print_t print;