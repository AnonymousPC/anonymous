#pragma once

namespace detail
{
    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>::array_lower ( )
        extends transpose_view ( static_cast<array<type,dim,device>&>(self) )
    {
        
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>::array_lower ( const auto&... shp )
        extends rows_view      ( static_cast<array<type,dim,device>&>(self), shp... ),
                columns_view   ( static_cast<array<type,dim,device>&>(self), shp... ),
                transpose_view ( static_cast<array<type,dim,device>&>(self) )
    {

    }

    template < class type, int dim, class device > 
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>::iterator array_lower<type,dim,device>::begin ( )
    {
        return rows<dim-1>().begin();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>::const_iterator array_lower<type,dim,device>::begin ( ) const
    {
        return rows<dim-1>().begin();
    }

    template < class type, int dim, class device > 
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>::iterator array_lower<type,dim,device>::end ( )
    {
        return rows<dim-1>().end();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>::const_iterator array_lower<type,dim,device>::end ( ) const
    {
        return rows<dim-1>().end();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array<type,dim-1,device>& array_lower<type,dim,device>::operator [] ( int ofs )
    {
        return rows<dim-1>()[ofs];
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr const array<type,dim-1,device>& array_lower<type,dim,device>::operator [] ( int ofs ) const
    {
        return rows<dim-1>()[ofs];
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>& array_lower<type,dim,device>::clear ( )
    {
        rows_view   .clear();
        columns_view.clear();
        return self;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>& array_lower<type,dim,device>::resize ( const static_array<int,dim>& new_shape )
    {
        rows_view   .resize(new_shape, static_cast<array<type,dim,device>&>(self));
        columns_view.resize(new_shape, static_cast<array<type,dim,device>&>(self));
        return self;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> array_lower<type,dim,device>::rows ( int_type auto... offsets )
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return std::span<array_upper<type,dim2,device>>(rows_view.template value<dim2>().data() + detail::view_offset_begin(static_shape(), offsets...),
                                                        rows_view.template value<dim2>().data() + detail::view_offset_end  (static_shape(), offsets...));
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> array_lower<type,dim,device>::rows ( int_type auto... offsets ) const
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return std::span<array_upper<type,dim2,device>>(rows_view.template value<dim2>().data() + detail::view_offset_begin(static_shape(), offsets...),
                                                        rows_view.template value<dim2>().data() + detail::view_offset_end  (static_shape(), offsets...));
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> array_lower<type,dim,device>::columns ( int_type auto... offsets )
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return std::span<array_upper<type,dim2,device>>(columns_view.template value<dim2>().data() + detail::view_offset_begin(static_shape(), offsets...),
                                                        columns_view.template value<dim2>().data() + detail::view_offset_end  (static_shape(), offsets...));
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> array_lower<type,dim,device>::columns ( int_type auto... offsets ) const
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return std::span<array_upper<type,dim2,device>>(columns_view.template value<dim2>().data() + detail::view_offset_begin(static_shape(), offsets...),
                                                        columns_view.template value<dim2>().data() + detail::view_offset_end  (static_shape(), offsets...));
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr array_upper<type,dim2,device>& array_lower<type,dim,device>::as_transpose ( )
    {
        return transpose_view;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr const array_upper<type,dim2,device>& array_lower<type,dim,device>::as_transpose ( ) const
    {
        return transpose_view;
    }
    







    template < class type, class device >
    class tuple_of_vector_array_upper<type,1,device>
    {
        private: // Data
            std::vector<array_upper<type,1,device>> vct;
        
        public: // Constructor
            constexpr tuple_of_vector_array_upper ( array<type,1,device>& arr, int shp, const auto&... /*unused*/ )
                extends vct ( shp, arr )
            {
                
            }

            constexpr tuple_of_vector_array_upper ( const array<type,1,device>& arr, int shp, const auto&... /*unused*/ )
                extends vct ( shp, arr )
            {
                
            }

        public: // Member
            template < int index >
            constexpr std::vector<array_upper<type,index,device>>& value ( )
                requires ( index == 1 )
            {
                return vct;
            }

            template < int index >
            constexpr const std::vector<array_upper<type,index,device>>& value ( ) const
                requires ( index == 1 )
            {
                return vct;
            }        
    };

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    class tuple_of_vector_array_upper<type,dim,device>
    {
        private: // Data
            std::vector<array_upper<type,dim,device>>      vct;
            tuple_of_vector_array_upper<type,dim-1,device> vcts;
        
        public: // Constructor
            constexpr tuple_of_vector_array_upper ( array<type,dim,device>& arr, int shp, const auto&... args )
                extends vct  ( shp, arr ),
                        vcts ( )
            {
                
            }

            constexpr tuple_of_vector_array_upper ( const array<type,dim,device>& arr, int shp, const auto&... args )
                extends vct ( shp, arr )
            {
                
            }

        public: // Member
            template < int index >
            constexpr std::vector<array_upper<type,index,device>>& value ( )
                requires ( index == 1 )
            {
                return vct;
            }

            template < int index >
            constexpr const std::vector<array_upper<type,index,device>>& value ( ) const
                requires ( index == 1 )
            {
                return vct;
            }        
    };
} // namespace detail


