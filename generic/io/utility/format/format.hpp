#pragma once

template < >
class std::formatter<ap::color>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  ( parse_context& );
        template < class format_context > constexpr format_context::iterator format ( const ap::color&, format_context& ) const;

    private: // Auxiliary
        mutable ap::string parse_ctx = "";
};


template < >
class std::formatter<ap::time_point>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  ( parse_context& );
        template < class format_context > constexpr format_context::iterator format ( const ap::time_point&, format_context& ) const;

    private: // Auxiliary
        mutable ap::string parse_ctx = "";
};

template < >
class std::formatter<ap::duration>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  ( parse_context& );
        template < class format_context > constexpr format_context::iterator format ( const ap::duration&, format_context& ) const;

    private: // Auxiliary
        mutable ap::string parse_ctx = "";
};

#include "format.ipp"