#pragma once

namespace aux
{
    template < std::endian endian, class type = void >
    constexpr bool requires_byteswap =
        sizeof(type) >= 2 and
        ( ( std::endian::native == std::endian::little and endian == std::endian::big    ) or
          ( std::endian::native == std::endian::big    and endian == std::endian::little ) );

    template < class type >
        requires ( not is_class<type> )
    constexpr void byteswap ( type& t )
    {
        if constexpr ( std::is_integral<type>::value )
            t = std::byteswap(t);
        else
            std::reverse(reinterpret_cast<char*>(&t), reinterpret_cast<char*>(&t) + sizeof(t));
    }
}

#include "stream_view.hpp"
#include "binary_stream_view.hpp"
#include "chunked_binary_stream_view.hpp"