#pragma once


/// Class array_line

template < class type, int dim >
constexpr array_line<type,dim>::array_line ( const array<type,dim>& init )
    extends array<type,dim> ( init )
{

}

template < class type, int dim >
constexpr array_line<type,dim>::array_line ( array<type,dim>&& init )
    extends array<type,dim> ( std::move ( init ) )
{

}

template < class type, int dim >
constexpr array_line<type,dim>& array_line<type,dim>::operator = ( const array<type,dim>& init )
{
    #if debug
        if ( shape() != init.shape() )
            throw value_error("cannot copy array of shape {} into array_line of shape {}", init.shape(), shape());
    #endif

    array<type,dim>::operator = ( init );
    return self;
}

template < class type, int dim >
constexpr array_line<type,dim>& array_line<type,dim>::operator = ( array<type,dim>&& init )
{
    #if debug
        if ( shape() != init.shape() )
            throw value_error("cannot move array of shape {} into array_line of shape {}", init.shape(), shape());
    #endif

    array<type,dim>::operator = ( std::move ( init ) );
    return self;
}