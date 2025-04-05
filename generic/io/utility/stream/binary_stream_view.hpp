#pragma once

namespace ranges
{
    template < class input_type, std::endian endian = std::endian::native >
    class binary_istream_view
        extends public std::ranges::view_interface<binary_istream_view<input_type,endian>>
    {
        private: // Data
            std::istream* s_ptr = nullptr;
            input_type    t     = input_type();

        private: // Typedef
            class iterator;

        public: // Interface
            constexpr binary_istream_view ( std::istream& );
            constexpr auto begin ( );
            constexpr auto end   ( );
    };

    template < class output_type, std::endian endian = std::endian::native >
    class binary_ostream_view
    {
        public: // Interface
            constexpr binary_ostream_view ( std::from_range_t, input_range auto&& r, std::ostream& ) requires same_as<output_type,range_value<decltype(r)>>;
    };
} // namespace ranges





namespace views
{
    template < class input_type, std::endian endian = std::endian::native >
    constexpr auto binary_istream ( std::istream& );

    template < class output_type, std::endian endian = std::endian::native >
    class binary_ostream
    {
        public:
            constexpr binary_ostream ( std::from_range_t, input_range auto&& r, std::ostream& ) requires same_as<output_type,range_value<decltype(r)>>;
    };
} // namespace views




#include "binary_stream_view.ipp"