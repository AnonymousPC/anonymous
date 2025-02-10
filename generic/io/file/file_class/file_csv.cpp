#pragma once

/// View (declaration)

template < class input_range, class pattern >
class file_csv::ranges::lazy_split_view
    extends public std::ranges::view_interface<lazy_split_view<input_range,pattern>>
{
    private: // Data
        input_range r;
        pattern     p;

    private: // Typedef
        class iterator;

    public: // Interface
        constexpr lazy_split_view ( input_range, pattern );
        constexpr auto begin ( );
        constexpr auto end   ( );
};

template < class input_range, class pattern >
class file_csv::ranges::lazy_split_view<input_range,pattern>::iterator
{
    private: // Typedef
        using subrange = std::ranges::subrange<decltype(std::declval<input_range>().begin()),decltype(std::declval<input_range>().end())>;
        template < class type > struct is_istream_view;

    private: // Data
        lazy_split_view* v;
        subrange         r;
        mutable bool     q = false; // Log current cursor is in quotes or not.

    public: // Interface
        constexpr iterator ( lazy_split_view& );
        constexpr auto      operator *  ( )      const;
        constexpr bool      operator == ( auto ) const;
        constexpr iterator& operator ++ ( );
        constexpr iterator& operator ++ ( int );

    public: // Typedef
        using iterator_concept = std::input_iterator_tag;
        using difference_type  = std::ptrdiff_t;
        class value_type;
};

template < class input_range, class pattern >
class file_csv::ranges::lazy_split_view<input_range,pattern>::iterator::value_type
    extends public decltype(*std::declval<iterator>()) // Only declaration to make value_type available.
{

};

template < class pattern >
class file_csv::views::lazy_split
    extends public std::ranges::range_adaptor_closure<lazy_split<pattern>>
{
    private: // Data
        mutable pattern p;

    public: // Interface
        constexpr lazy_split ( pattern&& );
        constexpr auto operator() ( std::ranges::input_range auto&& ) const;
};


/** File_csv is not a template class, so view implemention must be written before file_csv (for deduction of auto) **/

// Class file_csv::ranges::lazy_split_view

template < class input_range, class pattern >
constexpr file_csv::ranges::lazy_split_view<input_range,pattern>::lazy_split_view ( input_range init_r, pattern init_p )
    extends r ( std::move(init_r) ),
            p ( std::move(init_p) )
{

};

template < class input_range, class pattern >
constexpr auto file_csv::ranges::lazy_split_view<input_range,pattern>::begin ( )
{
    return iterator ( self );
};

template < class input_range, class pattern >
constexpr auto file_csv::ranges::lazy_split_view<input_range,pattern>::end ( )
{
    return r.end();
};

// Class file_csv::ranges::lazy_split_view::iterator

template < class input_range, class pattern >
constexpr file_csv::ranges::lazy_split_view<input_range,pattern>::iterator::iterator ( lazy_split_view& init_v )
    extends v ( &init_v ),
            r ( v->r.begin(), v->r.end() )
{

}

template < class input_range, class pattern >
constexpr auto file_csv::ranges::lazy_split_view<input_range,pattern>::iterator::operator * ( ) const
{
    q = false; // Maybe useless.
    let ret = r | std::views::take_while([&] (auto ch) { if ( ch == '"' ) q = not q; return ch != v->p or q; });
    return ret;
}

template < class input_range, class pattern >
constexpr bool file_csv::ranges::lazy_split_view<input_range,pattern>::iterator::operator == ( auto ) const
{
    if constexpr ( is_istream_view<input_range>::value )
        return r.begin() == r.end();
    else
        return *r.begin() == '\n' or r.begin() == v->r.base().end();

}

template < class input_range, class pattern >
constexpr file_csv::ranges::lazy_split_view<input_range,pattern>::iterator& file_csv::ranges::lazy_split_view<input_range,pattern>::iterator::operator ++ ( )
{
    if constexpr ( is_istream_view<input_range>::value )
        ++r.begin();
    else
        if ( *r.begin() != '\n' )
            ++r.begin();

    return self;
}

template < class input_range, class pattern >
constexpr file_csv::ranges::lazy_split_view<input_range,pattern>::iterator& file_csv::ranges::lazy_split_view<input_range,pattern>::iterator::operator ++ ( int )
{
    if constexpr ( is_istream_view<input_range>::value )
        ++r.begin();
    else
        if ( *r.begin() != '\n' )
            ++r.begin();

    return self;
}

template < class input_range, class pattern >
template < class type >
struct file_csv::ranges::lazy_split_view<input_range,pattern>::iterator::is_istream_view
{
    constexpr static const bool value = false;
};

template < class input_range, class pattern >
template < class stream_type, class iterate_type >
struct file_csv::ranges::lazy_split_view<input_range,pattern>::iterator::is_istream_view<ap::ranges::binary_istream_view<stream_type,iterate_type>>
{
    constexpr static const bool value = true;
};

// Class file_csv::views::lazy_split

template < class pattern >
constexpr file_csv::views::lazy_split<pattern>::lazy_split ( pattern&& init_p )
    extends p ( std::move(init_p) )
{

}

template < class pattern >
constexpr auto file_csv::views::lazy_split<pattern>::operator() ( std::ranges::input_range auto&& r ) const
{
    return ranges::lazy_split_view ( std::forward<decltype(r)>(r), std::forward<decltype(p)>(p) );
}















/// Class file_csv

// Core

file_csv::file_csv ( const char* pth )
{
    open(pth);
}

file_csv::file_csv ( const path& pth )
{
    open(pth);
}

// Interface (override)

file_csv& file_csv::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);
    let stream = file_stream(path(self), file_stream::read_only(true));

    // Read data.
    let raw_data = ap::views::binary_istream<char>(stream)
                 | file_csv::views::lazy_split('\n') // Only splits outside quotes.
                 | std::views::transform([] (const auto& stream_line)
                     {
                         let line = (stream_line
                                  | file_csv::views::lazy_split(',') // Only splits outside quotes.
                                  | std::ranges::to<vector<string>>())
                                  . for_each ([] (auto& str) { if ( str.begins_with('"') and str.ends_with('"') ) str.pop(1).pop(); })
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
                             . for_each ([] (auto& str) { if ( str.contains('"') or str.contains(',') or str.contains('\n') ) str.insert(1,'"').push('"'); })
                             | std::views::join_with(',')
                             | std::ranges::to<string>();
             })
         | std::views::join_with('\n')
         | std::ranges::to<ap::views::binary_ostream<char>>(std::ref(stream));

    return self;
}
