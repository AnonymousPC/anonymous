#pragma once

class file_tga
    extends public file_interface<file_tga>,
            public matrix<color>
{
    public: // Core
        using file_interface<file_tga>::file_interface;
        using matrix<color>::operator=;

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