#pragma once

class file_pcap
    extends public file_interface<file_pcap>,
            public vector<any>
{
    public: // Core
        using vector<any>::operator=;
        using file_interface<file_pcap>::file_interface;
        file_pcap ( const char* );
        file_pcap ( const path& );

    public: // Interface
        file_pcap& open ( const path& );
        file_pcap& save ( );

    public: // Headers
        struct file_header;
        struct packet_header;
};

#if dll
    #include "file_pcap.cpp"
#endif