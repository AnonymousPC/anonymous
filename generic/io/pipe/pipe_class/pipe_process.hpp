#pragma once

class pipe_process
    extends public pipe_interface<pipe_process>,
            public vector<string>
{
    public: // Core
        using pipe_interface<pipe_process>::pipe_interface;
        pipe_process ( const char*, pipe_mode auto... );
        pipe_process ( const path&, pipe_mode auto... );

    public: // Interface (override)
        pipe_process& open ( const path&, pipe_mode auto... );
};

#include "pipe_process.ipp"