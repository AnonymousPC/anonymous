#pragma once

class opencl_queue_context
    extends public execpools::thread_pool_base<opencl_queue_context>
{
    public: // Constructor
        opencl_queue_context ( ) = default;

    public: // Attribute
        constexpr auto std::execution::forward_progress_guarantee forward_progress_guarantee ( );
        constexpr auto available_parallelism ( ) const;

    public: // Kernel
        static const boost::compute::device&        device        ( );
        static const boost::compute::context&       context       ( );
        static       boost::compute::command_queue& command_queue ( );
        static       boost::compute::program        build_program ( std::string, const auto&... );
        static       boost::compute::kernel         build_kernel  ( const boost::compute::program&, std::string );
        /* Imagine cpu-thread 1 is solving a quite complex math problem on opencl,
         * while cpu-thread 2 want to copy a single device value.
         * There is no need for cpu-thread 2 to command_queue().flush(), which waits until
         * cpu-thread 1 completed its task.
         * Meanwhile, everything happens sequencely in same cpu-thread, which does not
         * requires re-construct a new command_queue. 
         */

    private: // Task
        void enqueue ( execpools::task_base*, std::uint32_t tid = 0 );
        static BOOST_COMPUTE_CL_CALLBACK void enqueue_callback ( void* args );
        struct task_type
        {
            execpools::task_base* task;
            std::uint32_t         tid;
        };  

    private: // Data
        inline static std::optional<boost::compute::device>        default_device        = [] { try { return boost::compute::system::default_device ();          } catch ( const boost::compute::no_device_found& ) { return std::nullopt; } } (); 
        inline static std::optional<boost::compute::context>       default_context       = [] { try { return boost::compute::system::default_context();          } catch ( const boost::compute::no_device_found& ) { return std::nullopt; } } (); 
        inline static std::optional<boost::compute::command_queue> default_command_queue = [] { try { return boost::compute::command_queue(context(), device()); } catch ( const boost::compute::no_device_found& ) { return std::nullopt; } } (); 

    private: // Friend
        friend execpools::thread_pool_base<opencl_queue_context>;
        template < class pool_type, class receiver > friend struct execpools::operation;  
};

#include "opencl_queue_context.ipp"
#ifdef dll
    #include "opencl_queue_context.cpp"
#endif