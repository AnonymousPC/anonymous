#pragma once

// This file is inside struct opencl { **this position** }.

class execution_context_t
    extends public execpools::thread_pool_base<execution_context_t>
{
    public: // Constructor
                 execution_context_t ( ) = default;
        explicit execution_context_t ( int ) { };

    public: // Member
               std::uint32_t                  available_parallelism ( ) const;
        static boost::compute::command_queue& get_command_queue         ( );

    public: // Friend
                                                     friend        execpools::thread_pool_base<execution_context_t>;
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

#if dll
    #include "execution_context_t.cpp"
#endif