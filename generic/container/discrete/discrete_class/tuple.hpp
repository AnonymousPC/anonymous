#pragma once

/// Declaration

template < class... types >
class tuple;



/// Tuple with size() == 0

template < >
class tuple<>
{
    public: // Core
        constexpr tuple ( ) = default;
        constexpr static int size ( );
};



/// Tuple with size() == 1

template < class type >
class tuple<type>
{
    public: // Data
        type first = type();

    public: // Core
        constexpr tuple ( )                                       requires std::default_initializable<type> = default;
        constexpr tuple ( type );
        constexpr static int size ( );
        constexpr decltype(auto) operator [] ( auto index )       requires ( index.value == 1 or index.value == -1 );
        constexpr decltype(auto) operator [] ( auto index ) const requires ( index.value == 1 or index.value == -1 );

    public: // Typedef ( declared after size() )
        template < int index > requires ( index == 1 or index == -1 ) using value_type = type;
        struct tuple_tag { };
};



/// Tuple with size() >= 2

template < class type, class... types >
class tuple<type,types...>
{
    private: // Data
        type            first = type();
        tuple<types...> other = tuple<types...>();

    public: // Core
        constexpr tuple ( )                                       requires ( std::default_initializable<type> and ... and std::default_initializable<types> ) = default;
        constexpr tuple ( type, types... );
        constexpr static int size ( );
        constexpr decltype(auto) operator [] ( auto index )       requires ( ( index.value >= -size() and index.value <= -1 ) or ( index.value >= 1 and index.value <= size() ) );
        constexpr decltype(auto) operator [] ( auto index ) const requires ( ( index.value >= -size() and index.value <= -1 ) or ( index.value >= 1 and index.value <= size() ) );

    public: // Typedef ( declared after size() )
        template < int index > requires ( ( index >= - size() and index <= -1 ) or ( index >= 1 and index <= size() ) ) using value_type = index_type_of<index,type,types...>;
        struct tuple_tag { };
};

/// Template deduction

template < class    type  > tuple ( type )            -> tuple<type>     requires ( not tuple_type<type> );
template < class... types > tuple ( tuple<types...> ) -> tuple<types...>;
template < class... types > tuple ( types... )        -> tuple<types...> requires ( sizeof...(types) >= 2 );



#include "tuple.ipp"