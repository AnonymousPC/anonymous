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





template < anonymous::tuple_type input_type >
struct tuple_size<input_type>
{
    constexpr static const size_t value = std::tuple_size<decltype(std::tuple(std::declval<input_type>()))>::value;
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
