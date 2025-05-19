namespace ranges
{
    template < class range >
        requires input_range<range> and 
                 same_as<range_value<range>,char>
    using encode_bzip2_view = detail::compress_view<range,boost::iostreams::bzip2_compressor>;

    template < class range >
        requires input_range<range> and
                 same_as<range_value<range>,char>
    using decode_bzip2_view = detail::compress_view<range,boost::iostreams::bzip2_decompressor>;

} // namespace ranges

namespace views
{
    using encode_bzip2_t = detail::compress_t<boost::iostreams::bzip2_compressor>;
    constexpr encode_bzip2_t encode_bzip2;

    using decode_bzip2_t = detail::compress_t<boost::iostreams::bzip2_decompressor>;
    constexpr decode_bzip2_t decode_bzip2;
    
} // namespace views