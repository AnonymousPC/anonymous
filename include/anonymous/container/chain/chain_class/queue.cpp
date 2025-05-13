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
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get front of queue (with empty() = true)");

    return base::front();
}

template < class type, class device >
constexpr queue<type,device>::const_reference queue<type,device>::front ( ) const
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get front of queue (with empty() = true)");

    return base::front();
}

template < class type, class device >
constexpr queue<type,device>::reference queue<type,device>::back ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get back of queue (with empty() = true)");

    return base::back();
}

template < class type, class device >
constexpr queue<type,device>::const_reference queue<type,device>::back ( ) const
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get back of queue (with empty() = true)");

    return base::back();
}

template < class type, class device >
constexpr queue<type,device>::reference queue<type,device>::push ( type new_value )
{
    base::push(std::move(new_value));
    return base::back();
}

template < class type, class device >
constexpr queue<type,device>::value_type queue<type,device>::pop ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot pop from queue (with empty() = true)");

    auto old_value = value_type(std::move(front()));
    base::pop();
    return old_value;
}