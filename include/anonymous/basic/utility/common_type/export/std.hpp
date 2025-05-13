template < >
struct common_type<anonymous::cpu,anonymous::cpu>;

template < anonymous::device_type type >
struct common_type<anonymous::cpu,type>;

template < anonymous::device_type type >
struct common_type<type,anonymous::cpu>;

#include "std.cpp"