#pragma once

#include "execution/system_scheduler.hpp"
#include "execution/system_context.hpp"

class system
{
    public: // Execution
        using  execution_context_type = system_context;
        static execution_context_type execution_context;

    public: // Random
        using               random_context_type = std::random_device;
        static thread_local random_context_type random_context;
}; 

#if dll
    #include "system.cpp"
#endif