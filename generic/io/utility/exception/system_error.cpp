#pragma once

detail::system_error::system_error ( const boost::system::system_error& e )
    extends error_what ( e.what() )
{
    error_what.encode(std::text_encoding::environment(), std::text_encoding::literal());
}

const char* detail::system_error::what ( ) const noexcept
{
    return error_what.c_str();
}