#pragma once

template < class char_type >
class basic_regex
    extends public basic_string<char_type>,
            public array_algo <basic_regex<char_type>,char_type>,
            public string_algo<basic_regex<char_type>,char_type>
{
    public: // Core
        constexpr          basic_regex ( ) = default;
        constexpr explicit basic_regex ( basic_string<char_type> );

    public: // Conversion
        constexpr basic_regex ( std::basic_regex<char_type> ) = delete; // std::regex does not support fetch raw string from it.
        constexpr operator      std::basic_regex<char_type> ( ) const;

    public: // Typedef
        using  value_type     = char_type;
        using  iterate_type   = char_type;
        using  iterator       = char_type*;
        using  const_iterator = const char_type*;
        using  array_algo     = array_algo <basic_regex,char_type>;
        using  string_algo    = string_algo<basic_regex,char_type>;
        struct string_tag { };

    public: // Algo
        using basic_string<char_type>::size,
              basic_string<char_type>::resize,
              basic_string<char_type>::empty,
              basic_string<char_type>::begin,
              basic_string<char_type>::end,
              basic_string<char_type>::operator[];

        using array_algo::clear,
              array_algo::erase,
           // array_algo::insert,
              array_algo::pop,
           // array_algo::push,

              array_algo::adjacent_find,
              array_algo::adjacent_where,
              array_algo::all,
           // array_algo::contains,
           // array_algo::count,
              array_algo::each,
           // array_algo::exist,
              array_algo::fill,
           // array_algo::find,
              array_algo::is_partitioned,
              array_algo::is_sorted,
              array_algo::max,
              array_algo::min,
              array_algo::next_permutation,
           // array_algo::none,
              array_algo::partition,
              array_algo::prev_permutation,
              array_algo::product,
           // array_algo::remove,
           // array_algo::replace,
              array_algo::reverse,
              array_algo::right_adjacent_find,
           // array_algo::right_find,
              array_algo::rotate,
              array_algo::sort,
              array_algo::sum,
              array_algo::transform,
              array_algo::unique;
           // array_algo::where;

        using string_algo::insert,
              string_algo::push,

              string_algo::begins_with,
              string_algo::capitalize,
              string_algo::center,
              string_algo::ends_with,
              string_algo::expand_tabs,
              string_algo::format,
              string_algo::join,
              string_algo::left_justify,
              string_algo::lower,
              string_algo::left_strip,
              string_algo::partition,
              string_algo::right_justify,
              string_algo::right_partition,
              string_algo::right_split,
              string_algo::right_strip,
              string_algo::split,
              string_algo::split_lines,
              string_algo::starts_with,
              string_algo::strip,
              string_algo::swap_case,
              string_algo::title,
              string_algo::upper,
              string_algo::zero_fill,

              string_algo::contains,
              string_algo::count,
              string_algo::exist,
              string_algo::find,
              string_algo::none,
              string_algo::replace,
              string_algo::remove,
              string_algo::right_find,
              string_algo::where,

              string_algo::all,
              string_algo::match;
};

#include "regex.ipp"