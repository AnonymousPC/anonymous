#pragma once

class file_tiff
    extends public file_interface<file_tiff>,
            public matrix<color>
{
    public: // Core
        using file_interface<file_tiff>::file_interface;
        using matrix<color>::operator=;
        file_tiff ( const char* );
        file_tiff ( const path& );

    public: // Interface (override)
        file_tiff& open ( const path& );
        file_tiff& save ( );

    public: // Interface
              int& depth ( );
        const int& depth ( ) const;

    private: // Data
        int image_depth = 32;
};

#if dll
    #include "file_tiff.cpp"
#endif