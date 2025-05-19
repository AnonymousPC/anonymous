namespace ranges
{
    template < class range >
        requires input_range<range> and 
                 same_as<range_value<range>,char>
    using encode_gzip_view = detail::compress_view<range,boost::iostreams::gzip_compressor>;

    template < class range >
        requires input_range<range> and
                 same_as<range_value<range>,char>
    using decode_gzip_view = detail::compress_view<range,boost::iostreams::gzip_decompressor>;

} // namespace ranges

namespace views
{
    using encode_gzip_t = detail::compress_t<boost::iostreams::gzip_compressor>;
    constexpr encode_gzip_t encode_gzip;

    using decode_gzip_t = detail::compress_t<boost::iostreams::gzip_decompressor>;
    constexpr decode_gzip_t decode_gzip;
    
} // namespace views