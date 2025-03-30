#pragma once

class file_csv
    extends public file_interface<file_csv>,
            public matrix<string>
{
    public: // Core
        using file_interface<file_csv>::file_interface;
        using matrix<string>::operator=;

    public: // Interface (override)
        file_csv& open ( const path& );
        file_csv& save ( );
};


#ifdef dll
    #include "file_csv.cpp"
#endif