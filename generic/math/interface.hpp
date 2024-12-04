#pragma once
#include "../container/interface.hpp"

namespace ap
{
    /// Constant
    namespace constants
    {
        constexpr const long double e   = std::numbers::e_v <long double>;
        constexpr const long double pi  = std::numbers::pi_v<long double>;
        constexpr const long double inf = std::numeric_limits<long double>::infinity();
    }

    /// Numeric/Geometric.concept
    template < class type > concept fraction_type = requires { typename type::fraction_tag; } and float_type<type>;
    template < class type > concept angle_type    = requires { typename type::angle_tag;    };
    template < class type > concept degree_type   = requires { typename type::degree_tag;   } and angle_type<type>;
    template < class type > concept radian_type   = requires { typename type::radian_tag;   } and angle_type<type>;
    template < class type > concept complex_type  = requires { typename type::complex_tag;  };
    template < class type > concept polar_type    = requires { typename type::polar_tag;    };

    template < class type > concept complex_int_type = []
    {
        if constexpr ( complex_type<type> )
        {
            static_assert ( requires { typename type::value_type; }, "class provides complex_tag but not provides value_type" );
            return int_type<typename type::value_type>;
        }
        else
            return false;
    } ();

    template < class type > concept complex_float_type = []
    {
        if constexpr ( complex_type<type> )
        {
            static_assert ( requires { typename type::value_type; }, "class provides complex_tag but not provides value_type" );
            return float_type<typename type::value_type>;
        }
        else
            return false;
    } ();

    template < class type > concept polar_float_type = []
    {
        if constexpr ( polar_type<type> )
        {
            static_assert ( requires { typename type::value_type; }, "class provides polar_tag but not provides value_type" );
            return float_type<typename type::value_type>;
        }
        else
            return false;
    } ();

    /// Numeric/Geometric.class
    template < int_type type = int >                            class fraction;
    template < float_type  type = double >                      class degree;
    template < float_type  type = double >                      class radian;
    template < number_type type >                               class complex;
    template < number_type type1, angle_type type2 = radian<> > class polar;


