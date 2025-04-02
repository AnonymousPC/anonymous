#pragma once

class file_png
    extends public matrix<color>,
            public file_interface<file_png>
{
    public: // Core
        using matrix<color>::operator=;
        using file_interface<file_png>::file_interface;

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