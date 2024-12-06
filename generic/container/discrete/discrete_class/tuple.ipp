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
template < int index >
constexpr decltype(auto) tuple<type>::value ( )
    requires ( index == 1 or index == -1 )
{
    return static_cast<type&> ( first );
}

template < class type >
template < int index >
constexpr decltype(auto) tuple<type>::value ( ) const
    requires ( index == 1 or index == -1 )
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
template < int index >
constexpr decltype(auto) tuple<type,types...>::value ( )
    requires ( ( index >= -size() and index <= -1 ) or ( index >= 1 and index <= size() ) )
{
    if constexpr ( index == 1 or index == -size() )
        return static_cast<type&> ( first );

    else if constexpr ( index > 0 )
        return other.template value<index-1>();

    else
        return other.template value<index>();
}

template < class type, class... types >
template < int index >
constexpr decltype(auto) tuple<type,types...>::value ( ) const
    requires ( ( index >= -size() and index <= -1 ) or ( index >= 1 and index <= size() ) )
{
    if constexpr ( index == 1 or index == -size() )
        return static_cast<const type&> ( first );

    else if constexpr ( index > 0 )
        return other.template value<index-1>();

    else
        return other.template value<index>();
}