#pragma once

class file_tga
    extends public matrix<color>,
            public file_interface<file_tga>
{
    public: // Core
        using matrix<color>::operator=;
        using file_interface<file_tga>::file_interface;

    public: // Interface (override)
        file_tga& open ( const path& );
        file_tga& save ( );

    public: // Interface
              int& depth ( );
        const int& depth ( ) const;

    private: // Data
        int image_depth = 32;
};

#ifdef dll
    #include "file_tga.cpp"
#endif