namespace detail
{
    // Helper

    template < class input_type, int count, class... int_types >
    constexpr bool invocable_by_n_ints_helper = []
        {
            if constexpr ( count >= 1 )
                return invocable_by_n_ints_helper<input_type,count-1,int_types...,int>;
            else
                return invocable<input_type,int_types...>;
        } ();

    template < class input_type, int count >
    concept invocable_by_n_ints = invocable_by_n_ints_helper<input_type,count>; // As concept cannot be recursive.

    template < class input_type, class result_type, int count, class... int_types >
    constexpr bool invocable_r_by_n_ints_helper = []
        {
            if constexpr ( count >= 1 )
                return invocable_r_by_n_ints_helper<input_type,result_type,count-1,int_types...,int>;
            else
                return invocable_r<input_type,result_type,int_types...>;
        } ();

    template < class input_type, class result_type, int count >
    concept invocable_r_by_n_ints = invocable_r_by_n_ints_helper<input_type,result_type,count>;

    template < class input_type, int count, class... types >
    struct invoke_result_by_n_ints_helper;

    template < class input_type, int count, class... types >
        requires ( count >= 1 )
    struct invoke_result_by_n_ints_helper<input_type,count,types...>
    {
        using type = invoke_result_by_n_ints_helper<input_type,count-1,int,types...>::type;
    };

    template < class input_type, int count, class... types >
        requires ( count == 0 )
    struct invoke_result_by_n_ints_helper<input_type,count,types...>
    {
        using type = invoke_result<input_type,types...>;
    };

    template < class input_type, int count >
    using invoke_result_by_n_ints = invoke_result_by_n_ints_helper<input_type,count>::type;





    // Concept

    template < class value_type, class... types >
    constexpr bool ints_until_last_type =
        all_of_constexpr<1,sizeof...(types)-1>([] <int index> { return convertible_to<index_type_of<index,types...>,int>; }) and
        ( (     is_void<value_type> and not invocable<last_type_of<types...>> and not invocable_by_n_ints<last_type_of<types...>,sizeof...(types)> ) or
          ( not is_void<value_type> and convertible_to<last_type_of<types...>,value_type> ) );

    template < class value_type, class... types >
    constexpr bool ints_until_last_generator =
        all_of_constexpr<1,sizeof...(types)-1>([] <int index> { return convertible_to<index_type_of<index,types...>,int>; }) and
        ( (     is_void<value_type> and invocable  <last_type_of<types...>>            ) or 
          ( not is_void<value_type> and invocable_r<last_type_of<types...>,value_type> ) );

    template < class value_type, class... types >
    constexpr bool ints_until_last_function =  
        all_of_constexpr<1,sizeof...(types)-1>([] <int index> { return convertible_to<index_type_of<index,types...>,int>; }) and 
        ( (     is_void<value_type> and invocable_by_n_ints  <last_type_of<types...>,           sizeof...(types)> ) or
          ( not is_void<value_type> and invocable_r_by_n_ints<last_type_of<types...>,value_type,sizeof...(types)> ) );



    /// Multi-dimensional Operation

    constexpr decltype(auto) md_access ( auto& arr, int_type auto idx1, int_type auto... idxs )
    {
        if constexpr ( sizeof...(idxs) >= 1 )
            return md_access(arr[idx1], idxs...);
        else
            return arr[idx1];
    }

    constexpr decltype(auto) md_access ( const auto& arr, int_type auto idx1, int_type auto... idxs )
    {
        if constexpr ( sizeof...(idxs) >= 1 )
            return md_access(arr[idx1], idxs...);
        else
            return arr[idx1];
    }

    constexpr void md_generate ( auto& arr, const auto& shp, const auto& func, int_type auto... idx )
    {
        if constexpr ( sizeof...(idx) <= decay<decltype(arr)>::dimension() - 2 )
            for ( int i in range(shp[sizeof...(idx)+1]) )
                md_generate(arr, shp, func, idx..., i);
        else
            for ( int i in range(shp[-1]) )
                md_access(arr, idx..., i) = func(idx..., i);
    }

    template < class device >
    constexpr auto md_common_smaller ( const auto& old_shape, const auto& new_shape )
    {
        static_assert ( decay<decltype(old_shape)>::size() == decay<decltype(new_shape)>::size() );

        auto smaller_shape     = old_shape;
        auto smaller_size      = 1;
        auto smaller_resizable = 0;
        for_constexpr<1,decay<decltype(old_shape)>::size()>([&] <int index>
        {
            if ( new_shape[index] < old_shape[index] )
            {
                smaller_shape[index] = new_shape[index];
                smaller_resizable += 1;
            }
        });
        for_constexpr<1,decay<decltype(smaller_shape)>::size()>([&] <int index> { smaller_size *= smaller_shape[index]; });
        auto smaller_relayoutable = not ( ( same_as<typename device::layout_type,std::layout_right> and smaller_resizable == 1 and new_shape[ 1] < old_shape[ 1] ) or
                                          ( same_as<typename device::layout_type,std::layout_left > and smaller_resizable == 1 and new_shape[-1] < old_shape[-1] ) );                   

        return tuple(smaller_shape, smaller_size, smaller_resizable > 0, smaller_relayoutable);
    }

