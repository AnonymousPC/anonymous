template < class type, int dim, class device > 
constexpr array<type,dim,device>& detail::to_array_pointer::operator() ( detail::array_upper<type,dim,device>& arr )
{
    return static_cast<array<type,dim,device>&>(arr);
}

template < class type, int dim, class device > 
constexpr const array<type,dim,device>& detail::to_array_pointer::operator() ( const detail::array_upper<type,dim,device>& arr )
{
    return static_cast<const array<type,dim,device>&>(arr);
}

template < class type, int dim, class device > 
constexpr array<type,dim,device>* detail::to_array_pointer::operator() ( detail::array_upper<type,dim,device>* arr )
{
    return static_cast<array<type,dim,device>*>(arr);
}

template < class type, int dim, class device > 
constexpr const array<type,dim,device>* detail::to_array_pointer::operator() ( const detail::array_upper<type,dim,device>* arr )
{
    return static_cast<const array<type,dim,device>*>(arr);
}