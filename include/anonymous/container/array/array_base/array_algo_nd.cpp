#include "detail/md_reverse.cpp"
#include "detail/md_rotate.cpp"

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<container,type,dim,device>::begin ( )
{
    return static_cast<container&>(self).begin();
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<container,type,dim,device>::begin ( ) const
{
    return static_cast<const container&>(self).begin();
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<container,type,dim,device>::end ( )
{
    return static_cast<container&>(self).end();
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<container,type,dim,device>::end ( ) const
{
    return static_cast<const container&>(self).end();
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<container,type,dim,device>::data ( )
{
    return static_cast<container&>(self).data();
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<container,type,dim,device>::data ( ) const
{
    return static_cast<const container&>(self).data();
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<container,type,dim,device>::size ( ) const
{
    return static_cast<const container&>(self).size();
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<container,type,dim,device>::shape ( ) const
{
    return static_cast<const container&>(self).shape();
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<container,type,dim,device>::empty ( ) const
{
    return static_cast<const container&>(self).empty();
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<container,type,dim,device>::ownership ( ) const
{
    return static_cast<const container&>(self).ownership();
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<container,type,dim,device>::contiguous ( ) const
{
    return static_cast<const container&>(self).contiguous();
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<container,type,dim,device>::transpose ( )
{
    return static_cast<container&>(self).transpose();
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
constexpr decltype(auto) array_algo<container,type,dim,device>::transpose ( ) const
{
    return static_cast<const container&>(self).transpose();
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
template < int axis >
constexpr container& array_algo<container,type,dim,device>::reverse ( )
    requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) )
{
    if constexpr ( axis == 1 or axis == -dim )
        device::reverse(begin(), end());
    else if constexpr ( axis == -1 or axis == dim )
        device::reverse(transpose().begin(), transpose().end());
    else
        if constexpr ( axis > 0 )
            detail::md_reverse<device,axis>      (static_cast<container&>(self), shape());
        else
            detail::md_reverse<device,axis+dim+1>(static_cast<container&>(self), shape());
    return static_cast<container&>(self);
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
template < int axis >
constexpr container& array_algo<container,type,dim,device>::rotate ( int n )
    requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) )
{
    if constexpr ( debug )
        if ( n < -shape()[axis] or n > shape()[axis] )
            throw value_error("cannot rotate array (with step = {}, shape() = {}, axis = {}): step out of range", n, shape(), axis);

    if constexpr ( axis == 1 or axis == -dim )
        n > 0 ? device::rotate(begin(), end() - n, end()) :
                device::rotate(begin(), begin() - n, end());
    else if constexpr ( axis == -1 or axis == dim )
        n > 0 ? device::rotate(transpose().begin(), transpose().end() - n, transpose().end()) :
                device::rotate(transpose().begin(), transpose().begin() - n, transpose().end());
    else
        if constexpr ( axis > 0 )
            detail::md_rotate<device,axis>      (static_cast<container&>(self), shape(), n);
        else
            detail::md_rotate<device,axis+dim+1>(static_cast<container&>(self), shape(), n);
    return static_cast<container&>(self);
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
template < int axis >
constexpr array<type,dim-1,device> array_algo<container,type,dim,device>::average ( ) const
    requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) ) and
             default_initializable<type> and plusable<type> and dividable_to<type,int>
{
    if constexpr ( debug )
        if ( shape()[axis] == 0 )
            throw value_error("cannot calculate average (with shape() = {}, axis = {}): array is empty", shape(), axis);

    return sum<axis>() / shape()[axis];
}

template < class container, class type, int dim, class device >
    requires ( dim >= 2 )
template < int axis >
constexpr array<type,dim-1,device> array_algo<container,type,dim,device>::sum ( ) const
    requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) ) and
             default_initializable<type> and plusable<type>
{
    static_assert(false, "not coded yet, you should find a way to add them in-place."
                         "device::accumulate() or device::reduce() is NOT OKAY."
                         "besides, if number_type<type> then use reduce in lowest layer."
                         "see array_algo<..., dim=1, ...>::sum().");
}

