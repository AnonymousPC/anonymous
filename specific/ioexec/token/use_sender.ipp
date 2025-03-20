#pragma once

auto use_sender_t::as_default_on ( auto&& obj )
{
    return typename decay<decltype(obj)>
               ::template rebind_executor<executor_with_default<typename decay<decltype(obj)>::executor_type>>
               ::other
           (std::forward<decltype(obj)>(obj));
}

template< class executor_type >
class use_sender_t::executor_with_default 
    extends public executor_type 
{
    public: // Typedef
        using default_completion_token_type = use_sender_t;

    public: // Core
        executor_with_default ( const executor_type& ) noexcept;
        executor_with_default ( const auto& ex       ) noexcept requires ( not same_as<decay<decltype(ex)>,executor_with_default> and convertible_to<decay<decltype(ex)>,executor_type> );
};


template < class executor_type >
use_sender_t::executor_with_default<executor_type>::executor_with_default ( const executor_type& ex ) noexcept
    extends executor_type ( ex )
{
    
}

template < class executor_type >
use_sender_t::executor_with_default<executor_type>::executor_with_default ( const auto& ex ) noexcept
    requires ( not same_as<decay<decltype(ex)>,executor_with_default> and 
               convertible_to<decay<decltype(ex)>,executor_type> )
    /* this requires-clause should be first "not same_as<ex,self>", then "convertible_to<lower_executor>",
     * because "convertible_to" depends on itself.
     */
    extends executor_type ( ex )
{

}