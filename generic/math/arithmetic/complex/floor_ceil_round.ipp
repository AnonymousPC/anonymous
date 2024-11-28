#pragma once

constexpr complex_type auto floor ( complex_float_type auto a )
{
    return complex ( floor(a.real()), floor(a.imag()) );
}

constexpr complex_type auto ceil ( complex_float_type auto a )
{
    return complex ( ceil(a.real()), ceil(a.imag()) );
}

constexpr complex_type auto round ( complex_float_type auto a )
{
    return complex ( round(a.real()), round(a.imag()) );
}