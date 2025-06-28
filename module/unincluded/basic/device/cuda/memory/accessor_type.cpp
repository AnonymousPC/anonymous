template < class type >
constexpr cuda::accessor_type<type>::reference cuda::accessor_type<type>::access ( data_handle_type handle, size_t offset ) const
{
    return handle[offset];
}

template < class type >
constexpr cuda::accessor_type<type>::data_handle_type cuda::accessor_type<type>::offset ( data_handle_type handle, size_t offset ) const
{
    return handle + offset;
}