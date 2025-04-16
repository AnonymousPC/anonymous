#pragma once

namespace ranges
{
    template < inputable input_type >
    class istream_view
        extends public std::ranges::view_interface<istream_view<input_type>>
    {
        private: // Data
            std::istream* s_ptr = nullptr;
            input_type    t     = input_type();

        private: // Typedef
            class iterator;

        public: // Interface
            constexpr istream_view ( std::istream& );
            constexpr auto begin ( );
            constexpr auto end   ( );
    };

    template < printable output_type >
    class ostream_view
    {
        public: // Interface
            constexpr ostream_view ( std::from_range_t, input_range auto&& r , std::ostream& ) requires same_as<output_type,range_value<decltype(r)>>;
    };
} // namespace ranges





namespace views
{
    template < inputable input_type >
    constexpr auto istream ( std::istream& );

    template < printable output_type >
    class ostream
    {
        public:
            constexpr ostream ( std::from_range_t, input_range auto&& r, std::ostream& ) requires same_as<output_type,range_value<decltype(r)>>;
    };
} // namespace views




#include "stream_view.cpp"