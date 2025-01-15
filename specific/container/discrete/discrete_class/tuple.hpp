#pragma once

/// Declaration

template < class... types >
class tuple
    extends public std::tuple<types...>
{
    public: // Traits
        constexpr static int size ( );

    public: // Typedef
        template < int index > requires ( ( index >= -size() and index <= -1 ) or ( index >= 1 and index <= size() ) )
        using value_type = index_type_of<index,types...>;
        struct tuple_tag { };

    public: // Core
        constexpr tuple ( )                                                      requires ( default_initializable<remove_cv<types>> and ... ) = default;  // Remove_cv is essential, as default_initializable<const int> == false (requires "new const int()").
        constexpr tuple ( types... );

    public: // Conversion
        template < class... types2 > constexpr tuple ( const tuple<types2...>& ) requires ( convertible_to<types2,types>     and ... ) but ( ( not same_as<types,types2>        ) or ... );
        template < class... types2 > constexpr tuple ( const tuple<types2...>& ) requires ( constructible_from<types,types2> and ... ) but ( ( not convertible_to<types2,types> ) or ... );

    public: // Member
        template < int index > constexpr decltype(auto) value ( )       requires ( index >= -size() and index <= -1 ) or ( index >= 1 and index <= size() );
        template < int index > constexpr decltype(auto) value ( ) const requires ( index >= -size() and index <= -1 ) or ( index >= 1 and index <= size() );
};

#include "tuple.ipp"