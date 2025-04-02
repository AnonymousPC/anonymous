#pragma once

class file_bmp
    extends public matrix<color>,
            public file_interface<file_bmp>
{
    public: // Core
        using matrix<color>::operator=;
        using file_interface<file_bmp>::file_interface;

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