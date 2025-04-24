namespace detail
{
    struct opencl_queue_guard
    {
        ~opencl_queue_guard ( );
        static boost::compute::command_queue& command_queue ( );
    };
} // namespace detail

#include "opencl_queue_guard.cpp"