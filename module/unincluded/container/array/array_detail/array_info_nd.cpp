namespace detail
{
    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr detail::array_info<type,dim,device>::array_info ( detail::array_shape<dim> init_shp )
        extends shp ( init_shp )
    {

    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int detail::array_info<type,dim,device>::size ( ) const
    {
        auto sz = 1;
        for_constexpr<1,dim>([&] <int index> { sz *= shp[index]; });
        return sz;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array<int> detail::array_info<type,dim,device>::shape ( ) const
    {
        auto dyn = array<int>(dim);
        for_constexpr<1,dim>([&] <int index> { dyn[index] = shp[index]; });
        return dyn;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int detail::array_info<type,dim,device>::row ( ) const
    {
        return shp[1];
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int detail::array_info<type,dim,device>::column ( ) const
        requires ( dim == 2 )
    {
        return shp[2];
    }
    
    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr bool detail::array_info<type,dim,device>::empty ( ) const
    {
        return any_of_constexpr<1,dim>([&] <int index> { return shp[index] == 0; });
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr detail::array_info<type,dim,device>& detail::array_info<type,dim,device>::clear ( )
    {
        for_constexpr<1,dim>([&] <int index> { shp[index] = 0; });
        return self;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    template < int axis >
    constexpr int detail::array_info<type,dim,device>::get_size_axis ( ) const
    {
        static_assert ( ( axis >= -dim or axis <= -1 ) or ( axis >= 1 and axis <= dim ) );

        if constexpr ( axis >= 0 )
            return shp[axis];
        else
            return get_size_axis<axis+dim+1>();
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr detail::array_shape<dim> detail::array_info<type,dim,device>::get_shape ( ) const
    {
        return shp;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr void detail::array_info<type,dim,device>::set_resize ( detail::array_shape<dim> new_shape )
    {
        shp = new_shape;
    }
} // namespace detail
