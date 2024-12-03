#pragma once

namespace aux
{
    constexpr auto int_log ( std::integral auto, std::integral auto );
}



constexpr int_type auto log ( int_type auto a, int_type auto b )
{
    if ( a <= 0 or a == 1 or b <= 0 )
        throw math_error("log({}, {}) is out of domain: log(x, y) requires x > 0, x != 1, y > 0", a, b);

    if constexpr ( std::integral<decltype(a)> and std::integral<decltype(b)> )
        return aux::int_log ( a, b );

    else if constexpr ( not std::same_as<decltype(a),decltype(b)> )
    {
        using type = common_type<decltype(a),decltype(b)>;
        return log ( type(a), type(b) );
    }

    else
        static_assert ( false, "unsolvable, try to overload this function to dedicated int-type" );
}

constexpr int_type auto log2 ( int_type auto a )
{
    return log ( 2, a );
}

constexpr int_type auto log10 ( int_type auto a )
{
    return log ( 10, a );
}

constexpr int_type auto ln ( int_type auto a )
{
    using constants::e;
    return log ( e, a );
}









// Auxiliary

constexpr auto aux::int_log ( std::integral auto a, std::integral auto b )
{
    // Assume a and b in domain.

    using type = common_type<decltype(a),decltype(b)>;

    if ( a == 2 )
    {
        type t = 0;
        while ( b != 0 )
        {
            b /= 2;
            t++;
        }

        return t - 1;
    }

    else
    {
        if ( a > b )
            return 0;

        type m = 1;
        type n = a;
        type p = ( m + n ) / 2;

        while ( m < n - 1 )
        {
            type t = pow ( a, p );
            if ( b == t )
                return p;
            else if ( b < t )
                n = p - 1;
            else if ( b > t )
                m = p;

            p = ( m + n ) / 2;
        }

        return ( m == n or b < pow ( a, n ) ) ? m otherwise n;
    }
}