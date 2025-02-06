#pragma once
#include "../container/interface.hpp"

namespace ap
{
    /// Constant
    inline namespace constants
    {
        constexpr const double          e   = std::numbers::e_v  <double>;
        constexpr const double          pi  = std::numbers::pi_v <double>;
        constexpr const double          inf = std::numeric_limits<double>::infinity();
     // constexpr const complex<double> i   = complex<double>(0, 1);
    }

    /// Numeric
    constexpr number_type auto abs   ( number_type auto );
    constexpr number_type auto mod   ( number_type auto, number_type auto );
    constexpr float_type  auto hypot ( number_type auto, number_type auto );
    constexpr float_type  auto pow   ( number_type auto, number_type auto );
    constexpr float_type  auto exp   ( number_type auto );
    constexpr float_type  auto sqrt  ( number_type auto );
    constexpr float_type  auto cbrt  ( number_type auto );
    constexpr float_type  auto log   ( number_type auto, number_type auto );
    constexpr float_type  auto ln    ( number_type auto );
    constexpr int_type    auto ceil  ( float_type  auto );
    constexpr int_type    auto floor ( float_type  auto );
    constexpr int_type    auto round ( float_type  auto );

    /// Complex
    template < number_type type > class complex;
    constexpr float_type   auto abs  ( complex_type auto );
    constexpr complex_type auto pow  ( complex_type auto, complex_type auto );
    constexpr complex_type auto exp  ( complex_type auto );
    constexpr complex_type auto sqrt ( complex_type auto );
    constexpr complex_type auto log  ( complex_type auto );
    constexpr complex_type auto ln   ( complex_type auto );
    constexpr complex_type auto conj ( complex_type auto );

    // /// Linear
    // #define left_type                         decay<decltype(left)>
    // #define left_value_type          typename decay<decltype(left)>::value_type
    // #define left_iterate_type        typename decay<decltype(left)>::iterate_type
    // #define right_type                        decay<decltype(right)>
    // #define right_value_type         typename decay<decltype(right)>::value_type
    // #define right_iterate_type       typename decay<decltype(right)>::iterate_type
    // #define vector_type                       decay<decltype(vector)>
    // #define vector_value_type        typename decay<decltype(vector)>::value_type
    // #define vector_iterate_type      typename decay<decltype(vector)>::iterate_type
    // #define matrix_type                       decay<decltype(matrix)>
    // #define matrix_value_type        typename decay<decltype(matrix)>::value_type
    // #define matrix_iterate_type      typename decay<decltype(matrix)>::iterate_type
    // #define ndarray_type                      decay<decltype(ndarray)>
    // #define ndarray_value_type       typename decay<decltype(ndarray)>::value_type
    // #define ndarray_iterate_type     typename decay<decltype(ndarray)>::iterate_type

