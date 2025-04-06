#pragma once

class file_pnm
    extends public file_interface<file_pnm>,
            public matrix<color>
{
    public: // Core
        file_pnm ( ) = default;
        file_pnm ( path );

    public: // Interface (override)
        file_pnm& open  ( path );
        file_pnm& save  ( );
        file_pnm& close ( );

    public: // Interface
              int& depth ( );
        const int& depth ( ) const;

    private: // Data
        int image_depth = 32;
};

#ifdef dll
    #include "file_pnm.cpp"
#endif