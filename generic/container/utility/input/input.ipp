#pragma once

namespace aux
{
    struct input_t
    {
        string operator() ( )                       const;
        string operator() ( const printable auto& ) const;
    };

    string input_t::operator() ( ) const
    {
        string str = "";
        char   ch  = '\0';
        while ( true )
        {
            std::cin.get(ch);
            if ( ch != '\n' and ch != '\0' )
                str.push(ch);
            else
                break;
        }
        return str;
    }

    string input_t::operator() ( const printable auto& prompt ) const
    {

        string str = "";
        char   ch  = '\0';
        std::cout << prompt;
        while ( true )
        {
            std::cin.get(ch);
            if ( ch != '\n' and ch != '\0' )
                str.push(ch);
            else
                break;
        } 
        return str;
    }  
} 

aux::input_t input;
