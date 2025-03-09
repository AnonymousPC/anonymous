#pragma once

namespace detail
{
    template < class type >
    struct is_istream_view
    {
        constexpr static const bool value = false;
    };
    
    template < class stream_type, class value_type >
    struct is_istream_view<ranges::binary_istream_view<stream_type,value_type>>
    {
        constexpr static const bool value = true;
    };
}

namespace ranges
{
    template < input_range range, class pattern >
        requires equalable_to<range_value<range>,pattern>
    class csv_lazy_split_view
        extends public std::ranges::view_interface<csv_lazy_split_view<range,pattern>>
    {
        private: // Data
            range   r;
            pattern p;
            bool    q = false; // Log current cursor is in quotes or not.
    
        private: // Typedef
            class iterator;
    
        public: // Interface
            constexpr csv_lazy_split_view ( range, pattern );
            constexpr auto begin ( );
            constexpr auto end   ( );
    };
    
} // namespace ranges

namespace views
{   
    template < class pattern >
    class csv_lazy_split
        extends public std::ranges::range_adaptor_closure<csv_lazy_split<pattern>>
    {
        private: // Data
            pattern p;
    
        public: // Interface
            constexpr csv_lazy_split ( pattern&& );
            constexpr auto operator() ( input_range auto&& r ) const requires equalable_to<range_value<decltype(r)>,pattern>;
    };

} // namespace views


template < input_range range, class pattern >
    requires equalable_to<range_value<range>,pattern>
constexpr ranges::csv_lazy_split_view<range,pattern>::csv_lazy_split_view ( range init_r, pattern init_p )
extends r ( std::move(init_r) ),
        p ( std::move(init_p) )
{

};

template < input_range range, class pattern >
    requires equalable_to<range_value<range>,pattern>
constexpr auto ranges::csv_lazy_split_view<range,pattern>::begin ( )
{
    return iterator(self);
};

template < input_range range, class pattern >
    requires equalable_to<range_value<range>,pattern>
constexpr auto ranges::csv_lazy_split_view<range,pattern>::end ( )
{
    return std::default_sentinel;
}


template < input_range range, class pattern >
    requires equalable_to<range_value<range>,pattern>
class ranges::csv_lazy_split_view<range,pattern>::iterator
{
    private: // Data
        csv_lazy_split_view*  v;
        range_iterator<range> i;

    public: // Interface
        constexpr iterator ( csv_lazy_split_view& );
        constexpr auto      operator *  ( )                         const;
        constexpr bool      operator == ( std::default_sentinel_t ) const;
        constexpr iterator& operator ++ ( );
        constexpr iterator& operator ++ ( int );

    public: // Typedef
        using iterator_concept  = std::input_iterator_tag;
     // using iterator_category = not supported;
        class value_type; 
        using difference_type   = std::ptrdiff_t;
};

template < input_range range, class pattern >
    requires equalable_to<range_value<range>,pattern>
constexpr ranges::csv_lazy_split_view<range,pattern>::iterator::iterator ( csv_lazy_split_view& init_v )
    extends v ( &init_v ),
            i ( v->r.begin() )
{

}

template < input_range range, class pattern >
    requires equalable_to<range_value<range>,pattern>
constexpr auto ranges::csv_lazy_split_view<range,pattern>::iterator::operator * ( ) const
{
    v->q = false; // Maybe useless.
    let r = std::views::iota(i, v->r.end())
          | std::views::transform ([]  (const auto& i) { return *i; })
          | std::views::take_while([&] (const auto& c)
              {
                  if ( c == '"' )
                      v->q = not v->q;
                  return (c != v->p and c != '\n') or v->q;
              });
    return r;
}

template < input_range range, class pattern >
    requires equalable_to<range_value<range>,pattern>
constexpr bool ranges::csv_lazy_split_view<range,pattern>::iterator::operator == ( std::default_sentinel_t ) const
{
    if constexpr ( detail::is_istream_view<range>::value )
        return i == v->r.end();
    else
        return *i == '\n' or i == v->r.end();
}

template < input_range range, class pattern >
    requires equalable_to<range_value<range>,pattern>
constexpr ranges::csv_lazy_split_view<range,pattern>::iterator& ranges::csv_lazy_split_view<range,pattern>::iterator::operator ++ ( )
{
    if constexpr ( detail::is_istream_view<range>::value )
        ++i;
    else
        if ( *i != '\n' )
            ++i;
    return self;
}

template < input_range range, class pattern >
    requires equalable_to<range_value<range>,pattern>
constexpr ranges::csv_lazy_split_view<range,pattern>::iterator& ranges::csv_lazy_split_view<range,pattern>::iterator::operator ++ ( int )
{
    return operator++();
}

template < input_range range, class pattern >
    requires equalable_to<range_value<range>,pattern>
class ranges::csv_lazy_split_view<range,pattern>::iterator::value_type
    extends public decltype(*std::declval<iterator>()) // Only a declaration to make value_type available.
{

};

template < class pattern >
constexpr views::csv_lazy_split<pattern>::csv_lazy_split ( pattern&& init_p )
    extends p ( std::move(init_p) )
{

}

template < class pattern >
constexpr auto views::csv_lazy_split<pattern>::operator() ( input_range auto&& r ) const
    requires equalable_to<range_value<decltype(r)>,pattern>
{
    return ranges::csv_lazy_split_view(std::forward<decltype(r)>(r), p);
}

















file_csv::file_csv ( const char* pth )
{
    open(pth);
}

file_csv::file_csv ( const path& pth )
{
    open(pth);
}

file_csv& file_csv::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);
    let stream = file_stream(path(self), file_stream::read_only(true));

    // Read data.
    let raw_data = views::binary_istream<char>(stream)
                 | views::csv_lazy_split('\n') // Only splits outside quotes.
                 | std::views::transform([] (const auto& stream_line)
                     {
                         let line = (stream_line
                                  | views::csv_lazy_split(',') // Only splits outside quotes.
                                  | std::ranges::to<vector<string>>())
                                  . for_each ([] (auto& str)
                                      {
                                          if ( str.begins_with('"') and str.ends_with('"') )
                                              str.pop(1).pop();
                                      })
                                  . for_each ([] (auto& str) { str.replace("\"\"", '"'); });
                         if ( not line.empty() and line[-1].ends_with('\r') )
                             line[-1].pop();
                         return line;
                     })
                 | std::ranges::to<vector<vector<string>>>();

    // Align.
    let align = 0;
    if ( not raw_data.empty() )
        align = raw_data.max([] (const auto& line1, const auto& line2) { return line1.size() < line2.size(); }).size();

    // Store.
    self.resize(raw_data.size(), align);
    std::ranges::move(raw_data | std::views::join, self.flatten().begin());

    return self;
}

file_csv& file_csv::save ( )
{
    // Save file.
    file_interface::save();
    let stream = file_stream(path(self), file_stream::write_only(true), file_stream::erase(true));

    // Write data.
    self | std::views::transform([] (auto line)
             {
                 return line . for_each ([] (auto& str) { str.replace('"', "\"\""); })
                             . for_each ([] (auto& str) 
                                 {
                                     if ( str.contains('"') or str.contains(',') or str.contains('\n') )
                                         str.insert(1,'"').push('"');
                                 })
                             | std::views::join_with(',')
                             | std::ranges::to<string>();
             })
         | std::views::join_with('\n')
         | std::ranges::to<views::binary_ostream<char>>(std::ref(stream));

    return self;
}
