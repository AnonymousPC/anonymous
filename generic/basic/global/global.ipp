#pragma once

namespace detail
{
    struct basic_initializer_t  
    {
        basic_initializer_t ( );

        static void signal_handler                          ( int, const char* );
        static void abort_signal_handler                    ( int );
        static void floating_point_exception_signal_handler ( int );
        static void illegal_instruction_signal_handler      ( int );
        static void interrupt_signal_handler                ( int );
        static void segmentation_violation_signal_handler   ( int );
        static void terminate_signal_handler                ( int );
    };

    extern basic_initializer_t basic_initializer;

    struct dll_loader_t
    {
        dll_loader_t ( );
    };
    
    inline dll_loader_t dll_loader = dll_loader_t();
}