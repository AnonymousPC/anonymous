#pragma once

class file_dll_any
{
    public:
        constexpr file_dll_any ( ) = default;
        constexpr file_dll_any ( boost::dll::shared_library, const std::string& );

    public: // Member
                                      constexpr       bool            empty ( ) const;
                                      constexpr const std::type_info& type  ( ) const = delete;
        template < class value_type > constexpr       value_type&     value ( );
        template < class value_type > constexpr const value_type&     value ( ) const;

    private: // Data
        boost::dll::shared_library library = boost::dll::shared_library();
        std::string                symbol  = ""; // Mangled.
};

class file_dll
    extends public  unordered_map<string,file_dll_any>,
            private boost::dll::shared_library,
            public  file_interface<file_dll>
{
    public: // Core
        using unordered_map<string,file_dll_any>::operator=;
        using file_interface<file_dll>::file_interface;

    public: // Interface (override)
        file_dll& open  ( const path& );
        file_dll& save  ( )             = delete; // Not supported.
        file_dll& close ( );

    public: // Interface (limitation)
              file_dll_any& operator [] ( const string& );       // Throws key_error if not found.
        const file_dll_any& operator [] ( const string& ) const;

};

#include "file_dll.ipp"
//#ifdef dll
    #include "file_dll.cpp"
//#endif