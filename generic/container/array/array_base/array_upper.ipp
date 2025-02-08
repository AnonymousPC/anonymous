#pragma once

namespace detail
{
    template < class type, class device >
    constexpr array_upper<type,1,device>::array_upper ( array<type,2,device>& init_host, array_attribute init_atr, int init_ofs )
        extends ptr ( &init_host ),
                atr ( init_atr ),
                ofs ( init_ofs )
    {

    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::array_upper ( const array<type,2,device>& init_host, array_attribute init_atr, int init_ofs )
        extends ptr ( const_cast<array<type,2,device>*>(&init_host) ),
                atr ( init_atr ),
                ofs ( init_ofs )
    {
        
    }

    template < class type, class device >
    constexpr int array_upper<type,1,device>::size ( ) const 
    {
        return get_size_axis<1>();
    }

    template < class type, class device >
    constexpr static_array<int,1> array_upper<type,1,device>::shape ( ) const 
    {
        return { size() };
    }

    template < class type, class device >
    constexpr bool array_upper<type,1,device>::empty ( ) const 
    {
        return size() == 0;
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::pointer array_upper<type,1,device>::data ( )
    {
        #if debug
        if ( not contiguous() )
            throw logic_error("cannot get native data from a non-contiguous view");
        #endif
        return get_host().data() + get_offset() * size();
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_pointer array_upper<type,1,device>::data ( ) const
    {
        #if debug
        if ( not contiguous() )
            throw logic_error("cannot get native data from a non-contiguous view");
        #endif
        return get_host().data() + get_offset() * size();
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::iterator array_upper<type,1,device>::begin ( )
    {
        return contiguous() ? iterator(data(), 1) otherwise iterator(get_pointer(0), get_stride());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_iterator array_upper<type,1,device>::begin ( ) const
    {
        return contiguous() ? const_iterator(data(), 1) otherwise const_iterator(get_pointer(0), get_stride());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::iterator array_upper<type,1,device>::end ( )
    {
        return contiguous() ? iterator(data()+size(), 1) otherwise iterator(get_pointer(0)+get_size_top(), get_stride());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_iterator array_upper<type,1,device>::end ( ) const
    {
        return contiguous() ? const_iterator(data()+size(), 1) otherwise const_iterator(get_pointer(0)+get_size_top(), get_stride());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::reference array_upper<type,1,device>::operator [] ( int offset )
    {
        return contiguous() ? data()[offset] otherwise get_value(offset);
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_reference array_upper<type,1,device>::operator [] ( int offset ) const
    {
        return contiguous() ? data()[offset] otherwise get_value(offset);
    }

    template < class type, class device >
    constexpr bool array_upper<type,1,device>::ownership ( ) const
    {
        [[assume((ptr == nullptr) == (atr == no_attribute))]];
        return ptr == nullptr;
    }

    template < class type, class device >
    constexpr bool array_upper<type,1,device>::contiguous ( ) const
    {
        return ( get_attribute() == rows_attribute    and same_as<typename device::layout_type,std::layout_right> ) or 
               ( get_attribute() == columns_attribute and same_as<typename device::layout_type,std::layout_left > );
    }

    template < class type, class device >
    constexpr array_attribute array_upper<type,1,device>::get_attribute ( ) const
    {
        return atr;
    }

    template < class type, class device >
    constexpr int array_upper<type,1,device>::get_offset ( ) const
    {   
        return ofs;
    }
    

    template < class type, class device >
    constexpr array<type,2,device>& array_upper<type,1,device>::get_host ( )
    {
        return *ptr;
    }
    
    template < class type, class device >
    constexpr const array<type,2,device>& array_upper<type,1,device>::get_host ( ) const
    {
        return *ptr;
    } 

    template < class type, class device >
    constexpr int array_upper<type,1,device>::get_size_top ( ) const
    {
        return get_host().get_size_top();
    }

    template < class type, class device >
    template < int axis >
    constexpr int array_upper<type,1,device>::get_size_axis ( ) const
    {
        static_assert ( axis == 1 );
        return get_attribute() == rows_attribute ? get_host().template get_size_axis<2>() otherwise
                                                   (get_host().ownership() ? get_host().template get_size_axis<1>() otherwise get_host().template get_size_axis<2>());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::reference array_upper<type,1,device>::get_value ( int offset )
    {
        return get_attribute() == rows_attribute ? get_host().get_value(get_offset(), offset) otherwise
                                                   get_host().get_value(offset, get_offset());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_reference array_upper<type,1,device>::get_value ( int offset ) const
    {
        return get_attribute() == rows_attribute ? get_host().get_value(get_offset(), offset) otherwise
                                                   get_host().get_value(offset, get_offset());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::pointer array_upper<type,1,device>::get_pointer ( int offset )
    {
        return get_attribute() == rows_attribute ? get_host().get_pointer(get_offset(), offset) otherwise
                                                   get_host().get_pointer(offset, get_offset());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_pointer array_upper<type,1,device>::get_pointer ( int offset ) const
    {
        return get_attribute() == rows_attribute ? get_host().get_pointer(get_offset(), offset) otherwise
                                                   get_host().get_pointer(offset, get_offset());
    }

    template < class type, class device >
    constexpr int array_upper<type,1,device>::get_stride ( ) const
    {
        return get_size_top() / size();
    }






    
    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_upper<type,dim,device>::array_upper ( array<type,dim+1,device>& init_host, array_attribute init_atr, int init_ofs )
        extends ptr1 ( &init_host ),
                atr  ( init_atr ),
                ofs  ( init_ofs )
    {

    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_upper<type,dim,device>::array_upper ( const array<type,dim+1,device>& init_host, array_attribute init_atr, int init_ofs )
        extends ptr1 ( &const_cast<array_upper<type,dim+1,device>&>(init_host) ),
                atr  ( init_atr ),
                ofs  ( init_ofs )
    {
        
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_upper<type,dim,device>::array_upper ( array<type,dim,device>& init_host )
        extends ptr2 ( &init_host ),
                atr  ( transpose_attribute )
    {

    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_upper<type,dim,device>::array_upper ( const array<type,dim,device>& init_host )
        extends ptr2 ( &const_cast<array_upper<type,dim,device>&>(init_host) ),
                atr  ( transpose_attribute )
    {

    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr int array_upper<type,dim,device>::size ( ) const
    {
        let s = 1;
        for_constexpr<1,dim>([&] <int index> { s *= get_size_axis<index>(); });
        return s;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr static_array<int,dim> array_upper<type,dim,device>::shape ( ) const
    {
        let s = static_array<int,dim>();
        for_constexpr<1,dim>([&] <int index> { s[index] = get_size_axis<index>(); });
        return s;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr int array_upper<type,dim,device>::row ( ) const
    {
        return get_size_axis<1>();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr int array_upper<type,dim,device>::column ( ) const    
        requires ( dim == 2 )
    {
        return get_size_axis<2>();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr bool array_upper<type,dim,device>::empty ( ) const
    {
        return get_attribute() == rows_attribute or get_attribute() == columns_attribute ? get_host<1>().empty() otherwise
                                                                                           get_host<2>().empty();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_upper<type,dim,device>::pointer array_upper<type,dim,device>::data ( )
    {
        #if debug
        if ( not contiguous() )
            throw logic_error("cannot get native data from a non-contiguous view");
        #endif
        return get_host<1>().data() + get_offset() * size();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_upper<type,dim,device>::const_pointer array_upper<type,dim,device>::data ( ) const
    {
        #if debug
        if ( not contiguous() )
            throw logic_error("cannot get native data from a non-contiguous view");
        #endif
        return get_host<1>().data() + get_offset() * size();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_upper<type,dim,device>::iterator array_upper<type,dim,device>::begin ( )
    {
        return get_attribute() == rows_attribute    ? get_host<1>().template get_rows   <dim-1>(get_offset()).begin() otherwise
               get_attribute() == columns_attribute ? get_host<1>().template get_columns<dim-1>(get_offset()).begin() otherwise 
                                                      get_host<2>().template get_columns<dim-1>().begin();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_upper<type,dim,device>::const_iterator array_upper<type,dim,device>::begin ( ) const
    {
        return get_attribute() == rows_attribute    ? get_host<1>().template get_rows   <dim-1>(get_offset()).begin() otherwise
               get_attribute() == columns_attribute ? get_host<1>().template get_columns<dim-1>(get_offset()).begin() otherwise 
                                                      get_host<2>().template get_columns<dim-1>().begin();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_upper<type,dim,device>::iterator array_upper<type,dim,device>::end ( )
    {
        return get_attribute() == rows_attribute    ? get_host<1>().template get_rows   <dim-1>(get_offset() + 1).begin() otherwise
               get_attribute() == columns_attribute ? get_host<1>().template get_columns<dim-1>(get_offset() + 1).begin() otherwise
                                                      get_host<2>().template get_columns<dim-1>().end();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_upper<type,dim,device>::const_iterator array_upper<type,dim,device>::end ( ) const
    {
        return get_attribute() == rows_attribute    ? get_host<1>().template get_rows   <dim-1>(get_offset() + 1).begin() otherwise
               get_attribute() == columns_attribute ? get_host<1>().template get_columns<dim-1>(get_offset() + 1).begin() otherwise
                                                      get_host<2>().template get_columns<dim-1>().end();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array<type,dim-1,device>& array_upper<type,dim,device>::operator [] ( int offset )
    {
        return get_attribute() == rows_attribute    ? static_cast<array<type,dim-1,device>&>(get_host<1>().template get_rows   <dim-1>(get_offset())[offset]) otherwise
               get_attribute() == columns_attribute ? static_cast<array<type,dim-1,device>&>(get_host<1>().template get_columns<dim-1>(get_offset())[offset]) otherwise 
                                                      static_cast<array<type,dim-1,device>&>(get_host<2>().template get_columns<dim-1>()[offset]);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr const array<type,dim-1,device>& array_upper<type,dim,device>::operator [] ( int offset ) const
    {
        return get_attribute() == rows_attribute    ? static_cast<const array<type,dim-1,device>&>(get_host<1>().template get_rows   <dim-1>(get_offset())[offset]) otherwise
               get_attribute() == columns_attribute ? static_cast<const array<type,dim-1,device>&>(get_host<1>().template get_columns<dim-1>(get_offset())[offset]) otherwise 
                                                      static_cast<const array<type,dim-1,device>&>(get_host<2>().template get_columns<dim-1>()[offset]);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr bool array_upper<type,dim,device>::ownership ( ) const
    {
        [[assume((ptr1 == nullptr and ptr2 == nullptr) == (atr == no_attribute))]];
        return ptr1 == nullptr and ptr2 == nullptr;
    }
    
    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr bool array_upper<type,dim,device>::contiguous ( ) const
    {
        return ( get_attribute() == rows_attribute    and same_as<typename device::layout_type,std::layout_right> ) or 
               ( get_attribute() == columns_attribute and same_as<typename device::layout_type,std::layout_left > );

        /* Transpose-view is never considered contiguous.
         * A contiguous array means that:
         * - std::mdspan can directly apply on array.data() (with correct device::layout_type).
         * - Two array which equals to each other and are both contiguous must be memcpy-able.
         */
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_attribute array_upper<type,dim,device>::get_attribute ( ) const
    {
        return atr;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr int array_upper<type,dim,device>::get_offset ( ) const
    {
        #if debug
        if ( get_attribute() == transpose_attribute )   
            throw logic_error("using offset() on a transposed array");
        #endif
        return ofs;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    template < int attr >
    constexpr array<type,dim+1,device>& array_upper<type,dim,device>::get_host ( )
        requires ( attr == 1 )
    {
        return *ptr1;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    template < int attr >
    constexpr const array<type,dim+1,device>& array_upper<type,dim,device>::get_host ( ) const
        requires ( attr == 1 )
    {
        return *ptr1;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    template < int attr >
    constexpr array<type,dim,device>& array_upper<type,dim,device>::get_host ( )
        requires ( attr == 2 )
    {
        return *ptr2;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    template < int attr >
    constexpr const array<type,dim,device>& array_upper<type,dim,device>::get_host ( ) const
        requires ( attr == 2 )
    {
        return *ptr2;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr int array_upper<type,dim,device>::get_size_top ( ) const
    {
        return get_attribute() == rows_attribute or get_attribute() == columns_attribute ? get_host<1>().get_size_top() otherwise
                                                                                           get_host<2>().get_size_top();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    template < int axis >
    constexpr int array_upper<type,dim,device>::get_size_axis ( ) const
    {
        static_assert ( axis >= 1 and axis <= dim );
        return get_attribute() == rows_attribute    ? get_host<1>().template get_size_axis<axis+1>() otherwise
               get_attribute() == columns_attribute ? (get_host<1>().ownership() ? get_host<1>().template get_size_axis<dim-axis+1>() otherwise get_host<1>().template get_size_axis<axis+1>()) otherwise
                                                      get_host<2>().template get_size_axis<dim-axis+1>();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> array_upper<type,dim,device>::get_rows ( int_type auto... offsets )
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return get_attribute() == rows_attribute    ? get_host<1>().template get_rows<dim2>(get_offset(), offsets...) otherwise
               get_attribute() == columns_attribute ? throw logic_error("cannot get a rows view from a columns view") otherwise
                                                      get_host<2>().template get_columns<dim2>(offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> array_upper<type,dim,device>::get_rows ( int_type auto... offsets ) const
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return get_attribute() == rows_attribute    ? get_host<1>().template get_rows<dim2>(get_offset(), offsets...) otherwise
               get_attribute() == columns_attribute ? throw logic_error("cannot get a rows view from a columns view") otherwise
                                                      get_host<2>().template get_columns<dim2>(offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> array_upper<type,dim,device>::get_columns ( int_type auto... offsets )
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return get_attribute() == rows_attribute    ? throw logic_error("cannot get a columns view from a rows view")    otherwise
               get_attribute() == columns_attribute ? get_host<1>().template get_columns<dim2>(offsets..., get_offset()) otherwise
                                                      get_host<2>().template get_columns<dim2>(offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> array_upper<type,dim,device>::get_columns ( int_type auto... offsets ) const
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return get_attribute() == rows_attribute    ? throw logic_error("cannot get a columns view from a rows view")    otherwise
               get_attribute() == columns_attribute ? get_host<1>().template get_columns<dim2>(offsets..., get_offset()) otherwise
                                                      get_host<2>().template get_columns<dim2>(offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_upper<type,dim,device>::reference array_upper<type,dim,device>::get_value ( int_type auto... offsets )
    {
        static_assert ( sizeof...(offsets) == dim );
        #if debug
        if ( get_attribute() == transpose_attribute )
            throw logic_error("using get_value() on a transposed array");
        #endif
        return get_attribute() == rows_attribute ? get_host<1>().get_value(get_offset(), offsets...) otherwise
                                                   get_host<1>().get_value(offsets..., get_offset());
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_upper<type,dim,device>::const_reference array_upper<type,dim,device>::get_value ( int_type auto... offsets ) const
    {
        static_assert ( sizeof...(offsets) == dim );
        #if debug
        if ( get_attribute() == transpose_attribute )
            throw logic_error("using get_value() from a transposed array");
        #endif
        return get_attribute() == rows_attribute ? get_host<1>().get_value(get_offset(), offsets...) otherwise
                                                   get_host<1>().get_value(offsets..., get_offset());
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_upper<type,dim,device>::pointer array_upper<type,dim,device>::get_pointer ( int_type auto... offsets )
    {
        #if debug
        if ( get_attribute() == transpose_attribute )
            throw logic_error("using get_pointer() on a transposed array");
        #endif
        return get_attribute() == rows_attribute ? get_host<1>().get_pointer(get_offset(), offsets...) otherwise
                                                   get_host<1>().get_pointer(offsets..., get_offset());
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr array_upper<type,dim,device>::const_pointer array_upper<type,dim,device>::get_pointer ( int_type auto... offsets ) const
    {
        #if debug
        if ( get_attribute() == transpose_attribute )
            throw logic_error("using get_pointer() from a transposed array");
        #endif
        return get_attribute() == rows_attribute ? get_host<1>().get_pointer(get_offset(), offsets...) otherwise
                                                   get_host<1>().get_pointer(offsets..., get_offset());
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 and dim <= max_dim - 1 )
    constexpr int array_upper<type,dim,device>::get_stride ( ) const
    {
        #if debug
        if ( get_attribute() == transpose_attribute )
            throw logic_error("using get_stride() from a transposed array");
        #endif
        return get_size_top() / size();
    }






    template < class type, class device >
    constexpr array_upper<type,max_dim,device>::array_upper ( array<type,max_dim,device>& init_host )
        extends ptr ( &init_host )
    {

    }

    template < class type, class device >
    constexpr array_upper<type,max_dim,device>::array_upper ( const array<type,max_dim,device>& init_host )
        extends ptr ( &const_cast<array_upper<type,max_dim,device>&>(init_host) )
    {
        
    }

    template < class type, class device >
    constexpr int array_upper<type,max_dim,device>::size ( ) const
    {
        return get_host().size();
    }

    template < class type, class device >
    constexpr static_array<int,max_dim> array_upper<type,max_dim,device>::shape ( ) const
    {
        let s1 = get_host().shape();
        let s2 = static_array<int,max_dim>();
        for_constexpr<1,max_dim>([&] <int index> { s2[index] = s1[-index]; });
        return s2;
    }

    template < class type, class device >
    constexpr int array_upper<type,max_dim,device>::row ( ) const
    {
        return get_host().shape()[-1]; 
    }

    template < class type, class device >
    constexpr int array_upper<type,max_dim,device>::column ( ) const    
        requires ( max_dim == 2 )
    {
        return get_host().shape()[1]; 
    }

    template < class type, class device >
    constexpr bool array_upper<type,max_dim,device>::empty ( ) const
    {
        return get_host().empty();
    }

    template < class type, class device >
    constexpr array_upper<type,max_dim,device>::iterator array_upper<type,max_dim,device>::begin ( )
    {
        return get_host().template get_columns<max_dim-1>().begin();
    }

    template < class type, class device >
    constexpr array_upper<type,max_dim,device>::const_iterator array_upper<type,max_dim,device>::begin ( ) const
    {
        return get_host().template get_columns<max_dim-1>().begin();
    }

    template < class type, class device >
    constexpr array_upper<type,max_dim,device>::iterator array_upper<type,max_dim,device>::end ( )
    {
        return get_host().template get_columns<max_dim-1>().end();
    }

    template < class type, class device >
    constexpr array_upper<type,max_dim,device>::const_iterator array_upper<type,max_dim,device>::end ( ) const
    {
        return get_host().template get_columns<max_dim-1>().end();
    }

    template < class type, class device >
    constexpr array<type,max_dim-1,device>& array_upper<type,max_dim,device>::operator [] ( int offset )
    {
        return static_cast<array<type,max_dim-1,device>&>(get_host().template get_columns<max_dim-1>()[offset]);
    }

    template < class type, class device >
    constexpr const array<type,max_dim-1,device>& array_upper<type,max_dim,device>::operator [] ( int offset ) const
    {
        return static_cast<const array<type,max_dim-1,device>&>(get_host().template get_columns<max_dim-1>()[offset]);
    }

    template < class type, class device >
    constexpr bool array_upper<type,max_dim,device>::ownership ( ) const
    {
        return ptr == nullptr;
    }

    template < class type, class device >
    constexpr array<type,max_dim,device>& array_upper<type,max_dim,device>::get_host ( )
    {
        return *ptr;
    }

    template < class type, class device >
    constexpr const array<type,max_dim,device>& array_upper<type,max_dim,device>::get_host ( ) const
    {
        return *ptr;
    }

    template < class type, class device >
    template < int axis >
    constexpr int array_upper<type,max_dim,device>::get_size_axis ( ) const
    {
        static_assert ( axis >= 1 and axis <= max_dim );
        return get_host().template get_size_axis<max_dim-axis+1>();
    }

    template < class type, class device >
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> array_upper<type,max_dim,device>::get_rows ( int_type auto... offsets )
    {
        static_assert ( dim2 > 0 and dim2 < max_dim );
        static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
        return get_host().template get_columns<dim2>(offsets...);
    }

    template < class type, class device >
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> array_upper<type,max_dim,device>::get_rows ( int_type auto... offsets ) const
    {
        static_assert ( dim2 > 0 and dim2 < max_dim );
        static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
        return get_host().template get_columns<dim2>(offsets...);
    }

    template < class type, class device >
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> array_upper<type,max_dim,device>::get_columns ( int_type auto... offsets )
    {
        static_assert ( dim2 > 0 and dim2 < max_dim );
        static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
        return get_host().template get_columns<dim2>(offsets...);
    }

    template < class type, class device >
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> array_upper<type,max_dim,device>::get_columns ( int_type auto... offsets ) const
    {
        static_assert ( dim2 > 0 and dim2 < max_dim );
        static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
        return get_host().template get_columns<dim2>(offsets...);
    }



} // namespace detail