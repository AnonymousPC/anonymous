#pragma once

/// Class basic_string

template < class char_type >
class basic_string
    extends public array_algo <basic_string<char_type>,char_type>,
            public string_algo<basic_string<char_type>,char_type>
{
    private: // Precondition
        static_assert ( ap::char_type<char_type> );

    private: // Small string optimization
        constexpr static const int sso = 16 / sizeof(char_type) - 1;

    private: // Data
        int        m        = 0;
        char_type  internal   [sso+1] {};
        char_type* external = nullptr;

    public: // Typedef
        using  value_type     = char_type;
        using  iterate_type   = char_type;
        using  iterator       = char_type*;
        using  const_iterator = const char_type*;
        using  array_algo     = array_algo <basic_string,char_type>;
        using  string_algo    = string_algo<basic_string,char_type>;
        struct string_tag { };

    public: // Core
        constexpr           basic_string ( ) = default;
        constexpr           basic_string ( const basic_string&  );
        constexpr           basic_string (       basic_string&& );
        constexpr           basic_string ( const basic_string_range_view<char_type>& );
        constexpr           basic_string ( const basic_string_view      <char_type>& );
        constexpr           basic_string (       std::same_as<char_type> auto );
        constexpr explicit  basic_string ( int,  std::same_as<char_type> auto );
        constexpr           basic_string ( const char_type* );
        constexpr           basic_string ( std::from_range_t, std::ranges::input_range auto&& r      ) requires requires { std::declval<basic_string>().push(*r.begin()); };
        constexpr           basic_string ( std::from_range_t, std::ranges::input_range auto&& r, int ) requires requires { std::declval<basic_string>().push(*r.begin()); };
        constexpr          ~basic_string ( );
        constexpr           basic_string& operator = ( const basic_string&  );
        constexpr           basic_string& operator = (       basic_string&& );
        constexpr           basic_string& operator = ( const basic_string_range_view<char_type>& );
        constexpr           basic_string& operator = ( const basic_string_view      <char_type>& );
        constexpr           basic_string& operator = (       std::same_as<char_type> auto );
        constexpr           basic_string& operator = ( const char_type* );

    public: // Conversion. The sequence below indicates the priority. Note: concept std::convertible_to checks both std::is_convertible and std::is_constructible, which may recursively depends on itself (happens in constuctor from printable or operator inputable()).
        template < class char_type2 >  constexpr explicit basic_string ( const basic_string<char_type2>& );
        template < class char_type2 >  constexpr explicit operator             basic_string<char_type2> ( )          const;
        template < class bool_type >   constexpr explicit basic_string ( const bool_type& )                                requires std::same_as<char_type,char> and std::same_as<bool_type,bool>;
        template < class bool_type >   constexpr explicit operator             bool_type ( )                         const requires std::same_as<char_type,char> and std::same_as<bool_type,bool>;
        template < class number_type > constexpr explicit basic_string ( const number_type& )                              requires std::same_as<char_type,char> and ( not std::is_convertible<number_type,basic_string>::value ) and ( not general_string_type<number_type> ) and ( not std::same_as<number_type,bool> ) and ( std::integral<number_type> or std::floating_point<number_type> );
        template < class number_type > constexpr explicit operator             number_type ( )                       const requires std::same_as<char_type,char> and ( not std::is_convertible<basic_string,number_type>::value ) and ( not general_string_type<number_type> ) and ( not std::same_as<number_type,bool> ) and ( std::integral<number_type> or std::floating_point<number_type> );
        template < class printable >   constexpr explicit basic_string ( const printable& )                                requires std::same_as<char_type,char> and ( not std::is_convertible<printable,basic_string>::value   ) and ( not general_string_type<printable>   ) and ( not std::same_as<printable,  bool> ) and ( not ( std::integral<printable> or std::floating_point<printable> ) ) and ap::printable<printable>;
        template < class inputable >   constexpr explicit operator             inputable ( )                         const requires std::same_as<char_type,char> and ( not std::is_convertible<basic_string,inputable>::value   ) and ( not general_string_type<inputable>   ) and ( not std::same_as<inputable,  bool> ) and ( not ( std::integral<inputable> or std::floating_point<inputable> ) ) and ap::inputable<inputable>;
                                       constexpr explicit basic_string ( const std::basic_string<char_type>& );
                                       constexpr explicit operator             std::basic_string<char_type> ( )      const;
                                       constexpr explicit basic_string ( const std::basic_string_view<char_type>& );
                                       constexpr explicit operator             std::basic_string_view<char_type> ( ) const;
                                       constexpr explicit basic_string ( const std::type_info& );

    public: // Interface
        constexpr       int            size        ( )          const;
        constexpr       basic_string&  resize      ( int );
        constexpr       bool           empty       ( )          const;
        constexpr       char_type*     data        ( );
        constexpr const char_type*     data        ( )          const;
        constexpr       char_type*     begin       ( );
        constexpr const char_type*     begin       ( )          const;
        constexpr       char_type*     end         ( );
        constexpr const char_type*     end         ( )          const;
        constexpr       char_type&     operator [] ( int );
        constexpr const char_type&     operator [] ( int )      const;
        constexpr       auto           operator [] ( int, int );
        constexpr const auto           operator [] ( int, int ) const;

    public: // C-style
        constexpr                   const char_type* c_str ( ) const;

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

    private: // Auxiliary
        constexpr static char_type* allocate   ( int );
        constexpr static void       deallocate ( char_type* );
        constexpr static int        capacity   ( int );
};



/// Template deduction

template < char_type type > basic_string ( basic_string           <type> ) -> basic_string<type>;
template < char_type type > basic_string ( basic_string_range_view<type> ) -> basic_string<type>;
template < char_type type > basic_string ( basic_string_view      <type> ) -> basic_string<type>;
template < char_type type > basic_string ( type )                          -> basic_string<type>;
template < char_type type > basic_string ( const type* )                   -> basic_string<type>;


#include "string.ipp"