#pragma once

#define first_type typename std::decay<decltype(first)>::type


// Print and input.

namespace aux
{
    void print ( );
    void print ( const printable auto&, const printable auto&... );
    std::recursive_mutex print_mutex;
}

constexpr auto print = [] ( const auto&... args ) { aux::print(args...); };











// Auxiliary

namespace aux
{

void print ( )
{
    std::cout << std::endl;
}

void print ( const printable auto& first, const printable auto&... args )
{
    let guard = std::unique_lock<std::recursive_mutex>(aux::print_mutex);

    std::cout << first;
    if constexpr ( sizeof...(args) >= 1 )
        std::cout << ' ';
    return print ( args... );
}

}


#undef first_type