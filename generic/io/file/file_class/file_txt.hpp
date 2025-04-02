#pragma once

class file_txt
    extends public vector<string>,
            public file_interface<file_txt>
{
    public: // Core
        using vector<string>::operator=;
        using file_interface<file_txt>::file_interface;

    public: // Interface (override)
        file_txt& open ( const path& );
        file_txt& save ( );
};

#ifdef dll
    #include "file_txt.cpp"
#endif