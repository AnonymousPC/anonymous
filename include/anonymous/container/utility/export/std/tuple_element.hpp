template < size_t index, class type1, class type2 >
struct tuple_element<index,anonymous::pair<type1,type2>>;

template < size_t index, class... types >
struct tuple_element<index,anonymous::tuple<types...>>;

#include "tuple_element.cpp"