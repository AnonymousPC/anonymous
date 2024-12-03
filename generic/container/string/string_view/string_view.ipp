#pragma once

/// Class basic_string_view

// Core

template < class char_type >
constexpr basic_string_view<char_type>& basic_string_view<char_type>::operator = ( const basic_string_view& right )
{
    #if debug
        if ( ptr != nullptr )
            throw logic_error("basic_string_view does not permit re-assignment, after it has been initialized to view a slice of string");
    #endif

    ptr = right.ptr;
    m   = right.m;
    return self;
}

// Constructor

template < class char_type >
constexpr basic_string_view<char_type>::basic_string_view ( const std::same_as<char_type> auto& ch )
    extends ptr ( &ch ),
            m   ( 1 )
{

}

template < class char_type >
constexpr basic_string_view<char_type>::basic_string_view ( const char_type* ch )
    extends ptr ( ch ),
            m   ( string_algo::strlen ( ch ) )
{

}

template < class char_type >
constexpr basic_string_view<char_type>::basic_string_view ( const char_type* ptr_begin, int str_len )
    extends ptr ( ptr_begin ),
            m   ( str_len )
{
    #if debug
        if ( size() < 0 )
            throw value_error("cannot apply a string_view from {} length {} negative size {}", ptr_begin, str_len, size());
    #endif
}

template < class char_type >
constexpr basic_string_view<char_type>::basic_string_view ( const char_type* ptr_begin, const char_type* ptr_end )
    extends ptr ( ptr_begin ),
            m   ( ptr_end - ptr_begin )
{
    #if debug
        if ( size() < 0 )
            throw value_error("cannot apply a string_view between {} and {} with negative size {}", ptr_begin, ptr_end, size());
    #endif
}

template < class char_type >
constexpr basic_string_view<char_type>::basic_string_view ( const basic_string<char_type>& str )
    extends ptr ( str.begin() ),
            m   ( str.size() )
{

}

template < class char_type >
constexpr basic_string_view<char_type>::basic_string_view ( const basic_string_range_view<char_type>& str )
    extends ptr ( str.begin() ),
            m   ( str.size() )
{

}

// Conversion

template < class char_type >
template < class char_type2 >
constexpr basic_string_view<char_type>::operator basic_string<char_type2> ( ) const
{
    try
    {
        let converter = std::filesystem::path(self.operator std::basic_string_view<char_type>());

        if constexpr ( std::is_same<char_type2,char>::value )
            return basic_string<char_type2>(converter.string());
        else if constexpr ( std::is_same<char_type2,wchar_t>::value )
            return basic_string<char_type2>(converter.wstring());
        else if constexpr ( std::is_same<char_type2,char8_t>::value )
            return basic_string<char_type2>(converter.u8string());
        else if constexpr ( std::is_same<char_type2,char16_t>::value )
            return basic_string<char_type2>(converter.u16string());
        else if constexpr ( std::is_same<char_type2,char32_t>::value )
            return basic_string<char_type2>(converter.u32string());
        else
            static_assert(false, "unknown encoding");
    }
    catch ( std::filesystem::filesystem_error& )
    {
        throw encode_error("cannot encode string {} from {} into {} (bytes = {:03d})",
                           self, typeid(char_type), typeid(char_type2),
                           vector<int>(size() * sizeof(char_type), [&] (int i) -> unsigned char { return reinterpret_cast<const char*>(begin())[i-1]; }));
    }
}

template < class char_type >
template < class bool_type >
constexpr basic_string_view<char_type>::operator bool_type ( ) const
    requires std::same_as<char_type,char> and
             std::same_as<bool_type,bool>
{
    if ( self == "true" )
        return true;
    else if ( self == "false" )
        return false;
    else
        throw encode_error("cannot convert {} into {}", '\"' + self + '\"', typeid(bool_type));
}

template < class char_type >
template < class number_type >
constexpr basic_string_view<char_type>::operator number_type ( ) const
    requires std::same_as<char_type,char> and
             ( not std::is_convertible<basic_string_view,number_type>::value ) and
             ( not general_string_type<number_type> ) and
             ( not std::same_as<number_type,bool> ) and
             ( std::integral<number_type> or std::floating_point<number_type> )
{
    number_type cvt = number_type();
    auto [p,ec] = std::from_chars ( begin(), end(), cvt );
    if ( p != end() or ec != std::errc() )
        throw encode_error("cannot convert {} into {}", '\"' + self + '\"', typeid(number_type));
    return cvt;
}

template < class char_type >
template < class inputable >
constexpr basic_string_view<char_type>::operator inputable ( ) const
    requires std::same_as<char_type,char> and
             ( not std::is_convertible<basic_string_view,inputable>::value ) and
             ( not general_string_type<inputable> ) and
             ( not std::same_as<inputable,bool> ) and
             ( not ( std::integral<inputable> or std::floating_point<inputable> ) ) and
             ap::inputable<inputable>
{
    inputable cvt = inputable();
    let stream = std::stringstream(); // Not std::basic_stringstream, as the concept "inputable" only requires std::istream.
    stream << self;
    stream >> cvt;
    if ( not stream.eof() and stream.fail() ) // Not until the stream reaches end, that the stream fails.
        throw encode_error("cannot convert {} into {}", '\"' + self + '\"', typeid(inputable));
    return cvt;
}

template < class char_type >
constexpr basic_string_view<char_type>::operator std::basic_string<char_type> ( ) const
{
    return std::basic_string<char_type> ( begin(), size() );
}

template < class char_type >
constexpr basic_string_view<char_type>::operator std::basic_string_view<char_type> ( ) const
{
    return std::basic_string_view<char_type> ( begin(), end() );
}

// Interface

template < class char_type >
constexpr int basic_string_view<char_type>::size ( ) const
{
    return m;
}

template < class char_type >
constexpr bool basic_string_view<char_type>::empty ( ) const
{
    return size() == 0;
}

template < class char_type >
constexpr basic_string_view<char_type>::const_iterator basic_string_view<char_type>::begin ( ) const
{
    return ptr;
}

template < class char_type >
constexpr basic_string_view<char_type>::const_iterator basic_string_view<char_type>::end ( ) const
{
    return ptr + size();
}

template < class char_type >
constexpr const char_type& basic_string_view<char_type>::operator [] ( int pos ) const
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    return pos > 0 ? ptr[pos-1] otherwise
                     ptr[pos+size()];
}

template < class char_type >
constexpr auto basic_string_view<char_type>::operator [] ( int from, int to ) const
{
    return basic_string_view ( ptr + from - 1, to - from + 1 );
}