    // constexpr array_type     auto   convolve        ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  1 ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ;
    // constexpr array_type     auto   cross           ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  1 ) and   number_type<left_value_type>                                        and ( right.dimension() ==  1 ) and   number_type<right_value_type>; // Here complex-version is undefined.
    // constexpr /*value_type*/ auto   dot             ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  1 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    // constexpr array_type     auto   fft             ( const array_type auto&  vector )                              requires ( vector.dimension() ==  1 ) and ( number_type<vector_value_type> or complex_type<vector_value_type> );
    // constexpr array_type     auto   ifft            ( const array_type auto&  vector )                              requires ( vector.dimension() ==  1 ) and ( number_type<vector_value_type> or complex_type<vector_value_type> );
    // constexpr /*value_type*/ auto   operator *      ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() == -1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  1 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    // constexpr array_type     auto   operator *      ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() == -1 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    // constexpr array_type     auto   tensor          ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  1 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    // constexpr array_type     auto   convolve        ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  2 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  2 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    // constexpr array_type     auto   convolve        ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  2 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    // constexpr array_type     auto   convolve        ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() == -1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  2 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    // constexpr /*value_type*/ auto   det             ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr pair_type      auto   eigen           ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr array_type     auto   eigen_value     ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr array_type     auto   eigen_vector    ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr tuple_type     auto   evd             ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr array_type     auto   inverse         ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr tuple_type     auto   lu              ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr array_type     auto   operator *      ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  2 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  2 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    // constexpr array_type     auto   operator *      ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  2 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  1 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    // constexpr array_type     auto   operator *      ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() == -1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  2 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    // constexpr pair_type      auto   qr              ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr int                   rank            ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr tuple_type     auto   singular        ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr array_type     auto   singular_value  ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr pair_type      auto   singular_vector ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr tuple_type     auto   svd             ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr /*value_type*/ auto   tr              ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr                bool   operator ==     ( const array_type auto&  left, const array_type auto&  right ) requires ( left.dimension() == right.dimension() ) and equalable_to <left_value_type,right_value_type>;
    // constexpr                auto   operator <=>    ( const array_type auto&  left, const array_type auto&  right ) requires ( left.dimension() == right.dimension() ) and comparable_to<left_value_type,right_value_type>;
    // constexpr array_type     auto   operator  +     (                               const array_type auto&  right ) requires requires { + std::declval<right_value_type>(); };
    // constexpr array_type     auto   operator  -     (                               const array_type auto&  right ) requires requires { - std::declval<right_value_type>(); };
    // constexpr array_type     auto   operator  +     ( const array_type auto&  left, const array_type auto&  right ) requires ( left.dimension() == right.dimension() ) and addable_to     <left_value_type,right_value_type>;
    // constexpr array_type     auto   operator  -     ( const array_type auto&  left, const array_type auto&  right ) requires ( left.dimension() == right.dimension() ) and minusable_to   <left_value_type,right_value_type>;
    // constexpr array_type     auto   operator  *     ( const array_type auto&  left, const            auto&  right ) requires ( not array_type<right_type> )            and multipliable_to<left_value_type,right_type>;
    // constexpr array_type     auto   operator  *     ( const            auto&  left, const array_type auto&  right ) requires ( not array_type<left_type>  )            and multipliable_to<left_type,right_value_type>;
    // constexpr array_type     auto   operator  /     ( const array_type auto&  left, const            auto&  right ) requires ( not array_type<right_type> )            and dividable_to   <left_value_type,right_type>;
    // constexpr array_type     auto&  operator  +=    (       array_type auto&  left, const array_type auto&  right ) requires requires { left = left + right; };
    // constexpr array_type     auto&& operator  +=    (       array_type auto&& left, const array_type auto&  right ) requires requires { left = left + right; };
    // constexpr array_type     auto&  operator  -=    (       array_type auto&  left, const array_type auto&  right ) requires requires { left = left - right; };
    // constexpr array_type     auto&& operator  -=    (       array_type auto&& left, const array_type auto&  right ) requires requires { left = left - right; };
    // constexpr array_type     auto&  operator  *=    (       array_type auto&  left, const            auto&  right ) requires requires { left = left * right; };
    // constexpr array_type     auto&& operator  *=    (       array_type auto&& left, const            auto&  right ) requires requires { left = left * right; };
    // constexpr array_type     auto&  operator  /=    (       array_type auto&  left, const            auto&  right ) requires requires { left = left / right; };
    // constexpr array_type     auto&& operator  /=    (       array_type auto&& left, const            auto&  right ) requires requires { left = left / right; };
    // constexpr void                 swap             (       array_type auto&& left,       array_type auto&& right ) requires ( left.dimension() == right.dimension() ) and std::same_as<left_value_type,right_value_type> and std::swappable_with<left_value_type,right_value_type>;
    // constexpr array_type     auto  transpose        ( const array_type auto&  ndarray )                             requires std::copyable<ndarray_value_type>;
    // constexpr array_type     auto  hermitian        ( const array_type auto&  ndarray )                             requires complex_type<ndarray_value_type>;

    // template < int_type auto version = 2 >
    // constexpr array_type     auto  dct              ( const array_type auto&  vector )                              requires ( vector.dimension() ==  1 ) and   number_type<vector_value_type>;
    // template < number_type auto num = 1 >
    // constexpr /*value_type*/ auto  norm             ( const array_type auto&  vector )                              requires ( vector.dimension() ==  1 ) and ( number_type<vector_value_type> or complex_type<vector_value_type> );
    // template < number_type auto num = 1 >
    // constexpr /*value_type*/ auto  norm             ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );

    // #undef left_type
    // #undef left_value_type
    // #undef left_iterate_type
    // #undef right_type
    // #undef right_value_type
    // #undef right_iterate_type
    // #undef vector_type
    // #undef vector_value_type
    // #undef vector_iterate_type
    // #undef matrix_type
    // #undef matrix_value_type
    // #undef matrix_iterate_type
    // #undef ndarray_type
    // #undef ndarray_value_type
    // #undef ndarray_iterate_type

    /// Include
    #include "numeric/numeric.hpp"
    #include "complex/complex.hpp"
    //#include "geometric/geometric.hpp"
    //#include "linear/linear.hpp"
}
