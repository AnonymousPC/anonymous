#pragma once

// Core

template < class char_type >
constexpr basic_string<char_type>::basic_string ( const basic_string& init )
    extends m ( init.m )
{
    if ( size() <= sso )
        std::copy_n ( init.internal, size(), internal );
    else
    {
        external = allocate ( size() + 1 );
        std::copy_n ( init.external, size(), external );
    }
}

template < class char_type >
constexpr basic_string<char_type>::basic_string ( basic_string&& init )
    extends m ( std::exchange ( init.m, 0 ) )
{
    if ( size() <= sso )
        std::copy_n ( init.internal, size(), internal );
    else
        external = init.external;
}

template < class char_type >
constexpr basic_string<char_type>::basic_string ( const basic_string_range_view<char_type>& init )
    extends m ( init.size() )
{
    if ( size() <= sso )
        std::copy_n ( init.begin(), size(), internal );
    else
    {
        external = allocate ( size() + 1 );
        std::copy_n ( init.begin(), size(), external );
    }
}

template < class char_type >
constexpr basic_string<char_type>::basic_string ( const basic_string_view<char_type>& init )
    extends m ( init.size() )
{
    if ( size() <= sso )
        std::copy_n ( init.begin(), size(), internal );
    else
    {
        external = allocate ( size() + 1 );
        std::copy_n ( init.begin(), size(), external );
    }
}

template < class char_type >
constexpr basic_string<char_type>::basic_string ( std::same_as<char_type> auto init )
    extends m ( 1 )
{
    internal[0] = init;
}

template < class char_type >
constexpr basic_string<char_type>::basic_string ( int init_size, std::same_as<char_type> auto init_data )
    extends m ( init_size )
{
    if ( size() <= sso )
        std::fill_n ( internal, size(), init_data );

    else
    {
        external = allocate ( size() + 1 );
        std::fill_n ( external, size(), init_data );
    }
}

template < class char_type >
constexpr basic_string<char_type>::basic_string ( const char_type* init )
    extends m ( string_algo::strlen ( init ) )
{
    if ( size() <= sso )
        std::copy_n ( init, size(), internal );

    else
    {
        external = allocate ( size() + 1 );
        std::copy_n ( init, size(), external );
    }
}

template < class char_type >
constexpr basic_string<char_type>::basic_string ( std::from_range_t, std::ranges::input_range auto&& init )
    requires requires { std::declval<basic_string>().push(*init.begin()); }
{
    if constexpr ( requires { init.size(); self[1] = *init.begin(); } )
    {
        resize ( init.size() );
        std::move ( init.begin(), init.end(), begin() );
    }

    else
        for ( auto&& item in init )
            self.push(item);
}

template < class char_type >
constexpr basic_string<char_type>::basic_string ( std::from_range_t, std::ranges::input_range auto&& init, int init_size )
    requires requires { std::declval<basic_string>().push(*init.begin()); }
{
    resize ( init_size );

    int i = 1;
    for ( auto&& item in init )
    {
        #if debug
            if ( i > size() )
                throw value_error("cannot move range of size >= {} into string of size {}", i, size());
        #endif
        self[i++] = std::move(item);
    }

    #if debug
        if ( i - 1 < size() )
            throw value_error("cannot move range of size {} into string of size {}", i - 1, size());
    #endif
}

template < class char_type >
constexpr basic_string<char_type>::~basic_string ( )
{
    if ( size() > sso )
        deallocate ( external );
}

template < class char_type >
constexpr basic_string<char_type>& basic_string<char_type>::operator = ( const basic_string& right )
{
    resize ( right.size() );
    std::copy ( right.begin(), right.end(), size() <= sso ? internal otherwise external );
    return self;
}

template < class char_type >
constexpr basic_string<char_type>& basic_string<char_type>::operator = ( basic_string&& right )
{
    std::swap ( m,        right.m        );
    std::swap ( internal, right.internal );
    std::swap ( external, right.external );
    return self;
}

template < class char_type >
constexpr basic_string<char_type>& basic_string<char_type>::operator = ( const basic_string_range_view<char_type>& right )
{
    resize ( right.size() );
    std::copy ( right.begin(), right.end(), size() <= sso ? internal otherwise external );
    return self;
}

template < class char_type >
constexpr basic_string<char_type>& basic_string<char_type>::operator = ( const basic_string_view<char_type>& right )
{
    resize ( right.size() );
    std::copy ( right.begin(), right.end(), size() <= sso ? internal otherwise external );
    return self;
}

template < class char_type >
constexpr basic_string<char_type>& basic_string<char_type>::operator = ( std::same_as<char_type> auto right )
{
    self.resize ( 1 );
    self[1] = right;
    return self;
}

