#pragma once

namespace detail
{
    struct print_t
    {
        void operator() ( )                                                 const;
        void operator() ( const printable auto&, const printable auto&... ) const;

        static std::recursive_mutex print_mutex;
    };

    std::recursive_mutex print_t::print_mutex = std::recursive_mutex();

    void print_t::operator() ( ) const
    {
        let lock = std::unique_lock<std::recursive_mutex>(print_mutex);
        std::cout << std::endl;
    }

    void print_t::operator() ( const printable auto& first, const printable auto&... args ) const
    {
        let lock = std::unique_lock<std::recursive_mutex>(print_mutex);
        std::cout << first;
        if constexpr ( sizeof...(args) >= 1 )
            std::cout << ' ';
        return operator()(args...);
    }
}

detail::print_t print;