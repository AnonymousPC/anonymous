#pragma once

template < class type, class device >
class basic_string_view
    extends public device::template basic_string_view<type>
{
    private: // Precondition
        static_assert ( char_type<type> );

    private: // Typedef
        using base   = device::template basic_string_view<type>;
        using string = basic_string<type,device>; 

    public: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;
        using  iterator        = base::iterator;
        using  const_iterator  = base::const_iterator;
     // using  array_algo      = array_algo <basic_string_view,type>;
     // using  string_algo     = string_algo<basic_string_view,type>;
        using  string_view     = basic_string_view<type,device>; 
        struct string_tag { };

    private: // Core
        constexpr basic_string_view ( )                                      = delete;
        constexpr basic_string_view ( const basic_string_view& )             = delete;
        constexpr basic_string_view& operator = ( const basic_string_view& );

    public: // Constructor
        constexpr basic_string_view ( const type& );
        constexpr basic_string_view ( const char_type* );
        constexpr basic_string_view ( const char_type*, int );
        constexpr basic_string_view ( const string& );

    public: // Conversion (type)
        template < char_type   type2 > constexpr explicit operator basic_string<type2> ( ) const;
                                       constexpr explicit operator bool                ( ) const requires same_as<type,char>;
        template < number_type type2 > constexpr explicit operator number_type         ( ) const requires same_as<type,char>;
        template < inputable   type2 > constexpr explicit operator inputable           ( ) const requires same_as<type,char> and ( not number_type<type2> ) and ( not string_type<type2> );

    public: // Interface
        constexpr int               size        ( )          const;
        constexpr bool              empty       ( )          const;
        constexpr const_iterator    begin       ( )          const;
        constexpr const_iterator    end         ( )          const;
        constexpr const_pointer     data        ( )          const;
        constexpr const_reference   operator [] ( int )      const;
        constexpr basic_string_view operator [] ( int, int ) const;

    public: // Algo
        // using array_algo::clear,
        //       array_algo::erase,
        //    // array_algo::insert,
        //       array_algo::pop,
        //    // array_algo::push,

        //       array_algo::adjacent_find,
        //       array_algo::adjacent_where,
        //       array_algo::all,
        //    // array_algo::contains,
        //    // array_algo::count,
        //       array_algo::each,
        //    // array_algo::exist,
        //       array_algo::fill,
        //    // array_algo::find,
        //       array_algo::is_partitioned,
        //       array_algo::is_sorted,
        //       array_algo::max,
        //       array_algo::min,
        //       array_algo::next_permutation,
        //    // array_algo::none,
        //       array_algo::partition,
        //       array_algo::prev_permutation,
        //       array_algo::product,
        //    // array_algo::remove,
        //    // array_algo::replace,
        //       array_algo::reverse,
        //       array_algo::right_adjacent_find,
        //    // array_algo::right_find,
        //       array_algo::rotate,
        //       array_algo::sort,
        //       array_algo::sum,
        //       array_algo::transform,
        //       array_algo::unique;
        //    // array_algo::where;

        // using string_algo::insert,
        //       string_algo::push,

        //       string_algo::begins_with,
        //       string_algo::capitalize,
        //       string_algo::center,
        //       string_algo::ends_with,
        //       string_algo::expand_tabs,
        //       string_algo::format,
        //       string_algo::join,
        //       string_algo::left_justify,
        //       string_algo::lower,
        //       string_algo::left_strip,
        //       string_algo::partition,
        //       string_algo::right_justify,
        //       string_algo::right_partition,
        //       string_algo::right_split,
        //       string_algo::right_strip,
        //       string_algo::split,
        //       string_algo::split_lines,
        //       string_algo::starts_with,
        //       string_algo::strip,
        //       string_algo::swap_case,
        //       string_algo::title,
        //       string_algo::upper,
        //       string_algo::zero_fill,

        //       string_algo::contains,
        //       string_algo::count,
        //       string_algo::exist,
        //       string_algo::find,
        //       string_algo::none,
        //       string_algo::replace,
        //       string_algo::remove,
        //       string_algo::right_find,
        //       string_algo::where,

        //       string_algo::all,
        //       string_algo::match;
};

template < char_type type > basic_string_view ( type )               -> basic_string_view<type>;
template < char_type type > basic_string_view ( const type* )        -> basic_string_view<type>;
template < char_type type > basic_string_view ( basic_string<type> ) -> basic_string_view<type>;

#include "string_view.ipp"