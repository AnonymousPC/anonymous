#pragma once

class system_scheduler::sender
{
    public: // Traits
        using sender_concept        = std::execution::sender_t;
        using completion_signatures = std::execution::completion_signatures<std::execution::set_value_t(),std::execution::set_error_t(std::exception_ptr),std::execution::set_stopped_t()>;

    public: // Typedef
        template < class receiver > class operation_state; // TODO: template < std::execution::receiver receiver >. 
        class env;
        
    public: // Interface
        constexpr static std::execution::operation_state auto connect ( std::execution::receiver auto&& );
        constexpr static env query ( std::execution::get_env_t ) noexcept;
};

template < class receiver >
class system_scheduler::sender::operation_state
{
    public: // Data
        receiver recv;

    public: // Interface
        constexpr void start ( ) noexcept;
};

class system_scheduler::sender::env
{
    public: // Interface
        template < class channel > constexpr static system_scheduler query ( std::execution::get_completion_scheduler_t<channel> ) noexcept;
};

constexpr system_scheduler::sender system_scheduler::schedule ( ) noexcept
{
    return sender();
}

constexpr std::execution::operation_state auto system_scheduler::sender::connect ( std::execution::receiver auto&& recv )
{
    return operation_state<decay<decltype(recv)>>(std::forward<decltype(recv)>(recv));
}

constexpr system_scheduler::sender::env system_scheduler::sender::query ( std::execution::get_env_t ) noexcept
{
    return env();
}

template < class receiver >
constexpr void system_scheduler::sender::operation_state<receiver>::start ( ) noexcept
{
    if ( std::execution::get_stop_token(std::execution::get_env(recv)).stop_requested() )
    {
        std::execution::set_stopped(std::move(recv)); // Stop channel.
        return;
    }

    try
    {
        boost::asio::post(boost::asio::system_executor(), [&] { std::execution::set_value(std::move(recv)); }); // Value channel.
    }
    catch (...)
    {
        std::execution::set_error(std::move(recv), std::current_exception()); // Error channel.
    }
}

template < class channel >
constexpr system_scheduler system_scheduler::sender::env::query ( std::execution::get_completion_scheduler_t<channel> ) noexcept
{
    return system_scheduler();
}