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
    constexpr array_lower<type,dim,device>::array_lower ( const auto&... args )
        extends transpose_view ( static_cast<array<type,dim,device>&>(self) )
    {
        static_assert(sizeof...(args) == dim or sizeof...(args) == dim + 1);
        let shp = static_array<int,dim-1>();
        detail::for_constexpr<1,dim-1>([&] <int index> { shp[index] = index_value_of<index>(args...); });
        rows_view   .resize(shp, static_cast<array<type,dim,device>&>(self));
        columns_view.resize(shp, static_cast<array<type,dim,device>&>(self));
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
        return static_cast<array<type,dim-1,device>&>(rows<dim-1>()[ofs]);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr const array<type,dim-1,device>& array_lower<type,dim,device>::operator [] ( int ofs ) const
    {
        return static_cast<const array<type,dim-1,device>&>(rows<dim-1>()[ofs]);
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
        return rows_view.template value<dim2>(static_cast<array<type,dim,device>&>(self).static_shape(), offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> array_lower<type,dim,device>::rows ( int_type auto... offsets ) const
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return rows_view.template value<dim2>(static_cast<const array<type,dim,device>&>(self).static_shape(), offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> array_lower<type,dim,device>::columns ( int_type auto... offsets )
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return columns_view.template value<dim2>(static_cast<array<type,dim,device>&>(self).static_shape(), offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> array_lower<type,dim,device>::columns ( int_type auto... offsets ) const
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return columns_view.template value<dim2>(static_cast<const array<type,dim,device>&>(self).static_shape(), offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_upper<type,dim,device>& array_lower<type,dim,device>::as_transpose ( )
    {
        return transpose_view;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr const array_upper<type,dim,device>& array_lower<type,dim,device>::as_transpose ( ) const
    {
        return transpose_view;
    }
    







    template < class type, class device >
    class tuple_upper<type,1,device>
    {
        private: // Data
            std::vector<array_upper<type,1,device>> vct;

        public: // Access
            template < int dim2 > constexpr       std::span<array_upper<type,dim2,device>> value ( const auto&, const auto&... );
            template < int dim2 > constexpr const std::span<array_upper<type,dim2,device>> value ( const auto&, const auto&... ) const;
    
        public: // Member
            constexpr tuple_upper& clear  ( );
            constexpr tuple_upper& resize ( const static_array<int,1>&, array<type,2,device>& );
            constexpr tuple_upper& resize ( const static_array<int,1>&, std::vector<array_upper<type,2,device>>& );  
    };

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    class tuple_upper<type,dim,device>
    {
        private: // Data
            std::vector<array_upper<type,dim,device>> vct;
            tuple_upper<type,dim-1,device>            vct_other;

        public: // Access
            template < int dim2 > constexpr       std::span<array_upper<type,dim2,device>> value ( const auto&, const auto&... );
            template < int dim2 > constexpr const std::span<array_upper<type,dim2,device>> value ( const auto&, const auto&... ) const; 

        public: // Member
            constexpr tuple_upper& clear  ( );
            constexpr tuple_upper& resize ( const static_array<int,dim>&, array<type,dim+1,device>& );
            constexpr tuple_upper& resize ( const static_array<int,dim>&, std::vector<array_upper<type,dim+1,device>>& );  
    };

    template < class type, class device >
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> tuple_upper<type,1,device>::value ( const auto& shp, const auto&... offsets )
    {
        static_assert ( dim2 == 1 );
        return std::span<array_upper<type,dim2,device>>(vct.data() + detail::view_offset_begin(shp, offsets...),
                                                        vct.data() + detail::view_offset_end  (shp, offsets...));
    }

    template < class type, class device >
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> tuple_upper<type,1,device>::value ( const auto& shp, const auto&... offsets ) const
    {
        static_assert ( dim2 == 1 );
        return std::span<array_upper<type,dim2,device>>(const_cast<array_upper<type,dim2,device>*>(vct.data() + detail::view_offset_begin(shp, offsets...)),
                                                        const_cast<array_upper<type,dim2,device>*>(vct.data() + detail::view_offset_end  (shp, offsets...)));
    }

    template < class type, class device >
    constexpr tuple_upper<type,1,device>& tuple_upper<type,1,device>::clear ( )
    {
        vct.clear();
        return self;
    }

    template < class type, class device >
    constexpr tuple_upper<type,1,device>& tuple_upper<type,1,device>::resize ( const static_array<int,1>& shp, array<type,2,device>& arr )
    {
        vct.resize(shp[1]);
        std::fill(vct.begin(), vct.end(), array_upper<type,1,device>(arr));
        return self;
    }

    template < class type, class device >
    constexpr tuple_upper<type,1,device>& tuple_upper<type,1,device>::resize ( const static_array<int,1>& shp, std::vector<array_upper<type,2,device>>& arrs )
    {
        vct.resize(shp[1]);
        let ck = shp[1] / arrs.size(); // chunk.
        for ( int i in range(0, int(arrs.size()-1)) )
            std::fill(vct.begin() + i * ck, vct.begin() + (i + 1) * ck, array_upper<type,1,device>(static_cast<array<type,2,device>&>(arrs[i])));
        return self;
    }



    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> tuple_upper<type,dim,device>::value ( const auto& shp, const auto&... offsets )
    {
        static_assert ( dim2 >= 1 and dim2 <= dim );
        if constexpr ( dim2 == dim )
            return std::span<array_upper<type,dim2,device>>(vct.data() + detail::view_offset_begin(shp, offsets...),
                                                            vct.data() + detail::view_offset_end  (shp, offsets...));
        else
            return vct_other.template value<dim2>(shp, offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> tuple_upper<type,dim,device>::value ( const auto& shp, const auto&... offsets ) const
    {
        static_assert ( dim2 >= 1 and dim2 <= dim );
        if constexpr ( dim2 == dim )
            return std::span<array_upper<type,dim2,device>>(const_cast<array_upper<type,dim2,device>*>(vct.data() + detail::view_offset_begin(shp, offsets...)),
                                                            const_cast<array_upper<type,dim2,device>*>(vct.data() + detail::view_offset_end  (shp, offsets...)));
        else
            return vct_other.template value<dim2>(shp, offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr tuple_upper<type,dim,device>& tuple_upper<type,dim,device>::clear ( )
    {
        vct.clear();
        vct_other.clear();
        return self;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr tuple_upper<type,dim,device>& tuple_upper<type,dim,device>::resize ( const static_array<int,dim>& shp, array<type,dim+1,device>& arr )
    {
        vct.resize(shp[1]);
        std::fill(vct.begin(), vct.end(), array_upper<type,dim,device>(arr));

        let new_shp = static_array<int,dim-1>();
        new_shp[1] = shp[1] * shp[2];
        if constexpr ( dim >= 3 )
            detail::for_constexpr<2,dim-1>([&] <int index> { new_shp[index] = shp[index+1]; });
        vct_other.resize(new_shp, vct);

        return self;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr tuple_upper<type,dim,device>& tuple_upper<type,dim,device>::resize ( const static_array<int,dim>& shp, std::vector<array_upper<type,dim+1,device>>& arrs )
    {
        vct.resize(shp[1]);
        let ck = shp[1] / arrs.size(); // chunk.
        for ( int i in range(0, int(arrs.size()-1)) )
            std::fill(vct.begin() + i * ck, vct.begin() + (i + 1) * ck, array_upper<type,dim,device>(static_cast<array<type,dim+1,device>&>(arrs[i])));

        let new_shp = static_array<int,dim-1>();
        new_shp[1] = shp[1] * shp[2];
        if constexpr ( dim >= 3 )
            detail::for_constexpr<2,dim-1>([&] <int index> { new_shp[index] = shp[index+1]; });
        vct_other.resize(new_shp, vct);

        return self;
    }



    

} // namespace detail


