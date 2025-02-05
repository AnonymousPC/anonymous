#pragma once

template < class... types >
class cpu::tuple
    extends public std::tuple<types...>
{
    public: // Typedef
        using  device_type = cpu;
        struct tuple_tag { };

    public: // Core
        constexpr tuple ( );
        constexpr tuple ( types... );

    public: // Member
        constexpr static int size ( );
        template < int index > constexpr       auto& value ( )       requires ( index >= -size() and index <= -1 ) or ( index >= 1 and index <= size() );
        template < int index > constexpr const auto& value ( ) const requires ( index >= -size() and index <= -1 ) or ( index >= 1 and index <= size() );

    public: // Typedef
        template < int index > requires ( ( index >= -size() and index <= -1 ) or ( index >= 1 and index <= size() ) ) using value_type = index_type_of<index,types...>;
};

#include "tuple.ipp"