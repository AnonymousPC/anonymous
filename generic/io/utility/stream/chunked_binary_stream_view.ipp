#pragma once

/// Class chunked_binary_istream_view

// Interface

template < class stream_type, class input_type, std::endian endian >
constexpr ranges::chunked_binary_istream_view<stream_type,input_type,endian>::chunked_binary_istream_view ( stream_type& init_s, int chunk_len )
    extends s_ptr ( &init_s ),
            buff  ( chunk_len )
{

}

template < class stream_type, class input_type, std::endian endian >
constexpr auto ranges::chunked_binary_istream_view<stream_type,input_type,endian>::begin ( )
{
    return ++iterator(self);
}

template < class stream_type, class input_type, std::endian endian >
constexpr auto ranges::chunked_binary_istream_view<stream_type,input_type,endian>::end ( )
{
    return std::default_sentinel;
}




/// Class chunked_binary_istream_view::iterator

template < class stream_type, class input_type, std::endian endian >
class ranges::chunked_binary_istream_view<stream_type,input_type,endian>::iterator
{
    public: // Typedef
        using iterator_concept = std::input_iterator_tag;
        using value_type       = vector<input_type>;
        using difference_type  = std::ptrdiff_t;

    private: // Data
        chunked_binary_istream_view* v_ptr = nullptr;

    public: // Interface
        constexpr iterator ( chunked_binary_istream_view& );
        constexpr value_type& operator *  ( ) const;
        constexpr iterator&   operator ++ ( );
        constexpr iterator&   operator ++ ( int );
        constexpr bool        operator == ( std::default_sentinel_t ) const;
};


template < class stream_type, class input_type, std::endian endian >
constexpr ranges::chunked_binary_istream_view<stream_type,input_type,endian>::iterator::iterator ( chunked_binary_istream_view& init_v )
    extends v_ptr ( &init_v )
{

}

template < class stream_type, class input_type, std::endian endian >
constexpr ranges::chunked_binary_istream_view<stream_type,input_type,endian>::iterator::value_type& ranges::chunked_binary_istream_view<stream_type,input_type,endian>::iterator::operator * ( ) const
{
    return v_ptr->buff;
}

template < class stream_type, class input_type, std::endian endian >
constexpr ranges::chunked_binary_istream_view<stream_type,input_type,endian>::iterator& ranges::chunked_binary_istream_view<stream_type,input_type,endian>::iterator::operator ++ ( )
{
    v_ptr->s_ptr->read(reinterpret_cast<char*>(v_ptr->buff.begin()), v_ptr->buff.size() * sizeof(input_type));

    if constexpr ( aux::requires_byteswap<endian,input_type> )
        v_ptr->buff.each([] (auto& val) { aux::byteswap(val); });

    return self;
}

template < class stream_type, class input_type, std::endian endian >
constexpr ranges::chunked_binary_istream_view<stream_type,input_type,endian>::iterator& ranges::chunked_binary_istream_view<stream_type,input_type,endian>::iterator::operator ++ ( int )
{
    v_ptr->s_ptr->read(reinterpret_cast<char*>(v_ptr->buff.begin()), v_ptr->buff.size() * sizeof(input_type));

    if constexpr ( aux::requires_byteswap<endian,input_type> )
        v_ptr->buff.each([] (auto& val) { aux::byteswap(val); });

    return self;
}

template < class stream_type, class input_type, std::endian endian >
constexpr bool ranges::chunked_binary_istream_view<stream_type,input_type,endian>::iterator::operator == ( std::default_sentinel_t ) const
{
    return v_ptr->s_ptr->eof();
}














/// Class chunked_binary_ostream_view

// Interface

template < class stream_type, class output_type, std::endian endian >
constexpr ranges::chunked_binary_ostream_view<stream_type,output_type,endian>::chunked_binary_ostream_view ( std::from_range_t, std::ranges::input_range auto&& r, stream_type& s, int chunk_len )
    requires std::same_as<output_type,decay<decltype(*(*r.begin()).begin())>>
{
    let buff = vector<output_type>(chunk_len);

    for ( auto&& t in r )
    {
        std::ranges::move(t, buff.begin());

        if constexpr ( aux::requires_byteswap<endian,output_type> )
            buff.each([] (auto& val) { aux::byteswap(val); });

        s.write(reinterpret_cast<const char*>(buff.begin()), buff.size() * sizeof(output_type));
    }
}






/// Views

template < class input_type, std::endian endian >
constexpr auto views::chunked_binary_istream ( auto& /*stream_type*/ s, int chunk_len )
    requires requires ( input_type t ) { s.read(reinterpret_cast<char*>(&t), sizeof(input_type)); }
{
    return ranges::chunked_binary_istream_view<decay<decltype(s)>,input_type,endian>(s, chunk_len);
}

template < class output_type, std::endian endian >
constexpr views::chunked_binary_ostream<output_type,endian>::chunked_binary_ostream ( std::from_range_t, std::ranges::input_range auto&& r, auto /*std::reference_wrapper<stream_type>*/ s, int chunk_len )
    requires requires ( output_type t ) { s.get().write(reinterpret_cast<const char*>(&t), sizeof(output_type)); }
{
    ranges::chunked_binary_ostream_view<typename decay<decltype(s)>/*reference_wrapper*/::type/*stream_type*/,output_type,endian>(std::from_range, std::move(r), s.get(), chunk_len);
}