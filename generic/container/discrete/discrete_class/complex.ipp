#pragma once

template < class type >
constexpr complex<type>::complex ( type r )
    extends std::complex<type>(std::move(r))
{

}

template < class type >
constexpr complex<type>::complex ( type r, type i )
    extends std::complex<type>(std::move(r), std::move(i))
{

}

template < class type >
constexpr type& complex<type>::real ( )
{
    struct raw_complex { type r; type i; };
    static_assert(layout_compatible_with<complex,raw_complex>);
    return reinterpret_cast<raw_complex&>(self).r;
}

template < class type >
constexpr const type& complex<type>::real ( ) const
{
    struct raw_complex { type r; type i; };
    static_assert(layout_compatible_with<complex,raw_complex>);
    return reinterpret_cast<const raw_complex&>(self).r;
}

template < class type >
constexpr type& complex<type>::imag ( )
{
    struct raw_complex { type r; type i; };
    static_assert(layout_compatible_with<complex,raw_complex>);
    return reinterpret_cast<raw_complex&>(self).i;
}

template < class type >
constexpr const type& complex<type>::imag ( ) const
{
    struct raw_complex { type r; type i; };
    static_assert(layout_compatible_with<complex,raw_complex>);
    return reinterpret_cast<const raw_complex&>(self).i;
}