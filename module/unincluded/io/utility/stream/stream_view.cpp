template < inputable input_type >
constexpr ranges::istream_view<input_type>::istream_view ( std::istream& init_s )
    extends s_ptr ( &init_s )
{
    ++iterator(self);
}

template < inputable input_type >
constexpr auto ranges::istream_view<input_type>::begin ( )
{
    return iterator(self);
}

template < inputable input_type >
constexpr auto ranges::istream_view<input_type>::end ( )
{
    return std::default_sentinel;
}

template < inputable input_type >
class ranges::istream_view<input_type>::iterator
{
    public: // Typedef
        using iterator_concept  = std::input_iterator_tag;
     // using iterator_category = not supported; 
        using value_type        = input_type;
        using difference_type   = ptrdiff_t;

    private: // Data
        istream_view* v_ptr;

    public: // Interface
        constexpr iterator ( istream_view& );
        constexpr value_type& operator *  ( ) const;
        constexpr iterator&   operator ++ ( );
        constexpr void        operator ++ ( int );
        constexpr bool        operator == ( std::default_sentinel_t ) const;
};

template < inputable input_type >
constexpr ranges::istream_view<input_type>::iterator::iterator ( istream_view& init_v )
    extends v_ptr ( &init_v )
{

}

template < inputable input_type >
constexpr ranges::istream_view<input_type>::iterator::value_type& ranges::istream_view<input_type>::iterator::operator * ( ) const
{
    return v_ptr->t;
}

template < inputable input_type >
constexpr ranges::istream_view<input_type>::iterator& ranges::istream_view<input_type>::iterator::operator ++ ( )
{
    *v_ptr->s_ptr >> v_ptr->t;
    return self;
}

template < inputable input_type >
constexpr void ranges::istream_view<input_type>::iterator::operator ++ ( int )
{
    ++self;
}

template < inputable input_type >
constexpr bool ranges::istream_view<input_type>::iterator::operator == ( std::default_sentinel_t ) const
{
    return v_ptr->s->eof();
}

template < printable output_type >
constexpr ranges::ostream_view<output_type>::ostream_view ( std::from_range_t, input_range auto&& r, std::ostream& s )
    requires same_as<output_type,range_value<decltype(r)>>
{
    for ( auto&& e in r )
        s << std::move(e);
}

template < inputable input_type >
constexpr auto views::istream ( std::istream& s )
{
    return ranges::istream_view<input_type>(s);
}

template < printable output_type >
constexpr views::ostream<output_type>::ostream ( std::from_range_t, input_range auto&& r, std::ostream& s )
    requires same_as<output_type,range_value<decltype(r)>>
{
    ranges::ostream_view<output_type>(std::from_range, std::move(r), s);
}