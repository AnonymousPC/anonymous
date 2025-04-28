template < anonymous::pair_type input_type >
struct tuple_size<input_type>
{
    constexpr static const size_t value = 2;
};

template < size_t index, anonymous::pair_type input_type >
struct tuple_element<index,input_type>
{
    using type = conditional<index==0,typename input_type::key_type,typename input_type::value_type>::type;
};

template < size_t index, anonymous::pair_type input_type >
constexpr decltype(auto) get ( input_type& p )
{
    if constexpr ( index == 0 )
        return p.key();
    else
        return p.value();
}

template < size_t index, anonymous::pair_type input_type >
constexpr decltype(auto) get ( const input_type& p )
{
    if constexpr ( index == 0 )
        return p.key();
    else
        return p.value();
}

template < size_t index, anonymous::pair_type input_type >
constexpr decltype(auto) get ( input_type&& p )
{
    if constexpr ( index == 0 )
        return std::move ( p.key() );
    else
        return std::move ( p.value() );
}



namespace detail
{
    template < class input_type, int count = 1 >
    constexpr size_t tuple_size_helper = []
        {
            if constexpr ( requires { typename input_type::template value_type<count>; } )
                return tuple_size_helper<input_type,count+1>;
            else
                return count - 1;
        } ();
    
} // namespace detail


template < anonymous::tuple_type input_type >
struct tuple_size<input_type>
{
    constexpr static const size_t value = detail::tuple_size_helper<input_type>;
};

template < size_t index, anonymous::tuple_type input_type >
struct tuple_element<index,input_type>
{
    using type = input_type::template value_type<index+1>;
};

template < size_t index, anonymous::tuple_type input_type >
constexpr decltype(auto) get ( input_type& t )
{
    return t.template value<index+1>();
}

template < size_t index, anonymous::tuple_type input_type >
constexpr decltype(auto) get ( const input_type& t )
{
    return t.template value<index+1>();
}

template < size_t index, anonymous::tuple_type input_type >
constexpr decltype(auto) get ( input_type&& t )
{
    return std::move ( t.template value<index+1>() );
}
