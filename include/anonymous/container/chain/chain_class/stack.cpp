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
constexpr void stack<type,device>::push ( type val )
{
    base::push(std::move(val));
}

template < class type, class device >
constexpr type stack<type,device>::pop ( )
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot pop from stack (with empty() = true)");
            
    if constexpr ( requires { { base::pop() } -> convertible_to<type>; } )
        return base::pop();
    else
    {
        auto poped = type(std::move(top()));
        base::pop();
        return poped;
    }
}