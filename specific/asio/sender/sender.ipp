#pragma once

template < class... types >
sender<types...>::sender ( auto&& init_starter, types... init_args )
    extends starter ( new async_initiation(std::forward<decltype(init_starter)>(init_starter)) ),
            args    ( std::forward<decltype(init_args)>(init_args)... )
{
    
}

template < class... types >
auto sender<types...>::connect ( std::execution::receiver auto&& recv )
{
    return operation_state<decay<decltype(recv)>>(std::move(self), std::forward<decltype(recv)>(recv));
}

template < class... types >
template < std::execution::receiver receiver >
class sender<types...>::operation_state
    extends public operation_state_base
{
    public: // Core
        operation_state ( sender, receiver );

    public: // Interface
        void start ( );

    protected: // Detail
        void set_value ( types... ) override;

    private: // Data
        sender   snd;
        receiver recv;
};

template < class... types >
template < std::execution::receiver receiver >
sender<types...>::operation_state<receiver>::operation_state ( sender init_snd, receiver init_recv )
    extends snd  ( std::move(init_snd)  ),
            recv ( std::move(init_recv) )
{

}

template < class... types >
template < std::execution::receiver receiver >
void sender<types...>::operation_state<receiver>::start ( )
{
    if ( std::execution::get_stop_token(std::execution::get_env(recv)).stop_requested() )
    {
        std::execution::set_stopped(std::move(recv)); // Stop channel.
        return;
    }

    try
    {
        starter->operator()(snd.args, completion_token_base(self)); // Value channel, see completion_token::operator().
    }
    catch ( ... )
    {
        std::execution::set_error(std::move(recv), std::current_exception()); // Error channel.
    }
}

template < class... types >
class sender<types...>::operation_state_base
{
    public: // Interface   
        virtual void set_value ( types... ) = abstract;
};

template < class... types >
class sender<types...>::async_initiation_base
{
    public: // Core
        virtual ~async_initiation_base ( );

    public: // Interface
        virtual void operator() ( std::tuple<types...>, completion_token_base&& ) = abstract;
};

template < class... types >
sender<types...>::async_initiation_base::~async_initiation_base ( )
{

}

template < class... types >
class sender<types...>::completion_token_base
{
    public: // Data
        operation_state_base& op;
        
    public: // Interface
        void operator() ( types... );
};

template < class... types >
void sender<types...>::completion_token_base::operator() ( types... args )
{
    op->set_value(std::forward<decltype(args)>(args)...);
}


template < class... types >
template < class type >
class sender<types...>::async_initiation
    extends public async_initiation_base
{
    public: // Data
        type initiation;

    public: // Interface
        void operator() ( std::tuple<types...>, completion_token_base ) override;
};

template < class... types >
template < class type >
void sender<types...>::async_initiation<type>::operator() ( std::tuple<types...> args, completion_token_base token )
{
    std::apply(initiation, std::tuple_cat(std::make_tuple(std::move(token)), std::move(args)));
}


