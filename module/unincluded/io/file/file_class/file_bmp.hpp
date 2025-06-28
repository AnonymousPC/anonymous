class file_bmp
    extends public file_interface<file_bmp>,
            public matrix<color>
{
    public: // Core
        file_bmp ( ) = default;
        file_bmp ( path );

    public: // Interface (override)
        file_bmp& open  ( path );
        file_bmp& save  ( );
        file_bmp& close ( );

    public: // Interface
              int& depth ( );
        const int& depth ( ) const;

    private: // Data
        int image_depth = 32;
};

#ifdef dll
    #include "file_bmp.cpp"
#endif