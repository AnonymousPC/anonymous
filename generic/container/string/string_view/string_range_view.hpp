#pragma once

template < class char_type >
class basic_string_range_view
    extends public array_algo <basic_string_range_view<char_type>,char_type>,
            public string_algo<basic_string_range_view<char_type>,char_type>
{
    private: // Data
        basic_string<char_type>* ptr = nullptr;
        range<int,true>          idx = range<int,true>();

    public: // Typedef
        using  value_type     = char_type;
        using  iterate_type   = char_type;
        using  iterator       = char_type*;
        using  const_iterator = const char_type*;
        using  array_algo     = array_algo <basic_string_range_view,char_type>;
        using  string_algo    = string_algo<basic_string_range_view,char_type>;
        struct string_tag { };

    private: // Core
        friend vector<basic_string_range_view>;
        constexpr basic_string_range_view ( ) = default;

    public: // Core
        constexpr basic_string_range_view ( const basic_string_range_view& ) = default;
        constexpr basic_string_range_view& operator = ( const basic_string_range_view& );
        constexpr basic_string_range_view& operator = ( const basic_string<char_type>&  );
        constexpr basic_string_range_view& operator = (       basic_string<char_type>&& );

    private: // Constructor
        friend basic_string<char_type>;
        constexpr basic_string_range_view ( basic_string<char_type>&, int, int );

    public: // Conversion. The sequence below indicates the priority. Note: concept std::convertible_to checks both std::is_convertible and std::is_constructible, which may recursively depends on itself (happenes in operator inputable()).
        template < class char_type2 >  constexpr explicit operator basic_string<char_type2>          ( ) const;
        template < class bool_type >   constexpr explicit operator bool_type                         ( ) const requires std::same_as<char_type,char> and std::same_as<bool_type,bool>;
        template < class number_type > constexpr explicit operator number_type                       ( ) const requires std::same_as<char_type,char> and ( not std::is_convertible<basic_string_range_view,number_type>::value ) and ( not general_string_type<number_type> ) and ( not std::same_as<number_type,bool> ) and ( std::integral<number_type> or std::floating_point<number_type> );
        template < class inputable >   constexpr explicit operator inputable                         ( ) const requires std::same_as<char_type,char> and ( not std::is_convertible<basic_string_range_view,inputable>::value   ) and ( not general_string_type<inputable>   ) and ( not std::same_as<inputable,  bool> ) and ( not ( std::integral<inputable> or std::floating_point<inputable> ) ) and ap::inputable<inputable>;                                       constexpr explicit operator std::basic_string<char_type>      ( ) const;
                                       constexpr explicit operator std::basic_string_view<char_type> ( ) const;

    public: // Interface
        constexpr       int            size        ( )          const;
        constexpr       bool           empty       ( )          const;
        constexpr       void           resize      ( ) = delete;
        constexpr       iterator       begin       ( );
        constexpr       const_iterator begin       ( )          const;
        constexpr       iterator       end         ( );
        constexpr       const_iterator end         ( )          const;
        constexpr       char_type&     operator [] ( int );
        constexpr const char_type&     operator [] ( int )      const;
        constexpr       auto           operator [] ( int, int );
        constexpr const auto           operator [] ( int, int ) const;

    public: // Algo
        using array_algo::clear,
              array_algo::erase,
           // array_algo::insert,
              array_algo::pop,
           // array_algo::push,

              array_algo::adjacent_find,
              array_algo::adjacent_where,
              array_algo::all,
              array_algo::contains,
              array_algo::count,
              array_algo::each,
              array_algo::exist,
              array_algo::fill,
              array_algo::find,
              array_algo::is_partitioned,
              array_algo::is_sorted,
              array_algo::max,
              array_algo::min,
              array_algo::next_permutation,
              array_algo::none,
              array_algo::partition,
              array_algo::prev_permutation,
              array_algo::product,
              array_algo::remove,
              array_algo::replace,
              array_algo::reverse,
              array_algo::right_adjacent_find,
              array_algo::right_find,
              array_algo::rotate,
              array_algo::sort,
              array_algo::sum,
              array_algo::transform,
              array_algo::unique,
              array_algo::where;

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

// No template deduction is declared. Class string_range_view cannot construct from string ( without 2 index ) or any-string-like object else.

#include "string_range_view.ipp"