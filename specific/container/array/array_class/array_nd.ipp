#pragma once

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( )
    extends vector ( ),
            view   ( self ),
            info   ( self ),
{

}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( int_type auto... args )
    requires ( sizeof...(args) == dim )
    extends vector ( args * ... ),
            view   ( self, args... ),
            info   ( self, args... )
{

}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and 
             detail::ints_until_last_type<type,decltype(args)...> and
             std::copyable<type>
    extends vector ( detail::multiply_first_to_second_last(args...), last_value_of(args...) ),
            view   ( self, args... ),
            info   ( self, args... )
{

}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and
             detail::ints_until_last_func<type,decltype(args)...>
    extends vector ( detail::multiply_first_to_second_last(args...) ),
            info   ( self, args... ),
            view   ( self, args... )
{
    device::generate(vector::begin(), vector::end(), last_value_of(args...));
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and
               detail::ints_until_last_func_ints<type,decltype(args...)>
    extends vector ( detail::multiply_first_to_second_last(args...) ),
            info   ( self, args... ),
            view   ( self, args... )
{
    md_generate(vector::begin(), vector::end(), static_cast<const info&>(self), last_value_of(args...));
}
