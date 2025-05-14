template < class container, class type1, class device >
constexpr int detail::map_keys<container,type1,device>::size ( ) const
{
    return static_cast<const container&>(self).size();
}

template < class container, class type1, class device >
constexpr detail::map_keys<container,type1,device>::const_iterator detail::map_keys<container,type1,device>::begin ( ) const
{
    return const_iterator(static_cast<const container&>(self).begin());
}

template < class container, class type1, class device >
constexpr detail::map_keys<container,type1,device>::const_iterator detail::map_keys<container,type1,device>::end ( ) const
{
    return const_iterator(static_cast<const container&>(self).end());
}

template < class container, class type1, class device >
constexpr bool detail::map_keys<container,type1,device>::contains ( const type1& k ) const
{
    return static_cast<const container&>(self).contains(k);
}