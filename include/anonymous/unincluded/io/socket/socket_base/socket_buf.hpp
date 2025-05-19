template < class protocol >
class basic_socket_buf
    extends public std::streambuf
{
    public: // Interface
        void connect ( url );
        void listen  ( url );
        void close   ( );
        bool is_open ( ) const;

    public: // Interface (cache)
        url local_endpoint  ( ) const;
        url remote_endpoint ( ) const;

    protected: // Interface (virtual)
        virtual int underflow ( )                          override;
        virtual int overflow  ( int = traits_type::eof() ) override;
        virtual int sync      ( )                          override;

    private: // Data
        typename protocol::socket handle       = typename protocol::socket(boost::asio::system_executor());
        string                    send_buff    = "";
        string                    receive_buff = "";

    private: // Detail
        string local_endpoint_noexcept  ( )            const;
        string remote_endpoint_noexcept ( )            const;
        string protocol_name            ( )            const;
        auto   resolve_url              ( const url& ) const;

    private: // Settings
        constexpr static const int default_buffer_size = 65536;
};


#include "socket_buf.cpp"