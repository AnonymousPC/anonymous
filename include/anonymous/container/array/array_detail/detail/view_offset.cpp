namespace detail
{
    template < auto attr >
    constexpr int view_offset_begin ( const auto& shp, integral auto... offsets )
    {
        if constexpr ( sizeof...(offsets) == 0 )
            return 0;
        else
            if constexpr ( attr == rows_attribute )
            { 
                int ofs = 0;
                for_constexpr<1,sizeof...(offsets)>([&] <int index>
                    {
                        auto p = 1;
                        for_constexpr<1+index,1+sizeof...(offsets)>([&] <int index2> { p *= shp[index2]; });
                        p *= index_value_of<index>(offsets...);
                        ofs += p;
                    });
                return ofs;
            }
            else if constexpr ( attr == columns_attribute )
            {
                int ofs = 0;
                for_constexpr<1,sizeof...(offsets)>([&] <int index>
                    {
                        auto p = 1;
                        for_constexpr<shp.size()-sizeof...(offsets),shp.size()-sizeof...(offsets)+index-1>([&] <int index2> { p *= shp[index2]; });
                        p *= index_value_of<index>(offsets...);
                        ofs += p;
                    });
                return ofs;
            }
            else
                static_assert(false, "unknown attribute");
    }

    template < auto attr >
    constexpr int view_offset_end ( const auto& shp, integral auto... offsets )
    {
        if constexpr ( attr == rows_attribute )
            return view_offset_begin<attr>(shp, offsets...) + shp[1+sizeof...(offsets)];
        else if constexpr ( attr == columns_attribute )
            return view_offset_begin<attr>(shp, offsets...) + shp[shp.size()-sizeof...(offsets)];
        else
            static_assert(false, "unknown attribute");
    }
    
} // namespace detail

