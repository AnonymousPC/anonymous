template < class type, class device >
constexpr int forward_list<type,device>::size ( ) const
{
    return base::size();
}

template < class type, class device >
constexpr bool forward_list<type,device>::empty ( ) const
{
    return base::empty();
}

template < class type, class device >
constexpr forward_list<type,device>::iterator forward_list<type,device>::begin ( )
{
    return base::begin();
}

template < class type, class device >
constexpr forward_list<type,device>::const_iterator forward_list<type,device>::begin ( ) const
{
    return base::begin();
}

template < class type, class device >
constexpr forward_list<type,device>::iterator forward_list<type,device>::end ( )
{
    return base::end();
}

template < class type, class device >
constexpr forward_list<type,device>::const_iterator forward_list<type,device>::end ( ) const
{
    return base::end();
}

template < class type, class device >
constexpr forward_list<type,device>::reference forward_list<type,device>::front ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get front of forward_list (with empty() = true)");

    return base::front();
}

template < class type, class device >
constexpr forward_list<type,device>::const_reference forward_list<type,device>::front ( ) const
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get front of forward_list (with empty() = true)");

    return base::front();
}

template < class type, class device >
constexpr void forward_list<type,device>::push_front ( type val )
    requires movable<type>
{
    base::push_front(std::move(val));
}

template < class type, class device >
constexpr type forward_list<type,device>::pop_front ( )
    requires movable<type>
{
    if constexpr ( debug ) 
        if ( empty() )
            throw value_error("cannot pop front from forward_list (with empty() = true");

    if constexpr ( requires { { base::pop_front() } -> convertible_to<type>; } )
        return base::pop_front();
    else
    {
        auto poped = type(std::move(front()));
        base::pop_front();
        return poped;
    }
}