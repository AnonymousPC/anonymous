#pragma once

template < class type >
constexpr cpu::complex<type>::complex ( type r, type i )
    extends std::complex<type>(std::move(r), std::move(i))
{

}

template < class type >
constexpr type& cpu::complex<type>::real ( )
{
    struct raw_complex { type r; type i; };
    static_assert(layout_compatible_with<complex,raw_complex>);
    return reinterpret_cast<raw_complex&>(self).r;
}

template < class type >
constexpr const type& cpu::complex<type>::real ( ) const
{
    struct raw_complex { type r; type i; };
    static_assert(layout_compatible_with<complex,raw_complex>);
    return reinterpret_cast<const raw_complex&>(self).r;
}

template < class type >
constexpr type& cpu::complex<type>::imag ( )
{
    struct raw_complex { type r; type i; };
    static_assert(layout_compatible_with<complex,raw_complex>);
    return reinterpret_cast<raw_complex&>(self).i;
}

template < class type >
constexpr const type& cpu::complex<type>::imag ( ) const
{
    struct raw_complex { type r; type i; };
    static_assert(layout_compatible_with<complex,raw_complex>);
    return reinterpret_cast<const raw_complex&>(self).i;
}