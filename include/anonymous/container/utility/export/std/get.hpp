template < size_t index, class type1, class type2 >
constexpr decltype(auto) get ( anonymous::pair<type1,type2>& )
    requires ( index == 0 or index == 1 );

template < size_t index, class type1, class type2 >
constexpr decltype(auto) get ( const anonymous::pair<type1,type2>& )
    requires ( index == 0 or index == 1 );

template < size_t index, class type1, class type2 >
constexpr decltype(auto) get ( anonymous::pair<type1,type2>&& )
    requires ( index == 0 or index == 1 );

template < size_t index, class... types >
constexpr decltype(auto) get ( anonymous::tuple<types...>& )
    requires ( index >= 0 and index <= sizeof...(types) - 1 );

template < size_t index, class... types >
constexpr decltype(auto) get ( const anonymous::tuple<types...>& )
    requires ( index >= 0 and index <= sizeof...(types) - 1 );

template < size_t index, class... types >
constexpr decltype(auto) get ( anonymous::tuple<types...>&& )
    requires ( index >= 0 and index <= sizeof...(types) - 1 );

#include "get.cpp"
