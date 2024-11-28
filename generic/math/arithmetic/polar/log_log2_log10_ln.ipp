#pragma once

constexpr polar_type auto log ( polar_type auto a, polar_type auto b )
{
    using type = common_type<decltype(a),decltype(b)>;
    return type ( log ( complex<typename type::value_type>(a), complex<typename type::value_type>(b) ) );
}

constexpr polar_type auto log ( polar_type auto a, number_type auto b )
{
    return log ( a, polar(b) );
}

constexpr polar_type auto log ( number_type auto a, polar_type auto b )
{
    return log ( polar(a), b );
}

constexpr polar_type auto log2 ( polar_type auto a )
{
    return decltype(a) ( log2 ( complex<typename decltype(a)::value_type>(a) ) );
}

constexpr polar_type auto log10 ( polar_type auto a )
{
    return decltype(a) ( log10 ( complex<typename decltype(a)::value_type>(a) ) );
}

constexpr polar_type auto ln ( polar_type auto a )
{
    return decltype(a) ( ln ( complex<typename decltype(a)::value_type>(a) ) );
}