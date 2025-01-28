#pragma once

namespace detail
{
    class opencl_queue_context
        extends public execpools::thread_pool_base<opencl_queue_context>
    {
        public: // Constructor
            opencl_queue_context ( ) = default;
            explicit opencl_queue_context ( int );

        public: // Member
            constexpr static std::execution::forward_progress_guarantee forward_progress_guarantee ( ) { return std::execution::forward_progress_guarantee::weakly_parallel; };
            std::uint32_t available_parallelism ( ) const;
            void enqueue ( execpools::task_base* task, std::uint32_t tid = 0 ) noexcept;

        public: // Command queue
           static boost::compute::command_queue& get_command_queue ( );
           /* Imagine cpu-thread 1 is solving a quite complex math problem on opencl,
            * while cpu-thread 2 want to copy a single device value.
            * There is no need for cpu-thread 2 to command_queue().flush(), which waits until
            * cpu-thread 1 completed its task.
            * Meanwhile, everything happens sequencely in same cpu-thread, which does not
            * requires re-construct a new command_queue. 
            */

        public: // Friend
            friend execpools::thread_pool_base<opencl_queue_context>;
            template < class pool_type, class receiver > friend struct execpools::operation;  

        private: // Member
            static void throw_opencl_error ( const boost::compute::opencl_error& );
            static void throw_capatability_error ( );
            static BOOST_COMPUTE_CL_CALLBACK void enqueue_callback ( void* args );

        private: // Typedef
            struct task_type
            {
                execpools::task_base* task;
                std::uint32_t         tid;
            };   
    };
} // namespace detail

#if dll
    #include "opencl_queue_context.cpp"
#endif