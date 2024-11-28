#pragma once

/// Class queue

// Interface

template < class type >
constexpr int queue<type>::size ( ) const
{
    return deque<type>::size();
}

template < class type >
constexpr bool queue<type>::empty ( ) const
{
    return deque<type>::empty();
}

template < class type >
constexpr type& queue<type>::front ( )
{
    return deque<type>::front();
}

template < class type >
constexpr const type& queue<type>::front ( ) const
{
    return deque<type>::front();
}

template < class type >
constexpr type& queue<type>::back ( )
{
    return deque<type>::back();
}

template < class type >
constexpr const type& queue<type>::back ( ) const
{
    return deque<type>::back();
}

template < class type >
constexpr void queue<type>::push ( type val )
{
    return deque<type>::push_back ( std::move ( val ) );
}

template < class type >
constexpr type queue<type>::pop ( )
{
    return deque<type>::pop_front();
}