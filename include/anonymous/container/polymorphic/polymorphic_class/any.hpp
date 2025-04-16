#pragma once

class any
    extends public std::any
{
    private: // Typedef
        using base = std::any;
    
    public: // Core
        constexpr any ( ) = default;
        constexpr any ( auto );

    public: // Member
                                      constexpr       bool            empty ( ) const;
                                      constexpr const std::type_info& type  ( ) const;
        template < class value_type > constexpr       value_type&     value ( );
        template < class value_type > constexpr const value_type&     value ( ) const;
};

#include "any.cpp"