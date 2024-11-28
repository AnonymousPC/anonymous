#pragma once

constexpr complex_type auto pow ( complex_type auto a, complex_type auto b )
{
    using type = std::common_type<typename decltype(a)::value_type,typename decltype(b)::value_type>::type;

    let c = std::complex<type> ( a.real(), a.imag() );
    let d = std::complex<type> ( b.real(), b.imag() );
    let e = std::pow ( c, d );

    return complex<type> ( e.real(), e.imag() );
}

constexpr complex_type auto pow ( complex_type auto a, number_type auto b )
{
    return pow ( a, complex(b) );
}

constexpr complex_type auto pow ( number_type auto a, complex_type auto b )
{
    return pow ( complex(a), b );
}

constexpr complex_type auto sqrt ( complex_type auto a )
{
    let b = std::sqrt ( std::complex(a.real(), a.imag()) );
    return complex ( b.real(), b.imag() );
}

constexpr complex_type auto exp ( complex_type auto a )
{
    let b = std::exp ( std::complex(a.real(), a.imag()) );
    return complex ( b.real(), b.imag() );
}

constexpr complex_type auto exp2 ( complex_type auto a )
{
    return pow ( a, 2 ); // Uhh, std::exp2 is not overloaded for std::complex.
}