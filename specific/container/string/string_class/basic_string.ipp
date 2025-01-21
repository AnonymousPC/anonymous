#pragma once

template < class type, class device >
constexpr basic_string<type,device>::basic_string ( type init )
    extends base ( 1, init )
{
    
}

template < class type, class device >
constexpr basic_string<type,device>::basic_string ( int init_size, type init_char )
    extends base ( init_size, init_char )
{
    
}

template < class type, class device >
constexpr basic_string<type,device>::basic_string ( const type* init )
    extends base ( init )
{
    
}

template < class type, class device >
constexpr basic_string<type,device>::basic_string ( string_view cvt )
    extends base ( cvt.data(), cvt.size() )
{

}

template < class type, class device >
constexpr basic_string<type,device>::operator string_view ( ) const
{
    return string_view(data(), size());
}

template < class type, class device >
template < char_type type2 >
constexpr basic_string<type,device>::basic_string ( const basic_string<type2,device>& cvt )
{
    try
    {
        let converter = std::filesystem::path(cvt.c_str());

        if constexpr ( same_as<type,char> )
            self.base::operator=(converter.string());
        else if constexpr ( same_as<type,wchar_t> )
            self.base::operator=(converter.wstring());
        else if constexpr ( same_as<type,char8_t> )
            self.base::operator=(converter.u8string());
        else if constexpr ( same_as<type,char16_t> )
            self.base::operator=(converter.u16string());
        else if constexpr ( same_as<type,char32_t> )
            self.base::operator=(converter.u32string());
        else
            static_assert(false, "unknown encoding");
    }
    catch ( const std::filesystem::filesystem_error& /*unused*/ )
    {
        throw encode_error("cannot encode string \"{}\" from {} into {}", cvt, typeid(type2), typeid(type));
    }
}

template < class type, class device >
template < char_type type2 >
constexpr basic_string<type,device>::basic_string ( const basic_string_view<type2,device>& cvt )
{
    try
    {
        let converter = std::filesystem::path(cvt.begin(), cvt.end());

        if constexpr ( same_as<type,char> )
            self.base::operator=(converter.string());
        else if constexpr ( same_as<type,wchar_t> )
            self.base::operator=(converter.wstring());
        else if constexpr ( same_as<type,char8_t> )
            self.base::operator=(converter.u8string());
        else if constexpr ( same_as<type,char16_t> )
            self.base::operator=(converter.u16string());
        else if constexpr ( same_as<type,char32_t> )
            self.base::operator=(converter.u32string());
        else
            static_assert(false, "unknown encoding");
    }
    catch ( const std::filesystem::filesystem_error& /*unused*/ )
    {
        throw encode_error("cannot encode string \"{}\" from {} into {}", cvt, typeid(type2), typeid(type));
    }
}

template < class type, class device >
template < class device2 >
constexpr basic_string<type,device>::basic_string ( const basic_string<type,device2>& cvt )
    requires same_as<device,cpu> or same_as<device2,cpu>
    extends basic_string ( cvt.size(), '\0' )
{
    if constexpr ( not same_as<device,cpu> )
        device::copy(cvt.begin(), cvt.end(), begin());
    else
        device2::copy(cvt.begin(), cvt.end(), begin());
}

template < class type, class device >
template < class device2 >
constexpr basic_string<type,device>::basic_string ( const basic_string_view<type,device2>& cvt )
    requires same_as<device,cpu> or same_as<device2,cpu>
    extends basic_string ( cvt.size(), '\0' )
{
    if constexpr ( not same_as<device,cpu> )
        device::copy(cvt.begin(), cvt.end(), begin());
    else
        device2::copy(cvt.begin(), cvt.end(), begin());
}

template < class type, class device >
constexpr basic_string<type,device>::basic_string ( const bool& cvt )
    requires same_as<type,char>
    extends basic_string ( cvt ? "true" otherwise "false" ) 
{
    
}

template < class type, class device >
constexpr basic_string<type,device>::operator bool ( ) const
    requires same_as<type,char>
{
    return self == "true"  ? true  otherwise
           self == "false" ? false otherwise
                             throw value_error("cannot convert \"{}\" from {} into {}", self, typeid(self), typeid(bool));
}

template < class type, class device >
template < number_type type2 > 
constexpr basic_string<type,device>::basic_string ( const type2& cvt )
    requires same_as<type,char>
{
    resize(64);
    auto [p, ec] = std::to_chars ( begin(), end(), cvt );
    if ( ec != std::errc() )
        throw value_error("cannot convert {} from {} into {}", cvt, typeid(cvt), typeid(self));
    resize(p - begin());
}

template < class type, class device >
template < number_type type2 >
constexpr basic_string<type,device>::operator type2 ( ) const
    requires same_as<type,char>
{
    let cvt = type2();
    auto [p, ec] = std::from_chars ( begin(), end(), cvt );
    if ( p != end() or ec != std::errc() )
        throw value_error("cannot convert \"{}\" from {} into {}", self, typeid(self), typeid(cvt));
    return cvt;
}

template < class type, class device >
template < printable type2 >
constexpr basic_string<type,device>::basic_string ( const type2& cvt )
    requires same_as<type,char> and 
             ( not number_type<type2> ) and
             ( not string_type<type2> )
{
    let stream = std::stringstream();
    stream << cvt;
    self.base::operator=(stream.str());
}

