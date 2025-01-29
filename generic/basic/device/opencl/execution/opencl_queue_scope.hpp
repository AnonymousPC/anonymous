#pragma once

namespace detail
{
    struct opencl_queue_scope
    {
        ~opencl_queue_scope ( );
        static boost::compute::command_queue& command_queue ( );
    };
} // namespace detail

// .cpp is explicitly included in "opencl.hpp"
