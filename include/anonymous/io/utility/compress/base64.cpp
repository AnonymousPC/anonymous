#pragma once

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr ranges::encode_base64_view<range>::encode_base64_view ( range init_r )
    extends r ( std::move(init_r) )
{

}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr auto ranges::encode_base64_view<range>::begin ( )
{
    return iterator(self);
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr auto ranges::encode_base64_view<range>::end ( )
{
    return std::default_sentinel;
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr auto ranges::encode_base64_view<range>::size ( ) const
    requires std::ranges::sized_range<range>
{
    return (std::ranges::size(r) + 2) / 3 * 4;
}

template < input_range range >
    requires same_as<range_value<range>,char>
class ranges::encode_base64_view<range>::iterator 
{
    private: // Data
        range_iterator<range> i = range_iterator<range>(); // Iterator.
        range_sentinel<range> s = range_sentinel<range>(); // Sentinel.
        uint16_t              c = 0;                       // Cache.
        int8_t                b = 0;                       // Available ascii-bits, 8-bits per ascii-char. When it becomes >= 6, a 6-bit base64-char is available.
        int                   t = 0;                       // Total size we had encoded to output, as we should append '=' if output.size() % 4 != 0.

    public: // Typedef
        using iterator_concept  = std::input_iterator_tag;
     // using iterator_category = not supported; 
        using value_type        = char;
        using difference_type   = std::ptrdiff_t;

    public: // Interface
        constexpr iterator ( ) = default;
        constexpr iterator ( encode_base64_view& );
        constexpr char      operator *  ( )                         const;
        constexpr bool      operator == ( std::default_sentinel_t ) const;
        constexpr iterator& operator ++ ( );
        constexpr iterator  operator ++ ( int );

    private: // Detail
        constexpr static uint8_t mapping ( uint8_t );
};

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr ranges::encode_base64_view<range>::iterator::iterator ( encode_base64_view& v )
    extends i ( v.r.begin() ),
            s ( v.r.end  () )
{
    c |= uint8_t(*i); // At the beginning, we read 1 ascii-char.
    b += 8;           // As a result, we have 8 available ascii-bits.
    i ++;             // Step input iterator into next one.
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr char ranges::encode_base64_view<range>::iterator::operator * ( ) const
{
    if ( i != s ) [[likely]]                               // If input is readable...
        return mapping((c >> (b - 6))       & 0b00111111); // Then extract 6 ascii-bits on the left of c and mapping into base64. For example, if we have 8 available ascii-bits in c, then we should return (c >> 2) -> base64.
    else if ( b > 0 )                                      // If input is exhausted, and we still have available bits...
        return mapping((c << (12 - b) >> 6) & 0b00111111); // Then extrace 6 ascii-bits (with 0 right-filled) and mapping into bae64. For example, if 8 ascii-bits available then return (c >> 2) -> base64, if 4 bits available then return (c << 2) -> base64, 
    else                                                   // If nothing is encodable...
        return '=';                                        // We still need to fill '=' to make output.size() % 4 == 0.
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr bool ranges::encode_base64_view<range>::iterator::operator == ( std::default_sentinel_t ) const
{
    return i == s and b <= 0 and t % 4 == 0; // Input is exhausted, no cached bits, and output.size() % 4 == 0.
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr ranges::encode_base64_view<range>::iterator& ranges::encode_base64_view<range>::iterator::operator ++ ( )
{  
    b -= 6;                            // Consume 6 ascii-bits into output as the input steps.
    if ( b < 6 and i != s ) [[likely]] // If there are less than 6 ascii-bits, then we need to read a new ascii-char (if possible).
    {
        c <<= 8;                       // Prepare space for 8 ascii-bit.
        c |= uint8_t(*i);              // Read a new ascii-char (8 ascii-bit) from the input. The new ascii-char is pushed into c on the right.
        b += 8;                        // We now have 8 more available ascii-bits.
        i ++;                          // Step input into next one.
    }
    t++;                               // Refresh the total base64-size we have encoded to output.
    return self;
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr ranges::encode_base64_view<range>::iterator ranges::encode_base64_view<range>::iterator::operator ++ ( int )
{
    auto it = self;
    ++self;
    return it;
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr uint8_t ranges::encode_base64_view<range>::iterator::mapping ( uint8_t c )
{
    constexpr static const char* alphabet =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    return alphabet[c];
}

constexpr auto views::encode_base64_t::operator() ( input_range auto&& r ) const
    requires same_as<range_value<decltype(r)>,char>
{
    return ranges::encode_base64_view(std::forward<decltype(r)>(r));
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr ranges::decode_base64_view<range>::decode_base64_view ( range init_r )
    extends r ( std::move(init_r) )
{
    
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr auto ranges::decode_base64_view<range>::begin ( )
{
    return iterator(self);
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr auto ranges::decode_base64_view<range>::end ( )
{
    return std::default_sentinel;
}

template < input_range range >
    requires same_as<range_value<range>,char>
class ranges::decode_base64_view<range>::iterator
{
    private: // Data
        range_iterator<range> i = range_iterator<range>(); // Iterator.
        range_sentinel<range> s = range_sentinel<range>(); // Sentinel.
        uint16_t              c = 0;                       // Cache.
        int8_t                b = 0;                       // Available ascii-bits, 6-bits per base64-char. When it becomes >= 8, a 8-bit ascii-char is available.
        bool                  e = false;                   // Whether we reach the end.

    public: // Typedef
        using iterator_concept  = std::input_iterator_tag;
     // using iterator_category = not supported; 
        using value_type        = char;
        using difference_type   = std::ptrdiff_t;

    public: // Interface
        constexpr iterator ( ) = default;
        constexpr iterator ( decode_base64_view& );
        constexpr char      operator *  ( )                         const;
        constexpr bool      operator == ( std::default_sentinel_t ) const;
        constexpr iterator& operator ++ ( );
        constexpr iterator  operator ++ ( int );

    private: // Detail
        constexpr static uint8_t mapping ( uint8_t );
};

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr ranges::decode_base64_view<range>::iterator::iterator ( decode_base64_view& v )
    extends i ( v.r.begin() ),
            s ( v.r.end  () )
{
    /** BUG: 0 length input **/

    c |= mapping(uint8_t(*  i)) << 6; // At the beginning, we read 2 base64-char.
    c |= mapping(uint8_t(*++i));      // Continue...
    b += 12;                          // As a result, we have 12 available ascii-bits.
    i ++;                             // Step input iterator into next one.
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr char ranges::decode_base64_view<range>::iterator::operator * ( ) const
{
    return c >> (b - 8); // Then extract 8 ascii-bits on the left of c. For example, if we have 12 available ascii-bits in c, then we should return c >> 4.
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr bool ranges::decode_base64_view<range>::iterator::operator == ( std::default_sentinel_t ) const
{
    return i == s and b < 8; // Input is exhausted, or cached bits is less than a ascii-char.
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr ranges::decode_base64_view<range>::iterator& ranges::decode_base64_view<range>::iterator::operator ++ ( )
{
    b -= 8;                                               // Consume 8 ascii-bits into output as the input steps.
    while ( b < 8 and i != s and (*i) != '=' ) [[likely]] // If there are less than 8 ascii-bits, then we need to read one/two new base64-char (if possible).
    {
        c <<= 6;                                          // Prepare space for 6 ascii-bit.
        c |= mapping(uint8_t(*i));                        // Read a new base64-char (6 ascii-bit) from the input. The new ascii-char is pushed into c on the right.
        b += 6;                                           // We now have 8 more available ascii-bits.
        i ++;                                             // Step input into next one.
    }
    
    return self;
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr ranges::decode_base64_view<range>::iterator ranges::decode_base64_view<range>::iterator::operator ++ ( int )
{
    auto it = self;
    ++self;
    return it;
}

template < input_range range >  
    requires same_as<range_value<range>,char>
constexpr uint8_t ranges::decode_base64_view<range>::iterator::mapping ( uint8_t c )
{
    return c >= 'A' and c <= 'Z' ?  0 + c - 'A' : 
           c >= 'a' and c <= 'z' ? 26 + c - 'a' :
           c >= '0' and c <= '9' ? 52 + c - '0' :
           c == '+'              ? 62           :
           c == '/'              ? 63           :
                                   throw encode_error("failed to decode base64: illegal character (with character = {}, ascii = {}, requirement = [A-Za-z0-9+/])",  char(c), uint8_t(c));
}

constexpr auto views::decode_base64_t::operator() ( input_range auto&& r ) const
    requires same_as<range_value<decltype(r)>,char>
{
    return ranges::decode_base64_view(std::forward<decltype(r)>(r));
}