#pragma once

class file_csv
    extends public matrix<string>,
            public file_interface<file_csv>
{
    public: // Core
        using matrix<string>::operator=;
        using file_interface<file_csv>::file_interface;

    public: // Interface (override)
        file_csv& open ( const path& );
        file_csv& save ( );
};


#ifdef dll
    #include "file_csv.cpp"
#endif