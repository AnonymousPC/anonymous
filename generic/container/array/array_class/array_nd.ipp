#pragma once

#define base_of_self ( static_cast<array<array<type,dim-1>>&> ( self ) )

/// Class array with multi-dimension


template < class type, int dim >
    requires ( dim >= 2 )
constexpr array<type,dim>::array ( int init_row, int_type auto... args )
    requires ( 1 + sizeof...(args) == dim )
    extends array<array<type,dim-1>> ( init_row, array<type,dim-1> ( args... ) )
{

}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr array<type,dim>::array ( int init_row, auto... args )
    requires ( 1 + sizeof...(args) - 1 == dim ) and std::copyable<type> and aux::ints_until_last_type<type,int,decltype(args)...>
    extends array<array<type,dim-1>> ( init_row, array<type,dim-1> ( args... ) )
{

}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr array<type,dim>::array ( int init_row, auto... args )
    requires ( 1 + sizeof...(args) - 1 == dim ) and aux::ints_until_last_func<type,int,decltype(args)...>
    extends array<array<type,dim-1>> ( init_row, [&] { return array<type,dim-1> ( args... ); } )
{

}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr array<type,dim>::array ( int init_row, int init_column, auto... args )
    requires ( 2 + sizeof...(args) - 1 == dim ) and aux::ints_until_last_func_ints<type,int,int,decltype(args)...>
    extends array<array<type,dim-1>> ( init_row )
{
    auto  make_int = [] ( const auto& ) { return int(); };

    auto& fun  = last_value_of ( args... );
    auto  fun2 = [&] ( int x ) { return [=] ( decltype(make_int(args))... items ) { return fun ( x, items... ); }; };
    auto  fun3 = [&] ( int y ) { return [=] ( auto item ) { if constexpr ( int_type<decltype(item)> ) return item; else return fun2 ( y ); }; };

    for ( int i in range ( row() ) )
        self.array<array<type,dim-1>>::operator[](i) = array<type,dim-1> ( init_column, fun3(i) ( args )... );
}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr array<type,dim>::array ( int init_row, const array_type<type,dim-1> auto& init_line )
    requires std::copyable<type>
    extends array<array<type,dim-1>> ( init_row, init_line )
{

}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr array<type,dim>::array ( int init_row, function_type<array<type,dim-1>()> auto init_data )
    extends array<array<type,dim-1>> ( init_row, init_data )
{
    if ( not empty() )
    {
        #if debug
            for ( int i in range ( row() - 1 ) )
                if ( self[i].shape() != self[i+1].shape() )
                    throw value_error("initialize array with lines not aligned");
        #endif

        if ( array<array<type,dim-1>>::all([] (const auto& line) { return line.empty(); }) )
            self.clear(); // Avoid summoning array shaped (a, b, c, ... 0).
    }
}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr array<type,dim>::array ( int init_row, function_type<array<type,dim-1>(int)> auto init_data )
    extends array<array<type,dim-1>> ( init_row, init_data )
{
    if ( not empty() )
    {
        #if debug
            for ( int i in range ( row() - 1 ) )
                if ( self[i].shape() != self[i+1].shape() )
                    throw value_error("initialize array with lines not aligned");
        #endif

        if ( array<array<type,dim-1>>::all([] (const auto& line) { return line.empty(); }) )
            self.clear(); // Avoid summoning array shaped (a, b, c, ... 0).
    }
}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr array<type,dim>::array ( std::initializer_list<array<type,dim-1>>&& init )
    extends array<array<type,dim-1>> ( init.size(), [&] ( int i ) { return std::move ( const_cast<array<type,dim-1>&> ( init.begin()[i-1] ) ); } )
{

}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr array<type,dim>::array ( const array_type<type,dim> auto& init )
    requires std::copyable<type>
    extends array<array<type,dim-1>> ( init.row(), [&] ( int i ) { return array<type,dim-1> ( init[i] ); } )
{

}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr array<type,dim>::array ( const array_type auto& init )
    requires ( not std::same_as<typename decay<decltype(init)>::value_type,type> ) but
             std::convertible_to<typename decay<decltype(init)>::value_type,type> and
             ( decay<decltype(init)>::dimension() == 1 )
    extends array<array<type,dim-1>> ( init.row(), [&] ( int i ) { return array<type,dim-1> ( init[i] ); } )
{

}


// Conversion between types

template < class type, int dim >
    requires ( dim >= 2 )
template < class type2 >
constexpr array<type,dim>::array ( const array<type2,dim>& cvt )
    requires std::convertible_to<type2,type> but ( not std::same_as<type,type2> )
    extends array<array<type,dim-1>> ( cvt.row(), [&] ( int i ) { return array<type,dim-1> ( cvt[i] ); } )
{

}

template < class type, int dim >
    requires ( dim >= 2 )
template < class type2 >
constexpr array<type,dim>::array ( const array<type2,dim>& cvt )
    requires std::constructible_from<type,type2> but ( not std::convertible_to<type2,type> )
    extends array<array<type,dim-1>> ( cvt.row(), [&] ( int i ) { return array<type,dim-1> ( cvt[i] ); } )
{

}

