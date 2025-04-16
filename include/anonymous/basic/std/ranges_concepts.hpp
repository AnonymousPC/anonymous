#pragma once

export namespace std
{
    template<class _Iterator> using iter_const_reference_t = const iter_reference_t<_Iterator>;

    namespace ranges
    {
        template<range _Range> using range_const_reference_t = range_reference_t<const _Range>;
        template<range _Range> using const_iterator_t        = iterator_t       <const _Range>;
        template<range _Range> using const_sentinel_t        = sentinel_t       <const _Range>;
    }
} // namespace std

