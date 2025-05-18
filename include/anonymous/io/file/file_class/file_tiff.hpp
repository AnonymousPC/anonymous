class file_tiff
    extends public file_interface<file_tiff>,
            public matrix<color>
{
    public: // Core
        file_tiff ( ) = default;
        file_tiff ( path );

    public: // Interface (override)
        file_tiff& open  ( path );
        file_tiff& save  ( );
        file_tiff& close ( );

    public: // Interface
              int& depth ( );
        const int& depth ( ) const;

    private: // Data
        int image_depth = 32;
};

#ifdef dll
    #include "file_tiff.cpp"
#endif