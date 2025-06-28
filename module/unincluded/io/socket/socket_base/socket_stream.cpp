template < class protocol >
basic_socket_stream<protocol>::basic_socket_stream ( )
    extends std::iostream ( nullptr )
{
    rdbuf(buff_ptr.get());
    exceptions(std::ios::badbit);
}

template < class protocol >
basic_socket_stream<protocol>::basic_socket_stream ( url website )
    extends std::iostream ( nullptr )
{
    rdbuf(buff_ptr.get());
    exceptions(std::ios::badbit);
    connect(std::move(website));
}

template < class protocol >
basic_socket_stream<protocol>::basic_socket_stream ( basic_socket_stream&& init )
    extends std::iostream ( std::move(static_cast<std::iostream&>(init)) )
{
    self.rdbuf(buff_ptr.get());

    std::swap(self.buff_ptr, init.buff_ptr);
    auto self_rdbuf = self.rdbuf();
    auto init_rdbuf = init.rdbuf();
    self.rdbuf(init_rdbuf);
    init.rdbuf(self_rdbuf);
}

template < class protocol >
basic_socket_stream<protocol>::~basic_socket_stream ( )
{
    exceptions(std::ios::iostate());
}

template < class protocol >
basic_socket_stream<protocol>& basic_socket_stream<protocol>::operator = ( basic_socket_stream&& right )
{
    self.std::iostream::operator=(std::move(static_cast<std::iostream&>(right)));

    std::swap(self.buff_ptr, right.buff_ptr);
    auto self_rdbuf  = self .rdbuf();
    auto right_rdbuf = right.rdbuf();
    self .rdbuf(right_rdbuf);
    right.rdbuf(self_rdbuf );

    return self;
}

template < class protocol >
basic_socket_stream<protocol>& basic_socket_stream<protocol>::connect ( url website )
{
    static_cast<basic_socket_buf<protocol>*>(rdbuf())->connect(std::move(website));
    return self;
}

template < class protocol >
basic_socket_stream<protocol>& basic_socket_stream<protocol>::listen ( url portal )
{
    static_cast<basic_socket_buf<protocol>*>(rdbuf())->listen(std::move(portal));
    return self;
}

template < class protocol >
basic_socket_stream<protocol>& basic_socket_stream<protocol>::close ( )
{
    static_cast<basic_socket_buf<protocol>*>(rdbuf())->close();
    clear();
    return self;
}

template < class protocol >
bool basic_socket_stream<protocol>::is_open ( ) const
{
    return static_cast<const basic_socket_buf<protocol>*>(rdbuf())->is_open();
}

template < class protocol >
url basic_socket_stream<protocol>::local_endpoint ( ) const
{
    return static_cast<const basic_socket_buf<protocol>*>(rdbuf())->local_endpoint();
}

template < class protocol >
url basic_socket_stream<protocol>::remote_endpoint ( ) const
{
    return static_cast<const basic_socket_buf<protocol>*>(rdbuf())->remote_endpoint();
}