// Conversion between dims

template < class type, int dim >
    requires ( dim >= 2 )
template < int dim2, int dim3 >
constexpr array<type,dim>::array ( array<array<type,dim3>,dim2> cvt )
    requires ( dim == dim2 + dim3 )
{
    if constexpr ( dim2 == 1 )
    {
        #if debug
            if constexpr ( cvt.dimension() >= 2 )
                for ( int i in range ( cvt.row() - 1 ) )
                    if ( cvt[i].shape() != cvt[i+1].shape() )
                        throw value_error("initialize array with lines not aligned");
        #endif

        self.array<array<type,dim-1>>::operator = ( std::move(cvt) );
    }

    else
        self.array<array<type,dim-1>>::operator = ( array<array<type,dim3+1>,dim2-1> ( std::move(cvt) )  );
}

// Interface

template < class type, int dim >
    requires ( dim >= 2 )
constexpr int array<type,dim>::row ( ) const
{
    return array<array<type,dim-1>>::size();
}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr int array<type,dim>::column ( ) const
    requires ( dim == 2 )
{
    return empty() ? 0 otherwise self[1].size();
}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr int array<type,dim>::size ( ) const
{
    return shape().product();
}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr bool array<type,dim>::empty ( ) const
{
    return array<array<type,dim-1>>::empty();
}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr typename array<type,dim>::iterator array<type,dim>::begin ( )
{
    return static_cast<iterator> ( base::begin() );
}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr typename array<type,dim>::const_iterator array<type,dim>::begin ( ) const
{
    return static_cast<const_iterator> ( base::begin() );
}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr typename array<type,dim>::iterator array<type,dim>::end ( )
{
    return static_cast<iterator> ( base::end() );
}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr typename array<type,dim>::const_iterator array<type,dim>::end ( ) const
{
    return static_cast<const_iterator> ( base::end() );
}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr array_line<type,dim-1>& array<type,dim>::operator [] ( int pos )
{
    return static_cast<array_line<type,dim-1>&> ( array<array<type,dim-1>>::operator [] ( pos ) );
}

template < class type, int dim >
    requires ( dim >= 2 )
constexpr const array_line<type,dim-1>& array<type,dim>::operator [] ( int pos ) const
{
    return static_cast<const array_line<type,dim-1>&> ( array<array<type,dim-1>>::operator [] ( pos ) );
}

template < class type, int dim >
    requires ( dim >= 2 )
template < int axis >
constexpr array<type,dim>& array<type,dim>::resize ( int new_row, int_type auto... args )
    requires ( axis == 0 and 1 + sizeof...(args) == dim )
{
    if ( new_row * ( ... * args ) == 0 )
        clear();
    else
    {
        array<array<type,dim-1>>::resize ( new_row );
        for ( auto& line in base_of_self )
            line.resize ( args... );
    }

    return self;
}

template < class type, int dim >
    requires ( dim >= 2 )
template < int axis >
constexpr array<type,dim>& array<type,dim>::resize ( const array_coordinate<dim>& new_shape )
    requires ( axis == 0 )
{
    if ( new_shape.exist(0) )
        clear();
    else
    {
        array<array<type,dim-1>>::resize ( new_shape.template get<1>() );
        for ( auto& line in base_of_self )
            if constexpr ( dim == 2 )
                line.resize ( new_shape.template get<-1>() );
            else
                line.resize ( new_shape.template get<2,-1>() );
    }

    return self;
}

template < class type, int dim >
    requires ( dim >= 2 )
template < int axis >
constexpr array<type,dim>& array<type,dim>::resize ( const array_type<int,1> auto& new_shape )
    requires ( axis == 0 )
{
    #if debug
        if ( new_shape.size() != dimension() )
            throw value_error("cannot resize array of shape {} into shape {}", shape(), new_shape);
    #endif

    if ( new_shape.exist(0) )
        clear();
    else
    {
        array<array<type,dim-1>>::resize ( new_shape[1] );
        for ( auto& line in base_of_self )
            if constexpr ( dim == 2 )
                line.resize ( new_shape[-1] );
            else
                line.template resize ( new_shape[2,-1] );
    }

    return self;
}

template < class type, int dim >
    requires ( dim >= 2 )
template < int axis >
constexpr array<type,dim>& array<type,dim>::resize ( int new_size )
    requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) )
{
    // Oh ! It's hard to predict new_shape.exist(0).
    // But whenever it's empty, it cannot become non-empty
    // by changing single size on any axis.

    if ( empty() )
        clear();
    else
        if constexpr ( axis == 1 or axis == -dim )
            array<array<type,dim-1>>::resize ( new_size );

        else
            for ( auto& line in self )
                if constexpr ( dim == 2 )
                    static_cast<array<type,dim-1>&>(line).resize ( new_size );
                else
                    if constexpr ( axis > 0 )
                        static_cast<array<type,dim-1>&>(line).template resize<axis-1> ( new_size );
                    else
                        static_cast<array<type,dim-1>&>(line).template resize<axis>   ( new_size );

    return self;
}


#undef base_of_self