template < class char_type >
constexpr basic_string<char_type>& basic_string<char_type>::operator = ( const char_type* right )
{
    return self = basic_string_view<char_type> ( right );
}


// Conversion

template < class char_type >
template < class char_type2 >
constexpr basic_string<char_type>::basic_string ( const basic_string<char_type2>& cvt )
{
    try
    {
        let converter = std::filesystem::path(cvt.c_str());

        if constexpr ( std::is_same<char_type,char>::value )
            self = basic_string(converter.string());
        else if constexpr ( std::is_same<char_type,wchar_t>::value )
            self = basic_string(converter.wstring());
        else if constexpr ( std::is_same<char_type,char8_t>::value )
            self = basic_string(converter.u8string());
        else if constexpr ( std::is_same<char_type,char16_t>::value )
            self = basic_string(converter.u16string());
        else if constexpr ( std::is_same<char_type,char32_t>::value )
            self = basic_string(converter.u32string());
        else
            static_assert(false, "unknown encoding");
    }
    catch ( const std::filesystem::filesystem_error& /*ignored*/ )
    {
        throw encode_error("cannot encode string {} from {} into {} (bytes = {:03d})",
                           cvt, typeid(char_type2), typeid(char_type),
                           vector<int>(cvt.size() * sizeof(char_type2), [&] (int i) -> unsigned char { return reinterpret_cast<const char*>(cvt.begin())[i-1]; }));
    }
}

template < class char_type >
template < class char_type2 >
constexpr basic_string<char_type>::operator basic_string<char_type2> ( ) const
{
    return self[1,-1].operator basic_string<char_type2>();  // Also can be done in string_view.
}

template < class char_type >
template < class bool_type >
constexpr basic_string<char_type>::basic_string ( const bool_type& cvt )
    requires std::same_as<char_type,char> and
             std::same_as<bool_type,bool>
{
    self = cvt ? "true" otherwise "false";
}

template < class char_type >
template < class bool_type >
constexpr basic_string<char_type>::operator bool_type ( ) const
    requires std::same_as<char_type,char> and
             std::same_as<bool_type,bool>
{
    return self[1,-1].operator bool_type(); // Also can be done in string_view.
}

template < class char_type >
template < class number_type >
constexpr basic_string<char_type>::basic_string ( const number_type& cvt )
    requires std::same_as<char_type,char> and
             ( not std::is_convertible<number_type,basic_string>::value ) and
             ( not general_string_type<number_type> ) and
             ( not std::same_as<number_type,bool> ) and
             ( std::integral<number_type> or std::floating_point<number_type> )
{
    resize ( 64 );
    auto [p,ec] = std::to_chars ( begin(), end(), cvt );
    if ( ec != std::errc() )
        throw encode_error("cannot convert {} into {}", cvt, typeid(self));
    resize ( p - begin() );
}

template < class char_type >
template < class number_type >
constexpr basic_string<char_type>::operator number_type ( ) const
    requires std::same_as<char_type,char> and
             ( not std::is_convertible<basic_string,number_type>::value ) and
             ( not general_string_type<number_type> ) and
             ( not std::same_as<number_type,bool> ) and
             ( std::integral<number_type> or std::floating_point<number_type> )
{
    return self[1,-1].operator number_type(); // Also can be done in string_view.
}

template < class char_type >
template < class printable >
constexpr basic_string<char_type>::basic_string ( const printable& cvt )
    requires std::same_as<char_type,char> and
             ( not std::is_convertible<printable,basic_string>::value ) and
             ( not general_string_type<printable> ) and
             ( not std::same_as<printable,bool> ) and
             ( not ( std::integral<printable> or std::floating_point<printable> ) ) and
             ap::printable<printable>
{
    let stream = std::stringstream(); // Not std::basic_stringstream, as the concept "printable" only requires std::ostream.
    stream << cvt;
    stream >> self;
    if ( not stream.eof() and stream.fail() ) // Not until the stream reaches end, that the stream fails.
        throw encode_error("cannot convert {} into {}", cvt, typeid(self));
}

template < class char_type >
template < class inputable >
constexpr basic_string<char_type>::operator inputable ( ) const
    requires std::same_as<char_type,char> and
             ( not std::is_convertible<basic_string,inputable>::value ) and
             ( not general_string_type<inputable> ) and
             ( not std::same_as<inputable,bool> ) and
             ( not ( std::integral<inputable> or std::floating_point<inputable> ) ) and
             ap::inputable<inputable>
{
    return self[1,-1].operator inputable(); // Also can be done in string_view.
}

