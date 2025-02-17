#pragma once

detail::system_error::system_error ( )
    extends boost::system::system_error ( boost::system::error_code() )
{
    
}

detail::system_error::system_error ( const boost::system::system_error& e )
    extends boost::system::system_error ( boost::system::error_code() )
{
    error_what = detail::red + string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()) + detail::white;
}

const char* detail::system_error::what ( ) const noexcept
{
    return error_what.c_str();
}