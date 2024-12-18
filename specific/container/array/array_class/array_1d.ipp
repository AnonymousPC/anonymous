#pragma once

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size )
    extends device::vector<type> ( init_size )
{
    #if debug
        if ( init_size < 0 )
            throw value_error("initialize array with negative size {}", init_size);
    #endif
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const type& init_value )
    requires std::copyable<type>
    extends device::vector<type> ( init_size, init_value )
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
constexpr array<type,1,device>::array ( const array_type<type,1> auto& init )
    requires std::copyable<type>
    extends public ( init.size() )
{
    device::copy(init.begin(), init.end(), begin());
}