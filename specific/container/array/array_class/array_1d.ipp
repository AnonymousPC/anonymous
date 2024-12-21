#pragma once

template < class type, class device >
constexpr array<type,1,device>::array ( const array& init )
    requires std::copyable<type>
{
    copy_from(init);
} 

template < class type, class device >
constexpr array<type,1,device>::array ( array&& init )
{
    move_from(init);
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::operator = ( const array& right )
    requires std::copyable<type>
{
    copy_from(right);
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::operator = ( array&& right )
{
    move_from(right);
}


template < class type, class device >
constexpr array<type,1,device>::array ( int init_size )
    extends device::template vector<type> ( init_size ),
{
    #if debug
        if ( init_size < 0 )
            throw value_error("initialize array with negative size {}", init_size);
    #endif
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const type& init_value )
    requires std::copyable<type>
    extends device::template vector<type> ( init_size, init_value )
{
    #if debug
        if ( init_size < 0 )
            throw value_error("initialize array with negative size {}", init_size);
    #endif
}

template < class type, class device >
constexpr array<type,1,device>::array ( const std::initializer_list<type>& init )
    requires std::copyable<type>
{
    std::copy(init.begin(), init.end(), begin());
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const function_type<type()> auto init_value )
    extends array ( init_size )
{
    device::generate(begin(), end(), init_value);
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const function_type<type(int)> auto init_value )
    extends array ( init_size )
{
    for ( int i in range(init_size) )
        self[i] = init_value(i);
}

template < class type, class device >
constexpr array<type,1,device>::array ( const range<type>& init )
    requires std::copyable<type>
    extends array ( init.size() )
{
    device::copy(init.begin(), init.end(), begin());
}

template < class type, class device >
constexpr array<type,1,device>::array ( std::from_range_t, std::ranges::input_range auto&& r )
    requires std::convertible_to<std::ranges::range_value_t<decltype(r)>,type>
{
    if constexpr ( requires { r.size(); } )
    {
        resize(r.size());
        if constexpr ( requires { device::move(r.begin(), r.end(), begin()); } )
            device::move(r.begin(), r.end(), begin());
        else
            std::ranges::move(r, begin());
    }
    else
        for ( auto&& val in r )
            self.push(std::forward<decltype(val)>(val));
}

template < class type, class device >
constexpr array<type,1,device>::array ( std::from_range_t, std::ranges::input_range auto&& r, int init_size )
    requires std::convertible_to<std::ranges::range_value_t<decltype(r)>,type>
    extends array ( init_size )
{
    #if debug
        if constexpr ( requires { r.size(); } )
            if ( r.size() != init_size )
                throw value_error("initialize array with ambiguous size (with range-size = {}, explicit-size = {})", r.size(), r);
    #endif

    if constexpr ( requires { device::move(r.begin(), r.end(), begin()); } )
        device::move(r.begin(), r.end(), begin());
    else
        std::ranges::move(r, begin());
}

template < class type, class device >
constexpr array<type,1,device>::array ( const array_type<type,1,device> auto& init )
    requires std::copyable<type>
    extends array ( init.size() )
{
    device::copy(init.begin(), init.end(), begin());
}

template < class type, class device >
template < class type2 >
constexpr array<type,1,device>::array ( const array_type<type2,1,device> auto& cvt )
    requires std::convertible_to<type2,type> but ( not std::same_as<type,type2> )
{
    resize(cvt.size());
    device::transform(cvt.begin(), cvt.end(), begin(), [] (const auto& val) { return type(val); });
}

template < class type, class device >
template < class type2 >
constexpr array<type,1,device>::array ( const array_type<type2,1,device> auto& cvt )
    requires std::constructible_from<type,type2> but ( not std::convertible_to<type2,type> )
{
    resize(cvt.size());
    device::transform(cvt.begin(), cvt.end(), begin(), [] (const auto& val) { return type(val); });
}

template < class type, class device >
constexpr int array<type,1,device>::size ( ) const
{
    return device::template vector<type>::size();
}

template < class type, class device >
constexpr int array<type,1,device>::capacity ( ) const
{
    return device::template vector<type>::capacity();
}

template < class type, class device >
constexpr bool array<type,1,device>::empty ( ) const
{
    return device::template vector<type>::empty();
}

template < class type, class device >
constexpr type* array<type,1,device>::data ( )
{
    return const_cast<type*>(device::template vector<type>::data());
}

template < class type, class device >
constexpr const type* array<type,1,device>::data ( ) const
{
    return device::template vector<type>::data();
}

template < class type, class device >
constexpr type* array<type,1,device>::begin ( )
{
    return const_cast<type*>(device::template vector<type>::data());
}

template < class type, class device >
constexpr const type* array<type,1,device>::begin ( ) const
{
    return device::template vector<type>::data();
}

template < class type, class device >
constexpr type* array<type,1,device>::end ( )
{
    return const_cast<type*>(device::template vector<type>::data()) + size();
}

template < class type, class device >
constexpr const type* array<type,1,device>::end ( ) const
{
    return device::template vector<type>::data() + size();
}

template < class type, class device >
constexpr type& array<type,1,device>::operator [] ( int pos )
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    return pos >= 0 ? device::template vector<type>::operator[](pos-1) otherwise
                      device::template vector<type>::operator[](pos+size());
}

template < class type, class device >
constexpr const type& array<type,1,device>::operator [] ( int pos ) const
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    return pos >= 0 ? device::template vector<type>::operator[](pos-1) otherwise
                      device::template vector<type>::operator[](pos+size());
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::clear ( )
{
    device::template vector<type>::clear();
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::resize ( int new_size )
{
    device::template vector<type>::resize(new_size);
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::push ( type new_value )
{
    device::template vector<type>::push_back(std::move(new_value));
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::pop ( int pos )
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    device::template vector<type>::erase(pos >= 0 ? device::template vector<type>::begin() + pos - 1 otherwise
                                                    device::template vector<type>::begin() + pos + size());
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::insert ( int pos, type new_value )
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    device::template vector<type>::insert(pos >= 0 ? device::template vector<type>::begin() + pos - 1 otherwise
                                                     device::template vector<type>::begin() + pos + size(),
                                          std::move(new_value));
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::erase ( int pos_1, int pos_2 )
{
    if ( pos_1 < 0 )
        pos_1 += size();
    if ( pos_2 < 0 )
        pos_2 += size();

    #if debug
        if ( ( ( pos_1 < 1 or pos_1 > size() ) or
               ( pos_2 < 1 or pos_2 > size() ) )
        and not // Except for below:
             ( ( pos_1 == size() + 1 or pos_2 == 0 ) and pos_1 == pos_2 + 1 ) )
            throw index_error("index [{},{}] is out of range with size {}", pos_1, pos_2, size());
    #endif

    device::template vector<type>::erase(device::template vector<type>::begin() + pos_1 - 1, device::template vector<type>::begin() + pos_2 - 1);
}
