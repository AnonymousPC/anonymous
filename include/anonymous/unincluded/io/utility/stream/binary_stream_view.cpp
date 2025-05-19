template < class input_type, std::endian endian >
constexpr ranges::binary_istream_view<input_type,endian>::binary_istream_view ( std::istream& init_s )
    extends s_ptr ( &init_s )
{
    ++iterator(self);
}

template < class input_type, std::endian endian >
constexpr auto ranges::binary_istream_view<input_type,endian>::begin ( )
{
    return iterator(self);
}

template < class input_type, std::endian endian >
constexpr auto ranges::binary_istream_view<input_type,endian>::end ( )
{
    return std::default_sentinel;
}

template < class input_type, std::endian endian >
class ranges::binary_istream_view<input_type,endian>::iterator
{
    public: // Typedef
        using iterator_concept  = std::input_iterator_tag;
     // using iterator_category = not supported; 
        using value_type        = input_type;
        using difference_type   = std::ptrdiff_t;

    private: // Data
        binary_istream_view* v_ptr = nullptr;

    public: // Interface
        constexpr iterator ( ) = default;
        constexpr iterator ( binary_istream_view& );
        constexpr value_type& operator *  ( )                         const;
        constexpr iterator&   operator ++ ( );
        constexpr void        operator ++ ( int );
        constexpr bool        operator == ( std::default_sentinel_t ) const;
};

template < class input_type, std::endian endian >
constexpr ranges::binary_istream_view<input_type,endian>::iterator::iterator ( binary_istream_view& init_v )
    extends v_ptr ( &init_v )
{

}

template < class input_type, std::endian endian >
constexpr ranges::binary_istream_view<input_type,endian>::iterator::value_type& ranges::binary_istream_view<input_type,endian>::iterator::operator * ( ) const
{
    return v_ptr->t;
}

template < class input_type, std::endian endian >
constexpr ranges::binary_istream_view<input_type,endian>::iterator& ranges::binary_istream_view<input_type,endian>::iterator::operator ++ ( )
{
    v_ptr->s_ptr->read(reinterpret_cast<char*>(&v_ptr->t), sizeof(input_type));

    if constexpr ( detail::requires_byteswap<endian,input_type> )
        detail::byteswap(v_ptr->t);

    return self;
}

template < class input_type, std::endian endian >
constexpr void ranges::binary_istream_view<input_type,endian>::iterator::operator ++ ( int )
{
    ++self;
}

template < class input_type, std::endian endian >
constexpr bool ranges::binary_istream_view<input_type,endian>::iterator::operator == ( std::default_sentinel_t ) const
{
    return v_ptr->s_ptr->eof();
}

template < class output_type, std::endian endian >
constexpr ranges::binary_ostream_view<output_type,endian>::binary_ostream_view ( std::from_range_t, input_range auto&& r, std::ostream& s )
    requires same_as<output_type,range_value<decltype(r)>>
{
    for ( auto&& e in r )
        if constexpr ( not detail::requires_byteswap<endian,output_type> )
            s.write(reinterpret_cast<const char*>(&e), sizeof(output_type));
        else
        {
            auto e2 = e;
            detail::byteswap(e2);
            s.write(reinterpret_cast<const char*>(&e2), sizeof(output_type));
        }
}

template < class input_type, std::endian endian >
constexpr auto views::binary_istream ( std::istream& s )
{
    return ranges::binary_istream_view<input_type,endian>(s);
}

template < class output_type, std::endian endian >
constexpr views::binary_ostream<output_type,endian>::binary_ostream ( std::from_range_t, input_range auto&& r, std::ostream& s )
    requires same_as<output_type,range_value<decltype(r)>>
{
    ranges::binary_ostream_view<output_type,endian>(std::from_range, std::move(r), s);
}