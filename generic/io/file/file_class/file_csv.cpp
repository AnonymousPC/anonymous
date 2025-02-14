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

    template < class range, class pattern >
    class csv_lazy_split_view
        extends public std::ranges::view_interface<csv_lazy_split_view<range,pattern>>
    {
        private: // Data
            range   r;
            pattern p;
    
        private: // Typedef
            class iterator;
    
        public: // Interface
            constexpr csv_lazy_split_view ( range init_r, pattern init_p )
                extends r ( std::forward<decltype(init_r)>(init_r) ),
                        p ( std::forward<decltype(init_p)>(init_p) )
            {
        
            };

            constexpr auto begin ( )
            {
                return iterator(self);
            };

            constexpr auto end ( )
            {
                return r.end();
            }
    };

    template < class range, class pattern >
    class csv_lazy_split_view<range,pattern>::iterator
    {
        private: // Typedef
            using subrange = std::ranges::subrange<decltype(std::declval<range>().begin()),decltype(std::declval<range>().end())>;
    
        private: // Data
            csv_lazy_split_view* v;
            subrange             r;
            mutable bool         q = false; // Log current cursor is in quotes or not.
    
        public: // Interface
            constexpr iterator ( csv_lazy_split_view& init_v )
                extends v ( &init_v ),
                        r ( v->r.begin(), v->r.end() )
            {

            }

            constexpr auto operator * ( ) const
            {
                q = false; // Maybe useless.
                let ret = r | std::views::take_while([&] (auto ch) { if ( ch == '"' ) q = not q; return ch != v->p or q; });
                return ret;
            }

            constexpr bool operator == ( auto ) const
            {
                if constexpr ( is_istream_view<range>::value )
                    return r.begin() == r.end();
                else
                    return *r.begin() == '\n' or r.begin() == v->r.base().end();
            }

            constexpr iterator& operator ++ ( )
            {
                if constexpr ( is_istream_view<range>::value )
                    ++r.begin();
                else
                    if ( *r.begin() != '\n' )
                        ++r.begin();
                return self;
            }

            constexpr iterator& operator ++ ( int )
            {
                return operator++();
            }
    
        public: // Typedef
            using iterator_concept = std::input_iterator_tag;
            using difference_type  = std::ptrdiff_t;
            class value_type;
    };
    
    template < class range, class pattern >
    class csv_lazy_split_view<range,pattern>::iterator::value_type
        extends public decltype(*std::declval<iterator>()) // Only a declaration to make value_type available.
    {
    
    };
    
    template < class pattern >
    class csv_lazy_split
        extends public std::ranges::range_adaptor_closure<csv_lazy_split<pattern>>
    {
        private: // Data
            mutable pattern p;
    
        public: // Interface
            constexpr csv_lazy_split ( pattern&& init_p )
                extends p ( std::forward<decltype(init_p)>(init_p) )
            {
            
            }

            constexpr auto operator() ( input_range auto&& r ) const
            {
                return csv_lazy_split_view(std::forward<decltype(r)>(r), std::forward<decltype(p)>(p));
            }
    };
} // namespace detail



















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
                 | detail::csv_lazy_split('\n') // Only splits outside quotes.
                 | std::views::transform([] (const auto& stream_line)
                     {
                         let line = (stream_line
                                  | detail::csv_lazy_split(',') // Only splits outside quotes.
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
