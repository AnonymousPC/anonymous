template < class type1, class type2 >
struct tuple_size<anonymous::pair<type1,type2>>;

template < size_t index, class type1, class type2 >
    requires ( index == 0 or index == 1 )
struct tuple_element<index,anonymous::pair<type1,type2>>;

template < size_t index, class type1, class type2 >
constexpr decltype(auto) get ( anonymous::pair<type1,type2>& )
    requires ( index == 0 or index == 1 );

template < size_t index, class type1, class type2 >
constexpr decltype(auto) get ( const anonymous::pair<type1,type2>& )
    requires ( index == 0 or index == 1 );

template < size_t index, class type1, class type2 >
constexpr decltype(auto) get ( anonymous::pair<type1,type2>&& )
    requires ( index == 0 or index == 1 );



template < class... types >
struct tuple_size<anonymous::tuple<types...>>;
    
template < size_t index, class... types >
    requires ( index >= 0 and index <= sizeof...(types) - 1 )
struct tuple_element<index,anonymous::tuple<types...>>;

template < size_t index, class... types >
constexpr decltype(auto) get ( anonymous::tuple<types...>& )
    requires ( index >= 0 and index <= sizeof...(types) - 1 );

template < size_t index, class... types >
constexpr decltype(auto) get ( const anonymous::tuple<types...>& )
    requires ( index >= 0 and index <= sizeof...(types) - 1 );

template < size_t index, class... types >
constexpr decltype(auto) get ( anonymous::tuple<types...>&& )
    requires ( index >= 0 and index <= sizeof...(types) - 1 );

#include "structured_binding.cpp"