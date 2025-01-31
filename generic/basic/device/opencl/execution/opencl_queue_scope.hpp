#pragma once

namespace detail
{
    struct opencl_queue_scope
    {
        ~opencl_queue_scope ( );
        static boost::compute::command_queue& command_queue ( );
    };
} // namespace detail

#if dll
    #include "opencl_queue_scope.cpp"
#endif