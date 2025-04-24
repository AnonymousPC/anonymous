template < class type, class device >
constexpr int deque<type,device>::size ( ) const
{
    return base::size();
}

template < class type, class device >
constexpr bool deque<type,device>::empty ( ) const
{
    return base::empty();
}

template < class type, class device >
constexpr deque<type,device>::iterator deque<type,device>::begin ( )
{
    return base::begin();
}

template < class type, class device >
constexpr deque<type,device>::const_iterator deque<type,device>::begin ( ) const
{
    return base::begin();
}

template < class type, class device >
constexpr deque<type,device>::iterator deque<type,device>::end ( )
{
    return base::end();
}

template < class type, class device >
constexpr deque<type,device>::const_iterator deque<type,device>::end ( ) const
{
    return base::end();
}

template < class type, class device >
constexpr deque<type,device>::reference deque<type,device>::operator [] ( int pos )
{
    if constexpr ( debug )
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
  
    return base::operator[](pos >= 0 ? pos-1 : pos+size());
}

template < class type, class device >
constexpr deque<type,device>::const_reference deque<type,device>::operator [] ( int pos ) const
{
    if constexpr ( debug )
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    
    return base::operator[](pos >= 0 ? pos-1 : pos+size());
}

template < class type, class device >
constexpr deque<type,device>::reference deque<type,device>::front ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get front of deque (with empty() = true)");

    return base::front();
}

template < class type, class device >
constexpr deque<type,device>::const_reference deque<type,device>::front ( ) const
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get front of deque (with empty() = true)");

    return base::front();
}

template < class type, class device >
constexpr deque<type,device>::reference deque<type,device>::back ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get back of deque (with empty() = true)");

    return base::back();
}

template < class type, class device >
constexpr deque<type,device>::const_reference deque<type,device>::back ( ) const
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get back of deque (with empty() = true)");

    return base::back();
}

template < class type, class device >
constexpr void deque<type,device>::push_front ( type val )
{
    base::push_front(std::move(val));
}

template < class type, class device >
constexpr void deque<type,device>::push_back ( type val )
{
    base::push_back(std::move(val));
}

template < class type, class device >
constexpr type deque<type,device>::pop_front ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot pop front from deque (with empty() = true)");

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
constexpr type deque<type,device>::pop_back ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot pop back from deque (with empty() = true)");

    if constexpr ( requires { { base::pop_back() } -> convertible_to<type>; } )
        return base::pop();
    else
    {
        auto poped = type(std::move(front()));
        base::pop_back();
        return poped;
    }
}
