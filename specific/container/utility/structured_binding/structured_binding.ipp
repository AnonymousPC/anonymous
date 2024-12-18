#pragma once

/// Pair

namespace std
{
    template < ap::pair_type input_type >
    struct tuple_size<input_type>
    {
        constexpr static const int value = 2;
    };

    template < size_t index, ap::pair_type input_type >
        requires ( index == 0 or index == 1 )
    struct tuple_element<index,input_type>
    {
        using type = conditional<index==0,typename input_type::key_type,typename input_type::value_type>::type;
    };
}

namespace ap 
{
    template < int index, pair_type input_type >
        requires ( index == 0 or index == 1 )
    constexpr decltype(auto) get ( input_type& p )
    {
        if constexpr ( index == 0 )
            return p.key();
        else
            return p.value();
    }

    template < int index, pair_type input_type >
        requires ( index == 0 or index == 1 )
    constexpr decltype(auto) get ( const input_type& p )
    {
        if constexpr ( index == 0 )
            return p.key();
        else
            return p.value();
    }

    template < int index, pair_type input_type >
        requires ( index == 0 or index == 1 )
    constexpr decltype(auto) get ( input_type&& p )
    {
        if constexpr ( index == 0 )
            return std::move ( p.key() );
        else
            return std::move ( p.value() );
    }
}




/// Tuple

namespace std 
{
    template < ap::tuple_type input_type >
    struct tuple_size<input_type>
    {
        constexpr static const int value = input_type::size();
    };

    template < size_t index, ap::tuple_type input_type >
        requires ( index >= 0 and index <= input_type::size() - 1 )
    struct tuple_element<index,input_type>
    {
        using type = typename input_type::template value_type<index+1>;
    };
}

namespace ap
{
    template < int index, tuple_type input_type >
        requires ( index >= 0 and index <= input_type::size() - 1 )
    constexpr decltype(auto) get ( input_type& t )
    {
        return t.template value<index+1>();
    }

    template < int index, tuple_type input_type >
        requires ( index >= 0 and index <= input_type::size() - 1 )
    constexpr decltype(auto) get ( const input_type& t )
    {
        return t.template value<index+1>();
    }

    template < int index, tuple_type input_type >
        requires ( index >= 0 and index <= input_type::size() - 1 )
    constexpr decltype(auto) get ( input_type&& t )
    {
        return std::move ( t.template value<index+1>() );
    }
}
