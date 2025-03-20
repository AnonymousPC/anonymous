#pragma once

class serial_port_buf
    extends public std::streambuf
{
    public: // Interface
        void open    ( string );
        void close   ( );
        bool is_open ( ) const;

    protected: // Interface (virtual)
        virtual int underflow ( )                          override;
        virtual int overflow  ( int = traits_type::eof() ) override;
        virtual int sync      ( )                          override;

    private: // Data
        boost::asio::serial_port handle       = typename boost::asio::serial_port(boost::asio::system_executor());
        string                   send_buff    = "";
        string                   receive_buff = "";

    private: // Detail
        constexpr static const int default_buffer_size = 672; // Default MTU in L2CAP.
};

#if dll
    #include "serial_port_buf.cpp"
#endif