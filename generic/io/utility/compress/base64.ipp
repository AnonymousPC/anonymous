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
struct ranges::encode_base64_view<range>::iterator 
{
    private: // Data
        range_iterator<range> i = range_iterator<range>(); // Iterator.
        range_sentinel<range> s = range_sentinel<range>(); // Sentinel.
        uint32_t              c = 0;                       // Current char.
        int                   b = 0;                       // Available bits, 8-bits per input char. When it becomes >= 6, a 6-bit base64-letter is available.
        bool                  e = false;                   // Whether we reach the end.
        int                   t = 0;                       // Total size we had encoded to output. we should append '=' if output.size() % 4 != 0.

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
};

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr ranges::encode_base64_view<range>::iterator::iterator ( encode_base64_view& init_v )
    extends i ( init_v.r.begin() ),
            s ( init_v.r.end() )
{
    ++self;
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr char ranges::encode_base64_view<range>::iterator::operator * ( ) const
{
    constexpr static const char* alphabet =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    if ( i != s ) [[likely]]
        return alphabet[(c >> b) & 0x3F];
    else if ( b > -6 )
        return alphabet[((c << 8) >> (b + 8)) & 0x3F];
    else
        return '=';
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr bool ranges::encode_base64_view<range>::iterator::operator == ( std::default_sentinel_t ) const
{
    // Notice when t % 4 == 0, the (last) char is stil valid, and we should run until t % 4 == 1 no notify the sentinel.
    return i == s and b <= -6 and t % 4 == 1;
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr ranges::encode_base64_view<range>::iterator& ranges::encode_base64_view<range>::iterator::operator++ ( )
{  
    if ( i != s and b < 6 ) [[likely]] // If there are less 6 bits, we need to read a new char.
    {
        c = (c << 8) + uint8_t(*i);    // We read a new char (8 bit) from the input. It is pushed into 'c' on the right.
        i ++;                          // Step input iterator into next one.
        b += 8;                        // We now have 8 more available bits.
    }
    b -= 6;                            // Now, we consume 6 bits into output as the iterator steps.
    t++;

    return self;
}

template < input_range range >
    requires same_as<range_value<range>,char>
constexpr ranges::encode_base64_view<range>::iterator ranges::encode_base64_view<range>::iterator::operator++ ( int )
{
    let it = self;
    ++self;
    return it;
}

constexpr auto views::encode_base64_t::operator() ( input_range auto&& r ) const
    requires same_as<range_value<decltype(r)>,char>
{
    return ranges::encode_base64_view(std::forward<decltype(r)>(r));
}
