namespace detail
{
    // Helper



    /// Multi-dimensional Operation






    template < auto attr >
    constexpr int view_offset_begin ( const auto& shp, int_type auto... offsets )
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
                        for_constexpr<decay<decltype(shp)>::size()-sizeof...(offsets),decay<decltype(shp)>::size()-sizeof...(offsets)+index-1>([&] <int index2> { p *= shp[index2]; });
                        p *= index_value_of<index>(offsets...);
                        ofs += p;
                    });
                return ofs;
            }
            else
                static_assert(false, "unknown attribute");
    }

    template < auto attr >
    constexpr int view_offset_end ( const auto& shp, int_type auto... offsets )
    {
        if constexpr ( attr == rows_attribute )
            return view_offset_begin<attr>(shp, offsets...) + shp[1+sizeof...(offsets)];
        else if constexpr ( attr == columns_attribute )
            return view_offset_begin<attr>(shp, offsets...) + shp[decay<decltype(shp)>::size()-sizeof...(offsets)];
        else
            static_assert(false, "unknown attribute");
    }





    auto stringalize_array ( auto& stream, const auto& arr )
    {
        return stringalize_array(stream, arr, [&] (const auto& item)
                   {
                       auto buff = std::stringstream();
                       buff.copyfmt(stream);
                       buff.setf(stream.flags());
                       buff << item;
                       return buff.str(); 
                   });
    }

    auto stringalize_array ( auto& stream, const auto& arr, const auto& stringalizer )
    {
        if constexpr ( decay<decltype(arr)>::dimension() == 1 )
            return array<std::string,decay<decltype(arr)>::dimension()>(arr.size(), [&] (int i) { return stringalizer(arr[i]); } );
        else
        {
            auto string_array = array<std::string,decay<decltype(arr)>::dimension()>();
            string_array.resize(arr.shape());
            for ( int i in range(arr.shape()[1]) )
                string_array[i] = stringalize_array(stream,arr[i],stringalizer);
            return string_array;
        }
    }

    void align_array ( auto& arr )
    {
        if constexpr ( decay<decltype(arr)>::dimension() == 1 )
        {
            auto align = arr.empty() ? 0 : arr.max([] (const auto& str1, const auto& str2) { return str1.size() < str2.size(); }).size();
            arr.for_each([&] (auto& str) { str.resize(align, ' '); });
        }
        else
        {
            auto align = arr.empty() ? 0 : arr.flatten().max([] (const auto& str1, const auto& str2) { return str1.size() < str2.size(); }).size();
            arr.flatten().for_each([&] (auto& str) { str.resize(align, ' '); });
        }
    }

    void print_array ( auto& stream, const auto& arr, int dep = 1 )
    {
        stream << '{';

        if constexpr ( decay<decltype(arr)>::dimension() == 1 )
            for ( int i in range(arr.size()) )
            {
                if ( i != 1 )
                    stream << ' ';
                stream << arr[i];
            }

        else
            for ( int i in range(arr.shape()[1]) )
            {
                if ( i != 1 )
                {
                    stream << ' ';
                    for ( int _ in range(arr.dimension() - 1) )
                        stream << '\n';
                    for ( int _ in range(dep) )
                        stream << ' ';
                }
                print_array(stream, arr[i], dep + 1);
            }

        stream << '}';
    }

}