namespace detail
{
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
    
} // namespace detail