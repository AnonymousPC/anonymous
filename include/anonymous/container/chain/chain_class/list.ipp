#pragma once

template < class type, class device >
constexpr int list<type,device>::size ( ) const
{
    return base::size();
}

template < class type, class device >
constexpr bool list<type,device>::empty ( ) const
{
    return base::empty();
}

template < class type, class device >
constexpr list<type,device>::iterator list<type,device>::begin ( )
{
    return base::begin();
}

template < class type, class device >
constexpr list<type,device>::const_iterator list<type,device>::begin ( ) const
{
    return base::begin();
}

template < class type, class device >
constexpr list<type,device>::iterator list<type,device>::end ( )
{
    return base::end();
}

template < class type, class device >
constexpr list<type,device>::const_iterator list<type,device>::end ( ) const
{
    return base::end();
}

template < class type, class device >
constexpr list<type,device>::reference list<type,device>::front ( )
{
    #ifdef debug
        if ( empty() )
            throw value_error("cannot access front of an empty list");
    #endif
    return base::front();
}

template < class type, class device >
constexpr list<type,device>::const_reference list<type,device>::front ( ) const
{
    #ifdef debug
        if ( empty() )
            throw value_error("cannot access front of an empty list");
    #endif
    return base::front();
}


template < class type, class device >
constexpr list<type,device>::reference list<type,device>::back ( )
{
    #ifdef debug
        if ( empty() )
            throw value_error("cannot access back of an empty list");
    #endif
    return base::back();
}

template < class type, class device >
constexpr list<type,device>::const_reference list<type,device>::back ( ) const
{
    #ifdef debug
        if ( empty() )
            throw value_error("cannot access back of an empty list");
    #endif
    return base::back();
}

template < class type, class device >
constexpr void list<type,device>::push_front ( type val )
    requires movable<type>
{
    base::push_front(std::move(val));
}

template < class type, class device >
constexpr void list<type,device>::push_back ( type val )
    requires movable<type>
{
    base::push_back(std::move(val));
}

template < class type, class device >
constexpr type list<type,device>::pop_front ( )
    requires movable<type>
{
    #ifdef debug
        if ( empty() )
            throw value_error("cannot pop_front from an empty list");
    #endif
    if constexpr ( requires { { base::pop_front() } -> convertible_to<type>; } )
        return base::pop_front();
    else
    {
        auto poped = type(std::move(front()));
        base::pop_front();
        return poped;
    }
}

template < class type, class device >
constexpr type list<type,device>::pop_back ( )
    requires movable<type>
{
    #ifdef debug
        if ( empty() )
            throw value_error("cannot pop_back from an empty list");
    #endif
    if constexpr ( requires { { base::pop_back() } -> convertible_to<type>; } )
        return base::pop();
    else
    {
        auto poped = type(std::move(front()));
        base::pop_back();
        return poped;
    }
}
