#pragma once

class file_pnm
    extends public matrix<color>,
            public file_interface<file_pnm>
{
    public: // Core
        using matrix<color>::operator=;
        using file_interface<file_pnm>::file_interface;

    public: // Interface (override)
        file_pnm& open ( const path& );
        file_pnm& save ( );

    public: // Interface
              int& depth ( );
        const int& depth ( ) const;

    private: // Data
        int image_depth = 32;
};

#ifdef dll
    #include "file_pnm.cpp"
#endif