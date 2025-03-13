#pragma once

template < class stream_type, class input_type >
constexpr ranges::istream_view<stream_type,input_type>::istream_view ( stream_type& init_s )
    extends s_ptr ( &init_s )
{
    ++iterator(self);
}

template < class stream_type, class input_type >
constexpr auto ranges::istream_view<stream_type,input_type>::begin ( )
{
    return iterator(self);
}

template < class stream_type, class input_type >
constexpr auto ranges::istream_view<stream_type,input_type>::end ( )
{
    return std::default_sentinel;
}

template < class stream_type, class input_type >
class ranges::istream_view<stream_type,input_type>::iterator
{
    public: // Typedef
        using iterator_concept  = std::input_iterator_tag;
     // using iterator_category = not supported; 
        using value_type        = input_type;
        using difference_type   = std::ptrdiff_t;

    private: // Data
        istream_view* v_ptr = nullptr;

    public: // Interface
        constexpr iterator ( istream_view& );
        constexpr value_type& operator *  ( ) const;
        constexpr iterator&   operator ++ ( );
        constexpr void        operator ++ ( int );
        constexpr bool        operator == ( std::default_sentinel_t ) const;
};

template < class stream_type, class input_type >
constexpr ranges::istream_view<stream_type,input_type>::iterator::iterator ( istream_view& init_v )
    extends v_ptr ( &init_v )
{

}

template < class stream_type, class input_type >
constexpr ranges::istream_view<stream_type,input_type>::iterator::value_type& ranges::istream_view<stream_type,input_type>::iterator::operator * ( ) const
{
    return v_ptr->t;
}

template < class stream_type, class input_type >
constexpr ranges::istream_view<stream_type,input_type>::iterator& ranges::istream_view<stream_type,input_type>::iterator::operator ++ ( )
{
    *v_ptr->s_ptr >> v_ptr->t;
    return self;
}

template < class stream_type, class input_type >
constexpr void ranges::istream_view<stream_type,input_type>::iterator::operator ++ ( int )
{
    ++self;
}

template < class stream_type, class input_type >
constexpr bool ranges::istream_view<stream_type,input_type>::iterator::operator == ( std::default_sentinel_t ) const
{
    return v_ptr->s_ptr->eof();
}

template < class stream_type, class output_type >
constexpr ranges::ostream_view<stream_type,output_type>::ostream_view ( std::from_range_t, input_range auto&& r, stream_type& s )
    requires same_as<output_type,range_value<decltype(r)>>
{
    for ( auto&& t in r )
        s << std::move(t);
}

template < class input_type >
constexpr auto views::istream ( auto& s )
    requires requires ( input_type t ) { s >> t; }
{
    return ranges::istream_view<decay<decltype(s)>,input_type>(s);
}

template < class output_type >
constexpr views::ostream<output_type>::ostream ( std::from_range_t, input_range auto&& r, auto /*std::reference_wrapper<stream_type>*/ s )
    requires requires ( output_type t ) { s.get() << t; }
{
    ranges::ostream_view<typename decay<decltype(s)>/*reference_wrapper*/::type/*stream_type*/,output_type>(std::from_range, std::move(r), s);
}