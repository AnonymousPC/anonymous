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
        extends ptr ( &const_cast<array<type,2,device>&>(init_host) )
    {
        
    }

    template < class type, class device >
    constexpr int array_upper<type,1,device>::size ( ) const 
    {
        return attribute() == rows ? host().column() otherwise host().row();
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
        return contiguous() ? data() otherwise { data(), attribute() == rows ? host().row() otherwise host().column() };
    }

    template < class type, class device >
    constexpr const array_upper<type,1,device>::iterator array_upper<type,1,device>::begin ( ) const
    {
        return contiguous() ? data() otherwise { data(), attribute() == rows ? host().row() otherwise host().column() };
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::iterator array_upper<type,1,device>::end ( )
    {
        return contiguous() ? data() + size() otherwise { data() + host().size(), attribute() == rows ? host().row() otherwise host().column() };
    }

    template < class type, class device >
    constexpr const array_upper<type,1,device>::iterator array_upper<type,1,device>::end ( ) const
    {
        return contiguous() ? data() + size() otherwise { data() + host().size(), attribute() == rows ? host().row() otherwise host().column() };
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::reference array_upper<type,1,device>::operator [] ( int args )
    {
        return contiguous()        ? data()[args]              otherwise 
               attribute() == rows ? host().at(offset(), args) otherwise 
                                     host().at(args, offset());
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_reference array_upper<type,1,device>::operator [] ( int args ) const
    {
        return contiguous()        ? data()[args]              otherwise 
               attribute() == rows ? host().at(offset(), args) otherwise 
                                     host().at(args, offset());
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
        return ( attribute() == rows    and same_as<typename device::layout_type,std::layout_right> ) or 
               ( attribute() == columns and same_as<typename device::layout_type,std::layout_left > );
    }

    template < class type, class device >
    constexpr auto array_upper<type,1,device>::attribute ( ) const
    {
        const auto& rows_list = host().template rows<1>();
        if ( this >= rows_list.begin() and this <= rows_list.end() ) 
            return rows;
            
        #if debug
        const auto& columns_list = host().template columns<1>();
        if ( this >= columns_list.begin() and this <= columns_list.end() )
            return columns;
        throw logic_error("unknown attribute: this array is probably not a view");
        #else
        return columns;
        #endif
    }

    template < class type, class device >
    constexpr int array_upper<type,1,device>::offset ( ) const
    {   
        return attribute() == rows ? this - host().template rows   <1>().begin() otherwise 
                                     this - host().template columns<1>().begin();
    }
    






    
    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::array_upper ( array_upper<type,dim+1,device>& init_host )
        extends ptr_1 ( &init_host )
    {

    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::array_upper ( const array_upper<type,dim+1,device>& init_host )
        extends ptr_1 ( &const_cast<array_upper<type,dim+1,device>&>(init_host) )
    {
        
    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::array_upper ( array_upper<type,dim,device>& init_host )
        extends ptr_2 ( &init_host )
    {

    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::array_upper ( const array_upper<type,dim,device>& init_host )
        extends ptr_2 ( &const_cast<array_upper<type,dim,device>&>(init_host) )
    {

    }

    template < class type, int dim, class device >
    constexpr int array_upper<type,dim,device>::size ( ) const
    {
        return attribute() == rows    ? partial_size<2,-1>(host<1>()) otherwise
               attribute() == columns ? partial_size<1,-2>(host<1>()) otherwise
                                        host<2>().size();
    }

    template < class type, int dim, class device >
    constexpr bool array_upper<type,dim,device>::empty ( ) const
    {
        return attribute() == rows or attribute() == columns ? host<1>().empty() otherwise host<2>().empty();
    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::pointer array_upper<type,dim,device>::data ( )
    {
        #if debug
        if ( not contiguous() )
            throw logic_error("cannot get native data from a non-contiguous view");
        #endif
        return attribute() == rows or attribute() == columns ? host<1>().data() + offset() * size() otherwise host<2>().data();
    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::const_pointer array_upper<type,dim,device>::data ( ) const
    {
        #if debug
        if ( not contiguous() )
            throw logic_error("cannot get native data from a non-contiguous view");
        #endif
        return attribute() == rows or attribute() == columns ? host<1>().data() + offset() * size() otherwise host<2>().data();
    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::iterator array_upper<type,dim,device>::begin ( )
    {
        return attribute() == rows    ? host<1>().template rows   <dim-1>().begin() + offset() * row()    otherwise
               attribute() == columns ? host<1>().template columns<dim-1>().begin() + offset() * column() otherwise 
                                        host<2>().template columns<dim-1>().begin();
    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::const_iterator array_upper<type,dim,device>::begin ( ) const
    {
        return attribute() == rows    ? host<1>().template rows   <dim-1>().begin() + offset() * row()    otherwise
               attribute() == columns ? host<1>().template columns<dim-1>().begin() + offset() * column() otherwise 
                                        host<2>().template columns<dim-1>().begin();
    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::iterator array_upper<type,dim,device>::end ( )
    {
        return attribute() == rows    ? host<1>().template rows   <dim-1>().begin() + (offset() + 1) * row()    /* == begin() + row() */ otherwise
               attribute() == columns ? host<1>().template columns<dim-1>().begin() + (offset() + 1) * column() /* == begin() + row() */ otherwise
                                        host<2>().template columns<dim-1>().end();
    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::const_iterator array_upper<type,dim,device>::end ( ) const
    {
        return attribute() == rows    ? host<1>().template rows   <dim-1>().begin() + (offset() + 1) * row()    /* == begin() + row() */ otherwise
               attribute() == columns ? host<1>().template columns<dim-1>().begin() + (offset() + 1) * column() /* == begin() + row() */ otherwise
                                        host<2>().template columns<dim-1>().end();
    }

    template < class type, int dim, class device >
    constexpr array<type,dim-1,device>& array_upper<type,dim,device>::operator [] ( int pos )
    {
        return attribute() == rows    ? host<1>().template rows   <dim-1>()[offset() * row()    + pos] otherwise
               attribute() == columns ? host<1>().template columns<dim-1>()[offset() * column() + pos] otherwise 
                                        host<2>().template columns<dim-1>()[pos];
    }

    template < class type, int dim, class device >
    constexpr array<type,dim-1,device>& array_upper<type,dim,device>::operator [] ( int pos )
    {
        return attribute() == rows    ? host<1>().template rows   <dim-1>()[offset() * row()    + pos] otherwise
               attribute() == columns ? host<1>().template columns<dim-1>()[offset() * column() + pos] otherwise 
                                        host<2>().template columns<dim-1>()[pos];
    }

    template < class type, int dim, class device >
    template < int attribute >
    constexpr array<type,dim+1,device>& array_upper<type,dim,device>::host ( )
        requires ( attribute == 1 )
    {
        return *ptr1;
    }

    template < class type, int dim, class device >
    template < int attribute >
    constexpr const array<type,dim+1,device>& array_upper<type,dim,device>::host ( ) const
        requires ( attribute == 1 )
    {
        return *ptr1;
    }

    template < class type, int dim, class device >
    template < int attribute >
    constexpr array<type,dim,device>& array_upper<type,dim,device>::host ( )
        requires ( attribute == 2 )
    {
        return *ptr2;
    }

    template < class type, int dim, class device >
    template < int attribute >
    constexpr const array<type,dim,device>& array_upper<type,dim,device>::host ( ) const
        requires ( attribute == 2 )
    {
        return *ptr2;
    }

    template < class type, int dim, class device >
    constexpr bool array_upper<type,dim,device>::ownership ( ) const
    {
        return ptr1 == nullptr and ptr2 == nullptr;
    }
    
    template < class type, int dim, class device >
    constexpr bool array_upper<type,dim,device>::contiguous ( ) const
    {
        return ( attribute() == rows       and same_as<typename device::layout_type,layout_right> ) or 
               ( attribute() == columns    and same_as<typename device::layout_type,layout_left > ) or
               ( attribute() == transposed and host<2>().contiguous() );
    }

    template < class type, int dim, class device >
    constexpr auto array_upper<type,dim,device>::attribute ( ) const
    {
        if ( ptr1 != nullptr )
        {
            let rows_list = host<1>().template rows<dim>();
            if ( this >= rows_list.begin() and this <= rows_list.end() ) 
                return rows;
                
            #if debug
            let columns_list = host<1>().template columns<dim>();
            if ( this >= columns_list.begin() and this <= columns_list.end() )
                return columns;
            throw logic_error("unknown attribute: this array is probably not a view");
            #else
            return columns;
            #endif
        }

        #if debug
        if ( ptr2 != nullptr )
            return transposed;
        throw logic_error("unknown attribute: this array is probably not a view");
        #else
        return transposed;
        #endif
    }

    template < class type, int dim, class device >
    constexpr int array_upper<type,dim,device>::offset ( ) const
    {
        #if debug
        if ( attribute() == transposed )   
            throw logic_error("get view offset from a transposed one");
        #endif
        return attribute() == rows ? this - host<1>().template rows   <dim>().begin() otherwise
                                     this - host<1>().template columns<dim>().begin();
    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::reference array_upper<type,dim,device>::at ( int_type auto... args )
        requires ( sizeof...(args) == dim )
    {
        return attribute() == rows    ? host<1>().at(offset(), args...) otherwise
               attribute() == columns ? host<2>().at(args..., offset()) otherwise 
                                        host<2>().at(          args...);
    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::const_reference array_upper<type,dim,device>::at ( int_type auto... args ) const
        requires ( sizeof...(args) == dim )
    {
        return attribute() == rows or attribute() == columns ? host<1>().at(offset(), args...) otherwise
                                                               host<2>().at(          args...);
    }



} // namespace detail