template < class protocol >
basic_http_stream<protocol>::basic_http_stream ( )
    extends std::iostream ( nullptr )
{
    rdbuf(buff_ptr.get());
    exceptions(std::ios::badbit);
}

template < class protocol >
basic_http_stream<protocol>::basic_http_stream ( url website, http_client_mode auto... args )
    extends std::iostream ( nullptr )
{
    rdbuf(buff_ptr.get());
    exceptions(std::ios::badbit);
    connect(std::move(website), std::forward<decltype(args)>(args)...);
}

template < class protocol >
basic_http_stream<protocol>::basic_http_stream ( basic_http_stream&& init )
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
basic_http_stream<protocol>::~basic_http_stream ( )
{
    exceptions(std::ios::iostate());
}

template < class protocol >
basic_http_stream<protocol>& basic_http_stream<protocol>::operator = ( basic_http_stream&& right )
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
basic_http_stream<protocol>& basic_http_stream<protocol>::connect ( url website, http_client_mode auto... args )
{
    static_cast<basic_http_buf<protocol>*>(rdbuf())->connect(std::move(website), std::forward<decltype(args)>(args)...);
    return self;
}

template < class protocol >
basic_http_stream<protocol>& basic_http_stream<protocol>::listen ( url portal, http_server_mode auto... args )
{
    static_cast<basic_http_buf<protocol>*>(rdbuf())->listen(std::move(portal), std::forward<decltype(args)>(args)...);
    return self;
}

template < class protocol >
basic_http_stream<protocol>& basic_http_stream<protocol>::close ( )
{
    static_cast<basic_http_buf<protocol>*>(rdbuf())->close();
    clear();
    return self;
}

template < class protocol >
bool basic_http_stream<protocol>::is_open ( ) const
{
    return static_cast<const basic_http_buf<protocol>*>(rdbuf())->is_open();
}

template < class protocol >
url basic_http_stream<protocol>::local_endpoint ( ) const
{
    return static_cast<const basic_http_buf<protocol>*>(rdbuf())->local_endpoint();
}

template < class protocol >
url basic_http_stream<protocol>::remote_endpoint ( ) const
{
    return static_cast<const basic_http_buf<protocol>*>(rdbuf())->remote_endpoint();
}

template < class protocol >
string& basic_http_stream<protocol>::request_method ( )
{
    return static_cast<basic_http_buf<protocol>*>(rdbuf())->request_method();
}

template < class protocol >
const string& basic_http_stream<protocol>::request_method ( ) const
{
    return static_cast<const basic_http_buf<protocol>*>(rdbuf())->request_method();
}

template < class protocol >
string& basic_http_stream<protocol>::request_path ( )
{
    return static_cast<basic_http_buf<protocol>*>(rdbuf())->request_path();
}

template < class protocol >
const string& basic_http_stream<protocol>::request_path ( ) const
{
    return static_cast<const basic_http_buf<protocol>*>(rdbuf())->request_path();
}

template < class protocol >
map<string, string>& basic_http_stream<protocol>::request_param ( )
{
    return static_cast<basic_http_buf<protocol>*>(rdbuf())->request_param();
}

template < class protocol >
const map<string, string>& basic_http_stream<protocol>::request_param () const
{
    return static_cast<const basic_http_buf<protocol>*>(rdbuf())->request_param();
}

template < class protocol >
float& basic_http_stream<protocol>::request_version ( )
{
    return static_cast<basic_http_buf<protocol>*>(rdbuf())->request_version();
}

template < class protocol >
const float& basic_http_stream<protocol>::request_version ( ) const
{
    return static_cast<const basic_http_buf<protocol>*>(rdbuf())->request_version();
}

template < class protocol >
map<string, string>& basic_http_stream<protocol>::request_header ( )
{
    return static_cast<basic_http_buf<protocol>*>(rdbuf())->request_header();
}

template < class protocol >
const map<string, string>& basic_http_stream<protocol>::request_header ( ) const
{
    return static_cast<const basic_http_buf<protocol>*>(rdbuf())->request_header();
}

template < class protocol >
float& basic_http_stream<protocol>::response_version ( )
{
    return static_cast<basic_http_buf<protocol>*>(rdbuf())->response_version();
}

template < class protocol >
const float& basic_http_stream<protocol>::response_version ( ) const
{
    return static_cast<const basic_http_buf<protocol>*>(rdbuf())->response_version();
}

template < class protocol >
int& basic_http_stream<protocol>::response_status_code ( )
{
    return static_cast<basic_http_buf<protocol>*>(rdbuf())->response_status_code();
}

template < class protocol >
const int& basic_http_stream<protocol>::response_status_code ( ) const
{
    return static_cast<const basic_http_buf<protocol>*>(rdbuf())->response_status_code();
}

template < class protocol >
string& basic_http_stream<protocol>::response_reason ( )
{
    return static_cast<basic_http_buf<protocol>*>(rdbuf())->response_reason();
}

template < class protocol >
const string& basic_http_stream<protocol>::response_reason ( ) const
{
    return static_cast<const basic_http_buf<protocol>*>(rdbuf())->response_reason();
}

template < class protocol >
map<string, string>& basic_http_stream<protocol>::response_header ( )
{
    return static_cast<basic_http_buf<protocol>*>(rdbuf())->response_header();
}

template < class protocol >
const map<string, string>& basic_http_stream<protocol>::response_header ( ) const
{
    return static_cast<const basic_http_buf<protocol>*>(rdbuf())->response_header();
}