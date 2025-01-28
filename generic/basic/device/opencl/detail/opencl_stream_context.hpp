#pragma once

namespace detail
{
    class opencl_stream_context
        extends public execpools::thread_pool_base<opencl_stream_context>
    {
        public: // Constructor
            opencl_stream_context ( ) = default;
            explicit opencl_stream_context ( int );

        public: // Member
            constexpr static std::execution::forward_progress_guarantee forward_progress_guarantee ( ) { return std::execution::forward_progress_guarantee::weakly_parallel; };
            std::uint32_t available_parallelism ( ) const;
            void enqueue ( execpools::task_base* task, std::uint32_t tid = 0 ) noexcept;

        public: // Friend
            friend execpools::thread_pool_base<opencl_stream_context>;
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
}

#if dll
    #include "opencl_stream_context.cpp"
#endif