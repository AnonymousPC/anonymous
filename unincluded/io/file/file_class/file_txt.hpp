class file_txt
    extends public file_interface<file_txt>,
            public vector<string>
{
    public: // Core
        file_txt ( ) = default;
        file_txt ( path );

    public: // Interface (override)
        file_txt& open  ( path );
        file_txt& save  ( );
        file_txt& close ( );
};

#ifdef dll
    #include "file_txt.cpp"
#endif