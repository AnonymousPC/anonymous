class serial_port_stream
    extends public std::iostream
{
    public: // Core
        serial_port_stream ( );
        serial_port_stream ( string );
        serial_port_stream ( serial_port_stream&& );
       ~serial_port_stream ( );
        serial_port_stream& operator = ( serial_port_stream&& );

    public: // Interface
        serial_port_stream& open    ( string );
        serial_port_stream& close   ( );
        bool                is_open ( ) const;

    private: // Data
        std::unique_ptr<serial_port_buf> buff_ptr = std::make_unique<serial_port_buf>();
};

#ifdef dll
    #include "serial_port_stream.cpp"
#endif