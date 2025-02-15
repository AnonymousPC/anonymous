#pragma once

} // Out from namespace ap


namespace std
{
    template < ap::pair_type input_type >
    struct tuple_size<input_type>;

    template < size_t index, ap::pair_type input_type >
        requires ( index == 0 or index == 1 )
    struct tuple_element<index,input_type>;
}

namespace ap
{
    template < int index, pair_type input_type >
        requires ( index == 0 or index == 1 )
    constexpr decltype(auto) get ( input_type& );

    template < int index, pair_type input_type >
        requires ( index == 0 or index == 1 )
    constexpr decltype(auto) get ( const input_type& );

    template < int index, pair_type input_type >
        requires ( index == 0 or index == 1 )
    constexpr decltype(auto) get ( input_type&& );
}




/// Tuple

namespace std
{
    template < ap::tuple_type input_type >
    struct tuple_size<input_type>;

    template < size_t index, ap::tuple_type input_type >
        requires ( index >= 0 and index <= std::tuple_size<input_type>::value - 1 )
    struct tuple_element<index,input_type>;
}

namespace ap
{
    template < int index, tuple_type input_type >
        requires ( index >= 0 and index <= std::tuple_size<input_type>::value - 1 )
    constexpr decltype(auto) get ( input_type& );

    template < int index, tuple_type input_type >
        requires ( index >= 0 and index <= std::tuple_size<input_type>::value - 1 )
    constexpr decltype(auto) get ( const input_type& );

    template < int index, tuple_type input_type >
        requires ( index >= 0 and index <= std::tuple_size<input_type>::value - 1 )
    constexpr decltype(auto) get ( input_type&& );
}


#include "structured_binding.ipp"

namespace ap { // Back into namespace ap
