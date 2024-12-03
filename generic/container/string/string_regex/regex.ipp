#pragma once

/// Class regex

// Core

template < class char_type >
constexpr basic_regex<char_type>::basic_regex ( basic_string<char_type> rgx )
    extends basic_string<char_type> ( std::move(rgx) )
{
    self.operator std::basic_regex<char_type>(); // Testing.
}




// Conversion

template < class char_type >
constexpr basic_regex<char_type>::operator std::basic_regex<char_type> ( ) const
{
    try
    {
        return std::basic_regex<char_type>(self.c_str());
    }
    catch ( const std::regex_error& e )
    {
        throw regex_error("cannot create regex {}: [[caused by {}: {}]]", self, typeid(e), e.what());
    }
}