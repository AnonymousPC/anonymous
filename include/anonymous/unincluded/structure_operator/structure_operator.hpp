#include "detail/operatable.cpp"

constexpr           bool operator ==  ( const structure auto& left, const structure auto& right ) requires detail::tuplewise_equalable_to        <left_type,right_type>;
constexpr           auto operator <=> ( const structure auto& left, const structure auto& right ) requires detail::tuplewise_comparable_to       <left_type,right_type>;
constexpr structure auto operator  +  ( const structure auto& left, const structure auto& right ) requires detail::tuplewise_plusable_to         <left_type,right_type>;
constexpr structure auto operator  -  ( const structure auto& left, const structure auto& right ) requires detail::tuplewise_minusable_to        <left_type,right_type>;
constexpr structure auto operator  *  ( const structure auto& left, const           auto& right ) requires detail::tuplewise_each_multipliable_to<left_type,right_type> and ( not structure<right_type> );
constexpr structure auto operator  *  ( const           auto& left, const structure auto& right ) requires detail::tuplewise_multipliable_to_each<left_type,right_type> and ( not structure<left_type > );
constexpr structure auto operator  /  ( const structure auto& left, const           auto& right ) requires detail::tuplewise_each_dividable_to   <left_type,right_type> and ( not structure<right_type> );

// #include "structure_operator.cpp": the .cpp file is included in "discrete/discrete.hpp" as the implemention depends on tuple<>.