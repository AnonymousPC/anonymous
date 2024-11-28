#pragma once

/// Class http_interface

// Core

template < class type >
http_interface<type>::http_interface ( http_interface&& init )
    extends http_url  ( std::exchange ( init.http_url,  ""    ) ),
            http_open ( std::exchange ( init.http_open, false ) )
{

}

template < class type >
http_interface<type>& http_interface<type>::operator = ( http_interface&& right )
{
    http_url  = std::exchange ( right.http_url,  ""    );
    http_open = std::exchange ( right.http_open, false );
    return self;
}


// Interface (override)

template < class type >
type& http_interface<type>::connect ( const url& website )
{
    if ( http_open )
        throw network_error("cannot connect http {}: http_interface has already connected/listened {}", website, http_url);

    http_url  = website;
    http_open = true;

    return static_cast<type&>(self);
}

template < class type >
type& http_interface<type>::listen ( const url& portal )
{
    if ( http_open )
        throw network_error("cannot listen http {}: http_interface has already connected/listened {}", portal, http_url);

    http_url  = portal;
    http_open = true;

    return static_cast<type&>(self);
}

// Interface (non-override)

template < class type >
type& http_interface<type>::close ( )
{
    if ( not http_open )
        throw network_error("cannot close http: http_interface has not been opened");

    http_url  = "";
    http_open = false;

    return static_cast<type&>(self);
}

template < class type >
bool http_interface<type>::is_open ( ) const
{
    return http_open;
}

// Conversion

template < class type >
http_interface<type>::operator url ( ) const
{
    return http_url;
}



// Modes

template < class type >
struct http_interface<type>::content_encoding
{
    string value = "";
    struct http_client_mode_tag { };
};

template < class type >
struct http_interface<type>::max_redirect
{
    int value = 0;
    struct http_client_mode_tag { };
};


// Encoding

template < class type >
class http_interface<type>::encode
    extends public boost::iostreams::filtering_ostream
{
    public:
        encode ( http_stream&, string );
       ~encode ( );
};

template < class type >
class http_interface<type>::decode
    extends public boost::iostreams::filtering_istream
{
    public:
        decode ( http_stream&, string );
       ~decode ( );
};

template < class type >
http_interface<type>::encode::encode ( http_stream& stream, string encoding )
{
    if ( encoding == "bzip2" )
        push(boost::iostreams::bzip2_compressor());
    else if ( encoding == "deflate" or encoding == "zlib" )
        push(boost::iostreams::zlib_compressor());
    else if ( encoding == "gzip" )
        push(boost::iostreams::gzip_compressor());
    else
        throw network_error("unrecognized content encoding {} (supported: bzip2, deflate/zlib, gzip)", encoding);

    push(stream);
}

template < class type >
http_interface<type>::encode::~encode ( )
{
    flush();
    set_auto_close(false);
    while ( not empty() )
        pop();
}

template < class type >
http_interface<type>::decode::decode ( http_stream& stream, string encoding )
{
    if ( encoding == "bzip2" )
        push(boost::iostreams::bzip2_decompressor());
    else if ( encoding == "deflate" or encoding == "zlib" )
        push(boost::iostreams::zlib_decompressor());
    else if ( encoding == "gzip" )
        push(boost::iostreams::gzip_decompressor());
    else
        throw network_error("unrecognized content encoding {} (supported: bzip2, deflate/zlib, gzip)", encoding);

    push(stream);
}

template < class type >
http_interface<type>::decode::~decode ( )
{
    set_auto_close(false);
    while ( not empty() )
        pop();
}

// Auxiliary

template < class type >
template < class result_type >
void http_interface<type>::extract ( )
{

}

template < class type >
template < class result_type >
auto& http_interface<type>::extract ( auto& arg1, auto&... args )
    requires aux::same_as_only_one_of<result_type,decay<decltype(arg1)>,decay<decltype(args)>...>
{
    if constexpr ( std::same_as<decay<decltype(arg1)>,result_type> )
        return arg1;
    else
        return extract<result_type>(args...);
}

template < class type >
template < class result_type >
void http_interface<type>::extract ( auto& arg1, auto&... args )
    requires ( not aux::same_as_only_one_of<result_type,decay<decltype(arg1)>,decay<decltype(args)>...> )
{

}