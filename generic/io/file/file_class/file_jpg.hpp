#pragma once

class file_jpg
    extends public matrix<color>,
            public file_interface<file_jpg>
{
    public: // Core
        using matrix<color>::operator=;
        using file_interface<file_jpg>::file_interface;

    public: // Interface (override)
        file_jpg& open ( const path& );
        file_jpg& save ( );

    public: // Interface
              int& depth ( );
        const int& depth ( ) const;

    private: // Data
        int image_depth = 24;
};


#ifdef dll
    #include "file_jpg.cpp"
#endif