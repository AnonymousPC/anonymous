#pragma once

class random_engine_algo
{
    public:
        template < class, int >                                  class array;
        template < int_type auto, int_type auto, int_type auto > class mod;
};




/// Class random_engine_algo::array

template < class type, int len >
class random_engine_algo::array
{
    private: // Data
        type data[len] = {};

    public: // Core
        constexpr array ( ) = default;

    public: // Member
        constexpr       type& operator [] ( int );
        constexpr const type& operator [] ( int ) const;

    private: // Auxiliary
        constexpr static int transform ( int );
};


// Member

template < class type, int len >
constexpr type& random_engine_algo::array<type,len>::operator [] ( int pos )
{
    return data[transform(pos)];
}

template < class type, int len >
constexpr const type& random_engine_algo::array<type,len>::operator [] ( int pos ) const
{
    return data[transform(pos)];
}

// Auxiliary

template < class type, int len >
constexpr int random_engine_algo::array<type,len>::transform ( int pos )
{
    return pos >= 0 ? pos % len otherwise ( pos + 1 ) % len + len - 1;
}




/// Class random_engine_algo::mod

template < int_type auto a, int_type auto c, int_type auto m >
class random_engine_algo::mod
{
    public: // Interface
        constexpr static auto operator() ( auto );
};

// Interface

template < int_type auto a, int_type auto c, int_type auto m >
constexpr auto random_engine_algo::mod<a,c,m>::operator() ( auto x )
{
    // For m == 2^n or m == 0, integer overflow is safe.
    // If a * ( m - 1 ) + c fits in decltype(x), there is also no overflow.
    if constexpr ( ( m & ( m - 1 ) ) == 0 or ( std::numeric_limits<decltype(x)>::max() - c ) / a >= m - 1 )
        return static_cast<decltype(x)> ( ( a * x + c ) % m );

    // Use Schrage's algorithm to avoid integer overflow.
    else
    {
        static const auto q = m / a;
        static const auto r = m % a;

        let t1 = a * ( x % q );
        let t2 = r * ( x / q );

        x = t1 > t2 ? t1 - t2 otherwise m - t2 + t1;

        if constexpr ( c != 0 )
        {
            let d = m - x;
            x = d > c ? x + c otherwise c - d;
        }

        return x;
    }
}