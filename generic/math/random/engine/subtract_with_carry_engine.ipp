#pragma once

                          // +------------+---------------+---------------+
                          // | Class      | ranlux24_base | ranlux48_base |
template < int_type type, // +------------+---------------+---------------+
           int      w,    // | word_size  | 24            | 48            |
           int      s,    // | short_lag  | 10            | 5             |
           int      r     // | long_lag   | 24            | 12            |
         >                // +------------+---------------+---------------+
class subtract_with_carry_engine
{
    private: // Precondition
        static_assert ( w >= 1 and w <= std::numeric_limits<type>::digits );
        static_assert ( s >= 1 and s < r );

    private: // Data
        using unsigned_type = std::make_unsigned<type>::type;
        using data_type     = random_engine_algo::array<type,r>;
        data_type x = data_type();
        int       c = 0;
        int       k = 0; // Stores the pos in current twist.

    public: // Typedef
        using                       result_type  = type;
        constexpr static const type default_seed = 19780503;
        struct                      random_engine_tag { };

    public: // Core
        constexpr subtract_with_carry_engine ( type = default_seed );
        constexpr subtract_with_carry_engine& seed ( type );

    public: // Member
        constexpr        type operator() ( );
        constexpr static type min        ( );
        constexpr static type max        ( );
};




/// Class subtract_with_carry_engine

// Core

template < int_type type, int w, int s, int r >
constexpr subtract_with_carry_engine<type,w,s,r>::subtract_with_carry_engine ( type sd )
{
    seed ( sd );
}

template < int_type type, int w, int s, int r >
constexpr subtract_with_carry_engine<type,w,s,r>& subtract_with_carry_engine<type,w,s,r>::seed ( type sd )
{
    let e = linear_congruential_engine<int32_t,40014,0,2147483563> ( sd == 0 ? default_seed otherwise sd );
    let n = w / 32 + 1;
    for ( int i in range ( 0, r - 1 ) )
    {
        type sum    = 0;
        type factor = 1;

        for ( int j in range ( 0, n - 1 ) )
        {
            sum += e() * factor;

            if constexpr ( std::numeric_limits<type>::digits > 32 )
                if ( j < w / 32 )
                    factor <<= 32;
                else
                    factor = 0;
            else
                factor = 0;
        }

        x[i] = random_engine_algo::mod<1,0,type(1)<<w>() ( sum ); // = z0 * 1 mod 2^24 + z1 * 2^32 mod 2^24 + z2 * 2^64 mod 2^24
    }
    c = x[-1] == 0 ? 1 otherwise 0;

    return self;
}

// Member

template < int_type type, int w, int s, int r >
constexpr type subtract_with_carry_engine<type,w,s,r>::operator() ( )
{
    if ( k == r )
        k = 0;

    unsigned_type y = x[k-s] - x[k-r] - c;

    c = type(y) < 0 ? 1 otherwise 0;
    return x[k++] = random_engine_algo::mod<1,0,type(1)<<w>() ( y );
}

template < int_type type, int w, int s, int r >
constexpr type subtract_with_carry_engine<type,w,s,r>::min ( )
{
    return 0;
}

template < int_type type, int w, int s, int r >
constexpr type subtract_with_carry_engine<type,w,s,r>::max ( )
{
    return ( type(1) << w ) - 1;
}