    template < class device >
    constexpr auto md_common_larger ( const auto& old_shape, const auto& new_shape )
    {
        static_assert ( decay<decltype(old_shape)>::size() == decay<decltype(new_shape)>::size() );

        auto larger_shape     = old_shape;
        auto larger_size      = 1;
        auto larger_resizable = 0;
        for_constexpr<1,decay<decltype(old_shape)>::size()>([&] <int index>
        {
            if ( new_shape[index] > old_shape[index] )
            {
                larger_shape[index] = new_shape[index];
                larger_resizable += 1;
            }
        });
        for_constexpr<1,decay<decltype(larger_shape)>::size()>([&] <int index> { larger_size *= larger_shape[index]; });
        auto larger_relayoutable = not ( ( same_as<typename device::layout_type,std::layout_right> and larger_resizable == 1 and new_shape[ 1] > old_shape[ 1] ) or
                                         ( same_as<typename device::layout_type,std::layout_left > and larger_resizable == 1 and new_shape[-1] > old_shape[-1] ) );                   
  
        return tuple(larger_shape, larger_size, larger_resizable > 0, larger_relayoutable);
    }

    constexpr void md_relayout_strict_smaller ( auto& arr, const auto& old_shape, const auto& new_shape, int_type auto... idx )
    {   
        using device_type   = decay<decltype(arr)>::device_type;
        using value_type    = decay<decltype(arr)>::value_type;
        constexpr int dim   = decay<decltype(arr)>::dimension();
        using layout_type   = device_type::layout_type;
        using accessor_type = device_type::template accessor_type<value_type>;
        using mdspan        = std::mdspan<value_type,std::dextents<int,dim>,layout_type,accessor_type>;

        auto adjust = [] (int x) { return x - 1; };

        if constexpr ( same_as<layout_type,std::layout_right> )
        {
            if constexpr ( sizeof...(idx) <= decay<decltype(arr)>::dimension() - 2 )
                for ( int i in range(new_shape[sizeof...(idx)+1]) )
                    md_relayout_strict_smaller(arr, old_shape, new_shape, idx..., i);
            else
                for ( int i in range(new_shape[-1]) )
                {
                    auto old_offset = mdspan(arr.data(), old_shape).mapping()(adjust(idx)..., adjust(i)); 
                    auto new_offset = mdspan(arr.data(), new_shape).mapping()(adjust(idx)..., adjust(i));
                    if ( old_offset != new_offset )
                        arr.data()[new_offset] = std::move(arr.data()[old_offset]);
                }
        }
        
        else if constexpr ( same_as<layout_type,std::layout_left> )
        {
            if constexpr ( sizeof...(idx) <= decay<decltype(arr)>::dimension() - 2 )
                for ( int i in range(new_shape[-int(sizeof...(idx))-1]) )
                    md_relayout_strict_smaller(arr, old_shape, new_shape, i, idx...);
            else
                for ( int i in range(new_shape[1]) )
                {
                    auto old_offset = mdspan(arr.data(), old_shape).mapping()(adjust(i), adjust(idx)...); 
                    auto new_offset = mdspan(arr.data(), new_shape).mapping()(adjust(i), adjust(idx)...);
                    if ( old_offset != new_offset )
                        arr.data()[new_offset] = std::move(arr.data()[old_offset]);
                }
        }
    }

