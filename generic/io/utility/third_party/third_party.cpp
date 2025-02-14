#pragma once

detail::boost_system_error::boost_system_error ( const boost::system::system_error& e )
    extends error_what ( e.what() )
{
    error_what.encode(std::text_encoding::environment(), std::text_encoding::literal());
}

const char* detail::boost_system_error::what ( ) const
{
    return error_what.c_str();
}