#pragma once

template < class type, class device >
constexpr array<type,1,device>::array ( const array& init )
    requires copyable<type>
{
    if ( init.ownership() ) [[likely]]
        self.base::operator=(static_cast<const base&>(init));
    else
    {
        self.resize(init.size());
        device::copy(init.begin(), init.end(), self.begin());
    }
} 

template < class type, class device >
constexpr array<type,1,device>::array ( array&& init )
{
    if ( init.ownership() ) [[likely]]
        self.base::operator=(static_cast<base&&>(init));
    else
    {
        self.resize(init.size());
        device::move(init.begin(), init.end(), self.begin());
    }
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::operator = ( const array& right )
    requires copyable<type>
{
    if ( self.ownership() and right.ownership() ) [[likely]]
        self.base::operator=(static_cast<const base&>(right));

    else if ( self.ownership() and not right.ownership() )
    {
        self.resize(right.size());
        device::copy(right.begin(), right.end(), self.begin());
    }

    else
    {
        #if debug
        if ( self.size() != right.size() )
            throw logic_error("cannot copy assign array: the left array does not own its data, and the right array mismatches on size (with left_size = {}, right_size = {})", self.size(), right.size());
        #endif
        device::copy(right.begin(), right.end(), self.begin());
    }

    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::operator = ( array&& right )
{
    if ( self.ownership() and right.ownership() ) [[likely]]
        self.base::operator=(static_cast<base&&>(right));

    else if ( self.ownership() and not right.ownership() )
    {
        self.resize(right.upper::size());
        device::move(right.begin(), right.end(), self.begin());
    }

    else
    {
        #if debug
        if ( self.size() != right.size() )
            throw logic_error("cannot move assign array: the left array does not own its data, and the right array mismatches on size (with left_size = {}, right_size = {})", self.size(), right.size());
        #endif
        device::move(right.begin(), right.end(), self.begin());
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
    device::generate(self.begin(), self.end(), init_value);
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const function_type<type(int)> auto init_value )
    extends array ( init_size )
{
    for ( int i in range(init_size) )
        self[i] = init_value(i);
}

template < class type, class device >
constexpr array<type,1,device>::array ( std::initializer_list<type> init )
    requires copyable<type>
    extends base ( std::forward<decltype(init)>(init) )
{
    
}

template < class type, class device >
constexpr array<type,1,device>::array ( range<type> init )
    requires copyable<type>
    extends base ( init.begin(), init.end() )
{

}

template < class type, class device >
template < int len >
constexpr array<type,1,device>::array ( const inplace_array<type,len,device>& cvt )
    extends array ( cvt.size() )
{
    device::copy(cvt.begin(), cvt.end(), self.begin());
}

template < class type, class device >
template < int len >
constexpr array<type,1,device>::array ( const static_array<type,len,device>& cvt )
    extends array ( cvt.size() )
{
    device::copy(cvt.begin(), cvt.end(), self.begin());
}

template < class type, class device >
template < class type2 >
constexpr array<type,1,device>::array ( const array<type2,1,device>& cvt )
    requires convertible_to<type2,type> but ( not same_as<type,type2> )
    extends array ( cvt.size() )
{
    device::transform(cvt.array<type2,1,device>::base::begin(), cvt.array<type2,1,device>::end(), self.begin(), [] (const auto& val) { return type(val); });
}

template < class type, class device >
template < class type2 >
constexpr array<type,1,device>::array ( const array<type2,1,device>& cvt )
    requires constructible_from<type,type2> but ( not convertible_to<type2,type> )
    extends array ( cvt.size() )
{
    device::transform(cvt.array<type2,1,device>::base::begin(), cvt.array<type2,1,device>::base::end(), self.base::begin(), [] (const auto& val) { return type(val); });
}

template < class type, class device >
template < class device2 >
constexpr array<type,1,device>::array ( const array<type,1,device2>& cvt )
    requires same_as<device,cpu> or same_as<device2,cpu>
    extends array ( cvt.size() )
{
    if constexpr ( not same_as<device,cpu> )
        device::copy(cvt.begin(), cvt.end(), self.begin());
    else
        device2::copy(cvt.begin(), cvt.end(), self.begin());
}

template < class type, class device >
constexpr int array<type,1,device>::dimension ( )
{
    return 1;
}

template < class type, class device >
constexpr int array<type,1,device>::size ( ) const
{
    if ( ownership() ) [[likely]]
        return base::size();
    else
        return upper::size();
}

template < class type, class device >
constexpr int array<type,1,device>::capacity ( ) const
{
    if ( ownership() ) [[likely]]
        return base::capacity();
    else
        throw value_error("cannot get memory capacity from array: it does not own its data");
}

template < class type, class device >
constexpr array<int> array<type,1,device>::shape ( ) const
{
    return { size() };
}

template < class type, class device >
constexpr inplace_array<int,1> array<type,1,device>::inplace_shape ( ) const
{
    return { size() };
}

template < class type, class device >
constexpr static_array<int,1> array<type,1,device>::static_shape ( ) const
{
    return { size() };
}

template < class type, class device >
constexpr bool array<type,1,device>::empty ( ) const
{
    if ( ownership() ) [[likely]]
        return base::empty();
    else
        return upper::empty();
}

template < class type, class device >
constexpr array<type,1,device>::pointer array<type,1,device>::data ( )
{
    if ( ownership() ) [[likely]]
        return base::data();
    else if ( contiguous() )
        return upper::data();
    else
        throw logic_error("cannot get native data from array: it does not own its data, meanwhile the borrowed data might be not contiguous");
}

template < class type, class device >
constexpr array<type,1,device>::const_pointer array<type,1,device>::data ( ) const
{
    if ( ownership() ) [[likely]]
        return base::data();
    else if ( contiguous() )
        return upper::data();
    else
        throw logic_error("cannot get native data from array: it does not own its data, meanwhile the borrowed data might be not contiguous");
}

template < class type, class device >
constexpr array<type,1,device>::iterator array<type,1,device>::begin ( )
{
    if ( ownership() ) [[likely]]
        return base::data();
    else
        return upper::begin();
}

template < class type, class device >
constexpr array<type,1,device>::const_iterator array<type,1,device>::begin ( ) const
{
    if ( ownership() ) [[likely]]
        return base::data();
    else
        return upper::begin();
}

template < class type, class device >
constexpr array<type,1,device>::iterator array<type,1,device>::end ( )
{
    if ( ownership() ) [[likely]]
        return base::data() + base::size();
    else
        return upper::end();
}

template < class type, class device >
constexpr array<type,1,device>::const_iterator array<type,1,device>::end ( ) const
{
    if ( ownership() ) [[likely]]
        return base::data() + base::size();
    else
        return upper::end();
}

template < class type, class device >
constexpr array<type,1,device>::reference array<type,1,device>::operator [] ( int pos )
{
    #if debug
    if ( pos < -size() or pos == 0 or pos > size() )
        throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    if ( ownership() ) [[likely]]
        return pos >= 0 ? base::operator[](pos-1) otherwise
                          base::operator[](pos+size());
    else
        return pos >= 0 ? upper::operator[](pos-1) otherwise
                          upper::operator[](pos+size());
}

template < class type, class device >
constexpr array<type,1,device>::const_reference array<type,1,device>::operator [] ( int pos ) const
{
    #if debug
    if ( pos < -size() or pos == 0 or pos > size() )
        throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    if ( ownership() ) [[likely]]
        return pos >= 0 ? base::operator[](pos-1) otherwise
                          base::operator[](pos+size());
    else
        return pos >= 0 ? upper::operator[](pos-1) otherwise
                          upper::operator[](pos+size());
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::clear ( )
{
    #if debug
    if ( not ownership() ) [[unlikely]]
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
    if ( not ownership() ) [[unlikely]]
        throw logic_error("cannot resize array: it does not own its data");
    if ( new_size < 0 )
        throw value_error("resize array with negative size {}", new_size);
    #endif

    base::resize(new_size);
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::push ( type new_value )
{
    #if debug
    if ( not ownership() ) [[unlikely]]
        throw logic_error("cannot push into array: it does not own its data");
    #endif

    base::push_back(std::move(new_value));
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::pop ( int old_pos )
{
    #if debug
    if ( not ownership() ) [[unlikely]]
        throw logic_error("cannot pop from array: it does not own its data");
    if ( old_pos < -size() or old_pos == 0 or old_pos > size() )
        throw index_error("index {} is out of range with size {}", old_pos, size());
    #endif

    base::erase(old_pos >= 0 ? base::begin() + old_pos - 1 otherwise base::begin() + old_pos + base::size());
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::insert ( int new_pos, type new_value )
{
    #if debug
    if ( not ownership() ) [[unlikely]]
        throw logic_error("cannot insert into array: it does not own its data");
    if ( new_pos < -size() or new_pos == 0 or new_pos > size() )
        throw index_error("index {} is out of range with size {}", new_pos, size());
    #endif
    
    base::insert(new_pos >= 0 ? base::begin() + new_pos - 1 otherwise base::begin() + new_pos + base::size(), std::move(new_value));
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::erase ( int old_pos_1, int old_pos_2 )
{
    #if debug
    if ( not ownership() ) [[unlikely]]
        throw logic_error("cannot erase from array: it does not own its data");
    #endif

    let p1 = old_pos_1 >= 0 ? old_pos_1 otherwise old_pos_1 + size();
    let p2 = old_pos_2 >= 0 ? old_pos_2 otherwise old_pos_2 + size();

    #if debug
    if ( ( ( p1 < 1 or p1 > size() ) or
           ( p2 < 1 or p2 > size() ) )
    and not // Except for below:
         ( ( p1 == size() + 1 or p2 == 0 ) and p1 == p2 + 1 ) )
        throw index_error("index [{}, {}] is out of range with size {}", old_pos_1, old_pos_2, size());
    #endif

    base::erase(base::begin() + p1 - 1, base::begin() + p2 - 1);
}

template < class type, class device >
constexpr bool array<type,1,device>::ownership ( ) const
{
    return upper::ownership();
}

template < class type, class device >
constexpr bool array<type,1,device>::contiguous ( ) const
{
    return ownership() or upper::contiguous();
}

