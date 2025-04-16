#pragma once

} // Out from namespace anonymous


namespace std
{
    template < anonymous::pair_type input_type >
    struct tuple_size<input_type>;

    template < size_t index, anonymous::pair_type input_type >
        requires ( index == 0 or index == 1 )
    struct tuple_element<index,input_type>;
}

namespace anonymous
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
    template < anonymous::tuple_type input_type >
    struct tuple_size<input_type>;

    template < size_t index, anonymous::tuple_type input_type >
        requires ( index >= 0 and index <= std::tuple_size<input_type>::value - 1 )
    struct tuple_element<index,input_type>;
}

namespace anonymous
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


#include "structured_binding.cpp"

namespace anonymous { // Back into namespace anonymous
