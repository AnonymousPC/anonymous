#pragma once

namespace ranges
{
    template < class range >
        requires input_range<range> and 
                 same_as<range_value<range>,char>
    class encode_base64_view
        extends public std::ranges::view_interface<encode_base64_view<range>>
    {
        private: // Data
            range r;

        private: // Typedef
            struct iterator;
            
        public: // Interface
            constexpr encode_base64_view ( range );
            constexpr auto begin ( ) const;
            constexpr auto end   ( ) const;
        //    constexpr auto size  ( ) const requires std::ranges::sized_range<range>;
    };

} // namespace ranges

namespace views
{
    struct encode_base64_t
        extends public std::ranges::range_adaptor_closure<encode_base64_t>
    {
        constexpr auto operator() ( input_range auto&& r ) const requires same_as<range_value<decltype(r)>,char>;
    };

    encode_base64_t encode_base64;
    
} // namespace views

#include "encode_base64.ipp"