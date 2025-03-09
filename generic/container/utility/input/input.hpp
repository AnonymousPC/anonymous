#pragma once

namespace detail
{
    struct input_t
    {
        string operator() ( )                       const;
        string operator() ( const printable auto& ) const;
    };

    string input_t::operator() ( ) const
    {
        let str = std::string();
        std::getline(std::cin, str, '\n');
        return string(str);
    }

    string input_t::operator() ( const printable auto& prompt ) const
    {
        std::cout << prompt;
        return self();
    }  
} 

detail::input_t input;