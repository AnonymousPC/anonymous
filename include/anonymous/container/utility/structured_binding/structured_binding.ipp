#pragma once

/// Pair

namespace std
{
    template < anonymous::pair_type input_type >
    struct tuple_size<input_type>
    {
        constexpr static const int value = 2;
    };

    template < size_t index, anonymous::pair_type input_type >
        requires ( index == 0 or index == 1 )
    struct tuple_element<index,input_type>
    {
        using type = conditional<index==0,typename input_type::key_type,typename input_type::value_type>::type;
    };
}

namespace anonymous 
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

namespace anonymous::detail
{
    template < class input_type, int count >
    struct tuple_size_probe;

    template < class input_type, int count >
        requires requires { typename input_type::template value_type<count>; }
    struct tuple_size_probe<input_type,count>
    {
        constexpr static const int value = tuple_size_probe<input_type,count+1>::value;
    };

    template < class input_type, int count >
        requires ( not requires { typename input_type::template value_type<count>; } )
    struct tuple_size_probe<input_type,count>
    {
        constexpr static const int value = count - 1;
    };

    template < class input_type >
    constexpr int tuple_size_helper = tuple_size_probe<input_type,1>::value;
    
} // namespace anonymous::detail


namespace std 
{
    template < anonymous::tuple_type input_type >
    struct tuple_size<input_type>
    {
        constexpr static const int value = anonymous::detail::tuple_size_helper<input_type>;
    };

    template < size_t index, anonymous::tuple_type input_type >
        requires ( index >= 0 and index <= std::tuple_size<input_type>::value - 1 )
    struct tuple_element<index,input_type>
    {
        using type = typename input_type::template value_type<index+1>;
    };
}

namespace anonymous
{
    template < int index, tuple_type input_type >
        requires ( index >= 0 and index <= std::tuple_size<input_type>::value - 1 )
    constexpr decltype(auto) get ( input_type& t )
    {
        return t.template value<index+1>();
    }

    template < int index, tuple_type input_type >
        requires ( index >= 0 and index <= std::tuple_size<input_type>::value- 1 )
    constexpr decltype(auto) get ( const input_type& t )
    {
        return t.template value<index+1>();
    }

    template < int index, tuple_type input_type >
        requires ( index >= 0 and index <= std::tuple_size<input_type>::value - 1 )
    constexpr decltype(auto) get ( input_type&& t )
    {
        return std::move ( t.template value<index+1>() );
    }
}
