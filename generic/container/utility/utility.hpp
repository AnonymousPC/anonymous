#pragma once

/// Class

template < auto... digits >
class constexpr_index;


/// Function

namespace aux
{
    struct input_t
    {
        string operator() ( ) const
        {
            string str = "";
            char   ch  = '\0';
            while (true)
            {
                ch = std::cin.get();
                if ( ch != '\n' )
                    str.push(ch);
                else
                    break;
            }
            return str;
        }

        string operator() ( const printable auto& outputs ) const
        {
            std::cout << outputs << std::flush;
            return self();
        }
    };
}

let input = aux::input_t();


/// Include

#include "constexpr_index/constexpr_index.hpp"

} // Out of namespace ap
#include "format/format.hpp"
#include "structured_binding/structured_binding.hpp"
namespace ap { // Back into namespace ap
