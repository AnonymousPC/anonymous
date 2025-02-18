#pragma once

template < class range >
    requires input_range<range> and 
             same_as<range_value<range>,char>
constexpr ranges::encode_base64_view<range>::encode_base64_view ( range init_r )
    extends r ( std::move(init_r) )
{

}

template  < class range >
    requires input_range<range> and 
             same_as<range_value<range>,char>
constexpr auto ranges::encode_base64_view<range>::begin ( ) const
{
    return iterator(self);
}

template < class range >
    requires input_range<range> and 
             same_as<range_value<range>,char>
constexpr auto ranges::encode_base64_view<range>::end ( ) const
{
    return std::default_sentinel;
}

template < class range >
    requires input_range<range> and 
             same_as<range_value<range>,char>
constexpr auto ranges::encode_base64_view<range>::size ( ) const
    requires std::ranges::sized_range<range>
{
    return (std::ranges::size(r) + 2) / 3 * 4;
}

template < class range >
    requires input_range<range> and 
             same_as<range_value<range>,char>
struct ranges::encode_base64_view<range>::iterator 
{
    private: // Data
        range_const_iterator<range> i = range_const_iterator<range>(); // Iterator.
        range_const_sentinel<range> s = range_const_sentinel<range>(); // Sentinel.
        int                         c = 0;                             // Current char.
        int                         b = 0;                             // Available bits, 8-bits per input char. When it becomes >= 6, a 6-bit base64-letter is available.
        bool                        e = false;                         // Whether we reach the end.
        int                         t = 0;                             // Total size we had encoded to output. we should append '=' if output.size() % 4 != 0.

    public: // Typedef
        using iterator_concept = std::input_iterator_tag;
        using value_type       = char;
        using difference_type  = std::ptrdiff_t;

    public: // Interface
        constexpr iterator ( ) = default;
        constexpr iterator ( const encode_base64_view& );
        constexpr char      operator *  ( )                         const;
        constexpr bool      operator == ( std::default_sentinel_t ) const;
        constexpr iterator& operator ++ ( );
        constexpr iterator  operator ++ ( int );
};

template < class range >
    requires input_range<range> and 
             same_as<range_value<range>,char>
constexpr ranges::encode_base64_view<range>::iterator::iterator ( const encode_base64_view& init_v )
    extends i ( const_cast<encode_base64_view&>(init_v).r.begin() ),
            s ( const_cast<encode_base64_view&>(init_v).r.end() )
{

}

template < class range >
    requires input_range<range> and 
             same_as<range_value<range>,char>
constexpr char ranges::encode_base64_view<range>::iterator::operator * ( ) const
{
    constexpr static const char* alphabet =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    if ( i != s ) [[likely]]
        return alphabet[((c >> b) & 0x3F)];
    else if ( b > -6 )
        return alphabet[(((c << 8) >> (b + 8)) & 0x3F)];
    else
        return '=';
}

template < class range >
    requires input_range<range> and 
             same_as<range_value<range>,char>
constexpr bool ranges::encode_base64_view<range>::iterator::operator == ( std::default_sentinel_t ) const
{
    return i == s and b == -6 and t % 4 == 0;
}

template < class range >
    requires input_range<range> and 
             same_as<range_value<range>,char>
constexpr ranges::encode_base64_view<range>::iterator& ranges::encode_base64_view<range>::iterator::operator++ ( )
{
    t++;
    if ( i != s ) [[likely]]
        if ( b >= 0 )
            b -= 6;
        else
        {
            c = (c << 8) + *i;
            b += 8;
            ++i;
        }
    else
        if ( b > -6 )
            b = -6;

    return self;
}

template < class range >
    requires input_range<range> and 
             same_as<range_value<range>,char>
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
