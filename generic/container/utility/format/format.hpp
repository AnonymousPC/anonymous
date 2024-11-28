#pragma once

template < ap::array_type type >
    requires std::formattable<typename type::value_type,char>
class std::formatter<type>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  ( parse_context& );
        template < class format_context > constexpr format_context::iterator format ( const type&, format_context& ) const;

    private: // Auxiliary
        ap::string parse_ctx = "";
};




template < ap::string_type type >
class std::formatter<type,typename type::value_type>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  ( parse_context& );
        template < class format_context > constexpr format_context::iterator format ( const type&, format_context& ) const;

    private: // Auxiliary
        mutable std::formatter<std::basic_string_view<typename type::value_type>,typename type::value_type> std_fmt;
};

#include "format.ipp"