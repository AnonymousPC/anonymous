namespace ranges
{
    template < input_range range >
        requires same_as<range_value<range>,char>
    class encode_base64_view
        extends public std::ranges::view_interface<encode_base64_view<range>>
    {
        private: // Data
            range r;

        private: // Typedef
            class iterator;
            
        public: // Interface
            constexpr encode_base64_view ( range );
            constexpr auto begin ( );
            constexpr auto end   ( );
            constexpr auto size  ( ) const requires std::ranges::sized_range<range>;
    };

} // namespace ranges

namespace views
{
    struct encode_base64_t
        extends public std::ranges::range_adaptor_closure<encode_base64_t>
    {
        constexpr auto operator() ( input_range auto&& r ) const requires same_as<range_value<decltype(r)>,char>;
    };

    constexpr encode_base64_t encode_base64;
    
} // namespace views






namespace ranges
{
    template < input_range range >
        requires same_as<range_value<range>,char>
    class decode_base64_view
        extends public std::ranges::view_interface<decode_base64_view<range>>
    {
        private: // Data
            range r;

        private: // Typedef
            class iterator;
            
        public: // Interface
            constexpr decode_base64_view ( range );
            constexpr auto begin ( );
            constexpr auto end   ( );
         // constexpr auto size  ( ) const requires std::ranges::sized_range<range> and random_access_range<range>;
    };

} // namespace ranges

namespace views
{
    struct decode_base64_t
        extends public std::ranges::range_adaptor_closure<decode_base64_t>
    {
        constexpr auto operator() ( input_range auto&& r ) const requires same_as<range_value<decltype(r)>,char>;
    };

    constexpr decode_base64_t decode_base64;
    
} // namespace views


#include "base64.cpp"