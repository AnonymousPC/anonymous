#pragma once

template < class context_type >
auto asio_scheduler<context_type>::schedule ( ) const noexcept
{
    return sender(ctx);
}

template < class context_type >
class asio_scheduler<context_type>::sender
{
    public: // Traits
        using sender_concept = std::execution::sender_t;
        using completion_signatures = std::execution::completion_signatures<std::execution::set_value_t(),std::execution::set_error_t(std::exception_ptr),std::execution::set_stopped_t()>;

    public: // Data
        context_type& ctx;

    public: // Typedef
        template < class receiver > class operation_state; // TODO: template < std::execution::receiver receiver >. 
        class env;
        
    public: // Interface
        auto connect ( std::execution::receiver auto&& );
        auto query   ( std::execution::get_env_t )      const noexcept;
};

template < class context_type >
auto asio_scheduler<context_type>::sender::connect ( std::execution::receiver auto&& recv )
{
    return operation_state<decay<decltype(recv)>>(ctx, std::forward<decltype(recv)>(recv));
}

template < class context_type >
auto asio_scheduler<context_type>::sender::query ( std::execution::get_env_t ) const noexcept
{
    return env(ctx);
}

template < class context_type >
template < class receiver >
class asio_scheduler<context_type>::sender::operation_state
{
    public: // Data
        context_type& ctx;
        receiver      recv;

    public: // Interface
        void start ( ) noexcept;
};

template < class context_type >
template < class receiver >
void asio_scheduler<context_type>::sender::operation_state<receiver>::start ( ) noexcept
{
    if ( std::execution::get_stop_token(std::execution::get_env(recv)).stop_requested() )
    {
        std::execution::set_stopped(std::move(recv)); // Stop channel.
        return;
    }

    try
    {
        boost::asio::post(ctx, [&] { std::execution::set_value(std::move(recv)); }); // Value channel.
    }
    catch ( ... )
    {
        std::execution::set_error(std::move(recv), std::current_exception()); // Error channel.
    }
}

template < class context_type >
class asio_scheduler<context_type>::sender::env
{
    public: // Data
        context_type& ctx;

    public: // Interface
        template < class channel >
        auto query ( std::execution::get_completion_scheduler_t<channel> ) const;
};

template < class context_type >
template < class channel >
auto asio_scheduler<context_type>::sender::env::query ( std::execution::get_completion_scheduler_t<channel> ) const
{
    return asio_scheduler<context_type>(ctx);
}
