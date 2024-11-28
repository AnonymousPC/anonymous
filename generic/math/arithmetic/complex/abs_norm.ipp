#pragma once

constexpr number_type auto abs ( complex_type auto a )
{
    return sqrt ( a.real() * a.real() + a.imag() * a.imag() );
}

constexpr number_type auto norm ( complex_type auto a )
{
    return sqrt ( a.real() * a.real() + a.imag() * a.imag() );
}