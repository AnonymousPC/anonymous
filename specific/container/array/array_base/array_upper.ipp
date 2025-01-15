#pragma once

namespace detail
{
    template < class type, class device >
    constexpr array_upper<type,1,device>::array_upper ( array<type,2,device>& init_upper )
        extends ptr ( &init_upper )
    {

    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::array_upper ( const array<type,2,device>& init_upper )
        extends ptr ( &const_cast<array<type,2,device>&>(init_upper) )
    {
        
    }

    template < class type, class device >
    constexpr int array_upper<type,1,device>::size ( ) const 
    {
        if ( attribute() == row_view ) [[likely]]
            return upper().column();
        else // if ( attribute() == column_view )
            return upper().row();
    }

    template < class type, class device >
    constexpr bool array_upper<type,1,device>::empty ( ) const 
    {
        // Assume shape() cannot contain partial 0.
        return upper().empty();
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::pointer array_upper<type,1,device>::data ( )
    {
        if constexpr ( same_as<typename device::layout_type,std::layout_right> /* and [[assume(attribute() == row_view)]] */ )
            return upper().data() + (index() - 1) * upper().column();
        else if constexpr ( same_as<typename device::layout_type,std::layout_left> /* and [[assume(attribute() == column_view)]] */ )
            return upper().data() + (index() - 1) * upper().row();
        else
            static_assert(false, "device::layout_type is neither std::layout_right nor std::layout_left");
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::const_pointer array_upper<type,1,device>::data ( ) const
    {
        if constexpr ( same_as<typename device::layout_type,std::layout_right> /* and [[assume(attribute() == row_view)]] */ )
            return upper().data() + (index() - 1) * upper().column();
        else if constexpr ( same_as<typename device::layout_type,std::layout_left> /* and [[assume(attribute() == column_view)]] */ )
            return upper().data() + (index() - 1) * upper().row();
        else
            static_assert(false, "device::layout_type is neither std::layout_right nor std::layout_left");
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::iterator array_upper<type,1,device>::begin ( )
    {
        if constexpr ( same_as<typename device::layout_type,std::layout_right> )
            if ( attribute() == row_view ) [[likely]]
                return { data() };
            else 
                throw exception("not coded yet");
        else if constexpr ( same_as<typename device::layout_type,std::layout_left> )
            if ( attribute() == row_view ) [[likely]]
                throw exception("not coded yet");
            else
                return { data() };
        else
            static_assert(false, "device::layout_type is neither std::layout_right nor std::layout_left");
    }

    template < class type, class device >
    constexpr const array_upper<type,1,device>::iterator array_upper<type,1,device>::begin ( ) const
    {
        if constexpr ( same_as<typename device::layout_type,std::layout_right> )
            if ( attribute() == row_view ) [[likely]]
                return { data() };
            else 
                throw exception("not coded yet");
        else if constexpr ( same_as<typename device::layout_type,std::layout_left> )
            if ( attribute() == row_view ) [[likely]]
                throw exception("not coded yet");
            else
                return { data() };
        else
            static_assert(false, "device::layout_type is neither std::layout_right nor std::layout_left");
    }

    template < class type, class device >
    constexpr array_upper<type,1,device>::iterator array_upper<type,1,device>::end ( )
    {
        if constexpr ( same_as<typename device::layout_type,std::layout_right> )
            if ( attribute() == row_view ) [[likely]]
                return { data() + size() };
            else 
                throw exception("not coded yet");
        else if constexpr ( same_as<typename device::layout_type,std::layout_left> )
            if ( attribute() == row_view ) [[likely]]
                throw exception("not coded yet");
            else
                return { data() + size() };
        else
            static_assert(false, "device::layout_type is neither std::layout_right nor std::layout_left");
    }

    template < class type, class device >
    constexpr const array_upper<type,1,device>::iterator array_upper<type,1,device>::end ( ) const
    {
        if constexpr ( same_as<typename device::layout_type,std::layout_right> )
            if ( attribute() == row_view ) [[likely]]
                return { data() + size() };
            else 
                throw exception("not coded yet");
        else if constexpr ( same_as<typename device::layout_type,std::layout_left> )
            if ( attribute() == row_view ) [[likely]]
                throw exception("not coded yet");
            else
                return { data() + size() };
        else
            static_assert(false, "device::layout_type is neither std::layout_right nor std::layout_left");
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
    constexpr array<type,2,device>& array_upper<type,1,device>::upper ( )
    {
        return *ptr;
    }
    
    template < class type, class device >
    constexpr const array<type,2,device>& array_upper<type,1,device>::upper ( ) const
    {
        return *ptr;
    } 
        
    template < class type, class device >
    constexpr bool independent ( ) const
    {
        return upper_ptr == nullptr;
    }

    template < class type, class device >
    constexpr auto array_upper<type,1,device>::attribute ( ) const
    {
        let row_index = &self - upper().array_lower<type,2,device>::template row_views<1>().data() + 1;
        if ( row_index >= 1 and row_index <= upper().array_lower<type,2,device>::template row_views<1>().size() ) [[likely]]
            return row_view;
        else
            return column_view;
    }

    template < class type, class device >
    constexpr int array_upper<type,1,device>::index ( ) const
    {
        let row_index = &self - upper().array_lower<type,2,device>::template row_views<1>().data() + 1;
        if ( row_index >= 1 and row_index <= upper().array_lower<type,2,device>::template row_views<1>().size() ) [[likely]]
            return row_index;
        else
            return &self - upper().lower::column_views().data() + 1;
    }
    
    template < class type, int dim, class device >
    constexpr array_upper<type,dim,device>::array_upper ( array_upper<type,dim+1,device>& init_upper )
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