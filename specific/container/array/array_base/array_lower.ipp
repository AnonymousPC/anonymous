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
        return rows<dim-1>();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>::const_iterator array_lower<type,dim,device>::begin ( ) const
    {
        return rows<dim-1>();
    }

    template < class type, int dim, class device > 
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>::iterator array_lower<type,dim,device>::end ( )
    {
        return rows_end<dim-1>();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>::const_iterator array_lower<type,dim,device>::end ( ) const
    {
        return rows_end<dim-1>();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array<type,dim-1,device>& array_lower<type,dim,device>::operator [] ( int ofs )
    {
        return begin()[ofs];
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr const array<type,dim-1,device>& array_lower<type,dim,device>::operator [] ( int ofs ) const
    {
        return begin()[ofs];
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr const array_lower<type,dim,device>& array_lower<type,dim,device>::clear ( )
    {
        for_constexpr<1,dim-1>([&] <int index> ( std::integral_constant<int,index> ) { rows_view   .template value<index>().clear(); });
        for_constexpr<1,dim-1>([&] <int index> ( std::integral_constant<int,index> ) { columns_view.template value<index>().clear(); });
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr const array_lower<type,dim,device>& array_lower<type,dim,device>::resize ( const static_array<int,dim>& new_shape )
    {
        static_assert(dimension() == 2, "you need to fill() each part of lower-vectors");
        for_constexpr<1,dim-1>([&] <int index> ( std::integral_constant<int,index> ) { rows_view   .template value<index>().resize(new_shape[index], static_cast<array<type,dim,device>&>(self)); });
        for_constexpr<1,dim-1>([&] <int index> ( std::integral_constant<int,index> ) { columns_view.template value<index>().resize(new_shape[index], static_cast<array<type,dim,device>&>(self)); });
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


