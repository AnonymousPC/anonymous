#pragma once

} // Out from namespace anonymous.

/// Array

template < anonymous::array_type type >
    requires std::formattable<typename type::value_type,char>
class std::formatter<type>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  ( parse_context& );
        template < class format_context > constexpr format_context::iterator format ( const type&, format_context& ) const;

    private: // Data
        anonymous::string parse_ctx = "";
};

template < anonymous::string_type type >
class std::formatter<type,typename type::value_type>
    extends public std::formatter<std::basic_string_view<typename type::value_type>,typename type::value_type>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  ( parse_context& );
        template < class format_context > constexpr format_context::iterator format ( const type&, format_context& ) const;
};

#include "format.ipp"

namespace anonymous { // Back into namespace anonymous.