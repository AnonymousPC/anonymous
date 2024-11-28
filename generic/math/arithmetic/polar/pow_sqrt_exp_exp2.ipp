#pragma once

constexpr polar_type auto pow ( polar_type auto a, polar_type auto b )
{
    using type = common_type<decltype(a),decltype(b)>;
    return type ( pow ( complex<typename type::value_type>(a), complex<typename type::value_type>(b) ) );
}

constexpr polar_type auto pow ( polar_type auto a, number_type auto b )
{
    return pow ( a, polar(b) );
}

constexpr polar_type auto pow ( number_type auto a, polar_type auto b )
{
    return pow ( polar(a), b );
}

constexpr polar_type auto sqrt ( polar_type auto a )
{
    return decltype(a) ( sqrt ( complex<typename decltype(a)::value_type>(a) ) );
}

constexpr polar_type auto exp ( polar_type auto a )
{
    return decltype(a) ( exp ( complex<typename decltype(a)::value_type>(a) ) );
}

constexpr polar_type auto exp2 ( polar_type auto a )
{
    return decltype(a) ( exp2 ( complex<typename decltype(a)::value_type>(a) ) );
}