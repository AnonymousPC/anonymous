#pragma once

/// Declaration

                          // +---------------------------+------------+---------------------+
                          // | Class                     | mt19937    | mt19937_64          |
template < int_type type, // +---------------------------+------------+---------------------+
           int      w,    // | word_size                 | 32         | 64                  |
           int      n,    // | state_size                | 624        | 312                 |
           int      m,    // | shift_size                | 397        | 156                 |
           int      r,    // | mask_bits                 | 31         | 31                  |
           type     a,    // | xor_mask                  | 0x9908b0df | 0xb5026f5aa96619e9  |
           int      u,    // | tempering_u               | 11         | 29                  |
           type     d,    // | tempering_d               | 0xffffffff | 0x5555555555555555  |
           int      s,    // | tempering_s               | 7          | 17                  |
           type     b,    // | tempering_b               | 0x9d2c5680 | 0x71d67fffeda60000  |
           int      t,    // | tempering_t               | 15         | 37                  |
           type     c,    // | tempering_c               | 0xefc60000 | 0xfff7eee000000000  |
           int      l,    // | tempering_l               | 18         | 43                  |
           type     f     // | initialization_multiplier | 1812433253 | 6364136223846793005 |
         >                // +---------------------------+------------+---------------------+
class mersenne_twister_engine
{
    private: // Precondition
        static_assert ( m >= 1 and
                        m <= n );
        static_assert ( w >= 3 and
                        w >= r and
                        w >= u and
                        w >= s and
                        w >= t and
                        w >= l and
                        w <= std::numeric_limits<type>::digits + 1 );

    private: // Data
        using unsigned_type = std::make_unsigned<type>::type;
        using data_type     = random_engine_algo::array<unsigned_type,n>;
        data_type x = data_type();
        int       k = 0;          // Stores the pos in current twist.

    public: // Typedef
        using                       result_type  = type;
        constexpr static const type default_seed = 5489;
        struct                      random_engine_tag { };

    public: // Core
        constexpr mersenne_twister_engine ( type = default_seed );
        constexpr mersenne_twister_engine& seed ( type );

    public: // Member
        constexpr        type operator() ( );
        constexpr static type min        ( );
        constexpr static type max        ( );

    private: // Algo
        constexpr void transform ( );
        constexpr type generate  ( int );
};



/// Class mersenne_twister_engine

// Core

template < int_type type, int w, int n, int m, int r, type a, int u, type d, int s, type b, int t, type c, int l, type f >
constexpr mersenne_twister_engine<type,w,n,m,r,a,u,d,s,b,t,c,l,f>::mersenne_twister_engine ( type sd )
{
    seed ( sd );
}

template < int_type type, int w, int n, int m, int r, type a, int u, type d, int s, type b, int t, type c, int l, type f >
constexpr mersenne_twister_engine<type,w,n,m,r,a,u,d,s,b,t,c,l,f>& mersenne_twister_engine<type,w,n,m,r,a,u,d,s,b,t,c,l,f>::seed ( type sd )
{
    x[0] = sd;
    for ( int i in range ( 1, n - 1 ) )
        x[i] = f * ( x[i-1] xor ( x[i-1] >> ( w - 2 ) ) ) + i % n;
    k = n;
    return self;
}

// Member

template < int_type type, int w, int n, int m, int r, type a, int u, type d, int s, type b, int t, type c, int l, type f >
constexpr type mersenne_twister_engine<type,w,n,m,r,a,u,d,s,b,t,c,l,f>::operator() ( )
{
    if ( k == n )
    {
        transform();
        k = 0;
    }

    return generate ( k++ );
}

template < int_type type, int w, int n, int m, int r, type a, int u, type d, int s, type b, int t, type c, int l, type f >
constexpr type mersenne_twister_engine<type,w,n,m,r,a,u,d,s,b,t,c,l,f>::min ( )
{
    return 0;
}

template < int_type type, int w, int n, int m, int r, type a, int u, type d, int s, type b, int t, type c, int l, type f >
constexpr type mersenne_twister_engine<type,w,n,m,r,a,u,d,s,b,t,c,l,f>::max ( )
{
    return std::numeric_limits<type>::max();
}

// Algo

template < int_type type, int w, int n, int m, int r, type a, int u, type d, int s, type b, int t, type c, int l, type f >
constexpr void mersenne_twister_engine<type,w,n,m,r,a,u,d,s,b,t,c,l,f>::transform ( )
{
    constexpr unsigned_type upper_mask = ~(unsigned_type(0)) << r;
    constexpr unsigned_type lower_mask = ~upper_mask;

    for ( int i in range ( 0, n - 1 ) )
    {
        unsigned_type y = ( x[i] & upper_mask ) | ( x[i+1] & lower_mask );
        x[i] = x[i+m] ^ ( y >> 1 ) ^ ( y & 1 ? a otherwise 0 );
    }
}

template < int_type type, int w, int n, int m, int r, type a, int u, type d, int s, type b, int t, type c, int l, type f >
constexpr type mersenne_twister_engine<type,w,n,m,r,a,u,d,s,b,t,c,l,f>::generate ( int i )
{
    let z = x[i];

    z ^= ( z >> u ) & d;
    z ^= ( z << s ) & b;
    z ^= ( z << t ) & c;
    z ^= ( z >> l );

    return abs ( static_cast<type>(z) );
}