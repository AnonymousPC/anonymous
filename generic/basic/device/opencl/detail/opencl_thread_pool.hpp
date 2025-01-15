#pragma once

namespace detail
{
    class opencl_thread_pool
        extends public execpools::thread_pool_base<opencl_thread_pool>
    {
        public: // Constructor
                     opencl_thread_pool ( ) = default;
            explicit opencl_thread_pool ( int ) { };

        public: // Member
                   std::uint32_t                  available_parallelism ( ) const;
            static boost::compute::command_queue& get_command_queue         ( );

        public: // Friend
                                                         friend        execpools::thread_pool_base<opencl_thread_pool>;
            template < class pool_type, class receiver > friend struct execpools::operation;  

        private: // Member
            constexpr static std::execution::forward_progress_guarantee forward_progress_guarantee ( ) { return std::execution::forward_progress_guarantee::weakly_parallel; }
            void enqueue ( execpools::task_base* task, std::uint32_t tid = 0 ) noexcept;
            static void throw_opencl_error ( const boost::compute::opencl_error& );
            static void throw_device_error ( );
            static void BOOST_COMPUTE_CL_CALLBACK enqueue_callback ( void* args );
            struct task_type
            {
                execpools::task_base* task;
                std::uint32_t         tid;
            };   
    };
}

#if dll
    #include "opencl_thread_pool.cpp"
#endif