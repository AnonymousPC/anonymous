#pragma once

/// Class stack

// Interface

template < class type >
constexpr int stack<type>::size ( ) const
{
    return deque<type>::size();
}

template < class type >
constexpr bool stack<type>::empty ( ) const
{
    return deque<type>::empty();
}

template < class type >
constexpr type& stack<type>::top ( )
{
    return deque<type>::back();
}

template < class type >
constexpr const type& stack<type>::top ( ) const
{
    return deque<type>::back();
}

template < class type >
constexpr void stack<type>::push ( type val )
{
    return deque<type>::push_back ( std::move ( val ) );
}

template < class type >
constexpr type stack<type>::pop ( )
{
    return deque<type>::pop_back();
}