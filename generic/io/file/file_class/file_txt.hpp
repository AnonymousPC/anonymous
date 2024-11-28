#pragma once

class file_txt
    extends public file_interface<file_txt>,
            public vector<string>
{
    public: // Core
        using file_interface<file_txt>::file_interface;
        using vector<string>::operator=;
        file_txt ( const char* );
        file_txt ( const path& );

    public: // Interface (override)
        file_txt& open ( const path& );
        file_txt& save ( );
};

#if dll
    #include "file_txt.cpp"
#endif