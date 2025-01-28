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
        return axis_size<1>();
    }

    template < class type, class device >
    constexpr array<int> array_upper<type,1,device>::shape ( ) const 
    {
        return { size() };
    }

    template < class type, class device >
    constexpr inplace_array<int,1> array_upper<type,1,device>::inplace_shape ( ) const 
    {
        return { size() };
    }

    template < class type, class device >
    constexpr static_array<int,1> array_upper<type,1,device>::static_shape ( ) const 
    {
        return { size() };
    }

    template < class type, class device >
    constexpr bool array_upper<type,1,device>::empty ( ) const 
    {
        return host().empty();
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::pointer array_upper<type,1,device>::data ( )
    {
        #if debug
        if ( not contiguous() )
            throw logic_error("cannot get native data from a non-contiguous view");
        #endif
        return host().data() + offset() * size();
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_pointer array_upper<type,1,device>::data ( ) const
    {
        #if debug
        if ( not contiguous() )
            throw logic_error("cannot get native data from a non-contiguous view");
        #endif
        return host().data() + offset() * size();
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::iterator array_upper<type,1,device>::begin ( )
    {
        return contiguous() ? iterator(data()) otherwise iterator(&self[0], top_size()/size());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_iterator array_upper<type,1,device>::begin ( ) const
    {
        return contiguous() ? const_iterator(data()) otherwise const_iterator(&self[0], top_size()/size());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::iterator array_upper<type,1,device>::end ( )
    {
        return contiguous() ? iterator(data()+size()) otherwise iterator(&self[0]+top_size(), top_size()/size());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_iterator array_upper<type,1,device>::end ( ) const
    {
        return contiguous() ? const_iterator(data()+size()) otherwise const_iterator(&self[0]+top_size(), top_size()/size());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::reference array_upper<type,1,device>::operator [] ( int index )
    {
        return contiguous()                  ? data()[index]              otherwise 
               attribute() == rows_attribute ? host().at(offset(), index) otherwise 
                                               host().at(index, offset());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_reference array_upper<type,1,device>::operator [] ( int index ) const
    {
        return contiguous()                  ? data()[index]              otherwise 
               attribute() == rows_attribute ? host().at(offset(), index) otherwise 
                                               host().at(index, offset());
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
        return ( attribute() == rows_attribute    and same_as<typename device::layout_type,std::layout_right> ) or 
               ( attribute() == columns_attribute and same_as<typename device::layout_type,std::layout_left > );
    }

    template < class type, class device >
    constexpr array_attribute array_upper<type,1,device>::attribute ( ) const
    {
        return atr;
    }

    template < class type, class device >
    constexpr int array_upper<type,1,device>::offset ( ) const
    {   
        return ofs;
    }
    

    template < class type, class device >
    constexpr array<type,2,device>& array_upper<type,1,device>::host ( )
    {
        return *ptr;
    }
    
    template < class type, class device >
    constexpr const array<type,2,device>& array_upper<type,1,device>::host ( ) const
    {
        return *ptr;
    } 

    template < class type, class device >
    constexpr int array_upper<type,1,device>::top_size ( ) const
    {
        return host().top_size();
    }

    template < class type, class device >
    template < int axis >
    constexpr int array_upper<type,1,device>::axis_size ( ) const
    {
        static_assert ( axis == 1 );
        return attribute() == rows_attribute ? host().template axis_size<2>() otherwise
                                               (host().ownership() ? host().template axis_size<1>() otherwise host().template axis_size<2>());
    }






    
    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::array_upper ( array<type,dim+1,device>& init_host, array_attribute init_atr, int init_ofs )
        extends ptr1 ( &init_host ),
                atr  ( init_atr ),
                ofs  ( init_ofs )
    {

    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::array_upper ( const array<type,dim+1,device>& init_host, array_attribute init_atr, int init_ofs )
        extends ptr1 ( &const_cast<array_upper<type,dim+1,device>&>(init_host) ),
                atr  ( init_atr ),
                ofs  ( init_ofs )
    {
        
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::array_upper ( array<type,dim,device>& init_host )
        extends ptr2 ( &init_host ),
                atr  ( transpose_attribute )
    {

    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::array_upper ( const array<type,dim,device>& init_host )
        extends ptr2 ( &const_cast<array_upper<type,dim,device>&>(init_host) ),
                atr  ( transpose_attribute )
    {

    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int array_upper<type,dim,device>::size ( ) const
    {
        let s = 1;
        for_constexpr<1,dim>([&] <int index> { s *= axis_size<index>(); });
        return s;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array<int> array_upper<type,dim,device>::shape ( ) const
    {
        let s = array<int>(dim);
        for_constexpr<1,dim>([&] <int index> { s[index] = axis_size<index>(); });
        return s;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr inplace_array<int,dim> array_upper<type,dim,device>::inplace_shape ( ) const
    {
        let s = inplace_array<int,dim>();
        for_constexpr<1,dim>([&] <int index> { s[index] = axis_size<index>(); });
        return s;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr static_array<int,dim> array_upper<type,dim,device>::static_shape ( ) const
    {
        let s = static_array<int,dim>();
        for_constexpr<1,dim>([&] <int index> { s[index] = axis_size<index>(); });
        return s;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int array_upper<type,dim,device>::row ( ) const
    {
        return axis_size<1>();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int array_upper<type,dim,device>::column ( ) const    
        requires ( dim == 2 )
    {
        return axis_size<2>();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr bool array_upper<type,dim,device>::empty ( ) const
    {
        return attribute() == rows_attribute or attribute() == columns_attribute ? host<1>().empty() otherwise
                                                                                   host<2>().empty();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::pointer array_upper<type,dim,device>::data ( )
    {
        #if debug
        if ( not contiguous() )
            throw logic_error("cannot get native data from a non-contiguous view");
        #endif
        return host<1>().data() + offset() * size();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::const_pointer array_upper<type,dim,device>::data ( ) const
    {
        #if debug
        if ( not contiguous() )
            throw logic_error("cannot get native data from a non-contiguous view");
        #endif
        return host<1>().data() + offset() * size();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::iterator array_upper<type,dim,device>::begin ( )
    {
        return attribute() == rows_attribute    ? host<1>().template rows   <dim-1>(offset()).begin() otherwise
               attribute() == columns_attribute ? host<1>().template columns<dim-1>(offset()).begin() otherwise 
                                                  host<2>().template columns<dim-1>().begin();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::const_iterator array_upper<type,dim,device>::begin ( ) const
    {
        return attribute() == rows_attribute    ? host<1>().template rows   <dim-1>(offset()).begin() otherwise
               attribute() == columns_attribute ? host<1>().template columns<dim-1>(offset()).begin() otherwise 
                                                  host<2>().template columns<dim-1>().begin();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::iterator array_upper<type,dim,device>::end ( )
    {
        return attribute() == rows_attribute    ? host<1>().template rows   <dim-1>(offset() + 1).begin() otherwise
               attribute() == columns_attribute ? host<1>().template columns<dim-1>(offset() + 1).begin() otherwise
                                                  host<2>().template columns<dim-1>().end();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::const_iterator array_upper<type,dim,device>::end ( ) const
    {
        return attribute() == rows_attribute    ? host<1>().template rows   <dim-1>(offset() + 1).begin() otherwise
               attribute() == columns_attribute ? host<1>().template columns<dim-1>(offset() + 1).begin() otherwise
                                                  host<2>().template columns<dim-1>().end();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array<type,dim-1,device>& array_upper<type,dim,device>::operator [] ( int index )
    {
        return attribute() == rows_attribute    ? static_cast<array<type,dim-1,device>&>(host<1>().template rows   <dim-1>(offset())[index]) otherwise
               attribute() == columns_attribute ? static_cast<array<type,dim-1,device>&>(host<1>().template columns<dim-1>(offset())[index]) otherwise 
                                                  static_cast<array<type,dim-1,device>&>(host<2>().template columns<dim-1>()[index]);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr const array<type,dim-1,device>& array_upper<type,dim,device>::operator [] ( int index ) const
    {
        return attribute() == rows_attribute    ? static_cast<const array<type,dim-1,device>&>(host<1>().template rows   <dim-1>(offset())[index]) otherwise
               attribute() == columns_attribute ? static_cast<const array<type,dim-1,device>&>(host<1>().template columns<dim-1>(offset())[index]) otherwise 
                                                  static_cast<const array<type,dim-1,device>&>(host<2>().template columns<dim-1>()[index]);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr bool array_upper<type,dim,device>::ownership ( ) const
    {
        [[assume((ptr1 == nullptr and ptr2 == nullptr) == (atr == no_attribute))]];
        return ptr1 == nullptr and ptr2 == nullptr;
    }
    
    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr bool array_upper<type,dim,device>::contiguous ( ) const
    {
        return ( attribute() == rows_attribute    and same_as<typename device::layout_type,std::layout_right> ) or 
               ( attribute() == columns_attribute and same_as<typename device::layout_type,std::layout_left > );

        /* Transpose-view is never considered contiguous.
         * A contiguous array means that:
         * - std::mdspan can directly apply on array.data() (with correct device::layout_type).
         * - Two array which equals to each other and are both contiguous must be memcpy-able.
         */
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_attribute array_upper<type,dim,device>::attribute ( ) const
    {
        return atr;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int array_upper<type,dim,device>::offset ( ) const
    {
        #if debug
        if ( attribute() == transpose_attribute )   
            throw logic_error("using offset() on a transposed array");
        #endif
        return ofs;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int attr >
    constexpr array<type,dim+1,device>& array_upper<type,dim,device>::host ( )
        requires ( attr == 1 )
    {
        return *ptr1;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int attr >
    constexpr const array<type,dim+1,device>& array_upper<type,dim,device>::host ( ) const
        requires ( attr == 1 )
    {
        return *ptr1;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int attr >
    constexpr array<type,dim,device>& array_upper<type,dim,device>::host ( )
        requires ( attr == 2 )
    {
        return *ptr2;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int attr >
    constexpr const array<type,dim,device>& array_upper<type,dim,device>::host ( ) const
        requires ( attr == 2 )
    {
        return *ptr2;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int array_upper<type,dim,device>::top_size ( ) const
    {
        return attribute() == rows_attribute or attribute() == columns_attribute ? host<1>().top_size() otherwise
                                                                                   host<2>().top_size();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int axis >
    constexpr int array_upper<type,dim,device>::axis_size ( ) const
    {
        static_assert ( axis >= 1 and axis <= dim );
        return attribute() == rows_attribute    ? host<1>().template axis_size<axis+1>() otherwise
               attribute() == columns_attribute ? (host<1>().ownership() ? host<1>().template axis_size<dim-axis+1>() otherwise host<1>().template axis_size<axis+1>()) otherwise
                                                  host<2>().template axis_size<dim-axis+1>();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> array_upper<type,dim,device>::rows ( int_type auto... offsets )
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return attribute() == rows_attribute    ? host<1>().template rows<dim2>(offset(), offsets...)             otherwise
               attribute() == columns_attribute ? throw logic_error("cannot get a rows view from a columns view") otherwise
                                                  host<2>().template columns<dim2>(offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> array_upper<type,dim,device>::rows ( int_type auto... offsets ) const
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return attribute() == rows_attribute    ? host<1>().template rows<dim2>(offset(), offsets...)             otherwise
               attribute() == columns_attribute ? throw logic_error("cannot get a rows view from a columns view") otherwise
                                                  host<2>().template columns<dim2>(offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> array_upper<type,dim,device>::columns ( int_type auto... offsets )
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return attribute() == rows_attribute    ? throw logic_error("cannot get a columns view from a rows view") otherwise
               attribute() == columns_attribute ? host<1>().template columns<dim2>(offsets..., offset())          otherwise
                                                  host<2>().template columns<dim2>(offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> array_upper<type,dim,device>::columns ( int_type auto... offsets ) const
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return attribute() == rows_attribute    ? throw logic_error("cannot get a columns view from a rows view") otherwise
               attribute() == columns_attribute ? host<1>().template columns<dim2>(offsets..., offset())          otherwise
                                                  host<2>().template columns<dim2>(offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::reference array_upper<type,dim,device>::at ( int_type auto... offsets )
    {
        static_assert ( sizeof...(offsets) == dim );
        #if debug
        if ( attribute() == transpose_attribute )
            throw logic_error("using at() on a transposed array");
        #endif
        return attribute() == rows_attribute ? host<1>().at(offset(), offsets...) otherwise
                                               host<1>().at(offsets..., offset());
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::const_reference array_upper<type,dim,device>::at ( int_type auto... offsets ) const
    {
        static_assert ( sizeof...(offsets) == dim );
        #if debug
        if ( attribute() == transpose_attribute )
            throw logic_error("using at() from a transposed array");
        #endif
        return attribute() == rows_attribute ? host<1>().at(offset(), offsets...) otherwise
                                               host<1>().at(offsets..., offset());
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
        return host().size();
    }

    template < class type, class device >
    constexpr array<int> array_upper<type,max_dim,device>::shape ( ) const
    {
        let s1 = host().static_shape();
        let s2 = array<int>(max_dim);
        for_constexpr<1,max_dim>([&] <int index> { s2[index] = s1[-index]; });
        return s2;
    }

    template < class type, class device >
    constexpr inplace_array<int,max_dim> array_upper<type,max_dim,device>::inplace_shape ( ) const
    {
        let s1 = host().static_shape();
        let s2 = inplace_array<int,max_dim>();
        for_constexpr<1,max_dim>([&] <int index> { s2[index] = s1[-index]; });
        return s2;
    }

    template < class type, class device >
    constexpr static_array<int,max_dim> array_upper<type,max_dim,device>::static_shape ( ) const
    {
        let s1 = host().static_shape();
        let s2 = static_array<int,max_dim>();
        for_constexpr<1,max_dim>([&] <int index> { s2[index] = s1[-index]; });
        return s2;
    }

    template < class type, class device >
    constexpr int array_upper<type,max_dim,device>::row ( ) const
    {
        return host().static_shape()[-1]; 
    }

    template < class type, class device >
    constexpr int array_upper<type,max_dim,device>::column ( ) const    
        requires ( max_dim == 2 )
    {
        return host().static_shape()[1]; 
    }

    template < class type, class device >
    constexpr bool array_upper<type,max_dim,device>::empty ( ) const
    {
        return host().empty();
    }

    template < class type, class device >
    constexpr array_upper<type,max_dim,device>::iterator array_upper<type,max_dim,device>::begin ( )
    {
        return host().template columns<max_dim-1>().begin();
    }

    template < class type, class device >
    constexpr array_upper<type,max_dim,device>::const_iterator array_upper<type,max_dim,device>::begin ( ) const
    {
        return host().template columns<max_dim-1>().begin();
    }

    template < class type, class device >
    constexpr array_upper<type,max_dim,device>::iterator array_upper<type,max_dim,device>::end ( )
    {
        return host().template columns<max_dim-1>().end();
    }

    template < class type, class device >
    constexpr array_upper<type,max_dim,device>::const_iterator array_upper<type,max_dim,device>::end ( ) const
    {
        return host().template columns<max_dim-1>().end();
    }

    template < class type, class device >
    constexpr array<type,max_dim-1,device>& array_upper<type,max_dim,device>::operator [] ( int index )
    {
        return static_cast<array<type,max_dim-1,device>&>(host().template columns<max_dim-1>()[index]);
    }

    template < class type, class device >
    constexpr const array<type,max_dim-1,device>& array_upper<type,max_dim,device>::operator [] ( int index ) const
    {
        return static_cast<const array<type,max_dim-1,device>&>(host().template columns<max_dim-1>()[index]);
    }

    template < class type, class device >
    constexpr bool array_upper<type,max_dim,device>::ownership ( ) const
    {
        return ptr == nullptr;
    }

    template < class type, class device >
    constexpr array<type,max_dim,device>& array_upper<type,max_dim,device>::host ( )
    {
        return *ptr;
    }

    template < class type, class device >
    constexpr const array<type,max_dim,device>& array_upper<type,max_dim,device>::host ( ) const
    {
        return *ptr;
    }

    template < class type, class device >
    template < int axis >
    constexpr int array_upper<type,max_dim,device>::axis_size ( ) const
    {
        return host().static_shape()[-axis];
    }

    template < class type, class device >
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> array_upper<type,max_dim,device>::rows ( int_type auto... offsets )
    {
        static_assert ( dim2 > 0 and dim2 < max_dim );
        static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
        return host().template columns<dim2>(offsets...);
    }

    template < class type, class device >
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> array_upper<type,max_dim,device>::rows ( int_type auto... offsets ) const
    {
        static_assert ( dim2 > 0 and dim2 < max_dim );
        static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
        return host().template columns<dim2>(offsets...);
    }

    template < class type, class device >
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> array_upper<type,max_dim,device>::columns ( int_type auto... offsets )
    {
        static_assert ( dim2 > 0 and dim2 < max_dim );
        static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
        return host().template columns<dim2>(offsets...);
    }

    template < class type, class device >
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> array_upper<type,max_dim,device>::columns ( int_type auto... offsets ) const
    {
        static_assert ( dim2 > 0 and dim2 < max_dim );
        static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
        return host().template columns<dim2>(offsets...);
    }



} // namespace detail