template < class type1, class type2 >
struct tuple_size<anonymous::pair<type1,type2>>
{
    constexpr static const size_t value = 2;
};

template < size_t index, class type1, class type2 >
    requires ( index == 0 or index == 1 )
struct tuple_element<index,anonymous::pair<type1,type2>>
{
    using type = conditional<index==0,type1,type2>;
};

template < size_t index, class type1, class type2 >
constexpr decltype(auto) get ( anonymous::pair<type1,type2>& p )
    requires ( index == 0 or index == 1 )
{
    return p.key();
}

template < size_t index, class type1, class type2 >
constexpr decltype(auto) get ( const anonymous::pair<type1,type2>& p )
    requires ( index == 0 or index == 1 )
{
    return p.key();
}

template < size_t index, class type1, class type2 >
constexpr decltype(auto) get ( anonymous::pair<type1,type2>&& p )
    requires ( index == 0 or index == 1 )
{
    return std::move(p.key());
}



template < class... types >
struct tuple_size<anonymous::tuple<types...>>
{
    constexpr static const size_t value = sizeof...(types);
};
    
template < size_t index, class... types >
    requires ( index >= 0 and index <= sizeof...(types) - 1 )
struct tuple_element<index,anonymous::tuple<types...>>
{
    using type = types...[index];
};

template < size_t index, class... types >
constexpr decltype(auto) get ( anonymous::tuple<types...>& t )
    requires ( index >= 0 and index <= sizeof...(types) - 1 )
{
    return t.template value<index+1>();
}

template < size_t index, class... types >
constexpr decltype(auto) get ( const anonymous::tuple<types...>& t )
    requires ( index >= 0 and index <= sizeof...(types) - 1 )
{
    return t.template value<index+1>();
}

template < size_t index, class... types >
constexpr decltype(auto) get ( anonymous::tuple<types...>&& t )
    requires ( index >= 0 and index <= sizeof...(types) - 1 )
{
    return std::move(t.template value<index+1>());
}