template < class container, class type, class device > 
constexpr decltype(auto) collection_algo<container,type,device>::begin ( )
{
    return static_cast<container&>(self).begin();
}

template < class container, class type, class device > 
constexpr decltype(auto) collection_algo<container,type,device>::begin ( ) const
{
    return static_cast<const container&>(self).begin();
}

template < class container, class type, class device > 
constexpr decltype(auto) collection_algo<container,type,device>::end ( )
{
    return static_cast<container&>(self).end();
}

template < class container, class type, class device > 
constexpr decltype(auto) collection_algo<container,type,device>::end ( ) const
{
    return static_cast<const container&>(self).end();
}

template < class container, class type, class device > 
constexpr decltype(auto) collection_algo<container,type,device>::size ( ) const
{
    return static_cast<const container&>(self).size();
}

template < class container, class type, class device > 
constexpr auto collection_algo<container,type,device>::average ( ) const
    requires default_initializable<type> and plusable<type> and dividable_to<type,int>
{
    return sum() / size();
}

template < class container, class type, class device > 
constexpr auto collection_algo<container,type,device>::sum ( ) const
    requires default_initializable<type> and plusable<type>
{
    if constexpr ( number_type<type> )
        return device::reduce(begin(), end(), type(0));
    else
        return device::accumulate(begin(), end(), type(0));
}

template < class container, class type, class device > 
constexpr auto collection_algo<container,type,device>::product ( ) const
    requires convertible_to<int,type> and multipliable<type>
{
    if constexpr ( number_type<type> )
        return device::reduce(begin(), end(), type(1), typename device::template multiplies<type>());
    else
        return device::accumulate(begin(), end(), type(1), typename device::template multiplies<type>());
}

template < class container, class type, class device > 
constexpr container& collection_algo<container,type,device>::for_each ( invocable<type&> auto op )
{
    device::for_each(begin(), end(), op);
    return static_cast<container&>(self);
}

template < class container, class type, class device > 
constexpr const container& collection_algo<container,type,device>::for_each ( invocable<type> auto op ) const
{
    device::for_each(begin(), end(), op);
    return static_cast<const container&>(self);
}