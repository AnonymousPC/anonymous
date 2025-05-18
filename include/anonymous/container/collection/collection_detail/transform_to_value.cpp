template < class type1, class type2, class device >
constexpr device::template reference<type2> detail::transform_to_value<type1,type2,device>::operator() ( device::template reference<typename device::template pair<const type1,type2>> p )
{
    return p.second;
}

template < class type1, class type2, class device >
constexpr device::template const_reference<type2> detail::transform_to_value<type1,type2,device>::operator() ( device::template const_reference<typename device::template pair<const type1,type2>> p )
{
    return p.second;
}