#pragma once

namespace detail
{
    class print_t
    {
        public:
            constexpr static void operator() ( );
            constexpr static void operator() ( const printable auto&, const printable auto&... );
    };
     
} // namespace deteail



#include "print.cpp"
