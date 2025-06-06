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
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get top of priority_queue (with empty() = true)");

    return base::top();
}

template < class type, class compare, class device >
constexpr void priority_queue<type,compare,device>::push ( type new_value )
{
    base::push(std::move(new_value));
    return self;
}

template < class type, class compare, class device >
constexpr priority_queue<type,compare,device>::value_type priority_queue<type,compare,device>::pop ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot pop from priority_queue (with empty() = true)");

    auto old_value = value_type(std::move(top()));
    base::pop();
    return old_value;
}