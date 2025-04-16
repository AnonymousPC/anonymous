#pragma once

namespace detail
{
    template < class type >
    struct io_mode
    {
        type value = type();
        constexpr io_mode ( ) = default;
        constexpr io_mode ( type );
    };

    template < >
    struct io_mode<string>
    {
        string value = "";
        constexpr io_mode ( ) = default;
        constexpr io_mode ( string );
    };

    template < >
    struct io_mode<pair<string,string>>
    {
        pair<string,string> value = {};
        constexpr io_mode ( ) = default;
        constexpr io_mode ( string, string );
        constexpr io_mode ( pair<string,string> );
    };

    template < >
    struct io_mode<array<string>>
    {
        array<string> value = {};
        constexpr io_mode ( ) = default;
        constexpr io_mode ( string );
        constexpr io_mode ( string, convertible_to<string> auto... );
        constexpr io_mode ( array<string> );
    };
    
    template < >
    struct io_mode<map<string,string>>
    {
        map<string,string> value = {};
        constexpr io_mode ( ) = default;
        constexpr io_mode ( string, string );
        constexpr io_mode ( pair<string,string> );
        constexpr io_mode ( map <string,string> );
    };
    
    template < > // map<string,array<string>>
    struct io_mode<map<string,array<string>>>
    {
        map<string,array<string>> value = {};
        constexpr io_mode ( ) = default;
        constexpr io_mode ( string, string );
        constexpr io_mode ( string, array<string> );
        constexpr io_mode ( pair<string,string> );
        constexpr io_mode ( pair<string,array<string>> );
        constexpr io_mode ( map <string,string> );
        constexpr io_mode ( map <string,array<string>> );
    };

}

#include "io_mode.cpp"
