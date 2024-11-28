#pragma once

class file_wav
    extends public file_interface<file_wav>,
            public matrix<float>
{
    /** wav-file is always in little endian **/

    public: // Core
        using file_interface<file_wav>::file_interface;
        using matrix<float>::operator=;
        file_wav ( const char* );
        file_wav ( const path& );

    public: // Interface (override)
        file_wav& open ( const path& );
        file_wav& save ( );

    public: // Interface
              int&    rate         ( );
        const int&    rate         ( ) const;
              int&    depth        ( );
        const int&    depth        ( ) const;
              string& title        ( );
        const string& title        ( ) const;
              string& artist       ( );
        const string& artist       ( ) const;
              string& album        ( );
        const string& album        ( ) const;
              string& year         ( );
        const string& year         ( ) const;
              string& track        ( );
        const string& track        ( ) const;
              string& genre        ( );
        const string& genre        ( ) const;
              string& comment      ( );
        const string& comment      ( ) const;
     //       string& album_artist ( );       // .wav does not supports it.
     // const string& album_artist ( ) const; // .wav does not supports it.
     //       string& composer     ( );       // .wav does not supports it.
     // const string& composer     ( ) const; // .wav does not supports it.
     //       string& discnumber   ( );       // .wav does not supports it.
     // const string& discnumber   ( ) const; // .wav does not supports it.

    private: // Data
        int    audio_rate         = 44100;
        int    audio_depth        = 16;
        string audio_title        = "";
        string audio_artist       = "";
        string audio_album        = "";
        string audio_year         = "";
        string audio_track        = "";
        string audio_genre        = "";
        string audio_comment      = "";

    private: // Cache
        int    cache_format       = 1;
        int    cache_channel      = 2;

    private: // Header
        struct chunk;
        struct riff_chunk;
        struct fmt_chunk;
        struct fmt_extension_chunk;
        struct data_chunk;
        struct list_chunk;
        struct meta_chunk;
        struct id3_chunk;
        struct chunk_header;
        using  chunk_ptr = std::unique_ptr<chunk>;
        struct guid;

    private: // Auxiliary
                         void     read        ( file_stream&,       chunk&               );
                         void     read        ( file_stream&,       riff_chunk&          );
                         void     read        ( file_stream&,       fmt_chunk&           );
                         void     read        ( file_stream&,       fmt_extension_chunk& );
                         void     read        ( file_stream&,       data_chunk&          );
                         void     read        ( file_stream&,       list_chunk&          );
                         void     read        ( file_stream&,       meta_chunk&          );
                         void     read        ( file_stream&,       id3_chunk&           );
                         void     read        ( file_stream&,       chunk_header&        );
                         void     write       ( file_stream&                             );
                         void     write       ( file_stream&, const chunk&               );
                         void     write       ( file_stream&, const riff_chunk&          );
                         void     write       ( file_stream&, const fmt_chunk&           );
                         void     write       ( file_stream&, const fmt_extension_chunk& );
                         void     write       ( file_stream&, const data_chunk&          );
                         void     write       ( file_stream&, const list_chunk&          );
                         void     write       ( file_stream&, const meta_chunk&          );
                         void     write       ( file_stream&, const id3_chunk&           );
                         void     write       ( file_stream&, const chunk_header&        );
        constexpr static uint32_t from_string ( const string&   );
        constexpr static string   to_string   ( const uint32_t& );
};

#if dll
    #include "file_wav.cpp"
#endif