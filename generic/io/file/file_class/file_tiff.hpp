#pragma once

class file_tiff
    extends public matrix<color>,
            public file_interface<file_tiff>
{
    public: // Core
        using matrix<color>::operator=;
        using file_interface<file_tiff>::file_interface;

    public: // Interface (override)
        file_tiff& open ( const path& );
        file_tiff& save ( );

    public: // Interface
              int& depth ( );
        const int& depth ( ) const;

    private: // Data
        int image_depth = 32;
};

#ifdef dll
    #include "file_tiff.cpp"
#endif