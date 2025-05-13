export namespace std {
namespace ranges {

  template<range _Range> using range_const_reference_t = range_reference_t<const _Range>;
  template<range _Range> using const_iterator_t        = iterator_t       <const _Range>;
  template<range _Range> using const_sentinel_t        = sentinel_t       <const _Range>;
  
} // namespace ranges
} // namespace std