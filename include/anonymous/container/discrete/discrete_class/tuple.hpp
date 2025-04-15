#pragma once

template < class... types >
class tuple
    extends public std::tuple<types...>
{
    public: // Typedef
        template < int index > requires ( ( index >= -int(sizeof...(types)) and index <= -1 ) or ( index >= 1 and index <= int(sizeof...(types)) ) )
        using  value_type  = index_type_of<index,types...>;
        struct tuple_tag { };
    
    public: // Core
        constexpr tuple ( ) = default;
        constexpr tuple ( types... ) requires ( sizeof...(types) >= 1 );

    public: // Conversion
        template < class... types2 > constexpr tuple ( const tuple<types2...>& ) requires ( convertible_to<types2,types> and ... );

    public: // Member
        template < int index > constexpr       auto& value ( )       requires ( index >= -int(sizeof...(types)) and index <= -1 ) or ( index >= 1 and index <= int(sizeof...(types)) );
        template < int index > constexpr const auto& value ( ) const requires ( index >= -int(sizeof...(types)) and index <= -1 ) or ( index >= 1 and index <= int(sizeof...(types)) );
};

#include "tuple.ipp"