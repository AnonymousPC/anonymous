#pragma once

template < class type, class device >
class basic_string_view
    extends public  device::template basic_string_view<type>,
            private string_algo<basic_string_view<type,device>,type,device>
{
    private: // Precondition
        static_assert ( char_type<type> );

    private: // Base
        using base        = device::template basic_string_view<type>;
        using string      = basic_string<type,device>; 
        using string_algo = string_algo<basic_string_view<type,device>,type,device>;

    public: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;
        using  iterator        = pointer;
        using  const_iterator  = const_pointer;
        using  device_type     = device;  
        struct string_tag { };

    public: // Core
        constexpr basic_string_view ( )                                       = delete;
        constexpr basic_string_view ( const basic_string_view&  )             = default;
        constexpr basic_string_view (       basic_string_view&& )             = default;
        constexpr basic_string_view& operator = ( const basic_string_view&  ) = delete;
        constexpr basic_string_view& operator = (       basic_string_view&& ) = delete;

    public: // Constructor
        constexpr basic_string_view ( const_reference );
        constexpr basic_string_view ( const_pointer );
        constexpr basic_string_view ( const_pointer, int );

    public: // Conversion (other)
                                       constexpr explicit operator bool  ( ) const requires same_as<type,char>;
        template < number_type type2 > constexpr explicit operator type2 ( ) const requires same_as<type,char>;
        template < inputable   type2 > constexpr explicit operator type2 ( ) const requires same_as<type,char> and ( not number_type<type2> ) and ( not string_type<type2> );

    public: // Member
        constexpr int               size        ( )          const;
        constexpr bool              empty       ( )          const;
        constexpr const_iterator    begin       ( )          const;
        constexpr const_iterator    end         ( )          const;
        constexpr const_pointer     data        ( )          const;
        constexpr const_reference   operator [] ( int )      const;
        constexpr basic_string_view operator [] ( int, int ) const;

    public: // Memory
        constexpr static bool ownership  ( );
        constexpr static bool contiguous ( );

    public: // Algo (const only)
        using string_algo::begins_with,
              string_algo::ends_with,

              string_algo::is_alnum,
              string_algo::is_alpha,
              string_algo::is_ascii,
              string_algo::is_blank,
              string_algo::is_cntrl,
              string_algo::is_digit,
              string_algo::is_lower,
              string_algo::is_punct,
              string_algo::is_space,
              string_algo::is_title,
              string_algo::is_upper,

              string_algo::partition,
              string_algo::right_partition,

              string_algo::contains,
              string_algo::count,
              string_algo::exist,
              string_algo::find,
              string_algo::none,
              string_algo::right_find,
              string_algo::where,
              
              string_algo::all,
           // string_algo::contains,
           // string_algo::count,
           // string_algo::exist,
           // string_algo::find,
              string_algo::match;
           // string_algo::none,
           // string_algo::right_find,
           // string_algo::split,
           // string_algo::where;

    public: // Friend
        friend string_algo;
};

template < char_type type >               basic_string_view ( type )                      -> basic_string_view<type>;
template < char_type type >               basic_string_view ( const type* )               -> basic_string_view<type>;
template < char_type type, class device > basic_string_view ( basic_string<type,device> ) -> basic_string_view<type,device>;