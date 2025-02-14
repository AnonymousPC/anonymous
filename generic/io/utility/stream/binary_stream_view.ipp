#pragma once

template < class stream_type, class input_type, std::endian endian >
constexpr ranges::binary_istream_view<stream_type,input_type,endian>::binary_istream_view ( stream_type& init_s )
    extends s_ptr ( &init_s )
{

}

template < class stream_type, class input_type, std::endian endian >
constexpr auto ranges::binary_istream_view<stream_type,input_type,endian>::begin ( )
{
    return ++iterator(self);
}

template < class stream_type, class input_type, std::endian endian >
constexpr auto ranges::binary_istream_view<stream_type,input_type,endian>::end ( )
{
    return std::default_sentinel;
}

template < class stream_type, class input_type, std::endian endian >
constexpr ranges::binary_istream_view<stream_type,input_type,endian>& ranges::binary_istream_view<stream_type,input_type,endian>::operator >> ( same_as<input_type> auto& p )
{
    p = *(++iterator(self));
    return self;
}

template < class stream_type, class input_type, std::endian endian >
class ranges::binary_istream_view<stream_type,input_type,endian>::iterator
{
    public: // Typedef
        using iterator_concept = std::input_iterator_tag;
        using value_type       = input_type;
        using difference_type  = std::ptrdiff_t;

    private: // Data
        binary_istream_view* v_ptr = nullptr;

    public: // Interface
        constexpr iterator ( binary_istream_view& );
        constexpr value_type& operator *  ( ) const;
        constexpr iterator&   operator ++ ( );
        constexpr iterator&   operator ++ ( int );
        constexpr bool        operator == ( std::default_sentinel_t ) const;
};

template < class stream_type, class input_type, std::endian endian >
constexpr ranges::binary_istream_view<stream_type,input_type,endian>::iterator::iterator ( binary_istream_view& init_v )
    extends v_ptr ( &init_v )
{

}

template < class stream_type, class input_type, std::endian endian >
constexpr ranges::binary_istream_view<stream_type,input_type,endian>::iterator::value_type& ranges::binary_istream_view<stream_type,input_type,endian>::iterator::operator * ( ) const
{
    return v_ptr->t;
}

template < class stream_type, class input_type, std::endian endian >
constexpr ranges::binary_istream_view<stream_type,input_type,endian>::iterator& ranges::binary_istream_view<stream_type,input_type,endian>::iterator::operator ++ ( )
{
    v_ptr->s_ptr->read(reinterpret_cast<char*>(&v_ptr->t), sizeof(input_type));

    if constexpr ( detail::requires_byteswap<endian,input_type> )
        detail::byteswap(v_ptr->t);

    return self;
}

template < class stream_type, class input_type, std::endian endian >
constexpr ranges::binary_istream_view<stream_type,input_type,endian>::iterator& ranges::binary_istream_view<stream_type,input_type,endian>::iterator::operator ++ ( int )
{
    v_ptr->s_ptr->read(reinterpret_cast<char*>(&v_ptr->t), sizeof(input_type));

    if constexpr ( detail::requires_byteswap<endian,input_type> )
        detail::byteswap(v_ptr->t);

    return self;
}

template < class stream_type, class input_type, std::endian endian >
constexpr bool ranges::binary_istream_view<stream_type,input_type,endian>::iterator::operator == ( std::default_sentinel_t ) const
{
    return v_ptr->s_ptr->eof();
}

template < class stream_type, class output_type, std::endian endian >
constexpr ranges::binary_ostream_view<stream_type,output_type,endian>::binary_ostream_view ( std::from_range_t, input_range auto&& r, stream_type& s )
    requires same_as<output_type,decay<decltype(*r.begin())>>
{
    for ( auto&& t in r )
        if constexpr ( not detail::requires_byteswap<endian,output_type> )
            s.write(reinterpret_cast<const char*>(&t), sizeof(output_type));
        else
        {
            let t2 = t;
            detail::byteswap(t2);
            s.write(reinterpret_cast<const char*>(&t2), sizeof(output_type));
        }
}

template < class stream_type, class output_type, std::endian endian >
constexpr ranges::binary_ostream_view<stream_type,output_type,endian>& ranges::binary_ostream_view<stream_type,output_type,endian>::operator << ( const same_as<output_type> auto& p )
{
    if constexpr ( not detail::requires_byteswap<endian,output_type> )
        s_ptr->write(reinterpret_cast<const char*>(&p), sizeof(output_type));
    else
    {
        let p2 = p;
        detail::byteswap(p2);
        s_ptr->write(reinterpret_cast<const char*>(&p2), sizeof(output_type));
    }

    return self;
}

template < class stream_type, class output_type, std::endian endian >
constexpr ranges::binary_ostream_view<stream_type,output_type,endian>::binary_ostream_view ( stream_type& init_s )
    extends s_ptr ( &init_s )
{

}

template < class input_type, std::endian endian >
constexpr auto views::binary_istream ( auto& /*stream_type*/ s )
    requires requires ( input_type t ) { s.read(reinterpret_cast<char*>(&t), sizeof(input_type)); }
{
    return ranges::binary_istream_view<decay<decltype(s)>,input_type,endian>(s);
}

template < class output_type, std::endian endian >
constexpr views::binary_ostream<output_type,endian>::binary_ostream ( std::from_range_t, input_range auto&& r, auto /*std::reference_wrapper<stream_type>*/ s )
    requires requires ( output_type t ) { s.get().write(reinterpret_cast<const char*>(&t), sizeof(output_type)); }
{
    ranges::binary_ostream_view<typename decay<decltype(s)>/*reference_wrapper*/::type/*stream_type*/,output_type,endian>(std::from_range, std::move(r), s.get());
}