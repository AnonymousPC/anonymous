#pragma once

class file_jpg
    extends public file_interface<file_jpg>,   
            public matrix<color>
{
    public: // Core
        file_jpg ( ) = default;
        file_jpg ( path );

    public: // Interface (override)
        file_jpg& open  ( path );
        file_jpg& save  ( );
        file_jpg& close ( );

    public: // Interface
              int& depth ( );
        const int& depth ( ) const;

    private: // Data
        int image_depth = 24;
};

#include "file_jpg.ipp"