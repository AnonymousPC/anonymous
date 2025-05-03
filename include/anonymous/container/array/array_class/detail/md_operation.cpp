namespace detail
{
    constexpr decltype(auto) md_helper ( auto& arr, int_type auto idx1, int_type auto... idxs )
    {
        if constexpr ( sizeof...(idxs) >= 1 )
            return md_helper(arr[idx1], idxs...);
        else
            return arr[idx1];
    }

    constexpr decltype(auto) md_helper ( const auto& arr, int_type auto idx1, int_type auto... idxs )
    {
        if constexpr ( sizeof...(idxs) >= 1 )
            return md_helper(arr[idx1], idxs...);
        else
            return arr[idx1];
    }









    constexpr void md_generate ( auto& arr, const auto& shp, const auto& func, int_type auto... idx )
    {
        if constexpr ( sizeof...(idx) <= arr.dimension() - 2 )
            for ( int i in range(shp[sizeof...(idx)+1]) )
                md_generate(arr, shp, func, idx..., i);
        else
            for ( int i in range(shp[-1]) )
                md_helper(arr, idx..., i) = func(idx..., i);
    }

    template < class device >
    constexpr auto md_common_smaller ( const auto& old_shape, const auto& new_shape )
    {
        static_assert ( old_shape.size() == new_shape.size() );

        auto smaller_shape         = old_shape;
        auto smaller_size          = 1;
        auto smaller_resize_needed = 0;
        for_constexpr<1,old_shape.size()>([&] <int index>
            {
                if ( new_shape[index] < old_shape[index] )
                {
                    smaller_shape[index] = new_shape[index];
                    smaller_resize_needed += 1;
                }
            });
        for_constexpr<1,smaller_shape.size()>([&] <int index> 
            { 
                smaller_size *= smaller_shape[index]; 
            });
        auto smaller_relayout_needed = not ( ( same_as<typename device::layout_type,std::layout_right> and smaller_resize_needed == 1 and new_shape[ 1] < old_shape[ 1] ) or
                                             ( same_as<typename device::layout_type,std::layout_left > and smaller_resize_needed == 1 and new_shape[-1] < old_shape[-1] ) );                   

        return tuple(smaller_shape, smaller_size, smaller_resize_needed > 0, smaller_relayout_needed);
    }

    template < class device >
    constexpr auto md_common_larger ( const auto& old_shape, const auto& new_shape )
    {
        static_assert ( old_shape.size() == new_shape.size() );

        auto larger_shape         = old_shape;
        auto larger_size          = 1;
        auto larger_resize_needed = 0;
        for_constexpr<1,old_shape.size()>([&] <int index>
            {
                if ( new_shape[index] > old_shape[index] )
                {
                    larger_shape[index] = new_shape[index];
                    larger_resize_needed += 1;
                }
            });
        for_constexpr<1,larger_shape.size()>([&] <int index> 
            { 
                larger_size *= larger_shape[index]; 
            });
        auto larger_relayout_needed = not ( ( same_as<typename device::layout_type,std::layout_right> and larger_resize_needed == 1 and new_shape[ 1] > old_shape[ 1] ) or
                                            ( same_as<typename device::layout_type,std::layout_left > and larger_resize_needed == 1 and new_shape[-1] > old_shape[-1] ) );                   
  
        return tuple(larger_shape, larger_size, larger_resize_needed > 0, larger_relayout_needed);
    }

    constexpr void md_relayout_strict_smaller ( auto& arr, const auto& old_shape, const auto& new_shape, int_type auto... idx )
    {   
        using device_type   = remove_cvref<decltype(arr)>::device_type;
        using value_type    = remove_cvref<decltype(arr)>::value_type;
        using layout_type   = device_type::layout_type;
        using accessor_type = device_type::template accessor_type<value_type>;
        using mdspan        = std::mdspan<value_type,std::dextents<int,arr.dimension()>,layout_type,accessor_type>;

        auto adjust = [] (int x) { return x - 1; };

        if constexpr ( same_as<layout_type,std::layout_right> )
            if constexpr ( sizeof...(idx) <= arr.dimension() - 2 )
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
        
        else if constexpr ( same_as<layout_type,std::layout_left> )
            if constexpr ( sizeof...(idx) <= arr.dimension() - 2 )
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

        else
            static_assert(false, "not supported");
    }

    constexpr void md_relayout_strict_larger ( auto& arr, const auto& old_shape, const auto& new_shape, int_type auto... idx )
    {
        using device_type   = remove_cvref<decltype(arr)>::device_type;
        using value_type    = remove_cvref<decltype(arr)>::value_type;
        using layout_type   = device_type::layout_type;
        using accessor_type = device_type::template accessor_type<value_type>;
        using mdspan        = std::mdspan<value_type,std::dextents<int,arr.dimension()>,layout_type,accessor_type>;

        auto adjust = [] (int x) { return x - 1; };

        if constexpr ( same_as<layout_type,std::layout_right> )
            if constexpr ( sizeof...(idx) <= arr.dimension() - 2 )
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

        else if constexpr ( same_as<layout_type,std::layout_left> )
            if constexpr ( sizeof...(idx) <= arr.dimension() - 2 )
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
        
        else
            static_assert(false, "not supported yet");
    }
    
    template < class device, int axis, int depth = 1 >
    constexpr void md_push ( auto& arr, const auto& shp, auto&& new_value )
    {
        static_assert ( axis >= 1 and axis <= arr.dimension() );
        if constexpr ( axis == 1 )
            arr[-1] = std::move(new_value);
        else
            for ( int i in range(shp[depth]) )
                md_push<device,axis-1,depth+1>(arr[i], shp, std::move(new_value[i]));
    }

    template < class device, int axis, int depth = 1 >
    constexpr void md_pop ( auto& arr, const auto& shp, int pos )
    {
        static_assert ( axis >= 1 and axis <= arr.dimension() );
        

        if constexpr ( axis == 1 )
            device::move(arr.begin() + pos, arr.end(), arr.begin() + pos - 1);
        else
            for ( int i in range(shp[depth]) )
                md_pop<device,axis-1,depth+1>(arr[i], shp, pos); 
    }

    template < class device, int axis, int depth = 1 >
    constexpr void md_insert ( auto& arr, const auto& shp, int pos, auto&& new_value )
    {
        static_assert ( axis >= 1 and axis <= arr.dimension() );

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
        static_assert ( axis >= 1 and axis <= arr.dimension() );

        if constexpr ( axis == 1 )
            device::move(arr.begin() + pos_2, arr.end(), arr.begin() + pos_1 - 1);
        else
            for ( int i in range(shp[depth]) )
                md_erase<device,axis-1,depth+1>(arr[i], shp, pos_1, pos_2); 
    }
}