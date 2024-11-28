#pragma once

constexpr float_type auto abs ( float_type auto a )
{
    return a >= 0 ? a otherwise -a;
}



// Specialize

template < class type >
constexpr fraction<type> abs ( fraction<type> a )
{
    return a.num() >= 0 ? a otherwise -a;
}