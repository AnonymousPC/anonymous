class opencl_queue_context
    extends public execpools::thread_pool_base<opencl_queue_context>
{
    private: // Core
        opencl_queue_context ( ) = default;
        friend class opencl;

    public: // Attribute
        constexpr static auto forward_progress_guarantee ( );
        constexpr static auto available_parallelism      ( );

    public: // Kernel
        static boost::compute::context&       context       ( );
        static boost::compute::device&        device        ( );
        static boost::compute::command_queue& command_queue ( );
        static boost::compute::program        build_program ( std::string, const auto&... );
        static boost::compute::kernel         build_kernel  ( const boost::compute::program&, std::string );

    private: // Data
        inline static              boost::compute::context       ctx = boost::compute::system::default_context();
        inline static              boost::compute::device        dvc = boost::compute::system::default_device();
        inline static thread_local boost::compute::command_queue que = boost::compute::command_queue(ctx, dvc);

    private: // Task
        static void enqueue ( execpools::task_base*, std::uint32_t tid = 0 );
        static void enqueue_callback ( void* );
        struct task_type { execpools::task_base* task; std::uint32_t tid; };
        friend execpools::thread_pool_base<opencl_queue_context>;
        template < class pool_type, class receiver > friend struct execpools::operation;  
};

#include "opencl_queue_context.cpp"