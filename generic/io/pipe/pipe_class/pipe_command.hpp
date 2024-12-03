#pragma once

class pipe_command
    extends public pipe_interface<pipe_command>,
            public vector<string>
{
    public: // Core
        using pipe_interface<pipe_command>::pipe_interface;
        pipe_command ( const char*,   pipe_mode auto... );
        pipe_command ( const string&, pipe_mode auto... );

    public: // Interface (special)
        pipe_command& execute ( const string&, pipe_mode auto... );
};

#include "pipe_command.ipp"