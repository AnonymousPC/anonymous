template < class type1, class type2, class device >
constexpr device::template reference<type1> detail::transform_to_key<type1,type2,device>::operator() ( device::template reference<typename device::template pair<const type1,type2>> p )
{
    return p.first;
}

template < class type1, class type2, class device >
constexpr device::template const_reference<type1> detail::transform_to_key<type1,type2,device>::operator() ( device::template const_reference<typename device::template pair<const type1,type2>> p )
{
    return p.first;
}