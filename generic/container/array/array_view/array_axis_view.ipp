#pragma once

/// Class array_axis_view

// Host

template < class container_type, int axis, int axis_to_fill >
constexpr container_type& array_axis_view<container_type,axis,axis_to_fill>::host ( )
{
    return arr;
}

template < class container_type, int axis, int axis_to_fill >
constexpr const container_type& array_axis_view<container_type,axis,axis_to_fill>::host ( ) const
{
    return arr;
}

// Constructor

template < class container_type, int axis, int axis_to_fill >
constexpr array_axis_view<container_type,axis,axis_to_fill>::array_axis_view ( container_type& init_arr, const coor_type& init_idx, buff_type* init_buff_ptr )
    extends arr      ( init_arr ),
            idx      ( init_idx ),
            buff_ptr ( init_buff_ptr )
{

}

// Core

template < class container_type, int axis, int axis_to_fill >
constexpr array_axis_view<container_type,axis,axis_to_fill>::array_axis_view ( const array_axis_view& init )
    requires ( axis_to_fill == 2 )
    extends arr ( init.arr )
{
    buff_ptr = new buff_type();
    buff_own = true;

    if constexpr ( container_type::dimension() == 2 ) // In which only resize(int) is legal.
        if constexpr ( axis == 1 or axis == -2 )
            buff_ptr->resize ( host().column() );
        else
            buff_ptr->resize ( host().row() );
    else
        buff_ptr->resize ( host().tuple_shape().template pop<axis>() );

    std::copy ( init.begin(), init.end(), buff_ptr->begin() );
}

template < class container_type, int axis, int axis_to_fill >
constexpr array_axis_view<container_type,axis,axis_to_fill>::array_axis_view ( array_axis_view&& init )
    requires ( axis_to_fill == 2 )
    extends arr ( init.arr )
{
    buff_ptr = new buff_type();
    buff_own = true;

    if constexpr ( container_type::dimension() == 2 ) // In which only resize(int) is legal.
        if constexpr ( axis == 1 or axis == -2 )
            buff_ptr->resize ( host().column() );
        else
            buff_ptr->resize ( host().row() );
    else
        buff_ptr->resize ( host().tuple_shape().template pop<axis>() );

    std::move ( init.begin(), init.end(), buff_ptr->begin() );
}

template < class container_type, int axis, int axis_to_fill >
constexpr array_axis_view<container_type,axis,axis_to_fill>::~array_axis_view ( )
{
    if ( buff_own )
        delete buff_ptr;
}

template < class container_type, int axis, int axis_to_fill >
constexpr array_axis_view<container_type,axis,axis_to_fill>& array_axis_view<container_type,axis,axis_to_fill>::operator = ( const array_axis_view& right )
{
    std::copy ( right.begin(), right.end(), begin() );
    return self;
}

template < class container_type, int axis, int axis_to_fill >
constexpr array_axis_view<container_type,axis,axis_to_fill>& array_axis_view<container_type,axis,axis_to_fill>::operator = ( array_axis_view&& right )
{
    std::move ( right.begin(), right.end(), begin() );
    return self;
}

// N-dimension

template < class container_type, int axis, int axis_to_fill >
constexpr int array_axis_view<container_type,axis,axis_to_fill>::dimension ( )
{
    return container_type::dimension() - axis_to_fill + 1;
}

template < class container_type, int axis, int axis_to_fill >
constexpr array<int> array_axis_view<container_type,axis,axis_to_fill>::shape ( ) const
{
    if constexpr ( dimension() == 1 )
        return array<int> { size() };
    else
        if ( not empty() )
            return array<int> { row() } .push ( self[1].shape() );
        else
            return array<int> { row() } .push ( array<int> ( dimension() - 1 ) );
}

// Conversion

template < class container_type, int axis, int axis_to_fill >
constexpr array_axis_view<container_type,axis,axis_to_fill>& array_axis_view<container_type,axis,axis_to_fill>::operator = ( const array_type<value_type,dimension()> auto& cvt )
    requires ( axis_to_fill >= 2 )
{
    #if debug
        if ( cvt.shape() != self.shape() )
            throw value_error("cannot copy array of shape {} into array_view of shape {}", cvt.shape(), self.shape());
    #endif

    std::copy ( cvt.begin(), cvt.end(), begin() );
    return self;
}