template < class char_type >
constexpr basic_string<char_type>::basic_string ( const std::basic_string<char_type>& cvt )
{
    resize ( cvt.size() );
    std::copy ( cvt.begin(), cvt.end(), begin() );
}

template < class char_type >
constexpr basic_string<char_type>::operator std::basic_string<char_type> ( ) const
{
    return self[1,-1].operator std::basic_string<char_type>(); // Also can be done in string_view.
}

template < class char_type >
constexpr basic_string<char_type>::basic_string ( const std::basic_string_view<char_type>& cvt )
{
    resize ( cvt.size() );
    std::copy ( cvt.begin(), cvt.end(), begin() );
}

template < class char_type >
constexpr basic_string<char_type>::operator std::basic_string_view<char_type> ( ) const
{
    return self[1,-1].operator std::basic_string_view<char_type>(); // Also can be done in string_view.
}

template < class char_type >
constexpr basic_string<char_type>::basic_string ( const std::type_info& cvt )
    extends basic_string ( abi::demangle(cvt.name()) )
{

}

// Interface

template < class char_type >
constexpr int basic_string<char_type>::size ( ) const
{
    return m;
}

template < class char_type >
constexpr basic_string<char_type>& basic_string<char_type>::resize ( int new_size )
{
    #if debug
        if ( new_size < 0 )
            throw value_error("initialize string with negative size {}", new_size);
    #endif

    if ( capacity(size()) != capacity(new_size) ) // Needs new allocation.
    {
        let tmp = basic_string ( new_size, char_type(' ') );

        std::copy ( begin(), begin() + std::min ( size(), tmp.size() ), tmp.begin() );
        std::swap ( self.m,        tmp.m        );
        std::swap ( self.internal, tmp.internal );
        std::swap ( self.external, tmp.external );
    }

    else // Reuse allocated memory.
    {
        if ( new_size < size() )
            std::fill ( begin() + new_size, begin() + size(), char_type() );

        m = new_size;
    }

    return self;
}

template < class char_type >
constexpr bool basic_string<char_type>::empty ( ) const
{
    return size() == 0;
}

template < class char_type >
constexpr char_type* basic_string<char_type>::data ( )
{
    return size() <= sso ? internal otherwise external;
}

template < class char_type >
constexpr const char_type* basic_string<char_type>::data ( ) const
{
    return size() <= sso ? internal otherwise external;
}

template < class char_type >
constexpr char_type* basic_string<char_type>::begin ( )
{
    return size() <= sso ? internal otherwise external;
}

template < class char_type >
constexpr const char_type* basic_string<char_type>::begin ( ) const
{
    return size() <= sso ? internal otherwise external;
}

template < class char_type >
constexpr char_type* basic_string<char_type>::end ( )
{
    return size() <= sso ? internal + size() otherwise external + size();
}

template < class char_type >
constexpr const char_type* basic_string<char_type>::end ( ) const
{
    return size() <= sso ? internal + size() otherwise external + size();
}

template < class char_type >
constexpr char_type& basic_string<char_type>::operator [] ( int pos )
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    if ( size() <= sso )
        return internal [ pos > 0 ? pos - 1 otherwise pos + size() ];
    else
        return external [ pos > 0 ? pos - 1 otherwise pos + size() ];
}

template < class char_type >
constexpr const char_type& basic_string<char_type>::operator [] ( int pos ) const
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    if ( size() <= sso )
        return internal [ pos > 0 ? pos - 1 otherwise pos + size() ];
    else
        return external [ pos > 0 ? pos - 1 otherwise pos + size() ];
}

template < class char_type >
constexpr auto basic_string<char_type>::operator [] ( int from, int to )
{
    return basic_string_range_view<char_type> ( self, from, to );
}

template < class char_type >
constexpr const auto basic_string<char_type>::operator [] ( int from, int to ) const
{
    return basic_string_range_view<char_type> ( const_cast<basic_string&>(self), from, to );
}




// C-style

template < class char_type >
constexpr const char_type* basic_string<char_type>::c_str ( ) const
{
    return size() <= sso ? internal otherwise external;
}


// Auxiliary

template < class char_type >
constexpr char_type* basic_string<char_type>::allocate ( int len )
{
    #if debug
        if ( len < 0 )
            throw value_error();
    #endif

    int cap = sso + 1;
    while ( cap < len + 1 )
        cap *= 2;

    return new char_type[cap] {};
}

template < class char_type >
constexpr void basic_string<char_type>::deallocate ( char_type* addr )
{
    delete[] addr;
}

template < class char_type >
constexpr int basic_string<char_type>::capacity ( int len )
{
    if ( len == 0 )
        return 0;

    int cap = sso + 1;
    while ( cap < len + 1 )
        cap *= 2;

    return cap;
}