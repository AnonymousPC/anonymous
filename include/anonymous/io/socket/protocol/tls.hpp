class tls
    extends public tcp
{
    public:
        class acceptor;
        using tcp::endpoint;
        using tcp::resolver;
        class socket;
};

class tls::acceptor 
    extends public tcp::acceptor
{
    public:
        using tcp::acceptor::acceptor;

        void accept ( auto&, auto&&... );
};

class tls::socket
    extends public boost::asio::ssl::stream<typename tcp::socket>
{
    public:
        socket ( auto&&... );
    
        void        connect         ( auto&&... );
        void        shutdown        ( auto&&... );
        void        close           ( auto&&... );
        std::size_t send            ( auto&&... );
        std::size_t receive         ( auto&&... );
        endpoint    local_endpoint  ( )           const;
        endpoint    remote_endpoint ( )           const;
};

#include "tls.cpp"
#ifdef dll
    #include "tls.cpp"
#endif