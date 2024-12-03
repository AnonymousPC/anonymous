#pragma once

template < class pipe_type >
class pipe_interface
{
    public: // Core
        pipe_interface ( ) = default;
        pipe_interface ( const pipe_interface&  )             = delete;
        pipe_interface (       pipe_interface&& );
        pipe_interface& operator = ( const pipe_interface&  ) = delete;
        pipe_interface& operator = (       pipe_interface&& );

    protected: // Interface (non-override)
        pipe_type& open ( const path& );

    public: // Interface (non-override)
        pipe_type& close ( );

    public: // Conversion
        operator path ( ) const;

    public: // Modes
        using environment     = pipe_stream::environment;
        using param           = pipe_stream::param;
        using start_directory = pipe_stream::start_directory;

    private: // Data
        path pipe_path = "";
        bool pipe_open = false;
};

#include "pipe_interface.ipp"