#pragma once

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

    /// Linear
    #define left_type                         decay<decltype(left)>
    #define left_value_type          typename decay<decltype(left)>::value_type
    #define left_dimension                    decay<decltype(left)>::dimension()
    #define left_device_type         typename decay<decltype(left)>::device_type
    #define right_type                        decay<decltype(right)>
    #define right_value_type         typename decay<decltype(right)>::value_type
    #define right_dimension                   decay<decltype(right)>::dimension()
    #define right_device_type        typename decay<decltype(right)>::device_type
    #define vector_type                       decay<decltype(vector)>
    #define vector_value_type        typename decay<decltype(vector)>::value_type
    #define vector_dimension                  decay<decltype(vector)>::dimension()
    #define vector_device_type       typename decay<decltype(vector)>::device_type
    #define matrix_type                       decay<decltype(matrix)>
    #define matrix_value_type        typename decay<decltype(matrix)>::value_type
    #define matrix_dimension                  decay<decltype(matrix)>::dimension()
    #define matrix_device_type       typename decay<decltype(matrix)>::device_type
    #define ndarray_type                      decay<decltype(ndarray)>
    #define ndarray_value_type       typename decay<decltype(ndarray)>::value_type
    #define ndarray_dimension                 decay<decltype(ndarray)>::dimension()
    #define ndarray_device_type      typename decay<decltype(ndarray)>::device_type

    constexpr array_type auto  operator +     (                               const array_type auto&  right ) requires                                                                           number_type<right_value_type> or complex_type<right_value_type>;
    constexpr array_type auto  operator -     (                               const array_type auto&  right ) requires                                                                           number_type<right_value_type> or complex_type<right_value_type>;
    constexpr array_type auto  operator +     ( const array_type auto&  left, const array_type auto&  right ) requires ( ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ) and ( left_dimension == right_dimension )            and same_as<left_device_type,right_device_type>;
    constexpr array_type auto  operator -     ( const array_type auto&  left, const array_type auto&  right ) requires ( ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ) and ( left_dimension == right_dimension )            and same_as<left_device_type,right_device_type>;
    constexpr array_type auto  operator *     ( const            auto&  left, const array_type auto&  right ) requires   ( number_type<left_type>       or complex_type<left_type>       ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    constexpr array_type auto  operator *     ( const array_type auto&  left, const            auto&  right ) requires   ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_type>       or complex_type<right_type>       );
    constexpr array_type auto  operator *     ( const array_type auto&  left, const array_type auto&  right ) requires ( ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ) and ( left_dimension == 2 and right_dimension == 2 ) and same_as<left_device_type,right_device_type>;
    constexpr array_type auto  operator /     ( const array_type auto&  left, const            auto&  right ) requires   ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_type>       or complex_type<right_type>       );
    constexpr array_type auto& operator +=    (       array_type auto&  left, const array_type auto&  right ) requires ( ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ) and ( left_dimension == right_dimension )            and same_as<left_device_type,right_device_type>;
    constexpr array_type auto& operator -=    (       array_type auto&  left, const array_type auto&  right ) requires ( ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ) and ( left_dimension == right_dimension )            and same_as<left_device_type,right_device_type>;
    constexpr array_type auto& operator *=    (       array_type auto&  left, const            auto&  right ) requires   ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_type>       or complex_type<right_type>       );
    constexpr array_type auto& operator *=    (       array_type auto&  left, const array_type auto&  right ) requires ( ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ) and ( left_dimension == 2 and right_dimension == 2 ) and same_as<left_device_type,right_device_type>;
    constexpr array_type auto& operator /=    (       array_type auto&  left, const            auto&  right ) requires   ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> );



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
    // constexpr array_type     auto   operator *      ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  2 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  1 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    // constexpr array_type     auto   operator *      ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() == -1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  2 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    // constexpr pair_type      auto   qr              ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr int                   rank            ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr tuple_type     auto   singular        ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr array_type     auto   singular_value  ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr pair_type      auto   singular_vector ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr tuple_type     auto   svd             ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr /*value_type*/ auto   tr              ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
   
    // constexpr void                  swap            (       array_type auto&& left,       array_type auto&& right ) requires ( left.dimension() == right.dimension() ) and same_as<left_value_type,right_value_type> and swappable_with<left_value_type,right_value_type>;
    // constexpr array_type     auto   transpose       ( const array_type auto&  ndarray )                             requires copyable<ndarray_value_type>;
    // constexpr array_type     auto   hermitian       ( const array_type auto&  ndarray )                             requires complex_type<ndarray_value_type>;

    #undef left_type
    #undef left_value_type
    #undef left_dimension
    #undef left_device_type
    #undef right_type
    #undef right_value_type
    #undef right_dimension
    #undef right_device_type
    #undef vector_type
    #undef vector_value_type
    #undef vector_dimension
    #undef vector_device_type
    #undef matrix_type
    #undef matrix_value_type
    #undef matrix_dimension
    #undef matrix_device_type
    #undef ndarray_type
    #undef ndarray_value_type
    #undef ndarray_dimension
    #undef ndarray_device_type

    /// Include
    #include "numeric/numeric.hpp"
    #include "complex/complex.hpp"
    #include "linalg/linalg.hpp"
}
