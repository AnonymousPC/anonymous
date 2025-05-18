template < class type1, class type2, class device >
constexpr device::template reference<pair<const type1,type2>> detail::transform_to_pair<type1,type2,device>::operator() ( device::template reference<typename device::template pair<const type1,type2>> p )
{
    return static_cast<device::template reference<pair<const type1,type2>>>(p);
}

template < class type1, class type2, class device >
constexpr device::template const_reference<pair<const type1,type2>> detail::transform_to_pair<type1,type2,device>::operator() ( device::template const_reference<typename device::template pair<const type1,type2>> p )
{
    return static_cast<device::template const_reference<pair<const type1,type2>>>(p);
}