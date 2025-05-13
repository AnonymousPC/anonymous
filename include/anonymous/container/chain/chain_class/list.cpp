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
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get front of list (with empty() = true)");

    return base::front();
}

template < class type, class device >
constexpr list<type,device>::const_reference list<type,device>::front ( ) const
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get front of list (with empty() = true)");

    return base::front();
}

template < class type, class device >
constexpr list<type,device>::reference list<type,device>::back ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get back of list (with empty() = true");

    return base::back();
}

template < class type, class device >
constexpr list<type,device>::const_reference list<type,device>::back ( ) const
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get back of list (with empty() = true)");

    return base::back();
}

template < class type, class device >
constexpr list<type,device>::reference list<type,device>::push_front ( type new_value )
{
    base::push_front(std::move(new_value));
    return front();
}

template < class type, class device >
constexpr list<type,device>::reference list<type,device>::push_back ( type new_value )
{
    base::push_back(std::move(new_value));
    return back();
}

template < class type, class device >
constexpr list<type,device>::value_type list<type,device>::pop_front ( )
{
    if constexpr ( debug ) 
        if ( empty() )
            throw value_error("cannot pop front from list (with empty() = true");

    auto old_value = value_type(std::move(front()));
    base::pop_front();
    return old_value;
}

template < class type, class device >
constexpr list<type,device>::value_type list<type,device>::pop_back ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot pop back from list (with empty() = true)");

    auto old_value = value_type(std::move(back()));
    base::pop_back();
    return old_value;
}

template < class type, class device >
constexpr list<type,device>::reference list<type,device>::insert ( iterator new_pos, type new_value )
{
    return *base::insert(new_pos, std::move(new_value));
}

template < class type, class device >
constexpr list<type,device>::value_type list<type,device>::erase ( iterator old_pos )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot erase from list (with empty() = true)");

    auto old_value = value_type(std::move(*old_pos));
    base::erase(old_pos);
    return old_value;
}