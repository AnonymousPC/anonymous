#pragma once

class file_bmp
    extends public file_interface<file_bmp>,
            public matrix<color>
{
    public: // Core
        using file_interface<file_bmp>::file_interface;
        using matrix<color>::operator=;

    public: // Interface (override)
        file_bmp& open ( const path& );
        file_bmp& save ( );

    public: // Interface
              int& depth ( );
        const int& depth ( ) const;

    private: // Data
        int image_depth = 32;
};

#ifdef dll
    #include "file_bmp.cpp"
#endif