template < class type, int dim, class device > 
constexpr array<type,dim,device>& detail::transform_to_array<type,dim,device>::operator() ( detail::array_upper<type,dim,device>& arr )
{
    return static_cast<array<type,dim,device>&>(arr);
}

template < class type, int dim, class device > 
constexpr const array<type,dim,device>& detail::transform_to_array<type,dim,device>::operator() ( const detail::array_upper<type,dim,device>& arr )
{
    return static_cast<const array<type,dim,device>&>(arr);
}