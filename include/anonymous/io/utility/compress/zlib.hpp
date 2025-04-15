#pragma once

namespace ranges
{
    template < class range >
        requires input_range<range> and 
                 same_as<range_value<range>,char>
    using encode_zlib_view = detail::compress_view<range,boost::iostreams::zlib_compressor>;

    template < class range >
        requires input_range<range> and
                 same_as<range_value<range>,char>
    using decode_zlib_view = detail::compress_view<range,boost::iostreams::zlib_decompressor>;

} // namespace ranges

namespace views
{
    using encode_zlib_t = detail::compress_t<boost::iostreams::zlib_compressor>;
    constexpr encode_zlib_t encode_zlib;

    using decode_zlib_t = detail::compress_t<boost::iostreams::zlib_decompressor>;
    constexpr decode_zlib_t decode_zlib;
    
} // namespace views