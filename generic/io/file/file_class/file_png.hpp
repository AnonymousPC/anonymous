#pragma once

class file_png
    extends public file_interface<file_png>,
            public matrix<color>
{
    public: // Core
        using file_interface<file_png>::file_interface;
        using matrix<color>::operator=;

    public: // Interface (override)
        file_png& open ( const path& );
        file_png& save ( );

    public: // Interface
              int& depth ( );
        const int& depth ( ) const;

    private: // Data
        int image_depth = 32;
};

#ifdef dll
    #include "file_png.cpp"
#endif