template < class type, class device >
template < inputable type2 >
constexpr basic_string<type,device>::operator type2 ( ) const
    requires same_as<type,char> and 
             ( not number_type<type2> ) and
             ( not string_type<type2> )
{
    let cvt = type2();
    let stream = std::stringstream();
    stream << self;
    stream >> cvt;
    if ( not stream.eof() and stream.fail() ) // Not until the stream reaches end, that the stream fails.
        throw value_error("cannot convert \"{}\" from {} into {}", self, typeid(self), typeid(cvt));
}

template < class type, class device >
constexpr basic_string<type,device>::basic_string ( const std::type_info& cvt )
    requires same_as<type,char>
    extends base ( demangle(cvt) )
{
    
}

template < class type, class device >
constexpr int basic_string<type,device>::size ( ) const
{
    return base::size();
}

template < class type, class device >
constexpr basic_string<type,device>& basic_string<type,device>::resize ( int new_size )
{
    base::resize(new_size);
    return self;
}

template < class type, class device >
constexpr bool basic_string<type,device>::empty ( ) const
{
    return base::empty();
}

template < class type, class device >
constexpr basic_string<type,device>::iterator basic_string<type,device>::begin ( )
{
    return base::begin();
}

template < class type, class device >
constexpr basic_string<type,device>::const_iterator basic_string<type,device>::begin ( ) const
{
    return base::begin();
}

template < class type, class device >
constexpr basic_string<type,device>::iterator basic_string<type,device>::end ( )
{
    return base::end();
}

template < class type, class device >
constexpr basic_string<type,device>::const_iterator basic_string<type,device>::end ( ) const
{
    return base::end();
}  

template < class type, class device >
constexpr basic_string<type,device>::pointer basic_string<type,device>::data ( )
{
    return base::data();
}

template < class type, class device >
constexpr basic_string<type,device>::const_pointer basic_string<type,device>::data ( ) const
{
    return base::data();
}

template < class type, class device >
constexpr basic_string<type,device>::const_pointer basic_string<type,device>::c_str ( ) const
{
    return base::c_str();
}

template < class type, class device >
constexpr basic_string<type,device>::reference basic_string<type,device>::operator[] ( int pos )
{
    #if debug
    if ( pos < -size() or pos == 0 or pos > size() )
        throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    return base::operator[](pos >= 0 ? pos - 1 otherwise pos+size());
}

template < class type, class device >
constexpr basic_string<type,device>::const_reference basic_string<type,device>::operator[] ( int pos ) const
{
    #if debug
    if ( pos < -size() or pos == 0 or pos > size() )
        throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    return base::operator[](pos >= 0 ? pos - 1 otherwise pos + size());
}   

template < class type, class device >
constexpr basic_string<type,device>::string_view basic_string<type,device>::operator[] ( int pos_1, int pos_2 ) const
{
    let abs_pos_1 = pos_1 >= 0 ? pos_1 otherwise pos_1 + size();
    let abs_pos_2 = pos_2 >= 0 ? pos_2 otherwise pos_2 + size();

    #if debug
    if ( ( ( abs_pos_1 < 1 or abs_pos_1 > size() ) or
           ( abs_pos_2 < 1 or abs_pos_2 > size() ) )
    and not // Except for below:
         ( ( abs_pos_1 == size() + 1 or abs_pos_2 == 0 ) and abs_pos_1 == abs_pos_2 + 1 ) )
        throw index_error("index [{}, {}] is out of range with size {}", pos_1, pos_2, size());
    #endif

    return string_view(data() + abs_pos_1 - 1, abs_pos_2 - abs_pos_1 + 1);
}

template < class type, class device >
constexpr basic_string<type,device>& basic_string<type,device>::clear ( )
{
    base::clear();
    return self;
}

template < class type, class device >
constexpr basic_string<type,device>& basic_string<type,device>::erase ( int old_pos_1, int old_pos_2 )
{
    let abs_pos_1 = old_pos_1 >= 0 ? old_pos_1 otherwise old_pos_1 + size();
    let abs_pos_2 = old_pos_2 >= 0 ? old_pos_2 otherwise old_pos_2 + size();

    #if debug
    if ( ( ( abs_pos_1 < 1 or abs_pos_1 > size() ) or
           ( abs_pos_2 < 1 or abs_pos_2 > size() ) )
    and not // Except for below:
         ( ( abs_pos_1 == size() + 1 or abs_pos_2 == 0 ) and abs_pos_1 == abs_pos_2 + 1 ) )
        throw index_error("index [{}, {}] is out of range with size {}", old_pos_1, old_pos_2, size());
    #endif

    base::erase(abs_pos_1 - 1, abs_pos_2 - abs_pos_1 + 1);
    return self;
}

template < class type, class device >
constexpr basic_string<type,device>& basic_string<type,device>::insert ( int new_pos, string_view new_value )
{
    #if debug
    if ( new_pos < -size() or new_pos == 0 or new_pos > size() )
        throw index_error("index {} is out of range with size {}", new_pos, size());
    #endif
    base::insert(new_pos >= 0 ? new_pos - 1 otherwise new_pos + size(), new_value.data(), new_value.size());
    return self;
}

template < class type, class device >
constexpr basic_string<type,device>& basic_string<type,device>::push ( string_view new_value )
{
    base::append(new_value.data(), new_value.size());
    return self;
}

template < class type, class device >
constexpr basic_string<type,device>& basic_string<type,device>::pop ( int old_pos )
{
    #if debug
    if ( old_pos < -size() or old_pos == 0 or old_pos > size() )
        throw index_error("index {} is out of range with size {}", old_pos, size());
    #endif
    base::erase(old_pos >= 0 ? old_pos - 1 otherwise old_pos + size(), 1);
    return self;
}

template < class type, class device >
constexpr bool basic_string<type,device>::ownership ( )
{
    return true;
}
