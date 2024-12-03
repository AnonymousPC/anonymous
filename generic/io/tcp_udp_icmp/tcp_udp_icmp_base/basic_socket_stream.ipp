#pragma once

/// Class basic_socket_stream

// Core

template < class protocol >
basic_socket_stream<protocol>::basic_socket_stream ( )
    extends std::iostream ( nullptr )
{
    // Initialize
    rdbuf(buff_ptr.get());

    // Set exception cases.
    exceptions(std::ios::badbit);
}

template < class protocol >
basic_socket_stream<protocol>::basic_socket_stream ( url website )
    extends std::iostream ( nullptr )
{
    // Initialize
    rdbuf(buff_ptr.get());

    // Set exception cases.
    exceptions(std::ios::badbit);

    // Connect website.
    connect(website);
}

template < class protocol >
basic_socket_stream<protocol>::basic_socket_stream ( basic_socket_stream&& init )
    extends std::iostream ( std::move(static_cast<std::iostream&>(init)) )
{
    self.rdbuf(buff_ptr.get());

    std::swap(self.buff_ptr, init.buff_ptr);
    let self_rdbuf = self.rdbuf();
    let init_rdbuf = init.rdbuf();
    self.rdbuf(init_rdbuf);
    init.rdbuf(self_rdbuf);
}

template < class protocol >
basic_socket_stream<protocol>::~basic_socket_stream ( )
{
    // Reset exception cases.
    exceptions(std::ios::iostate());
}

template < class protocol >
basic_socket_stream<protocol>& basic_socket_stream<protocol>::operator = ( basic_socket_stream&& right )
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

template < class protocol >
void basic_socket_stream<protocol>::connect ( url website )
{
    let ptr = dynamic_cast<basic_socket_buf<protocol>*>(rdbuf());
    if ( ptr != nullptr )
        ptr->connect(std::move(website));
    else
        throw network_error("socket_stream.rdbuf() does not point to a socket_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(basic_socket_buf<protocol>));
}

template < class protocol >
void basic_socket_stream<protocol>::listen ( url portal )
{
    let ptr = dynamic_cast<basic_socket_buf<protocol>*>(rdbuf());
    if ( ptr != nullptr )
        ptr->listen(std::move(portal));
    else
        throw network_error("socket_stream.rdbuf() does not point to a socket_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(basic_socket_buf<protocol>));
}

template < class protocol >
void basic_socket_stream<protocol>::close ( )
{
    let ptr = dynamic_cast<basic_socket_buf<protocol>*>(rdbuf());
    if ( ptr != nullptr )
        ptr->close();
    else
        throw network_error("socket_stream.rdbuf() does not point to a socket_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(basic_socket_buf<protocol>));

    clear();
}

template < class protocol >
bool basic_socket_stream<protocol>::is_open ( ) const
{
    let ptr = dynamic_cast<basic_socket_buf<protocol>*>(rdbuf());
    if ( ptr != nullptr )
        return ptr->is_open();
    else
        throw network_error("socket_stream.rdbuf() does not point to a socket_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(basic_socket_buf<protocol>));
}




// Interface

template < class protocol >
url basic_socket_stream<protocol>::local_endpoint ( ) const
{
    let ptr = dynamic_cast<basic_socket_buf<protocol>*>(rdbuf());
    if ( ptr != nullptr )
        return ptr->local_endpoint();
    else
        throw network_error("socket_stream.rdbuf() does not point to a socket_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(basic_socket_buf<protocol>));
}

template < class protocol >
url basic_socket_stream<protocol>::remote_endpoint ( ) const
{
    let ptr = dynamic_cast<basic_socket_buf<protocol>*>(rdbuf());
    if ( ptr != nullptr )
        return ptr->remote_endpoint();
    else
        throw network_error("socket_stream.rdbuf() does not point to a socket_buf (with common = {}, current = {}, expected = {})",
                            typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(basic_socket_buf<protocol>));
}