    /// Arithmetic.function
    constexpr int_type     auto abs    ( int_type           auto );
    constexpr int_type     auto log    ( int_type           auto, int_type     auto );
    constexpr int_type     auto log2   ( int_type           auto );
    constexpr int_type     auto log10  ( int_type           auto );
    constexpr int_type     auto ln     ( int_type           auto );
    constexpr int_type     auto mod    ( int_type           auto, int_type     auto );
    constexpr int_type     auto pow    ( int_type           auto, int_type     auto );
    constexpr int_type     auto sqrt   ( int_type           auto );
    constexpr int_type     auto exp    ( int_type           auto );
    constexpr float_type   auto abs    ( float_type         auto );
    constexpr float_type   auto floor  ( float_type         auto );
    constexpr float_type   auto ceil   ( float_type         auto );
    constexpr float_type   auto round  ( float_type         auto );
    constexpr float_type   auto log    ( float_type         auto, float_type   auto );
    constexpr float_type   auto log    ( float_type         auto, int_type     auto );
    constexpr float_type   auto log    ( int_type           auto, float_type   auto );
    constexpr float_type   auto log2   ( float_type         auto );
    constexpr float_type   auto log10  ( float_type         auto );
    constexpr float_type   auto ln     ( float_type         auto );
    constexpr float_type   auto mod    ( float_type         auto, float_type   auto );
    constexpr float_type   auto mod    ( float_type         auto, int_type     auto );
    constexpr float_type   auto mod    ( int_type           auto, float_type   auto );
    constexpr float_type   auto pow    ( float_type         auto, float_type   auto );
    constexpr float_type   auto pow    ( float_type         auto, int_type     auto );
    constexpr float_type   auto pow    ( int_type           auto, float_type   auto );
    constexpr float_type   auto sqrt   ( float_type         auto );
    constexpr float_type   auto exp    ( float_type         auto );
    constexpr angle_type   auto abs    ( angle_type         auto );
    constexpr float_type   auto sin    ( angle_type         auto );
    constexpr float_type   auto cos    ( angle_type         auto );
    constexpr float_type   auto tan    ( angle_type         auto );
    constexpr float_type   auto cot    ( angle_type         auto );
    constexpr float_type   auto sec    ( angle_type         auto );
    constexpr float_type   auto csc    ( angle_type         auto );
    constexpr angle_type   auto mod    ( angle_type         auto, angle_type   auto );
    constexpr angle_type   auto arcsin ( float_type         auto );
    constexpr angle_type   auto arccos ( float_type         auto );
    constexpr angle_type   auto arctan ( float_type         auto );
    constexpr angle_type   auto arccot ( float_type         auto );
    constexpr angle_type   auto arcsec ( float_type         auto );
    constexpr angle_type   auto arccsc ( float_type         auto );
    constexpr number_type  auto abs    ( complex_type       auto );
    constexpr complex_type auto floor  ( complex_float_type auto );
    constexpr complex_type auto ceil   ( complex_float_type auto );
    constexpr complex_type auto round  ( complex_float_type auto );
    constexpr number_type  auto norm   ( complex_type       auto );
    constexpr complex_type auto conj   ( complex_type       auto );
    constexpr complex_type auto log    ( complex_type       auto, complex_type auto );
    constexpr complex_type auto log    ( complex_type       auto, number_type  auto );
    constexpr complex_type auto log    ( number_type        auto, complex_type auto );
    constexpr complex_type auto log2   ( complex_type       auto );
    constexpr complex_type auto log10  ( complex_type       auto );
    constexpr complex_type auto ln     ( complex_type       auto );
    constexpr complex_type auto pow    ( complex_type       auto, complex_type auto );
    constexpr complex_type auto pow    ( complex_type       auto, number_type  auto );
    constexpr complex_type auto pow    ( number_type        auto, complex_type auto );
    constexpr complex_type auto sqrt   ( complex_type       auto );
    constexpr complex_type auto exp    ( complex_type       auto );
    constexpr complex_type auto exp2   ( complex_type       auto );
    constexpr number_type  auto abs    ( polar_type         auto );
    constexpr polar_type   auto conj   ( polar_type         auto );
    constexpr polar_type   auto log    ( polar_type         auto, polar_type   auto );
    constexpr polar_type   auto log    ( polar_type         auto, number_type  auto );
    constexpr polar_type   auto log    ( number_type        auto, polar_type   auto );
    constexpr polar_type   auto log2   ( polar_type         auto );
    constexpr polar_type   auto log10  ( polar_type         auto );
    constexpr polar_type   auto ln     ( polar_type         auto );
    constexpr number_type  auto norm   ( polar_type         auto );
    constexpr polar_type   auto pow    ( polar_type         auto, polar_type   auto );
    constexpr polar_type   auto pow    ( polar_type         auto, number_type  auto );
    constexpr polar_type   auto pow    ( number_type        auto, polar_type   auto );
    constexpr polar_type   auto sqrt   ( polar_type         auto );
    constexpr polar_type   auto exp    ( polar_type         auto );
    constexpr polar_type   auto exp2   ( polar_type         auto );

    /// Linear
    #define left_type                         decay<decltype(left)>
    #define left_value_type          typename decay<decltype(left)>::value_type
    #define left_iterate_type        typename decay<decltype(left)>::iterate_type
    #define right_type                        decay<decltype(right)>
    #define right_value_type         typename decay<decltype(right)>::value_type
    #define right_iterate_type       typename decay<decltype(right)>::iterate_type
    #define vector_type                       decay<decltype(vector)>
    #define vector_value_type        typename decay<decltype(vector)>::value_type
    #define vector_iterate_type      typename decay<decltype(vector)>::iterate_type
    #define matrix_type                       decay<decltype(matrix)>
    #define matrix_value_type        typename decay<decltype(matrix)>::value_type
    #define matrix_iterate_type      typename decay<decltype(matrix)>::iterate_type
    #define ndarray_type                      decay<decltype(ndarray)>
    #define ndarray_value_type       typename decay<decltype(ndarray)>::value_type
    #define ndarray_iterate_type     typename decay<decltype(ndarray)>::iterate_type

