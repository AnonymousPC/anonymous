#pragma once

template < class type >
class cpu::complex
    extends public std::complex<type>
{
    public: // Typedef
        using  value_type  = type;
        using  device_type = cpu;
        struct complex_tag { };

    public: // Core
        constexpr complex ( ) = default;
        constexpr complex ( type, type );
        
    public: // Member
        constexpr       type& real ( );
        constexpr const type& real ( ) const;
        constexpr       type& imag ( );
        constexpr const type& imag ( ) const;
};

#include "complex.ipp"