template < class type, class device >
constexpr int stack<type,device>::size ( ) const
{
    return base::size();
}

template < class type, class device >
constexpr bool stack<type,device>::empty ( ) const
{
    return base::empty();
}

template < class type, class device >
constexpr stack<type,device>::reference stack<type,device>::top ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get top of stack (with empty() = true)");

    return base::top();
}

template < class type, class device >
constexpr stack<type,device>::const_reference stack<type,device>::top ( ) const
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get top of stack (with empty() = true)");

    return base::top();
}

template < class type, class device >
constexpr stack<type,device>::reference stack<type,device>::push ( type new_value )
{
    base::push(std::move(new_value));
    return top();
}

template < class type, class device >
constexpr stack<type,device>::value_type stack<type,device>::pop ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot pop from stack (with empty() = true)");

    auto old_value = value_type(std::move(top()));
    base::pop();
    return old_value;
}