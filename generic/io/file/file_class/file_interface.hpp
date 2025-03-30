#pragma once

template < class type >
class file_interface
{
    public: // Core
        file_interface ( )                                    = default;
        file_interface ( const file_interface&  )             = delete;
        file_interface (       file_interface&& );
        file_interface& operator = ( const file_interface&  ) = delete;
        file_interface& operator = (       file_interface&& );

    public: // Constructor
        file_interface ( const char* );
        file_interface ( const path& );

    protected: // Interface (override)
        type& open    ( const path& );
        type& save    ( );

    public: // Interface (non-override)
        type& save_as ( const path& );
        type& close   ( );
        bool  is_open ( ) const;

    public: // Conversion
        operator path ( ) const;

    public: // Modes
        using read_only  = file_stream::read_only;
        using write_only = file_stream::write_only;
        using erase      = file_stream::erase;
        using append     = file_stream::append;

    private: // Data
        path file_path = "";
        bool file_open = false;
};

#include "file_interface.ipp"