/// Global

std::execution::static_thread_pool  cpu_context = std::execution::static_thread_pool(int(std::thread::hardware_concurrency() * 0.8));
std::execution::static_thread_pool& gpu_context = cpu_context;




/// Initialize

class basic_initializer_t
{
    private: // Instance
        static basic_initializer_t basic_initializer;

    private: // Constructor
        basic_initializer_t ( );

    private: // Functions
        static void abort_signal                    ( int );
        static void floating_point_exception_signal ( int );
        static void illegal_instruction_signal      ( int );
        static void interrupt_signal                ( int );
        static void segmentation_violation_signal   ( int );
        static void terminate_signal                ( int );
};

#if dll
    basic_initializer_t::basic_initializer_t ( )
    {
        // Standard.print
        std::cout << std::boolalpha;

        // Standard.signal
        std::signal(SIGABRT, abort_signal);
        std::signal(SIGFPE,  floating_point_exception_signal);
        std::signal(SIGILL,  illegal_instruction_signal);
        std::signal(SIGINT,  interrupt_signal);
        std::signal(SIGSEGV, segmentation_violation_signal);
        std::signal(SIGTERM, terminate_signal);
    }

    void basic_initializer_t::abort_signal ( int )
    {
        std::cerr << "terminate called after throwing an instance of '" << abi::demangle(typeid(ap::abort_signal).name()) << "'\n"
                << "  what(): " << ap::abort_signal().what();
        std::exit(-1);
    }

    void basic_initializer_t::floating_point_exception_signal ( int )
    {
        throw ap::floating_point_exception_signal();
    }

    void basic_initializer_t::illegal_instruction_signal ( int )
    {
        throw ap::illegal_instruction_signal();      
    }

    void basic_initializer_t::interrupt_signal ( int )
    {
        throw ap::interrupt_signal();                
    }

    void basic_initializer_t::segmentation_violation_signal ( int )
    {
        throw ap::segmentation_violation_signal();   
    }

    void basic_initializer_t::terminate_signal ( int )
    {
        throw ap::terminate_signal();
    }
#endif

basic_initializer_t basic_initializer_t::basic_initializer;