#pragma once

template < class... types >
class sender
{
    public: // Traits
        using sender_concept = std::execution::sender_t;
        using completion_signatures = std::execution::completion_signatures<std::execution::set_value_t(types...),std::execution::set_error_t(std::exception_ptr),std::execution::set_stopped_t()>;
        
    public: // Typedef
        template < std::execution::receiver receiver >
        class operation_state;

    public: // Core
        sender ( auto&&, types... );

    public: // Interface
        auto connect ( std::execution::receiver auto&& );

    private: // Typedef
        class async_initiation_base; // Required by boost::asio::async_result::initate(**initiation**, use_sender, args...) { return sender<types...>::sender(**initiation**, args...); }. Asked to be non-template by sender<types...>::sender(**initiation**, args...), which does not contains the template of initiation_type.
        class completion_token_base; // Required by std::execution::set_value(args...). Asked to be non-template by starter->operator()(args..., completion_token_base), which is virtual and non-template.
        class operation_state_base;  // Required by completion_token_base::completion_token_base(operation_state). Asked to be non-template by completion_token_base::completion_token_base(operation_state), which is non-template.

    private: // Typedef
        template < class type > class async_initiation;

    private: // Data
        std::unique_ptr<async_initiation_base> starter;
        std::tuple<types...>                   args;
};

#include "sender.ipp"