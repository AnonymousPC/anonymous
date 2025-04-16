#pragma once

/* As system_scheduler is not a class-template, the declaration and implemention on different parts
 * should be written in a specific order, : a "cannot use incomplete type..." compile-error
 * may occur.
 * 
 * Thus, we provide a guide to declaration/implemetion.
 */


/// Declartion (system_scheduler.sender)

class system_scheduler::sender
{
    public: // Traits
        using sender_concept        = std::execution::sender_t;
        using completion_signatures = std::execution::completion_signatures<std::execution::set_value_t()>;

    public: // Typedef
        template < class receiver_type > class operation_state;
        
    public: // Interface
        constexpr static auto connect ( std::execution::receiver auto&& );

    public: // Query
                                        constexpr static auto query ( std::execution::get_env_t )                                noexcept; 
                                        constexpr static auto query ( std::execution::get_scheduler_t )                          noexcept;
        template < class channel_type > constexpr static auto query ( std::execution::get_completion_scheduler_t<channel_type> ) noexcept;

    private: // Data
        [[maybe_unused]] int i_am_not_constexpr = 42;
};

template < class receiver_type >
class system_scheduler::sender::operation_state
{
    public: // Data
        receiver_type recv;

    public: // Interface
        constexpr void start ( ) noexcept;
};




/// Declaration (system_scheduler.bulk_sender)

template < class sender_type, class shape_type, class function_type >
class system_scheduler::bulk_sender
{
    public: // Traits
        using sender_concept        = std::execution::sender_t;
        using completion_signatures = sender_type::completion_signatures;

    public: // Data
        sender_type   snd;
        shape_type    shp;
        function_type func;

    public: // Typedef
        template < class receiver_type > class bulk_receiver;
        template < class receiver_type > class operation_state;

    public: // Interface
        constexpr auto connect ( std::execution::receiver auto&& );

    public: // Query
                                        constexpr        auto query ( std::execution::get_env_t )                                const noexcept; 
                                        constexpr static auto query ( std::execution::get_scheduler_t )                                noexcept;
        template < class channel_type > constexpr static auto query ( std::execution::get_completion_scheduler_t<channel_type> )       noexcept;
};

template < class sender_type, class shape_type, class function_type >
template < class receiver_type >
class system_scheduler::bulk_sender<sender_type,shape_type,function_type>::bulk_receiver
{
    public: // Traits
        using receiver_concept = std::execution::receiver_t;
    
    public: // Data
        receiver_type           recv;
        shape_type              shp;
        function_type           func;
        std::atomic<shape_type> cnt  = 0;

    public: // Core
        constexpr bulk_receiver ( receiver_type, shape_type, function_type );
        constexpr bulk_receiver ( const bulk_receiver& );                    // std::atomic<shape_type> is not copyable.
        
    public: // Interface
        constexpr void set_value   ( auto&&... ) noexcept;
        constexpr void set_error   ( auto&&... ) noexcept;
        constexpr void set_stopped ( auto&&... ) noexcept;

    public: // Query    
                                        constexpr        auto query ( std::execution::get_env_t )                                const noexcept; 
                                        constexpr static auto query ( std::execution::get_scheduler_t )                                noexcept;
        template < class channel_type > constexpr static auto query ( std::execution::get_completion_scheduler_t<channel_type> )       noexcept;
};

template < class sender_type, class shape_type, class function_type >
template < class receiver_type >
class system_scheduler::bulk_sender<sender_type,shape_type,function_type>::operation_state
{
    public: // Data
        std::execution::connect_result_t<sender_type,bulk_receiver<receiver_type>> op;

    public: // Interface
        constexpr void start ( ) noexcept;
};











/// Implemention (system_scheduler.sender)

constexpr auto system_scheduler::sender::connect ( std::execution::receiver auto&& recv )
{
    return operation_state(std::forward<decltype(recv)>(recv));
}

constexpr auto system_scheduler::sender::query ( std::execution::get_env_t ) noexcept
{
    return sender();
}

constexpr auto system_scheduler::sender::query ( std::execution::get_scheduler_t ) noexcept
{
    return system_scheduler();
}

template < class channel_type >
constexpr auto system_scheduler::sender::query ( std::execution::get_completion_scheduler_t<channel_type> ) noexcept
{
    return system_scheduler();
}

template < class receiver_type >
constexpr void system_scheduler::sender::operation_state<receiver_type>::start ( ) noexcept
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




/// Implemention (system_scheduler.bulk_sender)

template < class sender_type, class shape_type, class function_type >
constexpr auto system_scheduler::bulk_sender<sender_type,shape_type,function_type>::connect ( std::execution::receiver auto&& recv )
{
    return operation_state<decay<decltype(recv)>>(std::execution::connect(std::move(snd), bulk_receiver(std::forward<decltype(recv)>(recv), std::move(shp), std::move(func))));
}