    constexpr array_type     auto   convolve        ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  1 ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ;
    constexpr array_type     auto   cross           ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  1 ) and   number_type<left_value_type>                                        and ( right.dimension() ==  1 ) and   number_type<right_value_type>; // Here complex-version is undefined.
    constexpr /*value_type*/ auto   dot             ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  1 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    constexpr array_type     auto   fft             ( const array_type auto&  vector )                              requires ( vector.dimension() ==  1 ) and ( number_type<vector_value_type> or complex_type<vector_value_type> );
    constexpr array_type     auto   ifft            ( const array_type auto&  vector )                              requires ( vector.dimension() ==  1 ) and ( number_type<vector_value_type> or complex_type<vector_value_type> );
    constexpr /*value_type*/ auto   operator *      ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() == -1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  1 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    constexpr array_type     auto   operator *      ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() == -1 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    constexpr array_type     auto   tensor          ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  1 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    constexpr array_type     auto   convolve        ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  2 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  2 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    constexpr array_type     auto   convolve        ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  2 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    constexpr array_type     auto   convolve        ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() == -1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  2 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    constexpr /*value_type*/ auto   det             ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    constexpr pair_type      auto   eigen           ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    constexpr array_type     auto   eigen_value     ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    constexpr array_type     auto   eigen_vector    ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    constexpr tuple_type     auto   evd             ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    constexpr array_type     auto   inverse         ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    constexpr tuple_type     auto   lu              ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    constexpr array_type     auto   operator *      ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  2 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  2 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    constexpr array_type     auto   operator *      ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() ==  2 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  1 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    constexpr array_type     auto   operator *      ( const array_type auto&  left, const array_type auto&  right ) requires ( left  .dimension() == -1 ) and ( number_type<left_value_type>   or complex_type<left_value_type>   ) and ( right.dimension() ==  2 ) and ( number_type<right_value_type> or complex_type<right_value_type> );
    constexpr pair_type      auto   qr              ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    constexpr int                   rank            ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    constexpr tuple_type     auto   singular        ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    constexpr array_type     auto   singular_value  ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    constexpr pair_type      auto   singular_vector ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    constexpr tuple_type     auto   svd             ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    constexpr /*value_type*/ auto   tr              ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );
    constexpr                bool   operator ==     ( const array_type auto&  left, const array_type auto&  right ) requires ( left.dimension() == right.dimension() ) and equalable_to <left_value_type,right_value_type>;
    constexpr                auto   operator <=>    ( const array_type auto&  left, const array_type auto&  right ) requires ( left.dimension() == right.dimension() ) and comparable_to<left_value_type,right_value_type>;
    constexpr array_type     auto   operator  +     (                               const array_type auto&  right ) requires requires { + std::declval<right_value_type>(); };
    constexpr array_type     auto   operator  -     (                               const array_type auto&  right ) requires requires { - std::declval<right_value_type>(); };
    constexpr array_type     auto   operator  +     ( const array_type auto&  left, const array_type auto&  right ) requires ( left.dimension() == right.dimension() ) and addable_to     <left_value_type,right_value_type>;
    constexpr array_type     auto   operator  -     ( const array_type auto&  left, const array_type auto&  right ) requires ( left.dimension() == right.dimension() ) and minusable_to   <left_value_type,right_value_type>;
    constexpr array_type     auto   operator  *     ( const array_type auto&  left, const            auto&  right ) requires ( not array_type<right_type> )            and multipliable_to<left_value_type,right_type>;
    constexpr array_type     auto   operator  *     ( const            auto&  left, const array_type auto&  right ) requires ( not array_type<left_type>  )            and multipliable_to<left_type,right_value_type>;
    constexpr array_type     auto   operator  /     ( const array_type auto&  left, const            auto&  right ) requires ( not array_type<right_type> )            and dividable_to   <left_value_type,right_type>;
    constexpr array_type     auto&  operator  +=    (       array_type auto&  left, const array_type auto&  right ) requires requires { left = left + right; };
    constexpr array_type     auto&& operator  +=    (       array_type auto&& left, const array_type auto&  right ) requires requires { left = left + right; };
    constexpr array_type     auto&  operator  -=    (       array_type auto&  left, const array_type auto&  right ) requires requires { left = left - right; };
    constexpr array_type     auto&& operator  -=    (       array_type auto&& left, const array_type auto&  right ) requires requires { left = left - right; };
    constexpr array_type     auto&  operator  *=    (       array_type auto&  left, const            auto&  right ) requires requires { left = left * right; };
    constexpr array_type     auto&& operator  *=    (       array_type auto&& left, const            auto&  right ) requires requires { left = left * right; };
    constexpr array_type     auto&  operator  /=    (       array_type auto&  left, const            auto&  right ) requires requires { left = left / right; };
    constexpr array_type     auto&& operator  /=    (       array_type auto&& left, const            auto&  right ) requires requires { left = left / right; };
    constexpr void                 swap             (       array_type auto&& left,       array_type auto&& right ) requires ( left.dimension() == right.dimension() ) and std::same_as<left_value_type,right_value_type> and std::swappable_with<left_value_type,right_value_type>;
    constexpr array_type     auto  transpose        ( const array_type auto&  ndarray )                             requires std::copyable<ndarray_value_type>;
    constexpr array_type     auto  hermitian        ( const array_type auto&  ndarray )                             requires complex_type<ndarray_value_type>;

    template < int_type auto version = 2 >
    constexpr array_type     auto  dct              ( const array_type auto&  vector )                              requires ( vector.dimension() ==  1 ) and   number_type<vector_value_type>;
    template < number_type auto num = 1 >
    constexpr /*value_type*/ auto  norm             ( const array_type auto&  vector )                              requires ( vector.dimension() ==  1 ) and ( number_type<vector_value_type> or complex_type<vector_value_type> );
    template < number_type auto num = 1 >
    constexpr /*value_type*/ auto  norm             ( const array_type auto&  matrix )                              requires ( matrix.dimension() ==  2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> );

    #undef left_type
    #undef left_value_type
    #undef left_iterate_type
    #undef right_type
    #undef right_value_type
    #undef right_iterate_type
    #undef vector_type
    #undef vector_value_type
    #undef vector_iterate_type
    #undef matrix_type
    #undef matrix_value_type
    #undef matrix_iterate_type
    #undef ndarray_type
    #undef ndarray_value_type
    #undef ndarray_iterate_type

    /// Random.concept
    template < class type > concept random_engine_type = requires { typename type::random_engine_tag; };

    /// Random.class
    template < int_type type, type, type, type >                                                    class linear_congruential_engine;
    template < int_type type, int, int, int, int, type, int, type, int, type, int, type, int,type > class mersenne_twister_engine;
    template < int_type type, int, int, int >                                                       class subtract_with_carry_engine;
    template < class engine_type, int, int >                                                        class discard_block_engine;
    template < class engine_type, int >                                                             class shuffle_order_engine;
    template < class engine_type, float_type >                                                      class floating_point_engine;
    using minstd_rand0 = linear_congruential_engine<int32_t,16807,0,2147483647>;
    using minstd_rand  = linear_congruential_engine<int32_t,48271,0,2147483647>;
    using mt19937      = mersenne_twister_engine   <int32_t,32,624,397,31,int32_t(0x9908b0df)        ,11,int32_t(0xffffffff)        ,7 ,int32_t(0x9d2c5680)        ,15,int32_t(0xefc60000)        ,18,int32_t(1812433253)         >;
    using mt19937_64   = mersenne_twister_engine   <int64_t,64,312,156,31,int64_t(0xb5026f5aa96619e9),29,int64_t(0x5555555555555555),17,int64_t(0x71d67fffeda60000),37,int64_t(0xfff7eee000000000),43,int64_t(6364136223846793005)>;
    using ranlux24     = discard_block_engine<subtract_with_carry_engine<int32_t,24,10,24>,223,23>;
    using ranlux48     = discard_block_engine<subtract_with_carry_engine<int64_t,48,5, 12>,389,11>;
    using knuth_b      = shuffle_order_engine<minstd_rand0,256>;

    /// Random.function
    constexpr int_type   auto random                   ( int_type   auto, int_type   auto );
    constexpr int_type   auto random                   ( int_type   auto, int_type   auto, random_engine_type auto& );
    constexpr char_type  auto random                   ( char_type  auto, char_type  auto );
    constexpr char_type  auto random                   ( char_type  auto, char_type  auto, random_engine_type auto& );
    constexpr            bool bernoulli_distribution   ( float_type auto );
    constexpr            bool bernoulli_distribution   ( float_type auto,                  random_engine_type auto& );
    constexpr int_type   auto binomial_distribution    ( int_type   auto, float_type auto );
    constexpr int_type   auto binomial_distribution    ( int_type   auto, float_type auto, random_engine_type auto& );
    constexpr float_type auto chi_squared_distribution ( float_type auto );
    constexpr float_type auto chi_squared_distribution ( float_type auto,                  random_engine_type auto& );
    constexpr float_type auto exponential_distribution ( float_type auto );
    constexpr float_type auto exponential_distribution ( float_type auto,                  random_engine_type auto& );
    constexpr float_type auto fisher_f_distribution    ( float_type auto, float_type auto );
    constexpr float_type auto fisher_f_distribution    ( float_type auto, float_type auto, random_engine_type auto& );
    constexpr float_type auto gamma_distribution       ( float_type auto, float_type auto );
    constexpr float_type auto gamma_distribution       ( float_type auto, float_type auto, random_engine_type auto& );
    constexpr            int  geometric_distribution   ( float_type auto );
    constexpr            int  geometric_distribution   ( float_type auto,                  random_engine_type auto& );
    constexpr float_type auto normal_distribution      ( float_type auto, float_type auto );
    constexpr float_type auto normal_distribution      ( float_type auto, float_type auto, random_engine_type auto& );
    constexpr            int  poisson_distribution     ( float_type auto );
    constexpr            int  poisson_distribution     ( float_type auto,                  random_engine_type auto& );
    constexpr float_type auto student_t_distribution   ( float_type auto );
    constexpr float_type auto student_t_distribution   ( float_type auto,                  random_engine_type auto& );
    constexpr float_type auto uniform_distribution     ( float_type auto, float_type auto );
    constexpr float_type auto uniform_distribution     ( float_type auto, float_type auto, random_engine_type auto& );

    /// Utility
    template < int_type   value_type > using int_to_float_type   = typename std::conditional<sizeof(value_type)<=16/8,float16_t,typename std::conditional<sizeof(value_type)==32/8,float32_t,typename std::conditional<sizeof(value_type)==64/8,float64_t,float128_t>::type>::type>::type;
    template < float_type value_type > using float_to_float_type = typename std::conditional<sizeof(value_type)<=16/8,float16_t,typename std::conditional<sizeof(value_type)==32/8,float32_t,typename std::conditional<sizeof(value_type)==64/8,float64_t,float128_t>::type>::type>::type;

    /// Global
    extern thread_local mt19937 random_engine;

    /// Include
    #include "numeric/numeric.hpp"
    #include "geometric/geometric.hpp"
    #include "arithmetic/arithmetic.hpp"
    #include "linear/linear.hpp"
    #include "random/random.hpp"
    #include "global.hpp"

    /// Literal
    namespace literals
    {
        constexpr degree  <double> operator ""deg ( unsigned long long num ) { return degree  <double>( num ); }
        constexpr degree  <double> operator ""deg ( long double        num ) { return degree  <double>( num ); }
        constexpr fraction<int>    operator ""f   ( unsigned long long num ) { return fraction<int>   ( num ); }
        constexpr complex <int>    operator ""i   ( unsigned long long num ) { return complex <int>   (0,num); }
        constexpr complex <double> operator ""i   ( long double        num ) { return complex <double>(0,num); }
        constexpr radian  <double> operator ""rad ( unsigned long long num ) { return radian  <double>( num ); }
        constexpr radian  <double> operator ""rad ( long double        num ) { return radian  <double>( num ); }
    }

}
