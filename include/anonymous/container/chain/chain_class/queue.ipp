#pragma once

template < class type, class device >
constexpr int queue<type,device>::size ( ) const
{
    return base::size();
}

template < class type, class device >
constexpr bool queue<type,device>::empty ( ) const
{
    return base::empty();
}

template < class type, class device >
constexpr queue<type,device>::reference queue<type,device>::front ( )
{
    #ifdef debug
        if ( empty() )
            throw value_error("cannot access front of an empty queue");
    #endif
    return base::front();
}

template < class type, class device >
constexpr queue<type,device>::const_reference queue<type,device>::front ( ) const
{
    #ifdef debug
        if ( empty() )
            throw value_error("cannot access front of an empty queue");
    #endif
    return base::front();
}

template < class type, class device >
constexpr queue<type,device>::reference queue<type,device>::back ( )
{
    #ifdef debug
        if ( empty() )
            throw value_error("cannot access back of an empty queue");
    #endif
    return base::back();
}

template < class type, class device >
constexpr queue<type,device>::const_reference queue<type,device>::back ( ) const
{
    #ifdef debug
        if ( empty() )
            throw value_error("cannot access back of an empty queue");
    #endif
    return base::back();
}

template < class type, class device >
constexpr void queue<type,device>::push ( type val )
{
    return base::push(std::move(val));
}

template < class type, class device >
constexpr type queue<type,device>::pop ( )
{
    #ifdef debug
        if ( empty() )
            throw value_error("cannot pop from an empty queue");
    #endif
    if constexpr ( requires { { base::pop() } -> convertible_to<type>; } )
        return base::pop();
    else
    {
        let poped = type(std::move(front()));
        base::pop();
        return poped;
    }
}