    constexpr void md_relayout_strict_larger ( auto& arr, const auto& old_shape, const auto& new_shape, int_type auto... idx )
    {
        using device_type   = decay<decltype(arr)>::device_type;
        using value_type    = decay<decltype(arr)>::value_type;
        constexpr int dim   = decay<decltype(arr)>::dimension();
        using layout_type   = device_type::layout_type;
        using accessor_type = device_type::template accessor_type<value_type>;
        using mdspan        = std::mdspan<value_type,std::dextents<int,dim>,layout_type,accessor_type>;

        auto adjust = [] (int x) { return x - 1; };

        if constexpr ( same_as<layout_type,std::layout_right> )
        {
            if constexpr ( sizeof...(idx) <= decay<decltype(arr)>::dimension() - 2 )
                for ( int i in range(old_shape[sizeof...(idx)+1], 1, -1) )
                    md_relayout_strict_larger(arr, old_shape, new_shape, idx..., i);
            else
                for ( int i in range(old_shape[-1], 1, -1) )
                {
                    auto old_offset = mdspan(arr.data(), old_shape).mapping()(adjust(idx)..., adjust(i));
                    auto new_offset = mdspan(arr.data(), new_shape).mapping()(adjust(idx)..., adjust(i));
                    if ( old_offset != new_offset )
                    {
                        arr.data()[new_offset] = std::move(arr.data()[old_offset]);
                        arr.data()[old_offset] = value_type();
                    }
                }
        }

        else if constexpr ( same_as<layout_type,std::layout_left> )
        {
            if constexpr ( sizeof...(idx) <= decay<decltype(arr)>::dimension() - 2 )
                for ( int i in range(old_shape[-int(sizeof...(idx))-1], 1, -1) )
                    md_relayout_strict_larger(arr, old_shape, new_shape, i, idx...);
            else
                for ( int i in range(old_shape[1], 1, -1) )
                {
                    auto old_offset = mdspan(arr.data(), old_shape).mapping()(adjust(i), adjust(idx)...);
                    auto new_offset = mdspan(arr.data(), new_shape).mapping()(adjust(i), adjust(idx)...);
                    if ( old_offset != new_offset )
                    {
                        arr.data()[new_offset] = std::move(arr.data()[old_offset]);
                        arr.data()[old_offset] = value_type();
                    }
                }
        }
    }
    
    template < class device, int axis, int depth = 1 >
    constexpr void md_push ( auto& arr, const auto& shp, auto&& new_value )
    {
        static_assert ( axis >= 1 and axis <= decay<decltype(arr)>::dimension() );
        if constexpr ( axis == 1 )
            arr[-1] = std::move(new_value);
        else
            for ( int i in range(shp[depth]) )
                md_push<device,axis-1,depth+1>(arr[i], shp, std::move(new_value[i]));
    }

    template < class device, int axis, int depth = 1 >
    constexpr void md_pop ( auto& arr, const auto& shp, int pos )
    {
        static_assert ( axis >= 1 and axis <= decay<decltype(arr)>::dimension() );

        if constexpr ( axis == 1 )
            device::move(arr.begin() + pos, arr.end(), arr.begin() + pos - 1);
        else
            for ( int i in range(shp[depth]) )
                md_pop<device,axis-1,depth+1>(arr[i], shp, pos); 
    }

    template < class device, int axis, int depth = 1 >
    constexpr void md_insert ( auto& arr, const auto& shp, int pos, auto&& new_value )
    {
        static_assert ( axis >= 1 and axis <= decay<decltype(arr)>::dimension() );

        if constexpr ( axis == 1 )
        {
            device::move_backward(arr.begin() + pos - 1, arr.end() - 1, arr.end());
            arr[pos] = std::move(new_value);
        }
        else
            for ( int i in range(shp[depth]) )
                md_insert<device,axis-1,depth+1>(arr[i], shp, pos, std::move(new_value[i]));
    }

    template < class device, int axis, int depth = 1 >
    constexpr void md_erase ( auto& arr, const auto& shp, int pos_1, int pos_2 )
    {
        static_assert ( axis >= 1 and axis <= decay<decltype(arr)>::dimension() );

        if constexpr ( axis == 1 )
            device::move(arr.begin() + pos_2, arr.end(), arr.begin() + pos_1 - 1);
        else
            for ( int i in range(shp[depth]) )
                md_erase<device,axis-1,depth+1>(arr[i], shp, pos_1, pos_2); 
    }

    template < class device, int axis, int depth = 1 >
    constexpr void md_reverse ( auto& arr, const auto& shp )
    {
        static_assert ( axis >= 1 and axis <= decay<decltype(arr)>::dimension() );
        if constexpr ( axis == 1 )
            device::reverse(arr.begin(), arr.end());
        else
            for ( int i in range(shp[depth]) )
                md_reverse<device,axis-1,depth+1>(arr[i], shp);
    }

    template < class device, int axis, int depth = 1 >
    constexpr void md_rotate ( auto& arr, const auto& shp, int n )
    {
        static_assert ( axis >= 1 and axis <= decay<decltype(arr)>::dimension() );
        if constexpr ( axis == 1 )
            n > 0 ? device::rotate(arr.begin(), arr.end() - n, arr.end()) :
                    device::rotate(arr.begin(), arr.begin() - n, arr.end());
        else
            for ( int i in range(shp[depth]) )
                md_rotate<device,axis-1,depth+1>(arr[i], shp, n);
    }

    enum array_attribute
    {
        no_attribute,
        rows_attribute,
        columns_attribute,
        transpose_attribute 
    };


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