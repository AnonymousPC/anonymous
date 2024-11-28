#pragma once

constexpr complex_type auto conj ( complex_type auto a )
{
    return complex ( a.real(), - a.imag() );
}