// Interface

template < class container_type, int axis, int axis_to_fill >
constexpr int array_axis_view<container_type,axis,axis_to_fill>::row ( ) const
    requires ( dimension() >= 2 )
{
    if constexpr ( axis_to_fill == 1 )
        return host().tuple_shape().template get<axis>();
    else if constexpr ( axis_to_fill <= axis )
        return host().tuple_shape().template get<axis_to_fill-1>();
    else
        return host().tuple_shape().template get<axis_to_fill>();
}

template < class container_type, int axis, int axis_to_fill >
constexpr int array_axis_view<container_type,axis,axis_to_fill>::column ( ) const
    requires ( dimension() == 2 )
{
    if constexpr ( axis != container_type::dimension() )
        return host().tuple_shape().template get<-1>();
    else
        return host().tuple_shape().template get<-2>();
}

template < class container_type, int axis, int axis_to_fill >
constexpr int array_axis_view<container_type,axis,axis_to_fill>::size ( ) const
{
    if constexpr ( axis_to_fill == 1 )
        return host().size();
    else if constexpr ( axis_to_fill <= axis )
        return host().tuple_shape().template pop<axis>().template get<axis_to_fill-1,-1>().product();
    else
        return host().tuple_shape().template get<axis_to_fill,-1>().product();
}

template < class container_type, int axis, int axis_to_fill >
constexpr bool array_axis_view<container_type,axis,axis_to_fill>::empty ( ) const
{
    return host().empty();
}

template < class container_type, int axis, int axis_to_fill >
constexpr array_axis_view<container_type,axis,axis_to_fill>::iterator array_axis_view<container_type,axis,axis_to_fill>::begin ( )
{
    return iterator ( self, 1 );
}

template < class container_type, int axis, int axis_to_fill >
constexpr array_axis_view<container_type,axis,axis_to_fill>::const_iterator array_axis_view<container_type,axis,axis_to_fill>::begin ( ) const
{
    return const_iterator ( self, 1 );
}

template < class container_type, int axis, int axis_to_fill >
constexpr array_axis_view<container_type,axis,axis_to_fill>::iterator array_axis_view<container_type,axis,axis_to_fill>::end ( )
{
    if constexpr ( dimension() == 1 )
        return iterator ( self, size() + 1 );
    else
        return iterator ( self, row() + 1 );
}

template < class container_type, int axis, int axis_to_fill >
constexpr array_axis_view<container_type,axis,axis_to_fill>::const_iterator array_axis_view<container_type,axis,axis_to_fill>::end ( ) const
{
    if constexpr ( dimension() == 1 )
        return const_iterator ( self, size() + 1 );
    else
        return const_iterator ( self, row() + 1 );
}

template < class container_type, int axis, int axis_to_fill >
constexpr decltype(auto) array_axis_view<container_type,axis,axis_to_fill>::operator [] ( int pos )
    requires ( dimension() == 1 )
{
    let new_idx = idx;

    if constexpr ( axis != container_type::dimension() )
        new_idx.template get<-1>() = pos;
    else
        new_idx.template get<-2>() = pos;

    return buff_ptr == nullptr ? at_arr ( host(), new_idx ) otherwise at_buff ( *buff_ptr, new_idx );
}

template < class container_type, int axis, int axis_to_fill >
constexpr decltype(auto) array_axis_view<container_type,axis,axis_to_fill>::operator [] ( int pos ) const
    requires ( dimension() == 1 )
{
    let new_idx = idx;

    if constexpr ( axis != container_type::dimension() )
        new_idx.template get<-1>() = pos;
    else
        new_idx.template get<-2>() = pos;

    return buff_ptr == nullptr ? at_arr ( host(), new_idx ) otherwise at_buff ( const_cast<const buff_type&>(*buff_ptr), new_idx );
}

