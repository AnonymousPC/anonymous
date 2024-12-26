#pragma once

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( int_type auto... args )
    requires ( sizeof...(args) == dim )
    extends device::template vector<type> ( args * ... )
{

}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and 
             detail::ints_until_last_type<type,decltype(args)...> and
             std::copyable<type>
    extends device::template vector<type> ( detail::multiply_first_to_second_last(args...), last_value_of(args...) )
{

}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and
             detail::ints_until_last_func<type,decltype(args)...>
    extends device::template vector<type> ( detail::multiply_first_to_second_last(args...) )
{
    device::generate(data(), data() + size(), last_value_of(args...));
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and
               detail::ints_until_last_func_ints<type,decltype(args...)>
    extends device::template vector<type> ( detail::multiply_first_to_second_last(args...) )
{
    mdspan_generate(std::mdspan(data(), static_shape()), last_vlaue_of(args...));
}