template < class sender_type, class shape_type, class function_type >
constexpr auto system_scheduler::bulk_sender<sender_type,shape_type,function_type>::query ( std::execution::get_env_t ) const noexcept
{
    return self;
}

template < class sender_type, class shape_type, class function_type >
constexpr auto system_scheduler::bulk_sender<sender_type,shape_type,function_type>::query ( std::execution::get_scheduler_t ) noexcept
{
    return system_scheduler();
}

template < class sender_type, class shape_type, class function_type >
template < class channel_type >
constexpr auto system_scheduler::bulk_sender<sender_type,shape_type,function_type>::query ( std::execution::get_completion_scheduler_t<channel_type> ) noexcept
{
    return system_scheduler();
}

template < class sender_type, class shape_type, class function_type >
template < class receiver_type >
constexpr system_scheduler::bulk_sender<sender_type,shape_type,function_type>::bulk_receiver<receiver_type>::bulk_receiver ( receiver_type init_recv, shape_type init_shp, function_type init_func )
    extends recv ( std::move(init_recv) ),
            shp  ( std::move(init_shp ) ),
            func ( std::move(init_func) )
{
}

template < class sender_type, class shape_type, class function_type >
template < class receiver_type >
constexpr system_scheduler::bulk_sender<sender_type,shape_type,function_type>::bulk_receiver<receiver_type>::bulk_receiver ( const bulk_receiver& init )
    extends recv ( init.recv ),
            shp  ( init.shp ),
            func ( init.func ),
            cnt  ( init.cnt.load() )
{
}

template < class sender_type, class shape_type, class function_type >
template < class receiver_type >
constexpr void system_scheduler::bulk_sender<sender_type,shape_type,function_type>::bulk_receiver<receiver_type>::set_value ( auto&&... args ) noexcept
{
    try
    {
        auto args_tuple = std::tuple(std::forward<decltype(args)>(args)...);

        for ( int i in range(0, shp-1) )
            boost::asio::post(boost::asio::system_executor(), [&, i]
                {
                    std::apply([&] (auto&&... args) { func(i, args...); }, args_tuple);
                    if ( (++cnt) == shp )
                        std::apply([&] (auto&&... args) { std::execution::set_value(std::move(recv), std::forward<decltype(args)>(args)...); }, args_tuple);
                });
    }
    catch (...)
    {
        std::execution::set_error(std::move(recv), std::current_exception());
    }
}

template < class sender_type, class shape_type, class function_type >
template < class receiver_type >
constexpr void system_scheduler::bulk_sender<sender_type,shape_type,function_type>::bulk_receiver<receiver_type>::set_error ( auto&&... args ) noexcept
{
    std::execution::set_error(std::move(recv), std::forward<decltype(args)>(args)...);
}

template < class sender_type, class shape_type, class function_type >
template < class receiver_type >
constexpr void system_scheduler::bulk_sender<sender_type,shape_type,function_type>::bulk_receiver<receiver_type>::set_stopped ( auto&&... args ) noexcept
{
    std::execution::set_stopped(std::move(recv), std::forward<decltype(args)>(args)...);
}

template < class sender_type, class shape_type, class function_type >
template < class receiver_type >
constexpr auto system_scheduler::bulk_sender<sender_type,shape_type,function_type>::bulk_receiver<receiver_type>::query ( std::execution::get_env_t ) const noexcept
{
    return self;
}

template < class sender_type, class shape_type, class function_type >
template < class receiver_type >
constexpr auto system_scheduler::bulk_sender<sender_type,shape_type,function_type>::bulk_receiver<receiver_type>::query ( std::execution::get_scheduler_t ) noexcept
{
    return system_scheduler();
}

template < class sender_type, class shape_type, class function_type >
template < class receiver_type >
template < class channel_type >
constexpr auto system_scheduler::bulk_sender<sender_type,shape_type,function_type>::bulk_receiver<receiver_type>::query ( std::execution::get_completion_scheduler_t<channel_type> ) noexcept
{
    return system_scheduler();
}

template < class sender_type, class shape_type, class function_type >
template < class receiver_type >
constexpr void system_scheduler::bulk_sender<sender_type,shape_type,function_type>::operation_state<receiver_type>::start ( ) noexcept
{
    std::execution::start(op);
}



/// Implemention (system_scheduler), should be the last one to instantiate.

constexpr std::execution::sender auto system_scheduler::schedule ( ) noexcept
{
    return sender();
}

constexpr std::execution::sender auto system_scheduler::bulk ( std::execution::sender auto&& snd, int_type auto&& shp, auto&& func ) noexcept
{
    return bulk_sender(std::forward<decltype(snd)>(snd), std::forward<decltype(shp)>(shp), std::forward<decltype(func)>(func));
}

constexpr auto system_scheduler::query ( std::execution::get_env_t ) noexcept
{
    return system_scheduler();
}

constexpr auto system_scheduler::query ( std::execution::get_forward_progress_guarantee_t ) noexcept
{
    return std::execution::forward_progress_guarantee::concurrent; // System is always your strong backing :)
}