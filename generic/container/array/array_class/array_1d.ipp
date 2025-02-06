#pragma once

template < class type, class device >
constexpr array<type,1,device>::array ( const array& init )
    requires copyable<type>
{
    if ( init.ownership() ) 
        self.base::operator=(static_cast<const base&>(init));
    else // if ( not init.ownership() )
    {
        self.base::resize(init.upper::size());
        device::copy(init.upper::begin(), init.upper::end(), self.base::begin());
    }
} 

template < class type, class device >
constexpr array<type,1,device>::array ( array&& init )
{
    if ( init.ownership() ) 
        self.base::operator=(static_cast<base&&>(init));
    else // if ( not init.ownership() )
    {
        self.base::resize(init.upper::size());
        device::move(init.upper::begin(), init.upper::end(), self.base::begin());
    }
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::operator = ( const array& right )
    requires copyable<type>
{
    if ( self.ownership() and right.ownership() ) 
        self.base::operator=(static_cast<const base&>(right));
    else if ( self.ownership() and not right.ownership() )
    {
        self.base::resize(right.size());
        device::copy(right.upper::begin(), right.upper::end(), self.base::begin());
    }
    else if ( not self.ownership() and right.ownership() )
    {
        #if debug
        if ( self.upper::size() != int(right.base::size()) )
            throw value_error("copy assign array with inconsistent size (with left_ownership = false, left_size = {}, right_size = {})", self.size(), right.size());
        #endif
        device::copy(right.base::begin(), right.base::end(), self.upper::begin());
    }
    else // if ( not self.ownership() and not right.ownership() )
    {
        #if debug
        if ( self.upper::size() != right.upper::size() )
            throw value_error("copy assign array with inconsistent size (with left_ownership = false, left_size = {}, right_size = {})", self.size(), right.size());
        #endif
        device::copy(right.upper::begin(), right.upper::end(), self.upper::begin());
    }

    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::operator = ( array&& right )
{
    if ( self.ownership() and right.ownership() ) 
        self.base::operator=(static_cast<base&&>(right));
    else if ( self.ownership() and not right.ownership() )
    {
        self.base::resize(right.upper::size());
        device::move(right.upper::begin(), right.upper::end(), self.base::begin());
    }
    else if ( not self.ownership() and right.ownership() )
    {
        #if debug
        if ( self.upper::size() != int(right.base::size()) )
            throw value_error("move assign array with inconsistent size (with left_ownership = false, left_size = {}, right_size = {})", self.size(), right.size());
        #endif
        device::move(right.base::begin(), right.base::end(), self.upper::begin());
    }
    else // if ( not self.ownership() and not right.ownership() )
    {
        #if debug
        if ( self.upper::size() != right.upper::size() )
            throw value_error("move assign array with inconsistent size (with left_ownership = false, left_size = {}, right_size = {})", self.size(), right.size());
        #endif
        device::move(right.upper::begin(), right.upper::end(), self.upper::begin());
    }

    return self;
}


template < class type, class device >
constexpr array<type,1,device>::array ( int init_size )
    extends base ( init_size )
{
    #if debug
    if ( init_size < 0 )
        throw value_error("initialize array with negative size {}", init_size);
    #endif
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const type& init_value )
    requires copyable<type>
    extends base ( init_size, init_value )
{
    #if debug
    if ( init_size < 0 )
        throw value_error("initialize array with negative size {}", init_size);
    #endif
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const function_type<type()> auto init_value )
    extends array ( init_size )
{
    device::generate(self.base::begin(), self.base::end(), init_value);
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const function_type<type(int)> auto init_value )
    extends array ( init_size )
{
    for ( int i in range(init_size) )
        self.base::operator[](i-1) = init_value(i);
}

template < class type, class device >
constexpr array<type,1,device>::array ( std::initializer_list<type> init )
    requires copyable<type>
    extends base ( std::forward<decltype(init)>(init) )
{
    
}

template < class type, class device >
constexpr array<type,1,device>::array ( range<type> init )
    requires copyable<type> and number_type<type>
    extends base ( init.begin(), init.end() )
{

}

template < class type, class device >
template < int len >
constexpr array<type,1,device>::array ( const inplace_array<type,len,device>& cvt )
    extends array ( cvt.size() )
{
    device::copy(cvt.begin(), cvt.end(), self.base::begin());
}

template < class type, class device >
template < int len >
constexpr array<type,1,device>::array ( const static_array<type,len,device>& cvt )
    extends array ( cvt.size() )
{
    device::copy(cvt.begin(), cvt.end(), self.base::begin());
}

template < class type, class device >
template < class type2 >
constexpr array<type,1,device>::array ( const array<type2,1,device>& cvt )
    requires convertible_to<type2,type> but ( not same_as<type,type2> )
    extends array ( cvt.size() )
{
    if ( cvt.ownership() )
        device::transform(cvt.array<type2,1,device>::base::begin(), cvt.array<type2,1,device>::base::end(), self.base::begin(), [] (const auto& val) { return type(val); });
    else
        device::transform(cvt.array<type2,1,device>::upper::begin(), cvt.array<type2,1,device>::upper::end(), self.base::begin(), [] (const auto& val) { return type(val); });
}

template < class type, class device >
template < class type2 >
constexpr array<type,1,device>::array ( const array<type2,1,device>& cvt )
    requires constructible_from<type,type2> but ( not convertible_to<type2,type> )
    extends array ( cvt.size() )
{
    if ( cvt.ownership() )
        device::transform(cvt.array<type2,1,device>::base::begin(), cvt.array<type2,1,device>::base::end(), self.base::begin(), [] (const auto& val) { return type(val); });
    else
        device::transform(cvt.array<type2,1,device>::upper::begin(), cvt.array<type2,1,device>::upper::end(), self.base::begin(), [] (const auto& val) { return type(val); });
}

template < class type, class device >
template < class device2 >
constexpr array<type,1,device>::array ( const array<type,1,device2>& cvt )
    requires same_as<device,cpu> or same_as<device2,cpu>
    extends array ( cvt.size() )
{
    if constexpr ( not same_as<device,cpu> )
        if ( cvt.ownership() )
            device::copy(cvt.array<type,1,device2>::base::begin(), cvt.array<type,1,device2>::base::end(), self.base::begin());
        else
            device::copy(cvt.array<type,1,device2>::upper::begin(), cvt.array<type,1,device2>::upper::end(), self.base::begin());
    else
        if ( cvt.ownership() )
            device2::copy(cvt.array<type,1,device2>::base::begin(), cvt.array<type,1,device2>::base::end(), self.base::begin());
        else
            device2::copy(cvt.array<type,1,device2>::upper::begin(), cvt.array<type,1,device2>::upper::end(), self.base::begin());
}

template < class type, class device >
constexpr int array<type,1,device>::dimension ( )
{
    return 1;
}

template < class type, class device >
constexpr int array<type,1,device>::size ( ) const
{
    return ownership() ? base::size() otherwise
                         upper::size();
}

template < class type, class device >
constexpr int array<type,1,device>::capacity ( ) const
{
    return ownership() ? base::capacity() otherwise
                         throw value_error("cannot get memory capacity from array: it does not own its data");
}

template < class type, class device >
constexpr static_array<int,1> array<type,1,device>::shape ( ) const
{
    return { size() };
}

template < class type, class device >
constexpr bool array<type,1,device>::empty ( ) const
{
    return ownership() ? base::empty() otherwise
                         upper::empty();
}

template < class type, class device >
constexpr array<type,1,device>::pointer array<type,1,device>::data ( )
{
    return ownership()     ? base::data() otherwise
           is_contiguous() ? upper::data() otherwise
                             throw logic_error("cannot get native data from array: it does not own its data, meanwhile the borrowed data is not contiguous");
}

template < class type, class device >
constexpr array<type,1,device>::const_pointer array<type,1,device>::data ( ) const
{
    return ownership()     ? base::data() otherwise
           is_contiguous() ? upper::data() otherwise
                             throw logic_error("cannot get native data from array: it does not own its data, meanwhile the borrowed data is not contiguous");
}

template < class type, class device >
constexpr array<type,1,device>::iterator array<type,1,device>::begin ( )
{
    return ownership() ? iterator(base::data(), 1) otherwise
                         upper::begin();
}

template < class type, class device >
constexpr array<type,1,device>::const_iterator array<type,1,device>::begin ( ) const
{
    return ownership() ? const_iterator(base::data(), 1) otherwise
                         upper::begin();
}

template < class type, class device >
constexpr array<type,1,device>::iterator array<type,1,device>::end ( )
{
    return ownership() ? iterator(base::data() + base::size(), 1) otherwise
                         upper::end();
}

template < class type, class device >
constexpr array<type,1,device>::const_iterator array<type,1,device>::end ( ) const
{
    return ownership() ? const_iterator(base::data() + base::size(), 1) otherwise
                         upper::end();
}

template < class type, class device >
constexpr array<type,1,device>::reference array<type,1,device>::operator [] ( int pos )
{
    #if debug
    if ( pos < -size() or pos == 0 or pos > size() )
        throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    return ownership() ? pos >= 0 ? base ::operator[](pos-1)             otherwise
                                    base ::operator[](pos+base::size())  otherwise
                         pos >= 0 ? upper::operator[](pos-1)             otherwise
                                    upper::operator[](pos+upper::size());
}

template < class type, class device >
constexpr array<type,1,device>::const_reference array<type,1,device>::operator [] ( int pos ) const
{
    #if debug
    if ( pos < -size() or pos == 0 or pos > size() )
        throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    return ownership() ? pos >= 0 ? base ::operator[](pos-1)             otherwise
                                    base ::operator[](pos+base::size())  otherwise
                         pos >= 0 ? upper::operator[](pos-1)             otherwise
                                    upper::operator[](pos+upper::size());
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::clear ( )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot clear array: it does not own its data");
    #endif

    base::clear();
    base::shrink_to_fit();
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::resize ( int new_size )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot resize array: it does not own its data");
    if ( new_size < 0 )
        throw value_error("resize array with negative size {}", new_size);
    #endif

    base::resize(new_size);
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::resize ( static_array<int,1> new_shape )
{
    return resize(new_shape[1]);
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::push ( type new_value )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot push into array: it does not own its data");
    #endif

    base::push_back(std::move(new_value));
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::pop ( int old_pos )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot pop from array: it does not own its data");
    if ( old_pos < -int(base::size()) or old_pos == 0 or old_pos > int(base::size()) )
        throw index_error("index {} is out of range with size {}", old_pos, base::size());
    #endif

    base::erase(old_pos >= 0 ? base::begin() + old_pos - 1 otherwise base::begin() + old_pos + base::size());
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::insert ( int new_pos, type new_value )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot insert into array: it does not own its data");
    if ( new_pos < -int(base::size()) or new_pos == 0 or new_pos > int(base::size()) )
        throw index_error("index {} is out of range with size {}", new_pos, base::size());
    #endif
    
    base::insert(new_pos >= 0 ? base::begin() + new_pos - 1 otherwise base::begin() + new_pos + base::size(), std::move(new_value));
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::erase ( int old_pos_1, int old_pos_2 )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot erase from array: it does not own its data");
    #endif

    let abs_pos_1 = old_pos_1 >= 0 ? old_pos_1 otherwise old_pos_1 + base::size();
    let abs_pos_2 = old_pos_2 >= 0 ? old_pos_2 otherwise old_pos_2 + base::size();
    #if debug
    if ( ( ( abs_pos_1 < 1 or abs_pos_1 > size() ) or
           ( abs_pos_2 < 1 or abs_pos_2 > size() ) )
    and not // Except for below:
         ( ( abs_pos_1 == base::size() + 1 or abs_pos_2 == 0 ) and abs_pos_1 == abs_pos_2 + 1 ) )
        throw index_error("index [{}, {}] is out of range with size {}", old_pos_1, old_pos_2, base::size());
    #endif

    base::erase(base::begin() + abs_pos_1 - 1, base::begin() + abs_pos_2 - 1);
    return self;
}

template < class type, class device >
constexpr bool array<type,1,device>::ownership ( ) const
{
    return upper::ownership();
}

template < class type, class device >
constexpr bool array<type,1,device>::is_contiguous ( ) const
{
    return ownership() or upper::is_contiguous();
}

template < class type, class device >
constexpr bool array<type,1,device>::is_strided ( ) const
{
    return not ownership() and upper::is_strided();
}

template < class type, class device >
constexpr bool array<type,1,device>::is_transposed ( ) const
{
    return not ownership() and upper::is_transposed();
}

template < class type, class device >
constexpr auto array<type,1,device>::mdspan ( )
{
    #if debug
    if ( not is_contiguous() )
        throw logic_error("applying a contiguous mdspan on a non-contiguous array");
    #endif
    using mdspan = std::mdspan<type,std::dextents<int,1>,typename device::layout_type,typename device::template accessor_type<type>>;
    return mdspan(data(), size());
}

template < class type, class device >
constexpr const auto array<type,1,device>::mdspan ( ) const
{
    #if debug
    if ( not is_contiguous() )
        throw logic_error("applying a contiguous mdspan on a non-contiguous array");
    #endif
    using mdspan = std::mdspan<type,std::dextents<int,1>,typename device::layout_type,typename device::template const_accessor_type<type>>;
    return mdspan(data(), size());
}

template < class type, class device >
constexpr auto array<type,1,device>::mdspan_strided ( )
{
    #if debug
    if ( not is_strided() )
        throw logic_error("applying a strided mdspan on a non-strided array");
    #endif
    using mdspan = std::mdspan<type,std::dextents<int,1>,std::layout_stride,typename device::template accessor_type<type>>;
    return mdspan(upper::get_pointer(0), std::layout_stride::template mapping<std::dextents<int,1>>(std::dextents<int,1>(upper::size()), std::array<int,1>{upper::get_size_top()/upper::size()}));
}

template < class type, class device >
constexpr const auto array<type,1,device>::mdspan_strided ( ) const
{
    #if debug
    if ( not is_strided() )
        throw logic_error("applying a strided mdspan on a non-strided array");
    #endif
    using mdspan = std::mdspan<type,std::dextents<int,1>,std::layout_stride,typename device::template const_accessor_type<type>>;
    return mdspan(upper::get_pointer(0), std::layout_stride::template mapping<std::dextents<int,1>>(std::dextents<int,1>(upper::size()), std::array<int,1>{upper::get_size_top()/upper::size()}));
}
