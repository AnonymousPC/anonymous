#pragma once

class file_csv
    extends public file_interface<file_csv>,
            public matrix<string>
{
    public: // Core
        using file_interface<file_csv>::file_interface;
        using matrix<string>::operator=;
        file_csv ( const char* );
        file_csv ( const path& );

    public: // Interface (override)
        file_csv& open ( const path& );
        file_csv& save ( );
};


#if dll
    #include "file_csv.cpp"
#endif