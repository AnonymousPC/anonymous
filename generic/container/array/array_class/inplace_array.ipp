#pragma once

template < class type, int len, class device >
constexpr inplace_array<type,len,device>::inplace_array ( int init_size )
    extends base ( init_size )
{
    #if debug
    if ( init_size < 0 )
        throw value_error("initialize inplace_array with negative size {}", init_size);
    if ( init_size > capacity() )
        throw value_error("initialize inplace_array with size {} out of capacity {}", init_size, capacity());
    #endif
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>::inplace_array ( int init_size, const type& init_value )
    requires copyable<type>
    extends base ( init_size, init_value )
{
    #if debug
    if ( init_size < 0 )
        throw value_error("initialize inplace_array with negative size {}", init_size);
    if ( init_size > capacity() )
        throw value_error("initialize inplace_array with size {} out of capacity {}", init_size, capacity());
    #endif
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>::inplace_array ( int init_size, function_type<type()> auto init_value )
    requires movable<type>
    extends inplace_array ( init_size )
{
    device::generate(begin(), end(), init_value);
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>::inplace_array ( int init_size, function_type<type(int)> auto init_value )
    requires movable<type>
    extends inplace_array ( init_size )
{
    for ( int i in range(size()) )
        self[i] = init_value(i);
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>::inplace_array ( std::initializer_list<type> init )
    requires copyable<type>
    extends base ( std::forward<decltype(init)>(init) )
{
    #if debug
    if ( int(init.size()) > capacity() )
        throw value_error("initialize inplace_array with size {} out of capacity {}", init.size(), size());
    #endif
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>::inplace_array ( range<type> init )
    requires copyable<type>
    extends base ( init.begin(), init.end() )
{
}

template < class type, int len, class device >
constexpr int inplace_array<type,len,device>::dimension ( )
{
    return 1;
}

template < class type, int len, class device >
constexpr int inplace_array<type,len,device>::size ( ) const
{
    return base::size();
}

template < class type, int len, class device >
constexpr int inplace_array<type,len,device>::capacity ( )
{
    return len;
}

template < class type, int len, class device >
constexpr static_array<int,1> inplace_array<type,len,device>::shape ( ) const
{
    return { size() };
}

template < class type, int len, class device >
constexpr bool inplace_array<type,len,device>::empty ( ) const
{
    return base::empty();
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>::pointer inplace_array<type,len,device>::data ( ) 
{
    return base::data();
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>::const_pointer inplace_array<type,len,device>::data ( ) const
{
    return base::data();
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>::iterator inplace_array<type,len,device>::begin ( ) 
{
    return base::begin();
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>::const_iterator inplace_array<type,len,device>::begin ( ) const
{
    return base::begin();
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>::iterator inplace_array<type,len,device>::end ( ) 
{
    return base::end();
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>::const_iterator inplace_array<type,len,device>::end ( ) const
{
    return base::end();
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>::reference inplace_array<type,len,device>::operator[] ( int pos )
{
    #if debug
    if ( pos < -size() or pos == 0 or pos > size() )
        throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    return pos >= 0 ? base::operator[](pos-1) otherwise
                      base::operator[](pos+size());
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>::const_reference inplace_array<type,len,device>::operator[] ( int pos ) const
{
    #if debug
    if ( pos < -size() or pos == 0 or pos > size() )
        throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    return pos >= 0 ? base::operator[](pos-1) otherwise
                      base::operator[](pos+size());
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>& inplace_array<type,len,device>::clear ( )
{
    base::clear();
    return self;
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>& inplace_array<type,len,device>::resize ( int new_size )
{
    #if debug
    if ( new_size < 0 )
        throw value_error("resize inplace_array with negative size {}", new_size);
    if ( new_size > capacity() )
        throw value_error("resize inplace_array with size {} out of capacity {}", new_size, capacity());
    #endif

    base::resize(new_size);
    return self;
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>& inplace_array<type,len,device>::push ( type new_value )
    requires movable<type>
{
    #if debug
    if ( size() == capacity() )
        throw value_error("cannot push into inplace_array: size has already reached capacity");
    #endif

    base::push(std::move(new_value));
    return self;
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>& inplace_array<type,len,device>::pop ( int old_pos )
    requires movable<type>
{
    #if debug
    if ( old_pos < -size() or old_pos == 0 or old_pos > size() )
        throw value_error("index {} is out of range with size {}", old_pos, size());
    #endif

    base::erase(old_pos >= 0 ? begin() + old_pos - 1 otherwise begin() + old_pos + size());
    return self;
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>& inplace_array<type,len,device>::insert ( int new_pos, type new_value )
    requires movable<type>
{
    #if debug
    if ( size() == capacity() )
        throw value_error("cannot insert into inplace_array: size has already reached capacity");
    if ( new_pos < -size() or new_pos == 0 or new_pos > size() )
        throw value_error("index {} is out of range with size {}", new_pos, size());
    #endif

    base::insert(new_pos >= 0 ? begin() + new_pos - 1 otherwise begin() + new_pos + size(), std::move(new_value));
    return self;
}

template < class type, int len, class device >
constexpr inplace_array<type,len,device>& inplace_array<type,len,device>::erase ( int old_pos_1, int old_pos_2 )
    requires movable<type>
{
    let p1 = old_pos_1 >= 0 ? old_pos_1 otherwise old_pos_1 + size();
    let p2 = old_pos_2 >= 0 ? old_pos_2 otherwise old_pos_2 + size();

    #if debug
    if ( ( ( p1 < 1 or p1 > size() ) or
           ( p2 < 1 or p2 > size() ) )
    and not // Except for below:
         ( ( p1 == size() + 1 or p2 == 0 ) and p1 == p2 + 1 ) )
        throw index_error("index [{}, {}] is out of range with size {}", old_pos_1, old_pos_2, size());
    #endif

    base::erase(begin() + p1 - 1, begin() + p2 - 1);
    return self;
}

template < class type, int len, class device >
constexpr bool inplace_array<type,len,device>::ownership ( )
{
    return true;
}

template < class type, int len, class device >
constexpr bool inplace_array<type,len,device>::contiguous ( )
{
    return true;
}