template < class container_type, int axis, int axis_to_fill >
constexpr auto array_axis_view<container_type,axis,axis_to_fill>::operator [] ( int pos )
    requires ( dimension() >= 2 )
{
    let new_idx = idx;

    if constexpr ( axis_to_fill == 1 )
        new_idx.template get<axis>() = pos;
    else if constexpr ( axis_to_fill <= axis )
        new_idx.template get<axis_to_fill-1>() = pos;
    else
        new_idx.template get<axis_to_fill>() = pos;

    return array_axis_view<container_type,axis,axis_to_fill+1> ( host(), new_idx, buff_ptr );
}

template < class container_type, int axis, int axis_to_fill >
constexpr const auto array_axis_view<container_type,axis,axis_to_fill>::operator [] ( int pos ) const
    requires ( dimension() >= 2 )
{
    let new_idx = idx;

    if constexpr ( axis_to_fill == 1 )
        new_idx.template get<axis>() = pos;
    else if constexpr ( axis_to_fill <= axis )
        new_idx.template get<axis_to_fill-1>() = pos;
    else
        new_idx.template get<axis_to_fill>() = pos;

    return array_axis_view<container_type,axis,axis_to_fill+1> ( const_cast<container_type&>(host()), new_idx, buff_ptr );
}

// Auxiliary

template < class container_type, int axis, int axis_to_fill >
template < int count >
constexpr auto& array_axis_view<container_type,axis,axis_to_fill>::at_arr ( auto& arr, const auto& coor )
{
    if constexpr ( coor.size() == 1 )
        return arr[coor.template get<1>()];
    else
        return at_arr<count+1> ( arr[coor.template get<1>()], coor.template get<2,-1>() );
}

template < class container_type, int axis, int axis_to_fill >
template < int count >
constexpr auto& array_axis_view<container_type,axis,axis_to_fill>::at_arr ( auto&& arr, const auto& coor )
{
    return at_arr ( arr, coor );
}

template < class container_type, int axis, int axis_to_fill >
template < int count >
constexpr const auto& array_axis_view<container_type,axis,axis_to_fill>::at_arr ( const auto& arr, const auto& coor )
{
    if constexpr ( coor.size() == 1 )
        return arr[coor.template get<1>()];
    else
        return at_arr<count+1> ( arr[coor.template get<1>()], coor.template get<2,-1>() );
}

template < class container_type, int axis, int axis_to_fill >
template < int count >
constexpr auto& array_axis_view<container_type,axis,axis_to_fill>::at_buff ( auto& buff, const auto& coor )
{
    if constexpr ( coor.size() == 1 or ( coor.size() == 2 and ( axis == container_type::dimension() or axis == -1 ) ) ) // coor == [x] or [x,0]
        return buff[coor.template get<1>()];
    else if constexpr ( count != axis and count != axis + container_type::dimension() + 1 )
        return at_buff<count+1> ( buff[coor.template get<1>()], coor.template get<2,-1>() );
    else
        return at_buff<count+1> ( buff,                         coor.template get<2,-1>() ); // Skip.
}

template < class container_type, int axis, int axis_to_fill >
template < int count >
constexpr auto& array_axis_view<container_type,axis,axis_to_fill>::at_buff ( auto&& buff, const auto& coor )
{
    return at_buff ( buff, coor );
}

template < class container_type, int axis, int axis_to_fill >
template < int count >
constexpr const auto& array_axis_view<container_type,axis,axis_to_fill>::at_buff ( const auto& buff, const auto& coor )
{
    if constexpr ( coor.size() == 1 or ( coor.size() == 2 and ( axis == container_type::dimension() or axis == -1 ) ) ) // coor == [x] or [x,0]
        return buff[coor.template get<1>()];
    else if constexpr ( count != axis and count != axis + container_type::dimension() + 1 )
        return at_buff<count+1> ( buff[coor.template get<1>()], coor.template get<2,-1>() );
    else
        return at_buff<count+1> ( buff,                         coor.template get<2,-1>() ); // Skip.
}





// Swap

template < class container_type, int axis, int axis_to_fill >
constexpr void swap ( array_axis_view<container_type,axis,axis_to_fill>&& a, array_axis_view<container_type,axis,axis_to_fill>&& b )
{
    std::swap_ranges ( a.begin(), a.end(), b.begin() );
}