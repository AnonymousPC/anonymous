#pragma once

class file_png
    extends public file_interface<file_png>,
            public matrix<color>
{
    public: // Core
        using file_interface<file_png>::file_interface;
        using matrix<color>::operator=;
        file_png ( const char* );
        file_png ( const path& );

    public: // Interface (override)
        file_png& open ( const path& );
        file_png& save ( );

    public: // Interface
              int& depth ( );
        const int& depth ( ) const;

    private: // Data
        int image_depth = 32;
};

#if dll
    #include "file_png.cpp"
#endif