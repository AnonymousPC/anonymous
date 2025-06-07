                                              constexpr decltype(auto) first_value_of    ( auto&&... );
                                              constexpr decltype(auto) last_value_of     ( auto&&... );
template < int index >                        constexpr decltype(auto) index_value_of    ( auto&&... );
template < int min, int max, int stride = 1 > constexpr void           for_constexpr     ( auto&& );
template < int min, int max, int stride = 1 > constexpr bool           all_of_constexpr  ( auto&& );
template < int min, int max, int stride = 1 > constexpr bool           any_of_constexpr  ( auto&& );
template < int min, int max, int stride = 1 > constexpr bool           none_of_constexpr ( auto&& );

#include "algorithm.cpp"