#pragma once

class file_png
    extends public file_interface<file_png>,
            public matrix<color>
{
    public: // Core
        file_png ( ) = default;
        file_png ( path );

    public: // Interface (override)
        file_png& open  ( path );
        file_png& save  ( );
        file_png& close ( );

    public: // Interface
              int& depth ( );
        const int& depth ( ) const;

    private: // Data
        int image_depth = 32;
};

#ifdef dll
    #include "file_png.cpp"
#endif