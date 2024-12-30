#pragma once

namespace detail
{
    struct print_t
    {
        void operator() ( )                                                 const;
        void operator() ( const printable auto&, const printable auto&... ) const;
    };

    void print_t::operator() ( ) const
    {
        std::cout << std::endl;
    }

    void print_t::operator() ( const printable auto& first, const printable auto&... args ) const
    {
        std::cout << first;
        if constexpr ( sizeof...(args) >= 1 )
            std::cout << ' ';
        return operator()(args...);
    }
}

detail::print_t print;