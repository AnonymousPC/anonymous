#pragma once

/// Member

template < class... types >
sender<types...>::sender ( auto&& init_start_func, auto&&... init_start_args )
    extends starter ( new async_starter(std::forward<decltype(init_start_func)>(init_start_func), std::tuple(std::forward<decltype(init_start_args)>(init_start_args)...)) )
{

}

template < class... types >
sender<types...>::sender ( const sender& init )
    extends starter ( &init.starter->copy() )
{
    
}

template < class... types >
std::execution::operation_state auto sender<types...>::connect ( std::execution::receiver auto&& recv )
{
    return operation_state<decay<decltype(recv)>>(std::move(self), std::forward<decltype(recv)>(recv));
}

template < class... types >
class sender<types...>::async_starter_base
{
    public: // Core
        virtual ~async_starter_base ( )             = default;
        virtual  async_starter_base& copy ( ) const = abstract;

    public: // Interface
        virtual void start ( function<void(types...)> ) = abstract; // function<void(types...)> refers to boost::asio::completion_token.
};

template < class... types >
template < class func_type, class... arg_types >
class sender<types...>::async_starter
    extends public async_starter_base
{
    public: // Data
        func_type                func;
        std::tuple<arg_types...> args;

    public: // Core
        async_starter ( func_type, std::tuple<arg_types...> );
        async_starter_base& copy ( ) const override;

    public: // Interface
        void start ( function<void(types...)> ) override; // function<void(types...)> refers to boost::asio::completion_token.
};

template < class... types >
template < class func_type, class... arg_types >
sender<types...>::async_starter<func_type,arg_types...>::async_starter ( func_type init_func, std::tuple<arg_types...> init_args )
    extends func ( std::move(init_func) ),
            args ( std::move(init_args) )
{

}

template < class... types >
template < class func_type, class... arg_types >
sender<types...>::async_starter_base& sender<types...>::async_starter<func_type,arg_types...>::copy ( ) const
{
    return *new async_starter(func, args); // Don't worry, we will then put it into a unique_ptr in sender::sender(const sender&).
}

template < class... types >
template < class func_type, class... arg_types >
void sender<types...>::async_starter<func_type,arg_types...>::start ( function<void(types...)> completion_token )
{
    std::apply(func, std::tuple_cat(std::make_tuple(std::move(completion_token)), std::move(args)));
}


template < class... types >
template < class receiver >
class sender<types...>::operation_state
{
    public: // Data
        sender   snd;
        receiver recv;

    public: // Core
        operation_state ( sender, receiver );

    public: // Interface
        void start ( ) noexcept;
};

/// Implemention

template < class... types >
template < class receiver >
sender<types...>::operation_state<receiver>::operation_state ( sender init_snd, receiver init_recv )
    extends snd  ( std::move(init_snd ) ),
            recv ( std::move(init_recv) )
{

}

template < class... types >
template < class receiver >
void sender<types...>::operation_state<receiver>::start ( ) noexcept
{
    if ( std::execution::get_stop_token(std::execution::get_env(recv)).stop_requested() )
    {
        std::execution::set_stopped(std::move(recv)); // Stop channel.
        return;
    }

    try
    {
        snd.starter->start([&] (types... args) { std::execution::set_value(std::move(recv), std::forward<decltype(args)>(args)...); }); // Value channel.
    }
    catch ( ... )
    {
        std::execution::set_error(std::move(recv), std::current_exception()); // Error channel.
    }
}


