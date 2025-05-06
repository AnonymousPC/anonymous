template < class type >
constexpr cpu::stride_pointer<type>::stride_pointer ( type* init_ptr, int init_step ) 
    extends ptr ( init_ptr ), step ( init_step ) 
{ 

}

template < class type >
constexpr cpu::stride_pointer<type>::stride_pointer ( cpu::template const_stride_pointer<type> cvt ) 
    extends ptr ( cvt.get_ptr() ), step ( cvt.get_step() ) 
{ 

}

template < class type >
constexpr cpu::stride_pointer<type>::reference cpu::stride_pointer<type>::operator * ( ) const
{
    return *ptr;
}

template < class type >
constexpr cpu::stride_pointer<type>::pointer cpu::stride_pointer<type>::operator -> ( ) const
{
    return ptr;
}

template < class type >
constexpr cpu::stride_pointer<type>::reference cpu::stride_pointer<type>::operator [] ( difference_type offset ) const
{
    return ptr[offset * step];
}

template < class type >
constexpr type* cpu::stride_pointer<type>::get_ptr ( ) const
{
    return ptr;
}

template < class type >
constexpr int cpu::stride_pointer<type>::get_step ( ) const
{
    return step;
}

template < class type >
constexpr cpu::const_stride_pointer<type>::const_stride_pointer ( const type* init_ptr, int init_step ) 
    extends ptr ( init_ptr ), step ( init_step ) 
{ 

}

template < class type >
constexpr cpu::const_stride_pointer<type>::const_stride_pointer ( cpu::template stride_pointer<type> cvt ) 
    extends ptr ( cvt.get_ptr() ), step ( cvt.get_step() ) 
{ 

}

template < class type >
constexpr cpu::const_stride_pointer<type>::reference cpu::const_stride_pointer<type>::operator * ( ) const
{
    return *ptr;
}

template < class type >
constexpr cpu::const_stride_pointer<type>::pointer cpu::const_stride_pointer<type>::operator -> ( ) const
{
    return ptr;
}

template < class type >
constexpr cpu::const_stride_pointer<type>::reference cpu::const_stride_pointer<type>::operator [] ( difference_type offset ) const
{
    return ptr[offset * step];
}

template < class type >
constexpr const type* cpu::const_stride_pointer<type>::get_ptr ( ) const
{
    return ptr;
}

template < class type >
constexpr int cpu::const_stride_pointer<type>::get_step ( ) const
{
    return step;
}