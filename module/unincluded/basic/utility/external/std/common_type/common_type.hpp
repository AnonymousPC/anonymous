template < >
struct common_type<anonymous::cpu,anonymous::cpu>;

template < class type >
struct common_type<anonymous::cpu,type>;

template < class type >
struct common_type<type,anonymous::cpu>;

#include "common_type.cpp"