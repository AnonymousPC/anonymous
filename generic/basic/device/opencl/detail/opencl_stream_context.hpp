#pragma once

namespace detail
{
    class opencl_stream_context
        extends public execpools::thread_pool_base<opencl_stream_context>
    {
        public: // Constructor
            opencl_stream_context ( ) = default;

            explicit opencl_stream_context ( int )
            {
                
            }

        public: // Member
            constexpr static std::execution::forward_progress_guarantee forward_progress_guarantee ( )
            {
                return std::execution::forward_progress_guarantee::weakly_parallel;
            }
            
            std::uint32_t available_parallelism ( ) const
            {
                return boost::compute::system::default_device().compute_units();
            }

            void enqueue ( execpools::task_base* task, std::uint32_t tid = 0 ) noexcept
            {
                if ( boost::compute::system::default_device().get_info<CL_DEVICE_EXECUTION_CAPABILITIES>() & CL_EXEC_NATIVE_KERNEL )
                    try
                    {
                        // TODO: I currently have no environment to check it.
                        boost::compute::system::default_queue().enqueue_native_kernel(enqueue_callback, new task_type(task, tid), sizeof(task_type), 0, 0, 0);
                        boost::compute::system::default_queue().flush();
                    }
                    catch ( const boost::compute::opencl_error& e )
                    {
                        throw_opencl_error(e);
                    }
                else
                    throw_capatability_error();
            }

        public: // Friend
            friend execpools::thread_pool_base<opencl_stream_context>;
            template < class pool_type, class receiver > friend struct execpools::operation;  

        private: // Member
            static void throw_opencl_error ( const boost::compute::opencl_error& e )
            {
                throw device_error("failed to enqueue task").from(e);
            }

            static void throw_capatability_error ( )
            {
                throw device_error("failed to enqueue task: this opencl device does not supports executing host function (with name = {}, vendor = {}, profile = {}, version = {}, driver_version = {}, capability = {{exec_kernel = {}, exec_native_kernel = {}}})",
                                   boost::compute::system::default_device().name(),
                                   boost::compute::system::default_device().vendor(),
                                   boost::compute::system::default_device().profile(),
                                   boost::compute::system::default_device().version(),
                                   boost::compute::system::default_device().driver_version(),
                                   boost::compute::system::default_device().get_info<CL_DEVICE_EXECUTION_CAPABILITIES>() & CL_EXEC_KERNEL,
                                   boost::compute::system::default_device().get_info<CL_DEVICE_EXECUTION_CAPABILITIES>() & CL_EXEC_NATIVE_KERNEL);
            }
            static BOOST_COMPUTE_CL_CALLBACK void enqueue_callback ( void* args )
            {
                let ptr = static_cast<task_type*>(args);
                ptr->task->__execute(ptr->task, /*tid=*/ptr->tid);
            }

        private: // Typedef
            struct task_type
            {
                execpools::task_base* task;
                std::uint32_t         tid;
            };   
    };
}