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
        // Assume shape() cannot contain partial 0.
        return host().empty();
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::pointer array_upper<type,1,device>::data ( )
    {
        assume[[contiguous()]];
        return host().data() + (index() - 1) * size();
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_pointer array_upper<type,1,device>::data ( ) const
    {
        assume[[contiguous()]];
        return host().data() + (index() - 1) * size();
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::iterator array_upper<type,1,device>::begin ( )
    {
        return contiguous() ? data() otherwise {data(), size()};
    }

    template < class type, class device >
    constexpr const array_upper<type,1,device>::iterator array_upper<type,1,device>::begin ( ) const
    {
        return contiguous() ? data() otherwise {data(), size()};
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::iterator array_upper<type,1,device>::end ( )
    {
        return contiguous() ? data() + size() otherwise {data() + host().size(), size()};
    }

    template < class type, class device >
    constexpr const array_upper<type,1,device>::iterator array_upper<type,1,device>::end ( ) const
    {
        return contiguous() ? data() + size() otherwise {data() + host().size(), size()};
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::reference array_upper<type,1,device>::operator [] ( int pos )
    {
        return upper().at(index(), pos);
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_reference array_upper<type,1,device>::operator [] ( int pos ) const
    {
        return upper().at(index(), pos);
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
        return ptr != nullptr;
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
        let rows_list = host().template rows<1>();
        return this >= rows_list.begin() and this <= rows_list.end() ? rows otherwise columns;
    }

    template < class type, class device >
    constexpr int array_upper<type,1,device>::index ( ) const
    {
        let rows_list = host().template rows<1>();
        if ( this >= rows_list.begin() and this <= rows_list.end() )
            return this - rows_list.begin() + 1;

        let columns_list = host().template columns<1>();
        if ( this >= columns_list.begin() and this <= columns_list.end() )
            return this - columns_list.begin() + 1;

        throw value_error("unknown index");
    }
    
    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::array_upper ( array_upper<type,dim+1,device>& init_  )
        extends ptr_1 ( &init_upper )
    {

    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::array_upper ( const array_upper<type,dim+1,device>& init_upper )
        extends ptr_1 ( &const_cast<array_upper<type,dim+1,device>&>(init_upper) )
    {
        
    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::array_upper ( array_upper<type,dim,device>& init_upper )
        extends ptr_2 ( &init_upper )
    {

    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::array_upper ( const array_upper<type,dim,device>& init_upper )
        extends ptr_2 ( &const_cast<array_upper<type,dim,device>&>(init_upper) )
    {

    }

    template < class type, int dim, class device >
    constexpr int array_upper<type,dim,device>::size ( ) const
    {
        if ( attribute() == row_view ) [[likely]]
            return upper<1>().size() / upper<1>().static_shape()[1];
        else if ( attribute() == column_view )
            return upper<1>().size() / upper<1>().static_shape()[-1];
        else // if ( attribute() == transpose_view )
            return upper<2>().size();
    }

    template < class type, int dim, class device >
    constexpr bool array_upper<type,dim,device>::empty ( ) const
    {
        // Assume shape() cannot contain partial 0.
        if ( attribute() == row_view or attribute() == column_view ) [[likely]]
            return upper<1>().empty();
        else // if ( attribute() == transpose_view )
            return upper<2>().empty();
    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::pointer array_upper<type,dim,device>::data ( )
    {
        if ( attribute() == row_view or attribute() == column_view ) [[likely]]
            if constexpr ( same_as<typename device::layout_type,std::layout_right> /* and [[assume(attribute() == row_view)]] */ )
                return upper<1>().data() + (index() - 1) * detail::array_product<2,-1>(upper<1>().static_shape());
            else if constexpr ( same_as<typename device::layout_type,std::layout_left> /* and [[assume(attribute() == column_view)]] */ )
                return upper<1>().data() + (index() - 1) * detail::array_product<1,-2>(upper<1>().static_shape());
            else
                static_assert(false, "device::layout_type is neither std::layout_right nor std::layout_left");
        else // if ( attribute() == transpose_view )
            return upper<2>().data();
    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::const_pointer array_upper<type,dim,device>::data ( ) const
    {
        if ( attribute() == row_view or attribute() == column_view ) [[likely]]
            if constexpr ( same_as<typename device::layout_type,std::layout_right> /* and [[assume(attribute() == row_view)]] */ )
                return upper<1>().data() + (index() - 1) * detail::array_product<2,-1>(upper<1>().static_shape());
            else if constexpr ( same_as<typename device::layout_type,std::layout_left> /* and [[assume(attribute() == column_view)]] */ )
                return upper<1>().data() + (index() - 1) * detail::array_product<1,-2>(upper<1>().static_shape());
            else
                static_assert(false, "device::layout_type is neither std::layout_right nor std::layout_left");
        else // if ( attribute() == transpose_view )
            return upper<2>().data();
    }

    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::iterator array_upper<type,dim,device>::begin ( )
    {
        if ( attribute() == row_view ) [[likely]]
            return upper<1>().array_lower<type,dim+1,device>::template row_views   <dim-1>().begin() + index() - 1;
        else if ( attribute() == column_view )
            return upper<1>().array_lower<type,dim+1,device>::template column_views<dim-1>().begin() + index() - 1;
        else // if ( attribute() == transpose_view )
            return upper<2>().array_lower<type,dim,  device>::template column_views<dim-1>().begin();
    } 



} // namespace detail