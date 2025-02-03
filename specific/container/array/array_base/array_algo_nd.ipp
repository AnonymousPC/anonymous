#pragma once

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<array_type,type,dim,device>::begin ( )
{
    return static_cast<array_type&>(self).begin();
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<array_type,type,dim,device>::begin ( ) const
{
    return static_cast<const array_type&>(self).begin();
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<array_type,type,dim,device>::end ( )
{
    return static_cast<array_type&>(self).end();
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<array_type,type,dim,device>::end ( ) const
{
    return static_cast<const array_type&>(self).end();
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<array_type,type,dim,device>::data ( )
{
    return static_cast<array_type&>(self).data();
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<array_type,type,dim,device>::data ( ) const
{
    return static_cast<const array_type&>(self).data();
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<array_type,type,dim,device>::size ( ) const
{
    return static_cast<const array_type&>(self).size();
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<array_type,type,dim,device>::shape ( ) const
{
    return static_cast<const array_type&>(self).shape();
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<array_type,type,dim,device>::empty ( ) const
{
    return static_cast<const array_type&>(self).empty();
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<array_type,type,dim,device>::ownership ( ) const
{
    return static_cast<const array_type&>(self).ownership();
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<array_type,type,dim,device>::contiguous ( ) const
{
    return static_cast<const array_type&>(self).contiguous();
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<array_type,type,dim,device>::transpose ( )
{
    return static_cast<array_type&>(self).transpose();
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<array_type,type,dim,device>::transpose ( ) const
{
    return static_cast<const array_type&>(self).transpose();
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
template < int axis >
constexpr array_type& array_algo<array_type,type,dim,device>::reverse ( )
    requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) )
{
    if constexpr ( axis == 1 or axis == -dim )
        device::reverse(begin(), end());
    else if constexpr ( axis == -1 or axis == dim )
        device::reverse(transpose().begin(), transpose().end());
    else
        if constexpr ( axis > 0 )
            detail::md_reverse<device,axis>      (static_cast<array_type&>(self), shape());
        else
            detail::md_reverse<device,axis+dim+1>(static_cast<array_type&>(self), shape());
    return static_cast<array_type&>(self);
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
template < int axis >
constexpr array_type& array_algo<array_type,type,dim,device>::rotate ( int n )
    requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) )
{
    #if debug
        if ( n < -shape()[axis] or n > shape()[axis] )
            throw value_error("rotate array with step {} out of range with shape {} axis {}", n, shape(), axis);
    #endif

    if constexpr ( axis == 1 or axis == -dim )
        n > 0 ? device::rotate(begin(), end() - n, end()) otherwise
                device::rotate(begin(), begin() - n, end());
    else if constexpr ( axis == -1 or axis == dim )
        n > 0 ? device::rotate(transpose().begin(), transpose().end() - n, transpose().end()) otherwise
                device::rotate(transpose().begin(), transpose().begin() - n, transpose().end());
    else
        if constexpr ( axis > 0 )
            detail::md_rotate<device,axis>      (static_cast<array_type&>(self), shape(), n);
        else
            detail::md_rotate<device,axis+dim+1>(static_cast<array_type&>(self), shape(), n);
    return static_cast<array_type&>(self);
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
template < int axis >
constexpr array<type,dim-1,device> array_algo<array_type,type,dim,device>::average ( ) const
    requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) ) and
             default_initializable<type> and plusable<type> and dividable_to<type,int>
{
    #if debug
        if ( shape()[axis] == 0 )
            throw value_error("get average from an empty array with shape {} axis {}", shape(), axis);
    #endif
    return sum<axis>() / shape()[axis];
}

template < class array_type, class type, int dim, class device >
    requires ( dim >= 2 )
template < int axis >
constexpr array<type,dim-1,device> array_algo<array_type,type,dim,device>::sum ( ) const
    requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) ) and
             default_initializable<type> and plusable<type>
{
    static_assert(false, "not coded yet, you should find a way to add them in-place"
                         "device::accumulate() or device::reduce() is NOT OKAY"
                         "besides, if number_type<type> then use reduce in lowest layer"
                         "see array_algo<..., dim=1, ...>::sum()");
}

