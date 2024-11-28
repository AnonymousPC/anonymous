#pragma once

namespace aux
{
    constexpr auto int_pow  ( std::integral auto, std::integral auto );
    constexpr auto int_sqrt ( std::integral auto );
}


constexpr int_type auto pow ( int_type auto a, int_type auto b )
{
    if constexpr ( std::integral<decltype(a)> and std::integral<decltype(b)> )
        return aux::int_pow ( a, b );

    else if constexpr ( not std::same_as<decltype(a),decltype(b)> )
    {
        using type = common_type<decltype(a),decltype(b)>;
        return pow ( type(a), type(b) );
    }

    else
        static_assert ( false, "unsolvable, try to overload this function to dedicated int-type" );
}

constexpr int_type auto sqrt ( int_type auto a )
{
    if ( a < 0 )
        throw math_error("sqrt({}) is out of domain: sqrt(x) requires x >= 0", a);

    if constexpr ( std::integral<decltype(a)> )
        return aux::int_sqrt ( a );

    else
        static_assert ( false, "unsolvable, try to overload this function to dedicated int-type" );
}

constexpr int_type auto exp ( int_type auto a )
{
    using constants::e;
    return static_cast<decltype(a)> ( pow ( e, a ) );
}

constexpr int_type auto exp2 ( int_type auto a )
{
    return pow ( a, 2 );
}





// Auxiliary

constexpr auto aux::int_pow ( std::integral auto a, std::integral auto b )
{
    if ( b < 0 )
        return 0;

    using type = common_type<decltype(a),decltype(b)>;

    type p = 1;
    while ( b > 0 )
    {
        if ( b % 2 == 1 )
            p *= a;
        a *= a;
        b /= 2;
    }

    return p;
}

constexpr auto aux::int_sqrt ( std::integral auto a )
{
    using type = decltype(a);

    if ( a == 0 )
        return 0;

    type m = 1;
    type n = a;
    type p = ( m + n ) / 2;

    while ( m < n - 1 )
    {
        type t = p * p;
        if ( a == t )
            return p;
        else if ( a < t )
            n = p - 1;
        else if ( a > t )
            m = p;

        p = ( m + n ) / 2;
    }

    return ( m == n or a < n * n ) ? m otherwise n;
}