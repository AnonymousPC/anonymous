#pragma once

class icmp_ping
    extends public icmp_interface<icmp_ping>,
            public vector<char>
{
    public: // Core
        using icmp_interface<icmp_ping>::icmp_interface;
        icmp_ping ( const char*, const printable auto& );
        icmp_ping ( const url&,  const printable auto& );

    public: // Interface (override)
        icmp_ping& ping ( const url&, const printable auto& );

    public:
        duration time_to_connect ( ) const;
        int      time_to_live    ( ) const;

        boost::asio::ip::icmp::
};