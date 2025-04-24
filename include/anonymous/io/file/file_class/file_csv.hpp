class file_csv
    extends public file_interface<file_csv>,
            public matrix<string>
{
    public: // Core
        file_csv ( ) = default;
        file_csv ( path );

    public: // Interface (override)
        file_csv& open  ( path );
        file_csv& save  ( );
        file_csv& close ( );
};


#ifdef dll
    #include "file_csv.cpp"
#endif