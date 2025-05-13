namespace detail
{
    template < class device, int axis, int depth = 1 >
    constexpr void md_reverse ( auto& arr, const auto& shp )
    {
        static_assert ( axis >= 1 and axis <= arr.dimension() );
        
        if constexpr ( axis == 1 )
            device::reverse(arr.begin(), arr.end());
        else
            for ( int i in range(shp[depth]) )
                md_reverse<device,axis-1,depth+1>(arr[i], shp);
    }

    template < class device, int axis, int depth = 1 >
    constexpr void md_rotate ( auto& arr, const auto& shp, int n )
    {
        static_assert ( axis >= 1 and axis <= arr.dimension() );
        
        if constexpr ( axis == 1 )
            n > 0 ? device::rotate(arr.begin(), arr.end() - n, arr.end()) :
                    device::rotate(arr.begin(), arr.begin() - n, arr.end());
        else
            for ( int i in range(shp[depth]) )
                md_rotate<device,axis-1,depth+1>(arr[i], shp, n);
    }
    
} // namespace detail
