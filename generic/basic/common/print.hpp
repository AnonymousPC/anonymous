#pragma once

class print_t
{
    public:
        constexpr static void operator() ( );
        constexpr static void operator() ( const printable auto&, const printable auto&... );
};

#include "print.ipp"
