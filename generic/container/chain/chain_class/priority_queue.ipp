#pragma once

template < class type, class compare >
constexpr int priority_queue<type,compare>::size ( ) const
{
    return vector<type>::size();
}

template < class type, class compare >
constexpr bool priority_queue<type,compare>::empty ( ) const
{
    return vector<type>::empty();
}

template < class type, class compare >
constexpr const type& priority_queue<type,compare>::top ( ) const
{
    return vector<type>::operator[] ( 1 );
}

template < class type, class compare >
constexpr void priority_queue<type,compare>::push ( type val )
{
    vector<type>::push ( std::move ( val ) );
    std::push_heap ( vector<type>::begin(), vector<type>::end(), reverse );
}

template < class type, class compare >
constexpr type priority_queue<type,compare>::pop ( )
{
    type ret = std::move ( const_cast<type&> ( top() ) );
    std::pop_heap ( vector<type>::begin(), vector<type>::end(), reverse );
    vector<type>::pop();
    return ret;
}