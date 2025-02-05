#pragma once

constexpr complex_type auto log ( complex_type auto a, complex_type auto b )
{
    using type = common_type<typename decltype(a)::value_type,typename decltype(b)::value_type>;

    let c = std::complex<type> ( a.real(), a.imag() );
    let d = std::complex<type> ( b.real(), b.imag() );
    let e = std::log(d) / std::log(c);

    return complex<type>(e.real(), e.imag());
}

constexpr complex_type auto log ( complex_type auto a, number_type auto b )
{
    return log ( a, complex(b) );
}

constexpr complex_type auto log ( number_type auto a, complex_type auto b )
{
    return log ( complex(a), b );
}

constexpr complex_type auto log2 ( complex_type auto a )
{
    return log ( 2, a ); // Uhh, std::log2 is not overloaded for std::complex.
}

constexpr complex_type auto log10 ( complex_type auto a )
{
    let b = std::log10 ( std::complex(a.real(), a.imag()) );
    return complex ( b.real(), b.imag() );
}

constexpr complex_type auto ln ( complex_type auto a )
{
    let b = std::log ( std::complex(a.real(), a.imag()) );
    return complex ( b.real(), b.imag() );
}