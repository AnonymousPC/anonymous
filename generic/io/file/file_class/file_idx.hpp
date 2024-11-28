#pragma once

class file_idx
    extends public file_interface<file_idx>,
            public any
{
    /** idx-file is always in big endian **/

    public: // Core
        using file_interface<file_idx>::file_interface;
        using any::operator=;
        file_idx ( const char* );
        file_idx ( const path& );

    public: // Interface (override)
        file_idx& open ( const path& );
        file_idx& save ( );

    private: // Headers
        struct info_header;

    private: // Auxiliary
        template < class type, int dimension, bool first = true > static array<type,dimension> read        ( auto&& /*stream-or-chunked-binary-istream-view*/, const auto& /*shape*/ );
        template < class type, int dimension, bool first = true > static void                  write       ( auto&& /*stream-or-chunked-binary-istream-view*/, const auto& /*data*/  );
                                                                  static decltype(auto)        write_aux   ( const auto& /*data*/ );
                                                                  friend file_stream&          operator >> ( file_stream&,       file_idx::info_header& );
                                                                  friend file_stream&          operator << ( file_stream&, const file_idx::info_header& );
};

#if dll
    #include "file_idx.cpp"
#endif