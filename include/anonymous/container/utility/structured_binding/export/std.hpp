template < anonymous::pair_type input_type >
struct tuple_size<input_type>;

template < size_t index, anonymous::pair_type input_type >
struct tuple_element<index,input_type>;

template < size_t index, anonymous::pair_type input_type >
constexpr decltype(auto) get ( input_type& );

template < size_t index, anonymous::pair_type input_type >
constexpr decltype(auto) get ( const input_type& );

template < size_t index, anonymous::pair_type input_type >
constexpr decltype(auto) get ( input_type&& );





template < anonymous::tuple_type input_type >
struct tuple_size<input_type>;

template < size_t index, anonymous::tuple_type input_type >
struct tuple_element<index,input_type>;

template < size_t index, anonymous::tuple_type input_type >
constexpr decltype(auto) get ( input_type& );

template < size_t index, anonymous::tuple_type input_type >
constexpr decltype(auto) get ( const input_type& );

template < size_t index, anonymous::tuple_type input_type >
constexpr decltype(auto) get ( input_type&& );



#include "std.cpp"
