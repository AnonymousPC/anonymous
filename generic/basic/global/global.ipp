#pragma once

inline detail::basic_initializer_t::basic_initializer_t ( )
{
    // Stdio
    std::cout << std::boolalpha;

    // Stdio.windows
    #ifdef _WIN32
        SetConsoleCP      (CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    #endif

    // Signal.standard
    std::signal(SIGFPE,  floating_point_exception_signal_handler);
    std::signal(SIGILL,  illegal_instruction_signal_handler);
    std::signal(SIGINT,  interrupt_signal_handler);
    std::signal(SIGSEGV, segmentation_violation_signal_handler);
    std::signal(SIGTERM, terminate_signal_handler);

    // Signal.posix
    #ifdef SIGALRM
    std::signal(SIGALRM,   [] (int s) { signal_handler(s, "SIGALRM (alarm clock)"); });
    #endif
    #ifdef SIGBUS
    std::signal(SIGBUS,    [] (int s) { signal_handler(s, "SIGBUS (access to an undefined portion of a memory object)"); });
    #endif
    #ifdef SIGHUP
    std::signal(SIGHUP,    [] (int s) { signal_handler(s, "SIGHUP (hangup)"); });
    #endif
    #ifdef SIGPIPE
    std::signal(SIGPIPE,   [] (int s) { signal_handler(s, "SIGPIPE (write on a pipe with no one to read it)"); });
    #endif
    #ifdef SIGPOLL
    std::signal(SIGPOLL,   [] (int s) { signal_handler(s, "SIGPOLL (pollable event)"); });
    #endif
    #ifdef SIGPROF
    std::signal(SIGPROF,   [] (int s) { signal_handler(s, "SIGPROF (profiling timer expired)"); });
    #endif
    #ifdef SIGQUIT
    std::signal(SIGQUIT,   [] (int s) { signal_handler(s, "SIGQUIT (terminal quit signal)"); });
    #endif
    #ifdef SIGSYS
    std::signal(SIGSYS,    [] (int s) { signal_handler(s, "SIGSYS (bad system call)"); });
    #endif
    #ifdef SIGTRAP
    std::signal(SIGTRAP,   [] (int s) { signal_handler(s, "SIGTRAP (trace/breakpoint trap)"); });
    #endif
    #ifdef SIGTSTP
    std::signal(SIGTSTP,   [] (int s) { signal_handler(s, "SIGTSTP (terminal stop signal)"); });
    #endif
    #ifdef SIGTTIN
    std::signal(SIGTTIN,   [] (int s) { signal_handler(s, "SIGTTIN (background process attempting read)"); });
    #endif
    #ifdef SIGTTOU
    std::signal(SIGTTOU,   [] (int s) { signal_handler(s, "SIGTTOU (background process attempting write)"); });
    #endif
    #ifdef SIGUSR1
    std::signal(SIGUSR1,   [] (int s) { signal_handler(s, "SIGUSR1 (user-defined signal 1)"); });
    #endif
    #ifdef SIGUSR2
    std::signal(SIGUSR2,   [] (int s) { signal_handler(s, "SIGUSR2 (user-defined signal 2)"); });
    #endif
    #ifdef SIGVTALRM
    std::signal(SIGVTALRM, [] (int s) { signal_handler(s, "SIGVTALRM (virtual timer expired)"); });
    #endif
    #ifdef SIGXCPU
    std::signal(SIGXCPU,   [] (int s) { signal_handler(s, "SIGXCPU (cpu time limit exceeded)"); });
    #endif
    #ifdef SIGXFSZ
    std::signal(SIGXCPU,   [] (int s) { signal_handler(s, "SIGXFSZ (file size limit exceeded)"); });
    #endif

    // Stack-overflow.windows
    #ifdef _WIN32
    SetUnhandledExceptionFilter([] WINAPI (PEXCEPTION_POINTERS ptrs) -> LONG
        {
            if ( ptrs->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW )
                segmentation_violation_signal_handler(SIGSEGV);
            return EXCEPTION_CONTINUE_SEARCH;
        });
    #endif

    // Stack-overflow.posix
    #if defined(SIGSTKSZ) and defined(SA_ONSTACK)
    stack_t ss;
    ss.ss_sp    = malloc(SIGSTKSZ);
    ss.ss_size  = SIGSTKSZ;
    ss.ss_flags = 0;
    sigaltstack(&ss, nullptr);
    struct sigaction sa_segv;
    sa_segv.sa_handler = segmentation_violation_signal_handler;
    sa_segv.sa_flags   = SA_ONSTACK;
    sigemptyset(&sa_segv.sa_mask);
    sigaction  (SIGSEGV, &sa_segv, nullptr);
    #endif
}

inline void detail::basic_initializer_t::signal_handler ( int, const char* msg )
{
    throw ap::signal("{}", msg);
}

inline void detail::basic_initializer_t::abort_signal_handler ( int )
{
    throw ap::abort_signal("SIGABRT (process abort signal)");
}

inline void detail::basic_initializer_t::floating_point_exception_signal_handler ( int )
{
    throw ap::floating_point_exception_signal("SIGFPE (erroneous arithmetic operation)");
}

inline void detail::basic_initializer_t::illegal_instruction_signal_handler ( int )
{
    throw ap::illegal_instruction_signal("SIGILL (illegal instruction)");      
}

inline void detail::basic_initializer_t::interrupt_signal_handler ( int )
{
    throw ap::interrupt_signal("SIGINT (terminal interrupt signal)");                
}

inline void detail::basic_initializer_t::segmentation_violation_signal_handler ( int )
{
    throw ap::segmentation_violation_signal("SIGSEGV (invalid memory reference)");   
}

inline void detail::basic_initializer_t::terminate_signal_handler ( int )
{
    throw ap::terminate_signal("SIGTERM (termination signal)");
}

