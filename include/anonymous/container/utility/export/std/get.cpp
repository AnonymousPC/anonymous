template < size_t index, class type1, class type2 >
constexpr decltype(auto) get ( anonymous::pair<type1,type2>& s )
    requires ( index == 0 or index == 1 )
{
    if constexpr ( index == 0 )
        return s.key();
    else
        return s.value();
}

template < size_t index, class type1, class type2 >
constexpr decltype(auto) get ( const anonymous::pair<type1,type2>& s )
    requires ( index == 0 or index == 1 )
{
    if constexpr ( index == 0 )
        return s.key();
    else
        return s.value();
}

template < size_t index, class type1, class type2 >
constexpr decltype(auto) get ( anonymous::pair<type1,type2>&& s )
    requires ( index == 0 or index == 1 )
{
    if constexpr ( index == 0 )
        return std::move(s.key());
    else 
        return std::move(s.value());
}

template < size_t index, class... types >
constexpr decltype(auto) get ( anonymous::tuple<types...>& s )
    requires ( index >= 0 and index <= sizeof...(types) )
{
    return s.template value<index+1>();
}

template < size_t index, class... types >
constexpr decltype(auto) get ( const anonymous::tuple<types...>& s )
    requires ( index >= 0 and index <= sizeof...(types) )
{
    return s.template value<index+1>();
}

template < size_t index, class... types >
constexpr decltype(auto) get ( anonymous::tuple<types...>&& s )
    requires ( index >= 0 and index <= sizeof...(types) )
{
    return std::move(s.template value<index+1>());
}
