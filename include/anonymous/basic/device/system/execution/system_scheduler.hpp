#pragma once

class system_scheduler
{
    private: // Typedef
                                                                              class sender;
        template < class sender_type, class shape_type, class function_type > class bulk_sender;

    public: // Interface
        constexpr static std::execution::sender auto schedule ( )                                                        noexcept;  
        constexpr static std::execution::sender auto bulk     ( std::execution::sender auto&&, int_type auto&&, auto&& ) noexcept;

    public: // Query
        constexpr static auto query ( std::execution::get_env_t )                        noexcept;
        constexpr static auto query ( std::execution::get_forward_progress_guarantee_t ) noexcept;

    public: // Operator
        friend constexpr bool operator == ( const system_scheduler&, const system_scheduler& ) = default;

    private: // Data
        [[maybe_unused]] int i_am_not_constexpr = 42;
};

#include <execpools/thread_pool_base.hpp>

#include "system_scheduler.cpp"

