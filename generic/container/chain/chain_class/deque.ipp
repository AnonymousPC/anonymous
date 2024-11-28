#pragma once

/// Class deque

// Core

template < class type >
constexpr deque<type>::deque ( deque&& init )
    extends arr         ( std::move     ( arr ) ),
            index_first ( std::exchange ( init.index_first,  1 ) ),
            index_last  ( std::exchange ( init.index_last,  -1 ) )
{

}

template < class type >
constexpr deque<type>& deque<type>::operator = ( deque<type>&& right )
{
    // We know nothing about how vector moves, so swap is the always-ok method.
    std::swap ( self.arr,         right.arr         );
    std::swap ( self.index_first, right.index_first );
    std::swap ( self.index_last,  right.index_last  );

    return self;
}

// Interface

template < class type >
constexpr int deque<type>::size ( ) const
{
    return arr.size() * chunk - ( index_first - 1 ) - ( chunk - index_last );
}

template < class type >
constexpr bool deque<type>::empty ( ) const
{
    return size() == 0;
}

template < class type >
constexpr type& deque<type>::front ( )
{
    #if debug
        if ( empty() )
            throw index_error("cannot get front from deque with size {}", size());
    #endif
    return arr[1][index_first];
}

template < class type >
constexpr const type& deque<type>::front ( ) const
{
    #if debug
        if ( empty() )
            throw index_error("cannot get front from deque with size {}", size());
    #endif
    return arr[1][index_first];
}

template < class type >
constexpr type& deque<type>::back ( )
{
    #if debug
        if ( empty() )
            throw index_error("cannot get back from deque with size {}", size());
    #endif
    return arr[-1][index_last];
}

template < class type >
constexpr const type& deque<type>::back ( ) const
{
    #if debug
        if ( empty() )
            throw index_error("cannot get back from deque with size {}", size());
    #endif
    return arr[-1][index_first];
}

template < class type >
constexpr void deque<type>::push_front ( type val )
{
    if ( index_first != 1 )
        arr[1][--index_first] = std::move(val);
    else
    {
        arr.insert(1, vector<type>(chunk));
        arr[1][chunk] = std::move(val);
        index_first = chunk;
    }
}

template < class type >
constexpr void deque<type>::push_back ( type val )
{
    if ( index_last != chunk )
        arr[-1][++index_last] = std::move(val);
    else
    {
        arr.push(vector<type>(chunk));
        arr[-1][1] = std::move(val);
        index_last = 1;
    }
}

template < class type >
constexpr type deque<type>::pop_front ( )
{
    #if debug
        if ( empty() )
            throw index_error("cannot pop front from deque with size {}", size());
    #endif

    if ( index_first != chunk )
        return std::move(arr[1][index_first++]);
    else
    {
        type poped = std::move(arr[1][chunk]);
        arr.pop(1);
        index_first = 1;
        return poped;
    }
}

template < class type >
constexpr type deque<type>::pop_back ( )
{
    #if debug
        if ( empty() )
            throw index_error("cannot pop back from deque with size {}", size());
    #endif

    if ( index_last != 1 )
        return std::move(arr[-1][index_last--]);
    else
    {
        type poped = std::move(arr[-1][1]);
        arr.pop();
        index_last = chunk;
        return poped;
    }
}


// Interface