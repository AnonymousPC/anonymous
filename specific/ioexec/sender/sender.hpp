#pragma once

template < class... types >
class sender
{
    public: // Traits
        using sender_concept = std::execution::sender_t;
        using completion_signatures = std::execution::completion_signatures<std::execution::set_value_t(types...),std::execution::set_error_t(std::exception_ptr),std::execution::set_stopped_t()>;
        
    public: // Core
        sender ( auto&&, auto&&... );
        sender ( const sender&  );
        sender (       sender&& ) = default;

    public: // Interface
        std::execution::operation_state auto connect ( std::execution::receiver auto&& );

    public: // Typedef
        template < class receiver > class operation_state; // The operation_state produced by sender.connect(receiver). Due to bug in clang++, we cannot use template < std::execution::receiver recevier >

    private: // Typedef
        template < class func_type, class... arg_types > class async_starter;      // Refers to boost::asio::async_initiate.
                                                         class async_starter_base; // Type erase some additional type-info of async_starter.

    private: // Data
        std::unique_ptr<async_starter_base> starter;
};

#include "sender.ipp"