class file_idx
    extends public any,
            public file_interface<file_idx>
{
    public: // Core
        file_idx ( ) = default;
        file_idx ( const path& );

    public: // Interface (override)
        file_idx& open  ( const path& );
        file_idx& save  ( );
        file_idx& close ( );
};

#ifdef dll
    #include "file_idx.cpp"
#endif