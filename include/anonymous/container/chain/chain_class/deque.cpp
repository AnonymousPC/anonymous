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
constexpr deque<type,device>::reference deque<type,device>::push_front ( type new_value )
{
    base::push_front(std::move(new_value));
    return front();
}

template < class type, class device >
constexpr deque<type,device>::reference deque<type,device>::push_back ( type new_value )
{
    base::push_back(std::move(new_value));
    return back();
}

template < class type, class device >
constexpr deque<type,device>::value_type deque<type,device>::pop_front ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot pop front from deque (with empty() = true)");

    auto old_value = value_type(std::move(front()));
    base::pop_front();
    return old_value;
}

template < class type, class device >
constexpr deque<type,device>::value_type deque<type,device>::pop_back ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot pop back from deque (with empty() = true)");

    auto old_value = value_type(std::move(back()));
    base::pop_back();
    return old_value;
}

template < class type, class device >
constexpr deque<type,device>::reference deque<type,device>::insert ( iterator new_pos, type new_value )
{
    return *base::insert(new_pos, std::move(new_value));
}

template < class type, class device >
constexpr deque<type,device>::value_type deque<type,device>::erase ( iterator old_pos )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot erase from deque (with empty() = true)");
    
    auto old_value = value_type(std::move(*old_pos));
    base::erase(old_pos);
    return old_value;
}
