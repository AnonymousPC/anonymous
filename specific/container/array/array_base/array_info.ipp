#pragma once

namespace detail
{
    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_info<type,dim,device>::array_info ( const auto&... args )
    {
        static_assert(sizeof...(args) == dim or sizeof...(args) == dim + 1);
        for_constexpr<1,dim>([&] <int index> ( std::integral_constant<int,index> ) { shp[index] = index_value_of<index>(args...); });
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int array_info<type,dim,device>::size ( ) const
    {
        return std::accumulate(shp.begin(), shp.end(), 1, std::multiplies<>());
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array<int> array_info<type,dim,device>::shape ( ) const
    {
        return shp;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr inplace_array<int,dim> array_info<type,dim,device>::inplace_shape ( ) const
    {
        return shp;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr static_array<int,dim> array_info<type,dim,device>::static_shape ( ) const
    {
        return shp;
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int array_info<type,dim,device>::row ( ) const
    {
        return shp[1];
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr int array_info<type,dim,device>::column ( ) const
        requires ( dim == 2 )
    {
        return shp[2];
    }
    
    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr bool array_info<type,dim,device>::empty ( ) const
    {
        return std::any_of(shp.begin(), shp.end(), [] (int s) { return s == 0; });
    }

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    constexpr array_info<type,dim,device>& array_info<type,dim,device>::resize ( const static_array<int,dim>& new_shape )
    {
        shp = new_shape;
        return self;
    }

} // namespace detail
