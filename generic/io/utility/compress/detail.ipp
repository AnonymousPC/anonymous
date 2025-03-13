#pragma once

template < input_range range, class method >
    requires same_as<range_value<range>,char>
constexpr detail::compress_view<range,method>::compress_view ( range init_r )
    extends r ( std::move(init_r) ),
            s ( r ),
            p ( [&]
                { 
                    let i = std::shared_ptr<boost::iostreams::filtering_istream>(
                                new boost::iostreams::filtering_istream(), 
                                [] (auto p) { p->exceptions(std::ios::iostate()); }
                            );
                    i->push(method());
                    i->push(s);
                    i->exceptions(std::ios::badbit);
                    return i;
                } () ),
            v ( *p )
{

}


template < input_range range, class method >
    requires same_as<range_value<range>,char>
constexpr auto detail::compress_view<range,method>::begin ( )
{
    return v.begin();
}

template < input_range range, class method >
    requires same_as<range_value<range>,char>
constexpr auto detail::compress_view<range,method>::end ( )
{
    return v.end();
}

template < input_range range, class method >
    requires same_as<range_value<range>,char>
struct detail::compress_view<range,method>::source_type
    extends public boost::iostreams::source
{
    private:
        range_iterator<range> i;
        range_sentinel<range> s;

    public:
        constexpr source_type ( range& );
        constexpr std::streamsize read ( char*, std::streamsize );
};

template < input_range range, class method >
    requires same_as<range_value<range>,char>
constexpr detail::compress_view<range,method>::source_type::source_type ( range& r )
    extends i ( r.begin() ),
            s ( r.end() )
{

}

template < input_range range, class method >
    requires same_as<range_value<range>,char>
constexpr std::streamsize detail::compress_view<range,method>::source_type::read ( char* c, std::streamsize n )
{
    if constexpr ( random_access_range<range> )
    {
        let d = std::min(n, std::streamsize(s-i));
        let [e, _] = std::ranges::copy_n(i, d, c);
        i = e;
        return d != 0 ? d otherwise -1;
    }
    else
    {
        let d = 0;
        while ( d < n and i != s )
        {
            *c = *i;
            ++c;
            ++i;
            ++d;
        }
        return d != 0 ? d otherwise -1;
    }
}

template < class method >
constexpr auto detail::compress_t<method>::operator() ( input_range auto&& r ) const
    requires same_as<range_value<decltype(r)>,char>
{
    return detail::compress_view<decay<decltype(r)>,method>(std::forward<decltype(r)>(r));
}