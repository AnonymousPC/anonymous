#pragma once

#include "execution/system_scheduler.hpp"
#include "execution/system_context.hpp"

class system
{
    public: // Execution
        using execution_context_type = system_context;
        inline static execution_context_type execution_context = execution_context_type();

    public: // Random
        using random_context_type = std::random_device;
        inline static thread_local random_context_type random_context = random_context_type();
}; 