#pragma once


/// Tuple with size() == 0

// Core

constexpr int tuple<>::size ( )
{
    return 0;
}



/// Tuple with size() == 1
// Core

template < class type >
constexpr tuple<type>::tuple ( type init )
    extends first ( std::forward<decltype(init)>(init) )
{

}

template < class type >
constexpr int tuple<type>::size ( )
{
    return 1;
}

template < class type >
constexpr decltype(auto) tuple<type>::operator [] ( auto index )
    requires ( index.value == 1 or index.value == -1 )
{
    return static_cast<type&> ( first );
}

template < class type >
constexpr decltype(auto) tuple<type>::operator [] ( auto index ) const
    requires ( index.value == 1 or index.value == -1 )
{
    return static_cast<const type&> ( first );
}




/// Tuple with size() >= 2

// Core

template < class type, class... types >
constexpr tuple<type,types...>::tuple ( type init, types... args )
    extends first ( std::forward<decltype(init)>(init) ),
            other ( std::forward<decltype(args)>(args)... )
{

}

template < class type, class... types >
constexpr int tuple<type,types...>::size ( )
{
    return sizeof...(types) + 1;
}

template < class type, class... types >
constexpr decltype(auto) tuple<type,types...>::operator [] ( auto index )
    requires ( ( index.value >= -size() and index.value <= -1 ) or ( index.value >= 1 and index.value <= size() ) )
{
    if constexpr ( index.value == 1 or index.value == -size() )
        return static_cast<type&> ( first );

    else if constexpr ( index.value > 0 )
        return other [ constexpr_index<index.value-1> () ];

    else
        return other [ constexpr_index<index.value>   () ];
}

template < class type, class... types >
constexpr decltype(auto) tuple<type,types...>::operator [] ( auto index ) const
    requires ( ( index.value >= -size() and index.value <= -1 ) or ( index.value >= 1 and index.value <= size() ) )
{
    if constexpr ( index.value == 1 or index.value == -size() )
        return static_cast<const type&> ( first );

    else if constexpr ( index.value > 0 )
        return other [ constexpr_index<index.value-1> () ];

    else
        return other [ constexpr_index<index.value>   () ];
}