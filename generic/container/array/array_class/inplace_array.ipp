#pragma once

/// Class inplace_array

// Core

template < class type, int len >
constexpr inplace_array<type,len>::inplace_array ( const inplace_array& init )
    requires std::copyable<type>
    extends m ( init.m )
{
    std::copy ( init.begin(), init.end(), begin() );
}

template < class type, int len >
constexpr inplace_array<type,len>::inplace_array ( inplace_array&& init )
    extends m ( init.m )
{
    std::move ( init.begin(), init.end(), begin() );
}

template < class type, int len >
constexpr inplace_array<type,len>::inplace_array ( int init_size )
    extends m ( init_size )
{
    #if debug
        if ( size() < 0 or size() > capacity() )
            throw value_error("initialize inplace_array with size {} out of capacity {}", size(), capacity());
    #endif
}

template < class type, int len >
constexpr inplace_array<type,len>::inplace_array ( int init_size, const type& init_arr )
    requires std::copyable<type>
    extends inplace_array ( init_size )
{
    std::fill ( begin(), end(), init_arr );
}

template < class type, int len >
constexpr inplace_array<type,len>::inplace_array ( int init_size, function_type<type()> auto init_arr )
    extends inplace_array ( init_size )
{
    std::generate ( begin(), end(), init_arr );
}

template < class type, int len >
constexpr inplace_array<type,len>::inplace_array ( int init_size, function_type<type(int)> auto init_arr )
    extends inplace_array ( init_size )
{
    for ( int i in range(size()) )
        self[i] = init_arr(i);
}

template < class type, int len >
constexpr inplace_array<type,len>::inplace_array ( std::initializer_list<type>&& init )
    extends inplace_array ( init.size() )
{
    std::move ( const_cast<type*>(init.begin()), const_cast<type*>(init.end()), begin() );
}

template < class type, int len >
constexpr inplace_array<type,len>::inplace_array ( const array_type<type> auto& init )
    requires std::copyable<type>
    extends inplace_array ( init.size() )
{
    std::copy ( init.begin(), init.end(), begin() );
}

template < class type, int len >
constexpr inplace_array<type,len>::inplace_array ( const range_type<type> auto& init )
    requires std::copyable<type>
    extends inplace_array ( init.size() )
{
    std::copy ( init.begin(), init.end(), begin() );
}

template < class type, int len >
constexpr inplace_array<type,len>::inplace_array ( std::from_range_t, std::ranges::input_range auto&& r )
    requires requires { std::declval<inplace_array>().push(*std::ranges::begin(r)); }
{
    if constexpr ( requires { std::ranges::size(r); self[1] = *std::ranges::begin(r); } )
    {
        resize ( std::ranges::size(r) );
        std::move ( std::ranges::begin(r), std::ranges::end(r), begin() );
    }

    else
        for ( auto&& v in r )
            self.push(std::forward<decltype(v)>(v));
}

template < class type, int len >
constexpr inplace_array<type,len>::inplace_array ( std::from_range_t, std::ranges::input_range auto&& r, int init_size )
    requires ( requires { std::declval<inplace_array>().push(*std::ranges::begin(r)); } )
    extends inplace_array ( init_size )
{
    int i = 0;
    for ( auto&& v in r )
    {
        i++;

        #if debug
            if ( i > size() )
                throw value_error("cannot move range of size >= {} into inplace_array of size {}", i, size());
        #endif
        self[i] = std::forward<decltype(v)>(v);
    }

    #if debug
        if ( i < size() )
            throw value_error("cannot move range of size {} into inplace_array of size {}", i, size());
    #endif
}

template < class type, int len >
constexpr inplace_array<type,len>& inplace_array<type,len>::operator = ( const inplace_array& right )
    requires std::copyable<type>
{
    resize ( right.size() );
    std::copy ( right.begin(), right.end(), begin() );
    return self;
}

template < class type, int len >
constexpr inplace_array<type,len>& inplace_array<type,len>::operator = ( inplace_array&& right )
{
    resize ( right.size() );
    std::move ( right.begin(), right.end(), begin() );
    return self;
}



// Conversion

template < class type, int len >
template < int len2 >
constexpr inplace_array<type,len>::inplace_array ( const inplace_array<type,len2>& cvt )
    requires ( len != len2 ) and std::copyable<type>
{
    resize ( cvt.size() );
    std::copy ( cvt.begin(), cvt.end(), begin() );
}

template < class type, int len >
template < int len2 >
constexpr inplace_array<type,len>::inplace_array ( inplace_array<type,len2>&& cvt )
    requires ( len != len2 )
{
    resize ( cvt.size() );
    std::move ( cvt.begin(), cvt.end(), begin() );
}

template < class type, int len >
template < class type2, int len2 >
constexpr inplace_array<type,len>::inplace_array ( const inplace_array<type2,len2>& cvt )
    requires std::convertible_to<type2,type> but ( not std::same_as<type,type2> )
{
    resize ( cvt.size() );
    std::transform ( cvt.begin(), cvt.end(), begin(), [] (const type2& arr) { return type1(arr); } );
}

template < class type, int len >
template < class type2, int len2 >
constexpr inplace_array<type,len>::inplace_array ( const inplace_array<type2,len2>& cvt )
    requires std::constructible_from<type,type2> but ( not std::convertible_to<type2,type> )
{
    resize ( cvt.size() );
    std::transform ( cvt.begin(), cvt.end(), begin(), [] (const type2& arr) { return type1(arr); } );
}

// Interface

template < class type, int len >
constexpr int inplace_array<type,len>::size ( ) const
{
    return m;
}

template < class type, int len >
constexpr int inplace_array<type,len>::capacity ( )
{
    return len;
}

template < class type, int len >
constexpr bool inplace_array<type,len>::empty ( ) const
{
    return size() == 0;
}

template < class type, int len >
constexpr inplace_array<type,len>& inplace_array<type,len>::resize ( int new_size )
{
    #if debug
        if ( new_size < 0 or new_size > capacity() )
            throw value_error("cannot resize inplace_array of size {} capacity {} into size {}", size(), capacity(), new_size);
    #endif

    std::fill ( begin() + new_size, begin() + size(), type() );
    m = new_size;
    return self;
}

template < class type, int len >
constexpr type* inplace_array<type,len>::data ( )
{
    return arr;
}

template < class type, int len >
constexpr const type* inplace_array<type,len>::data ( ) const
{
    return arr;
}

template < class type, int len >
constexpr type* inplace_array<type,len>::begin ( )
{
    return arr;
}

template < class type, int len >
constexpr const type* inplace_array<type,len>::begin ( ) const
{
    return arr;
}

template < class type, int len >
constexpr type* inplace_array<type,len>::end ( )
{
    return arr + size();
}

template < class type, int len >
constexpr const type* inplace_array<type,len>::end ( ) const
{
    return arr + size();
}

template < class type, int len >
constexpr type& inplace_array<type,len>::operator [] ( int pos )
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    return pos > 0 ? arr[pos-1] otherwise arr[pos+size()];
}

template < class type, int len >
constexpr const type& inplace_array<type,len>::operator [] ( int pos ) const
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    return pos > 0 ? arr[pos-1] otherwise arr[pos+size()];
}