#pragma once

template < class type >
class file_interface
{
    public: // Core
        file_interface ( )                                    = default;
        file_interface ( const file_interface&  )             = delete;
        file_interface (       file_interface&& )             = default;
        file_interface& operator = ( const file_interface&  ) = delete;
        file_interface& operator = (       file_interface&& ) = default;

    protected: // Interface (override)
        type& open    ( path );
        type& save    ( );
        type& close   ( );

    public: // Interface (non-override)
        type& save_as ( path );
        bool  is_open ( )      const;
        operator path ( )      const;

    private:
        path file_path = "";
};

#include "file_interface.cpp"