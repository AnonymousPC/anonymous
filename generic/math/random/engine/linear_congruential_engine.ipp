#pragma once

/// Declaration

                          // +------------+--------------+-------------+
                          // | Class      | minstd_rand0 | minstd_rand |
template < int_type type, // +------------+--------------+-------------+
           type     a,    // | multiplier | 16807        | 48271       |
           type     c,    // | increment  | 0            | 0           |
           type     m     // | modulus    | 2147483647   | 2147483647  |
         >                // +------------+--------------+-------------+
class linear_congruential_engine
{
    private: // Precondition
        static_assert ( m != 0 and a < m and c < m );

    private: // Data
        using data_type = int;
        data_type x = 0;

    public: // Typedef
        using                       result_type  = type;
        constexpr static const type default_seed = 1;
        struct                      random_engine_tag { };

    public: // Core
        constexpr linear_congruential_engine ( type = default_seed );
        constexpr linear_congruential_engine& seed ( type );

    public: // Member
        constexpr        type operator() ( );
        constexpr static type min        ( );
        constexpr static type max        ( );
};




/// Class linear_congruential_engine

// Core

template < int_type type, type a, type c, type m >
constexpr linear_congruential_engine<type,a,c,m>::linear_congruential_engine ( type sd )
{
    seed ( sd );
}

template < int_type type, type a, type c, type m >
constexpr linear_congruential_engine<type,a,c,m>& linear_congruential_engine<type,a,c,m>::seed ( type sd )
{
    x = ( c % m == 0 and sd % m == 0 ) ? 1 otherwise sd % m;
    return self;
}

// Member

template < int_type type, type a, type c, type m >
constexpr type linear_congruential_engine<type,a,c,m>::operator() ( )
{
    return x = random_engine_algo::mod<a,c,m>() ( x ); // x = ( a * x + c ) mod m.
}

template < int_type type, type a, type c, type m >
constexpr type linear_congruential_engine<type,a,c,m>::min ( )
{
    if constexpr ( c == 0 )
        return 1;
    else
        return 0;
}

template < int_type type, type a, type c, type m >
constexpr type linear_congruential_engine<type,a,c,m>::max ( )
{
    return m - 1;
}