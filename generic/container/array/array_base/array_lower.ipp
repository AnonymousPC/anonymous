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
        if constexpr ( sizeof...(args) == dim ) // Without trailing value
        {
            let shp = static_array<int,dim>{args...};
            rows_view   .template resize<rows_attribute   >(shp, static_cast<array<type,dim,device>&>(self));
            columns_view.template resize<columns_attribute>(shp, static_cast<array<type,dim,device>&>(self));
        }
        else if constexpr ( sizeof...(args) == dim + 1 ) // With trailing value
        {
            let shp = static_array<int,dim>();
            for_constexpr<1,dim>([&] <int index> { shp[index] = index_value_of<index>(args...); });
            rows_view   .template resize<rows_attribute   >(shp, static_cast<array<type,dim,device>&>(self));
            columns_view.template resize<columns_attribute>(shp, static_cast<array<type,dim,device>&>(self));
        }
        else
            static_assert(false, "invalid argument list");
    }

    template < class type, int dim, class device > 
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>::iterator array_lower<type,dim,device>::begin ( )
    {
        return get_rows<dim-1>().begin();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>::const_iterator array_lower<type,dim,device>::begin ( ) const
    {
        return get_rows<dim-1>().begin();
    }

    template < class type, int dim, class device > 
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>::iterator array_lower<type,dim,device>::end ( )
    {
        return get_rows<dim-1>().end();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_lower<type,dim,device>::const_iterator array_lower<type,dim,device>::end ( ) const
    {
        return get_rows<dim-1>().end();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array<type,dim-1,device>& array_lower<type,dim,device>::operator [] ( int ofs )
    {
        return static_cast<array<type,dim-1,device>&>(get_rows<dim-1>()[ofs]);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr const array<type,dim-1,device>& array_lower<type,dim,device>::operator [] ( int ofs ) const
    {
        return static_cast<const array<type,dim-1,device>&>(get_rows<dim-1>()[ofs]);
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
        rows_view   .template resize<rows_attribute   >(new_shape, static_cast<array<type,dim,device>&>(self));
        columns_view.template resize<columns_attribute>(new_shape, static_cast<array<type,dim,device>&>(self));
        return self;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array<type,dim,device>& array_lower<type,dim,device>::transpose ( )
    {
        return static_cast<array<type,dim,device>&>(transpose_view);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr const array<type,dim,device>& array_lower<type,dim,device>::transpose ( ) const
    {
        return static_cast<const array<type,dim,device>&>(transpose_view);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> array_lower<type,dim,device>::get_rows ( int_type auto... offsets )
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return rows_view.template value<rows_attribute,dim2>(static_cast<array<type,dim,device>&>(self).shape(), offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> array_lower<type,dim,device>::get_rows ( int_type auto... offsets ) const
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return rows_view.template value<rows_attribute,dim2>(static_cast<const array<type,dim,device>&>(self).shape(), offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> array_lower<type,dim,device>::get_columns ( int_type auto... offsets )
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return columns_view.template value<columns_attribute,dim2>(static_cast<array<type,dim,device>&>(self).shape(), offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> array_lower<type,dim,device>::get_columns ( int_type auto... offsets ) const
    {
        static_assert ( dim2 > 0 and dim2 < dim );
        static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
        return columns_view.template value<columns_attribute,dim2>(static_cast<const array<type,dim,device>&>(self).shape(), offsets...);
    }
    







    template < class type, class device >
    class tuple_upper<type,1,device>
    {
        public: // Data
            std::vector<array_upper<type,1,device>> vct;

        public: // Access
            template < auto attr, int dim2 > constexpr       std::span<array_upper<type,dim2,device>> value ( const auto&, const auto&... );
            template < auto attr, int dim2 > constexpr const std::span<array_upper<type,dim2,device>> value ( const auto&, const auto&... ) const;
    
        public: // Member
                                   constexpr tuple_upper& clear  ( );
            template < auto attr > constexpr tuple_upper& resize ( const auto&, array<type,2,device>& );
            template < auto attr > constexpr tuple_upper& resize ( const auto&, std::vector<array_upper<type,2,device>>& );  
    };

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    class tuple_upper<type,dim,device>
    {
        public: // Data
            std::vector<array_upper<type,dim,device>> vct;
            tuple_upper<type,dim-1,device>            vct_other;

        public: // Access
            template < auto attr, int dim2 > constexpr       std::span<array_upper<type,dim2,device>> value ( const auto&, const auto&... );
            template < auto attr, int dim2 > constexpr const std::span<array_upper<type,dim2,device>> value ( const auto&, const auto&... ) const; 

        public: // Member
                                   constexpr tuple_upper& clear  ( );
            template < auto attr > constexpr tuple_upper& resize ( const auto&, array<type,dim+1,device>& );
            template < auto attr > constexpr tuple_upper& resize ( const auto&, std::vector<array_upper<type,dim+1,device>>& );  
    };

    template < class type, class device >
    template < auto attr, int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> tuple_upper<type,1,device>::value ( const auto& shp, const auto&... offsets )
    {
        static_assert ( dim2 == 1 );
        return std::span(vct.data() + detail::view_offset_begin<attr>(shp, offsets...),
                         vct.data() + detail::view_offset_end  <attr>(shp, offsets...));
    }

    template < class type, class device >
    template < auto attr, int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> tuple_upper<type,1,device>::value ( const auto& shp, const auto&... offsets ) const
    {
        static_assert ( dim2 == 1 );
        return std::span(const_cast<array_upper<type,dim2,device>*>(vct.data() + detail::view_offset_begin<attr>(shp, offsets...)),
                         const_cast<array_upper<type,dim2,device>*>(vct.data() + detail::view_offset_end  <attr>(shp, offsets...)));
    }

    template < class type, class device >
    constexpr tuple_upper<type,1,device>& tuple_upper<type,1,device>::clear ( )
    {
        vct.clear();
        return self;
    }

    template < class type, class device >
    template < auto attr >
    constexpr tuple_upper<type,1,device>& tuple_upper<type,1,device>::resize ( const auto& shp, array<type,2,device>& arr )
    {
        let s = 1;
        if constexpr ( attr == rows_attribute )
            for_constexpr<1,decay<decltype(shp)>::size()-1>([&] <int index> { s *= shp[index]; });
        else if constexpr ( attr == columns_attribute )
            for_constexpr<2,decay<decltype(shp)>::size()  >([&] <int index> { s *= shp[index]; });
        else
            static_assert(false, "unknown attribute");
        vct.resize(s);
        for ( int i in range(0, s-1) ) 
            vct[i] = array_upper<type,1,device>(arr, attr, i);
        return self;
    }

    template < class type, class device >
    template < auto attr >
    constexpr tuple_upper<type,1,device>& tuple_upper<type,1,device>::resize ( const auto& shp, std::vector<array_upper<type,2,device>>& arrs )
    {
        let s = 1;
        if constexpr ( attr == rows_attribute )
            for_constexpr<1,decay<decltype(shp)>::size()-1>([&] <int index> { s *= shp[index]; });
        else if constexpr ( attr == columns_attribute )
            for_constexpr<2,decay<decltype(shp)>::size()  >([&] <int index> { s *= shp[index]; });
        else
            static_assert(false, "unknown attribute");
        vct.resize(s);
        [[assume(s % arrs.size() == 0)]];
        let ck = s / arrs.size(); // chunk.
        for ( int i in range(0, int(arrs.size()-1)) )
            for ( int j in range(0, int(ck-1)))
                vct[i*ck+j] = array_upper<type,1,device>(static_cast<array<type,2,device>&>(arrs[i]), attr, j);
        return self;
    }



    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < auto attr, int dim2 >
    constexpr std::span<array_upper<type,dim2,device>> tuple_upper<type,dim,device>::value ( const auto& shp, const auto&... offsets )
    {
        static_assert ( dim2 >= 1 and dim2 <= dim );
        if constexpr ( dim2 == dim )
            return std::span(vct.data() + detail::view_offset_begin<attr>(shp, offsets...),
                             vct.data() + detail::view_offset_end  <attr>(shp, offsets...));
        else
            return vct_other.template value<attr,dim2>(shp, offsets...);
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < auto attr, int dim2 >
    constexpr const std::span<array_upper<type,dim2,device>> tuple_upper<type,dim,device>::value ( const auto& shp, const auto&... offsets ) const
    {
        static_assert ( dim2 >= 1 and dim2 <= dim );
        if constexpr ( dim2 == dim )
            return std::span(const_cast<array_upper<type,dim2,device>*>(vct.data() + detail::view_offset_begin<attr>(shp, offsets...)),
                             const_cast<array_upper<type,dim2,device>*>(vct.data() + detail::view_offset_end  <attr>(shp, offsets...)));
        else
            return vct_other.template value<attr,dim2>(shp, offsets...);
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
    template < auto attr >
    constexpr tuple_upper<type,dim,device>& tuple_upper<type,dim,device>::resize ( const auto& shp, array<type,dim+1,device>& arr )
    {
        let s = 1;
        if constexpr ( attr == rows_attribute )
            for_constexpr<1,decay<decltype(shp)>::size()-dim>([&] <int index> { s *= shp[index]; });
        else if constexpr ( attr == columns_attribute )
            for_constexpr<dim+1,decay<decltype(shp)>::size()>([&] <int index> { s *= shp[index]; });
        else
            static_assert(false, "unknown attribute");
        vct.resize(s);
        for ( int i in range(0, s-1) )
            vct[i] = array_upper<type,dim,device>(arr, attr, i);
        vct_other.template resize<attr>(shp, vct);
        return self;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < auto attr >
    constexpr tuple_upper<type,dim,device>& tuple_upper<type,dim,device>::resize ( const auto& shp, std::vector<array_upper<type,dim+1,device>>& arrs )
    {
        let s = 1;
        if constexpr ( attr == rows_attribute )
            for_constexpr<1,decay<decltype(shp)>::size()-dim>([&] <int index> { s *= shp[index]; });
        else if constexpr ( attr == columns_attribute )
            for_constexpr<dim+1,decay<decltype(shp)>::size()>([&] <int index> { s *= shp[index]; });
        else
            static_assert(false, "unknown attribute");
        vct.resize(s);
        [[assume(s % arrs.size() == 0)]];
        let ck = s / arrs.size(); // chunk.
        for ( int i in range(0, int(arrs.size()-1)) )
            for ( int j in range(0, int(ck-1)) )
                vct[i*ck+j] = array_upper<type,dim,device>(static_cast<array<type,dim+1,device>&>(arrs[i]), attr, j);
        vct_other.template resize<attr>(shp, vct);
        return self;
    }



    

} // namespace detail


