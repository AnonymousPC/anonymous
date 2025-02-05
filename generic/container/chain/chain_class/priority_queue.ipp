#pragma once

template < class type, class compare, class device >
constexpr int priority_queue<type,compare,device>::size ( ) const
{
    return base::size();
}

template < class type, class compare, class device >
constexpr bool priority_queue<type,compare,device>::empty ( ) const
{
    return base::empty();
}

template < class type, class compare, class device >
constexpr priority_queue<type,compare,device>::const_reference priority_queue<type,compare,device>::top ( ) const
{
    #if debug
        if ( empty() )
            throw value_error("cannot access top of an empty priority_queue");
    #endif
    return base::top();
}

template < class type, class compare, class device >
constexpr void priority_queue<type,compare,device>::push ( type val )
{
    base::push(std::move(val));
}

template < class type, class compare, class device >
constexpr type priority_queue<type,compare,device>::pop ( )
{
    #if debug
        if ( empty() )
            throw value_error("cannot pop from an empty priority_queue");
    #endif
    if constexpr ( requires { { base::pop() } -> convertible_to<type>; } )
        return base::pop();
    else
    {
        let poped = type(std::move(top()));
        base::pop();
        return poped;
    }
}