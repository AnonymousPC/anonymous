#pragma once

template < class type, int len, class device >
constexpr static_array<type,len,device>::static_array ( )
{
    if constexpr ( not is_class<type> )
        device::fill(begin(), end(), type());
}

template < class type, int len, class device >
constexpr static_array<type,len,device>::static_array ( std::initializer_list<type> init )
    requires copyable<type>
{
    #if debug
    if ( int(init.size()) != size() )
        throw value_error("initialize static_array with size {} inconsistent with fixed_size {}", init.size(), size());
    #endif
    device::copy(init.begin(), init.end(), begin());
}

template < class type, int len, class device >
constexpr static_array<type,len,device>::static_array ( range<type> init )
    requires copyable<type>
{
    #if debug
    if ( init.size() != size() )
        throw value_error("initialize static_array with size {} inconsistent with fixed_size {}", init.size(), size());
    #endif
    device::copy(init.begin(), init.end(), begin());
}

template < class type, int len, class device >
constexpr int static_array<type,len,device>::dimension ( )
{
    return 1;
}

template < class type, int len, class device >
constexpr int static_array<type,len,device>::size ( )
{
    return len;
}

template < class type, int len, class device >
constexpr int static_array<type,len,device>::capacity ( )
{
    return len;
}

// template < class type, int len, class device >
// constexpr array<int> static_array<type,len,device>::shape ( )
// {
//     return { size() };
// }

template < class type, int len, class device >
constexpr inplace_array<int,1> static_array<type,len,device>::inplace_shape ( )
{
    return { size() };
}

template < class type, int len, class device >
constexpr static_array<int,1> static_array<type,len,device>::static_shape ( )
{
    return { size() };
}

template < class type, int len, class device >
constexpr bool static_array<type,len,device>::empty ( )
{
    return false;
}

template < class type, int len, class device >
constexpr static_array<type,len,device>::pointer static_array<type,len,device>::data ( ) 
{
    return base::data();
}

template < class type, int len, class device >
constexpr static_array<type,len,device>::const_pointer static_array<type,len,device>::data ( ) const
{
    return base::data();
}

template < class type, int len, class device >
constexpr static_array<type,len,device>::iterator static_array<type,len,device>::begin ( ) 
{
    return base::begin();
}

template < class type, int len, class device >
constexpr static_array<type,len,device>::const_iterator static_array<type,len,device>::begin ( ) const
{
    return base::begin();
}

template < class type, int len, class device >
constexpr static_array<type,len,device>::iterator static_array<type,len,device>::end ( ) 
{
    return base::end();
}

template < class type, int len, class device >
constexpr static_array<type,len,device>::const_iterator static_array<type,len,device>::end ( ) const
{
    return base::end();
}

template < class type, int len, class device >
constexpr static_array<type,len,device>::reference static_array<type,len,device>::operator[] ( int pos )
{
    #if debug
    if ( pos < -size() or pos == 0 or pos > size() )
        throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    return pos >= 0 ? base::operator[](pos-1) otherwise
                      base::operator[](pos+size());
}

template < class type, int len, class device >
constexpr static_array<type,len,device>::const_reference static_array<type,len,device>::operator[] ( int pos ) const
{
    #if debug
    if ( pos < -size() or pos == 0 or pos > size() )
        throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    return pos >= 0 ? base::operator[](pos-1) otherwise
                      base::operator[](pos+size());
}

template < class type, int len, class device >
constexpr bool static_array<type,len,device>::ownership ( )
{
    return true;
}

template < class type, int len, class device >
constexpr bool static_array<type,len,device>::contiguous ( )
{
    return true;
}