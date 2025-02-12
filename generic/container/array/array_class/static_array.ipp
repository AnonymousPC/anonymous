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
template < class type2, class device2 >
constexpr static_array<type,len,device>::static_array ( const array<type2,1,device2>& cvt )
    requires ( same_as<type,type2> or same_as<device,device2> ) and 
             convertible_to<type2,type> and
             ( same_as<device,device2> or same_as<device,cpu> or same_as<device2,cpu> )
{
    #if debug
    if ( cvt.size() != size() )
        throw value_error("initialize static_array with size {} inconsistent with fixed_size {}", cvt.size(), size());
    #endif
        
    if constexpr ( same_as<type,type2> )
        if constexpr ( same_as<device,device2> )
            if ( cvt.ownership() )
                device::copy(cvt.array<type2,1,device2>::base::begin(), cvt.array<type2,1,device2>::base::end(), self.begin());
            else
                device::copy(cvt.begin(), cvt.end(), self.begin());
        else if constexpr ( same_as<device,cpu> )
            if ( cvt.ownership() )
                device2::copy(cvt.array<type2,1,device2>::base::begin(), cvt.array<type2,1,device2>::base::end(), self.begin());
            else 
                device2::copy(cvt.begin(), cvt.end(), self.begin());
        else // if constexpr ( same_as<device2,cpu> )
            if ( cvt.ownership() )
                device::copy(cvt.array<type2,1,device2>::base::begin(), cvt.array<type2,1,device2>::base::end(), self.begin());
            else
                device::copy(cvt.begin(), cvt.end(), self.begin());
    else // if constexpr ( same_as<device,device2> )
        if ( cvt.ownership() )
            device::transform(cvt.array<type2,1,device2>::base::begin(), cvt.array<type2,1,device2>::base::end(), self.begin(), [] (const auto& val) { return type(val); });
        else
            device::transform(cvt.begin(), cvt.end(), self.begin(), [] (const auto& val) { return type(val); });
}

template < class type, int len, class device >
template < class type2, int len2, class device2 >
constexpr static_array<type,len,device>::static_array ( const inplace_array<type2,len2,device2>& cvt )
    requires ( same_as<type,type2> or same_as<device,device2> ) and 
             convertible_to<type2,type> and
             ( same_as<device,device2> or same_as<device,cpu> or same_as<device2,cpu> ) and
             ( len2 >= len )
{
    #if debug
    if ( cvt.size() != size() )
        throw value_error("initialize static_array with size {} inconsistent with fixed_size {}", cvt.size(), size());
    #endif

    if constexpr ( same_as<type,type2> )
        if constexpr ( same_as<device,device2> )
            device::copy(cvt.begin(), cvt.end(), self.begin());
        else if constexpr ( same_as<device,cpu> )
            device2::copy(cvt.begin(), cvt.end(), self.begin());
        else // if constexpr ( same_as<device2,cpu> )
            device::copy(cvt.begin(), cvt.end(), self.begin());
    else // if constexpr ( same_as<device,device2> )
        device::transform(cvt.begin(), cvt.end(), self.begin(), [] (const auto& val) { return type(val); });
}

template < class type, int len, class device >
template < class type2, int len2, class device2 >
constexpr static_array<type,len,device>::static_array ( const static_array<type2,len2,device2>& cvt )
    requires ( same_as<type,type2> or same_as<device,device2> ) and 
             convertible_to<type2,type> and
             ( same_as<device,device2> or same_as<device,cpu> or same_as<device2,cpu> ) and
             ( len2 == len )
{
    if constexpr ( same_as<type,type2> )
        if constexpr ( same_as<device,device2> )
            /*copy constructor*/;
        else if constexpr ( same_as<device,cpu> )
            device2::copy(cvt.begin(), cvt.end(), self.begin());
        else // if constexpr ( same_as<device2,cpu> )
            device::copy(cvt.begin(), cvt.end(), self.begin());
    else // if constexpr ( same_as<device,device2> )
        device::transform(cvt.begin(), cvt.end(), self.begin(), [] (const auto& val) { return type(val); });
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

template < class type, int len, class device >
constexpr static_array<int,1> static_array<type,len,device>::shape ( )
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
    return data();
}

template < class type, int len, class device >
constexpr static_array<type,len,device>::const_iterator static_array<type,len,device>::begin ( ) const
{
    return data();
}

template < class type, int len, class device >
constexpr static_array<type,len,device>::iterator static_array<type,len,device>::end ( ) 
{
    return data() + size();
}

template < class type, int len, class device >
constexpr static_array<type,len,device>::const_iterator static_array<type,len,device>::end ( ) const
{
    return data() + size();
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

template < class type, int len, class device >
constexpr auto static_array<type,len,device>::mdspan ( )
{
    using type1 = std::mdspan<type,std::extents<int,1>,typename device::layout_type,typename device::template accessor_type<type>>;

    let ptr = data();
    let shp = std::extents<int,1> { size() };
    let mds = type1(ptr, shp);
    return variant<type1>(mds);
}

template < class type, int len, class device >
constexpr const auto static_array<type,len,device>::mdspan ( ) const
{
    using type1 = std::mdspan<const type,std::extents<int,1>,typename device::layout_type,typename device::template accessor_type<const type>>;

    let ptr = data();
    let shp = std::extents<int,1> { size() };
    let mds = type1(ptr, shp);
    return variant<type1>(mds);
}