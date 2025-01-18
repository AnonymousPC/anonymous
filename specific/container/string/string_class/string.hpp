#pragma once

template < class type, class device >
class basic_string
    extends public device::template basic_string<type>
{
    private: // Precondition
        static_assert ( char_type<type> );

    private: // Typedef
        using base        = device::template basic_string<type>;
        using string_view = basic_string_view<type,device>; 

    public: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;
        using  iterator        = base::iterator;
        using  const_iterator  = base::const_iterator;
     // using  array_algo      = array_algo <basic_string,type>;
     // using  string_algo     = string_algo<basic_string,type>;
        using  device_type     = device;
        struct string_tag { };

    public: // Core
        constexpr basic_string ( )                                  = default;
        constexpr basic_string ( const basic_string&  )             = default;
        constexpr basic_string (       basic_string&& )             = default;
        constexpr basic_string& operator = ( const basic_string&  ) = default;
        constexpr basic_string& operator = (       basic_string&& ) = default;

    public: // Constructor
        constexpr basic_string ( type );
        constexpr basic_string ( int, type );
        constexpr basic_string ( const type* );
        constexpr basic_string ( std::from_range_t, std::ranges::input_range auto&& r ) requires requires { std::declval<basic_string>().push(*std::ranges::begin(r)); };

    public: // Conversion (view)
        constexpr basic_string ( string_view );

    public: // Conversion (type)
        template < char_type type2 > constexpr explicit basic_string ( const basic_string     <type2,device>& );
        template < char_type type2 > constexpr explicit basic_string ( const basic_string_view<type2,device>& );

    public: // Conversion (device)
        template < class device2 > constexpr explicit basic_string ( const basic_string     <type,device2>& ) requires same_as<device,cpu> or same_as<device2,cpu>;
        template < class device2 > constexpr explicit basic_string ( const basic_string_view<type,device2>& ) requires same_as<device,cpu> or same_as<device2,cpu>;

    public: // Conversion (other)
                                       constexpr explicit basic_string ( const bool& )                 requires same_as<type,char>;
                                       constexpr explicit operator             bool ( )          const requires same_as<type,char>;
        template < number_type type2 > constexpr explicit basic_string ( const type2& )                requires same_as<type,char>;
        template < number_type type2 > constexpr explicit operator             type2 ( )         const requires same_as<type,char>;
        template < printable   type2 > constexpr explicit basic_string ( const type2& )                requires same_as<type,char> and ( not number_type<type2> ) and ( not string_type<type2> );
        template < inputable   type2 > constexpr explicit operator             type2 ( )         const requires same_as<type,char> and ( not number_type<type2> ) and ( not string_type<type2> );
                                       constexpr explicit basic_string ( const std::type_info& )       requires same_as<type,char>;

    public: // Member
        constexpr int             size        ( )                                    const;
        constexpr basic_string&   resize      ( int );
        constexpr bool            empty       ( )                                    const;
        constexpr iterator        begin       ( );
        constexpr const_iterator  begin       ( )                                    const;
        constexpr iterator        end         ( );
        constexpr const_iterator  end         ( )                                    const;
        constexpr pointer         data        ( );
        constexpr const_pointer   data        ( )                                    const;
        constexpr const_pointer   c_str       ( )                                    const;
        constexpr reference       operator [] ( int );
        constexpr const_reference operator [] ( int )                                const;
        constexpr string_view     operator [] ( int, int )                           const;

        constexpr basic_string&   clear       ( );
        constexpr basic_string&   erase       ( int, int );
        constexpr basic_string&   insert      ( int, string_view );
        constexpr basic_string&   push        (      string_view );
        constexpr basic_string&   pop         ( int );

    public: // Memory 
        constexpr static bool ownership ( );

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

template < char_type type >               basic_string ( type )                           -> basic_string<type>;
template < char_type type >               basic_string ( const type* )                    -> basic_string<type>;
template < char_type type, class device > basic_string ( basic_string_view<type,device> ) -> basic_string<type,device>;


#include "string.ipp"