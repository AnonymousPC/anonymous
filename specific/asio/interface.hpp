#pragma once

namespace ap::asio
{
    /// Class
    template < class context_type > class asio_context;
    template < class context_type > class asio_scheduler;
                                
    class use_sender_t;

    /// Include
    #include "context/asio_context.hpp"
    #include "context/asio_scheduler.hpp"
    #include "sender/sender.hpp"
    #include "token/use_sender.hpp"
    #include "result/result.hpp"
    
    /// Global
    constexpr use_sender_t use_sender = use_sender_t();
}
