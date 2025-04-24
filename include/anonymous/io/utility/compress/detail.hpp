namespace detail
{
    template < input_range range, class method >
        requires same_as<range_value<range>,char>
    class compress_view
        extends public std::ranges::view_interface<compress_view<range,method>>
    {
        private:
            struct source_type;

        private: // Data
            range                                                r;
            source_type                                          s;
            std::shared_ptr<boost::iostreams::filtering_istream> p;
            ranges::binary_istream_view<char>                    v;
            
        public: // Interface
            constexpr compress_view ( range );
            constexpr auto begin ( );
            constexpr auto end   ( );
    };

    template < class method >
    struct compress_t
        extends public std::ranges::range_adaptor_closure<compress_t<method>>
    {
        constexpr auto operator() ( input_range auto&& r ) const requires same_as<range_value<decltype(r)>,char>;
    };
    
} // namespace detail

#include "detail.cpp"