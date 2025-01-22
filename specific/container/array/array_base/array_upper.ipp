#pragma once

namespace detail
{
    template < class type, class device >
    constexpr array_upper<type,1,device>::array_upper ( array<type,2,device>& init_host )
        extends ptr ( &init_host )
    {

    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::array_upper ( const array<type,2,device>& init_host )
        extends ptr ( const_cast<array<type,2,device>*>(&init_host) )
    {
        
    }

    template < class type, class device >
    constexpr int array_upper<type,1,device>::size ( ) const 
    {
        return attribute() == row_view ? host().column() otherwise host().row();
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
    constexpr array_upper<type,1,device>::reference array_upper<type,1,device>::operator [] ( int ofs )
    {
        return contiguous()            ? data()[ofs]              otherwise 
               attribute() == row_view ? host().at(offset(), ofs) otherwise 
                                         host().at(ofs, offset());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_reference array_upper<type,1,device>::operator [] ( int ofs ) const
    {
        return contiguous()            ? data()[ofs]              otherwise 
               attribute() == row_view ? host().at(offset(), ofs) otherwise 
                                         host().at(ofs, offset());
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
    constexpr bool array_upper<type,1,device>::ownership ( ) const
    {
        return ptr == nullptr;
    }

    template < class type, class device >
    constexpr bool array_upper<type,1,device>::contiguous ( ) const
    {
        return ( attribute() == row_view    and same_as<typename device::layout_type,std::layout_right> ) or 
               ( attribute() == column_view and same_as<typename device::layout_type,std::layout_left > );
    }

    template < class type, class device >
    constexpr auto array_upper<type,1,device>::attribute ( ) const
    {
        const auto& rows_list = host().template rows<1>();
        if ( this >= rows_list.data() and this <= rows_list.data() + rows_list.size() ) 
            return row_view;
            
        #if debug
        const auto& columns_list = host().template columns<1>();
        if ( this >= columns_list.data() and this <= columns_list.data() + rows_list.size() )
            return column_view;
        throw logic_error("unknown attribute: this array is probably not a view");
        #else
        return column_view;
        #endif
    }

    template < class type, class device >
    constexpr int array_upper<type,1,device>::offset ( ) const
    {   
        return attribute() == row_view ? this - host().template rows   <1>().data() otherwise 
                                         this - host().template columns<1>().data();
    }

    template < class type, class device >
    constexpr int array_upper<type,1,device>::top_size ( ) const
    {
        return host().top_size();
    }
    






    
    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::array_upper ( array<type,dim+1,device>& init_host )
        extends ptr1 ( &init_host )
    {

    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::array_upper ( const array<type,dim+1,device>& init_host )
        extends ptr1 ( &const_cast<array_upper<type,dim+1,device>&>(init_host) )
    {
        
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::array_upper ( array<type,dim,device>& init_host )
        extends ptr2 ( &init_host )
    {

    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::array_upper ( const array<type,dim,device>& init_host )
        extends ptr2 ( &const_cast<array_upper<type,dim,device>&>(init_host) )
    {

    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int array_upper<type,dim,device>::size ( ) const
    {
        return attribute() == row_view    ? partial_size_of<2,-1>(host<1>()) otherwise
               attribute() == column_view ? partial_size_of<1,-2>(host<1>()) otherwise
                                            host<2>().size();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array<int> array_upper<type,dim,device>::shape ( ) const
    {
        return attribute() == row_view    ? partial_shape_of<2,-1>(host<1>()) otherwise
               attribute() == column_view ? partial_shape_of<1,-2>(host<1>()) otherwise
                                            host<2>().shape().reverse();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr inplace_array<int,dim> array_upper<type,dim,device>::inplace_shape ( ) const
    {
        return attribute() == row_view    ? partial_shape_of<2,-1>(host<1>()) otherwise
               attribute() == column_view ? partial_shape_of<1,-2>(host<1>()) otherwise
                                            host<2>().inplace_shape().reverse();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr static_array<int,dim> array_upper<type,dim,device>::static_shape ( ) const
    {
        return attribute() == row_view    ? partial_shape_of<2,-1>(host<1>()) otherwise
               attribute() == column_view ? partial_shape_of<1,-2>(host<1>()) otherwise
                                            host<2>().static_shape().reverse();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int array_upper<type,dim,device>::row ( ) const
    {
        return attribute() == row_view    ? host<1>().static_shape()[2] otherwise
               attribute() == column_view ? host<1>().static_shape()[1] otherwise
                                            host<2>().static_shape()[-1]; 
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int array_upper<type,dim,device>::column ( ) const    
        requires ( dim == 2 )
    {
        return attribute() == row_view    ? host<1>().static_shape()[-1] otherwise
               attribute() == column_view ? host<1>().static_shape()[-2] otherwise
                                            host<2>().static_shape()[1]; 
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr bool array_upper<type,dim,device>::empty ( ) const
    {
        return attribute() == row_view or attribute() == column_view ? host<1>().empty() otherwise host<2>().empty();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::pointer array_upper<type,dim,device>::data ( )
    {
        #if debug
        if ( not contiguous() )
            throw logic_error("cannot get native data from a non-contiguous view");
        #endif
        return attribute() == row_view or attribute() == column_view ? host<1>().data() + offset() * size() otherwise host<2>().data();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::const_pointer array_upper<type,dim,device>::data ( ) const
    {
        #if debug
        if ( not contiguous() )
            throw logic_error("cannot get native data from a non-contiguous view");
        #endif
        return attribute() == row_view or attribute() == column_view ? host<1>().data() + offset() * size() otherwise host<2>().data();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::iterator array_upper<type,dim,device>::begin ( )
    {
        return attribute() == row_view    ? host<1>().template rows   <dim-1>().begin() + offset() * row()    otherwise
               attribute() == column_view ? host<1>().template columns<dim-1>().begin() + offset() * column() otherwise 
                                            host<2>().template columns<dim-1>().begin();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::const_iterator array_upper<type,dim,device>::begin ( ) const
    {
        return attribute() == row_view    ? host<1>().template rows   <dim-1>().begin() + offset() * row()    otherwise
               attribute() == column_view ? host<1>().template columns<dim-1>().begin() + offset() * column() otherwise 
                                            host<2>().template columns<dim-1>().begin();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::iterator array_upper<type,dim,device>::end ( )
    {
        return attribute() == row_view    ? host<1>().template rows   <dim-1>().begin() + (offset() + 1) * row()    otherwise
               attribute() == column_view ? host<1>().template columns<dim-1>().begin() + (offset() + 1) * column() otherwise
                                            host<2>().template columns<dim-1>().end();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::const_iterator array_upper<type,dim,device>::end ( ) const
    {
        return attribute() == row_view    ? host<1>().template rows   <dim-1>().begin() + (offset() + 1) * row()    otherwise
               attribute() == column_view ? host<1>().template columns<dim-1>().begin() + (offset() + 1) * column() otherwise
                                            host<2>().template columns<dim-1>().end();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array<type,dim-1,device>& array_upper<type,dim,device>::operator [] ( int ofs )
    {
        return attribute() == row_view    ? host<1>().template rows   <dim-1>()[offset() * row()    + ofs] otherwise
               attribute() == column_view ? host<1>().template columns<dim-1>()[offset() * column() + ofs] otherwise 
                                            host<2>().template columns<dim-1>()[ofs];
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr const array<type,dim-1,device>& array_upper<type,dim,device>::operator [] ( int ofs ) const
    {
        return attribute() == row_view    ? host<1>().template rows   <dim-1>()[offset() * row()    + ofs] otherwise
               attribute() == column_view ? host<1>().template columns<dim-1>()[offset() * column() + ofs] otherwise 
                                            host<2>().template columns<dim-1>()[ofs];
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int attribute >
    constexpr array<type,dim+1,device>& array_upper<type,dim,device>::host ( )
        requires ( attribute == 1 )
    {
        return *ptr1;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int attribute >
    constexpr const array<type,dim+1,device>& array_upper<type,dim,device>::host ( ) const
        requires ( attribute == 1 )
    {
        return *ptr1;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int attribute >
    constexpr array<type,dim,device>& array_upper<type,dim,device>::host ( )
        requires ( attribute == 2 )
    {
        return *ptr2;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int attribute >
    constexpr const array<type,dim,device>& array_upper<type,dim,device>::host ( ) const
        requires ( attribute == 2 )
    {
        return *ptr2;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr bool array_upper<type,dim,device>::ownership ( ) const
    {
        return ptr1 == nullptr and ptr2 == nullptr;
    }
    
    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr bool array_upper<type,dim,device>::contiguous ( ) const
    {
        return ( attribute() == row_view       and same_as<typename device::layout_type,std::layout_right> ) or 
               ( attribute() == column_view    and same_as<typename device::layout_type,std::layout_left > ) or
               ( attribute() == transpose_view and host<2>().contiguous() );
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr auto array_upper<type,dim,device>::attribute ( ) const
    {
        if ( ptr1 != nullptr )
        {
            let rows_list = host<1>().template rows<dim>();
            if ( this >= rows_list.data() and this <= rows_list.data() + size() ) 
                return row_view;
                
            #if debug
            let columns_list = host<1>().template columns<dim>();
            if ( this >= columns_list.data() and this <= columns_list.data() + columns_list.size() )
                return column_view;
            throw logic_error("unknown attribute: this array is probably not a view");
            #else
            return column_view;
            #endif
        }

        #if debug
        if ( ptr2 != nullptr )
            return transpose_view;
        throw logic_error("unknown attribute: this array is probably not a view");
        #else
        return transpose_view;
        #endif
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int array_upper<type,dim,device>::offset ( ) const
    {
        #if debug
        if ( attribute() == transpose_view )   
            throw logic_error("using offset() on a transposed array");
        #endif
        return attribute() == row_view ? this - host<1>().template rows   <dim>().data() otherwise
                                         this - host<1>().template columns<dim>().data();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr std::vector<array_upper<type,dim2,device>>& array_upper<type,dim,device>::rows ( )
        requires ( dim2 > 0 and dim2 < dim )
    {
        return attribute() == row_view or attribute() == column_view ? host<1>().template rows<dim2>() otherwise
                                                                       host<2>().template columns<dim2>();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::reference array_upper<type,dim,device>::at ( int_type auto... args )
        requires ( sizeof...(args) == dim )
    {
        #if debug
        if ( attribute() == transpose_view )
            throw logic_error("using at() on a transposed array");
        #endif
        return attribute() == row_view ? host<1>().at(offset(), args...) otherwise
                                         host<2>().at(args..., offset());
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>::const_reference array_upper<type,dim,device>::at ( int_type auto... args ) const
        requires ( sizeof...(args) == dim )
    {
        #if debug
        if ( attribute() == transpose_view )
            throw logic_error("using at() from a transposed array");
        #endif
        return attribute() == row_view ? host<1>().at(offset(), args...) otherwise
                                         host<2>().at(args..., offset());
    }



} // namespace detail