#pragma once

class file_dll
    extends public file_interface<file_dll>,
            public map<string,void*>
{
    public: // Core
        using file_interface<file_dll>::file_interface;
        using map<string,void*>::operator=;

    public: // Interface (override)
        file_dll& open ( const path& );
        file_dll& save ( ) = delete; // Not supported.

    private: // Data
        boost::dll::experimental::smart_library lib = boost::dll::experimental::smart_library();
};

//#ifdef dll
    #include "file_dll.cpp"
//#endif