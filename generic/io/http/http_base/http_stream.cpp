#pragma once

/// Class http_stream

// Close

http_stream::http_stream ( )
    extends std::iostream ( nullptr )
{
    // Initialize.
    rdbuf(buff_ptr.get()); // Buff is contructed after std::iostream, so "extends std::iostream(&buff)" will cause segfault.

    // Set exception cases.
    exceptions(std::ios::badbit);
}

http_stream::http_stream ( http_stream&& init )
    extends std::iostream ( std::move(static_cast<std::iostream&>(init)) )
{
    self.rdbuf(buff_ptr.get());

    std::swap(self.buff_ptr, init.buff_ptr);
    let self_rdbuf = self.rdbuf();
    let init_rdbuf = init.rdbuf();
    self.rdbuf(init_rdbuf);
    init.rdbuf(self_rdbuf);
}

http_stream::~http_stream ( )
{
    // Reset exception cases.
    exceptions(std::ios::iostate());
}

http_stream& http_stream::operator = ( http_stream&& right )
{
    self.std::iostream::operator=(std::move(static_cast<std::iostream&>(right)));

    std::swap(self.buff_ptr, right.buff_ptr);
    let self_rdbuf  = self .rdbuf();
    let right_rdbuf = right.rdbuf();
    self .rdbuf(right_rdbuf);
    right.rdbuf(self_rdbuf );

    return self;
}

// Interface

void http_stream::close ( )
{
    let ptr = dynamic_cast<http_buf*>(rdbuf());
    if ( ptr != nullptr )
        ptr->close();
    else
        throw network_error("http_stream.rdbuf() does not point to a http_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(http_buf));

    clear();
}

bool http_stream::is_open ( ) const
{
    let ptr = dynamic_cast<const http_buf*>(rdbuf());
    if ( ptr != nullptr )
        return ptr->is_open();
    else
        throw network_error("http_stream.rdbuf() does not point to a http_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(http_buf));
}


// Interface (cache)

url http_stream::local_endpoint ( ) const
{
    let ptr = dynamic_cast<const http_buf*>(rdbuf());
    if ( ptr != nullptr )
        return dynamic_cast<http_buf*>(rdbuf())->local_endpoint();
    else
        throw network_error("http_stream.rdbuf() does not point to a http_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(http_buf));
}

url http_stream::remote_endpoint ( ) const
{
    let ptr = dynamic_cast<const http_buf*>(rdbuf());
    if ( ptr != nullptr )
        return dynamic_cast<http_buf*>(rdbuf())->remote_endpoint();
    else
        throw network_error("http_stream.rdbuf() does not point to a http_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(http_buf));
}

string http_stream::request_method ( ) const
{
    let ptr = dynamic_cast<const http_buf*>(rdbuf());
    if ( ptr != nullptr )
        return dynamic_cast<http_buf*>(rdbuf())->request_method();
    else
        throw network_error("http_stream.rdbuf() does not point to a http_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(http_buf));
}

string http_stream::request_path ( ) const
{
    let ptr = dynamic_cast<const http_buf*>(rdbuf());
    if ( ptr != nullptr )
        return ptr->request_path();
    else
        throw network_error("http_stream.rdbuf() does not point to a http_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(http_buf));
}

float http_stream::request_version ( ) const
{
    let ptr = dynamic_cast<const http_buf*>(rdbuf());
    if ( ptr != nullptr )
        return ptr->request_version();
    else
        throw network_error("http_stream.rdbuf() does not point to a http_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(http_buf));
}

map<string,string> http_stream::request_header ( ) const
{
    let ptr = dynamic_cast<const http_buf*>(rdbuf());
    if ( ptr != nullptr )
        return ptr->request_header();
    else
        throw network_error("http_stream.rdbuf() does not point to a http_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(http_buf));
}

int http_stream::response_status_code ( ) const
{
    let ptr = dynamic_cast<const http_buf*>(rdbuf());
    if ( ptr != nullptr )
        return ptr->response_status_code();
    else
        throw network_error("http_stream.rdbuf() does not point to a http_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(http_buf));
}

string http_stream::response_reason ( ) const
{
    let ptr = dynamic_cast<const http_buf*>(rdbuf());
    if ( ptr != nullptr )
        return ptr->response_reason();
    else
        throw network_error("http_stream.rdbuf() does not point to a http_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(http_buf));
}

map<string,string> http_stream::response_header ( ) const
{
    let ptr = dynamic_cast<const http_buf*>(rdbuf());
    if ( ptr != nullptr )
        return ptr->response_header();
    else
        throw network_error("http_stream.rdbuf() does not point to a http_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(http_buf));
}


// Override

std::ostream& http_stream::flush ( )
{
    if ( rdbuf() != nullptr )
    {
        std::ostream::sentry(self);
        let success = rdbuf()->pubsync(); // May throws network_error (instead of std::ios_base::failure).
        if ( success == -1 )
            setstate(std::ios::badbit);
    }

    return self;
}



