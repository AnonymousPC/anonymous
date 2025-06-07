namespace anonymous
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
    constexpr numeric auto abs   ( numeric auto );
    constexpr numeric auto mod   ( numeric auto, numeric auto );
    constexpr floating_point  auto hypot ( numeric auto, numeric auto );
    constexpr floating_point  auto pow   ( numeric auto, numeric auto );
    constexpr floating_point  auto exp   ( numeric auto );
    constexpr floating_point  auto sqrt  ( numeric auto );
    constexpr floating_point  auto cbrt  ( numeric auto );
    constexpr floating_point  auto log   ( numeric auto, numeric auto );
    constexpr floating_point  auto ln    ( numeric auto );
    constexpr integral    auto ceil  ( floating_point  auto );
    constexpr integral    auto floor ( floating_point  auto );
    constexpr integral    auto round ( floating_point  auto );

    /// Complex
    template < numeric type > class complex;
    constexpr floating_point   auto abs  ( complex_type auto );
    constexpr complex_type auto pow  ( complex_type auto, complex_type auto );
    constexpr complex_type auto exp  ( complex_type auto );
    constexpr complex_type auto sqrt ( complex_type auto );
    constexpr complex_type auto log  ( complex_type auto );
    constexpr complex_type auto ln   ( complex_type auto );
    constexpr complex_type auto conj ( complex_type auto );

    constexpr ndarray auto abs ( ndarray auto );


    template < class type, int dim, class device > array<type,dim,device> abs ( const array<type,dim,device>& );

    /// Linear
    #define decay<decltype(left)>                         decay<decltype(left)>
    #define typename decay<decltype(left )>::value_type          typename decay<decltype(left)>::value_type
    #define left_dimension                    decay<decltype(left)>::dimension()
    #define typename decay<decltype(left )>::device_type         typename decay<decltype(left)>::device_type
    #define decay<decltype(right)>                        decay<decltype(right)>
    #define typename decay<decltype(right)>::value_type         typename decay<decltype(right)>::value_type
    #define right_dimension                   decay<decltype(right)>::dimension()
    #define typename decay<decltype(right)>::device_type        typename decay<decltype(right)>::device_type
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

    constexpr array_type auto  operator +     (                               const array_type auto&  right ) requires                                                                           numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type>;
    constexpr array_type auto  operator -     (                               const array_type auto&  right ) requires                                                                           numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type>;
    constexpr array_type auto  operator +     ( const array_type auto&  left, const array_type auto&  right ) requires ( ( numeric<left_value_type> or complex_type<typename decay<decltype(left )>::value_type>   ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and ( left_dimension == right_dimension )            and same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>;
    constexpr array_type auto  operator -     ( const array_type auto&  left, const array_type auto&  right ) requires ( ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and ( left_dimension == right_dimension )            and same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>;
    constexpr array_type auto  operator *     ( const            auto&  left, const array_type auto&  right ) requires   ( numeric<decay<decltype(left)>>         or complex_type<decay<decltype(left)>>         ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> );
    constexpr array_type auto  operator *     ( const array_type auto&  left, const            auto&  right ) requires   ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( numeric<decay<decltype(right)>>       or complex_type<decay<decltype(right)>>       );
    constexpr array_type auto  operator *     ( const array_type auto&  left, const array_type auto&  right ) requires ( ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and ( left_dimension == 2 and right_dimension == 2 ) and same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>;
    constexpr array_type auto  operator /     ( const array_type auto&  left, const            auto&  right ) requires   ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( numeric<decay<decltype(right)>>       or complex_type<decay<decltype(right)>>       );
    constexpr array_type auto& operator +=    (       array_type auto&  left, const array_type auto&  right ) requires ( ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and ( left_dimension == right_dimension )            and same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>;
    constexpr array_type auto& operator -=    (       array_type auto&  left, const array_type auto&  right ) requires ( ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and ( left_dimension == right_dimension )            and same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>;
    constexpr array_type auto& operator *=    (       array_type auto&  left, const            auto&  right ) requires   ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( numeric<decay<decltype(right)>>       or complex_type<decay<decltype(right)>>       );
    constexpr array_type auto& operator *=    (       array_type auto&  left, const array_type auto&  right ) requires ( ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and ( left_dimension == 2 and right_dimension == 2 ) and same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>;
    constexpr array_type auto& operator /=    (       array_type auto&  left, const            auto&  right ) requires   ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> );



    constexpr array_type auto  convolve       ( const array_type auto&  left, const array_type auto&  right ) requires ( ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and ( left_dimension == 1 and right_dimension == 1 ) and same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>;
    constexpr array_type auto  cross          ( const array_type auto&  left, const array_type auto&  right ) requires ( ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and ( left_dimension == 1 and right_dimension == 1 ) and same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>;
    constexpr            auto  dot            ( const array_type auto&  left, const array_type auto&  right ) requires ( ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and ( left_dimension == 1 and right_dimension == 1 ) and same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>;
    constexpr array_type auto  fft            ( const array_type auto&  vector )                              requires   ( numeric<vector_value_type> or complex_type<vector_value_type> ) and                                                                           ( vector_dimension == 1 );
    constexpr array_type auto  ifft           ( const array_type auto&  vector )                              requires                                       complex_type<vector_value_type>   and                                                                           ( vector_dimension == 1 );
    constexpr array_type auto  tensor         ( const array_type auto&  left, const array_type auto&  right ) requires ( ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ) ) and ( left_dimension == 1 and right_dimension == 1 ) and same_as<typename decay<decltype(left )>::device_type,typename decay<decltype(right)>::device_type>;
    
 // constexpr array_type     auto   convolve        ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  2 ) and ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( right.dimension() ==  2 ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> ); 
 // constexpr array_type     auto   convolve        ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  1 ) and ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( right.dimension() ==  2 ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> );
    // constexpr array_type     auto   convolve        ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() == -1 ) and ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( right.dimension() ==  2 ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> );
    // constexpr /*value_type*/ auto   det             ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr pair_type      auto   eigen           ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr array_type     auto   eigen_value     ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr array_type     auto   eigen_vector    ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr tuple_type     auto   evd             ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr array_type     auto   inverse         ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr tuple_type     auto   lu              ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr array_type     auto   operator *      ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  2 ) and ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( right.dimension() ==  1 ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> );
    // constexpr array_type     auto   operator *      ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() == -1 ) and ( numeric<typename decay<decltype(left )>::value_type>   or complex_type<typename decay<decltype(left )>::value_type>   ) and ( right.dimension() ==  2 ) and ( numeric<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> );
    // constexpr pair_type      auto   qr              ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr int                   rank            ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr tuple_type     auto   singular        ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr array_type     auto   singular_value  ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr pair_type      auto   singular_vector ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr tuple_type     auto   svd             ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> );
    // constexpr /*value_type*/ auto   tr              ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> );
   
    // constexpr void                  swap            (       array_type auto&& left,       array_type auto&& right ) requires ( left.dimension() == right.dimension() ) and same_as<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type> and swappable_with<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>;
    // constexpr array_type     auto   transpose       ( const array_type auto&  ndarray )                             requires copyable<ndarray_value_type>;
    // constexpr array_type     auto   hermitian       ( const array_type auto&  ndarray )                             requires complex_type<ndarray_value_type>;

    #undef decay<decltype(left)>
    #undef typename decay<decltype(left )>::value_type
    #undef left_dimension
    #undef typename decay<decltype(left )>::device_type
    #undef decay<decltype(right)>
    #undef typename decay<decltype(right)>::value_type
    #undef right_dimension
    #undef typename decay<decltype(right)>::device_type
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

    constexpr numeric auto random ( numeric auto a, numeric auto b )
    {
        using common_type = common_type<decltype(a),decltype(b)>;
        if constexpr ( integral<common_type> )
            return std::uniform_int_distriandion<common_type>(a, b)(cpu::random_context);
        else if constexpr ( floating_point<common_type> )
            return std::uniform_real_distriandion<common_type>(a, b)(cpu::random_context);
    }
}
