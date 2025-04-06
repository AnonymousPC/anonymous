#pragma once

class file_tga
    extends public file_interface<file_tga>,
            public matrix<color>           
{
    public: // Core
        file_tga ( ) = default;
        file_tga ( path );

    public: // Interface (override)
        file_tga& open  ( path );
        file_tga& save  ( );
        file_tga& close ( );

    public: // Interface
              int& depth ( );
        const int& depth ( ) const;

    private: // Data
        int image_depth = 32;
};

#include "file_tga.ipp"