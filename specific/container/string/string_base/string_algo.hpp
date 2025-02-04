#pragma once

template < class container,
           class type,
           class device
         >
class string_algo
{
    private: // Base
        using view  = basic_string_view<type,device>;
        using regex = std::regex; // TODO:
        using code  = std::text_encoding;
        constexpr static const int inf = std::numeric_limits<int>::max();

    private: // Typedef
        using value_type      = device::template value_type     <type>;
        using reference       = device::template reference      <type>;
        using const_reference = device::template const_reference<type>;
        using pointer         = device::template pointer        <type>;
        using const_pointer   = device::template const_pointer  <type>;

    private: // Abbreviation
        constexpr decltype(auto) begin       ( );
        constexpr decltype(auto) begin       ( )     const;
        constexpr decltype(auto) end         ( );
        constexpr decltype(auto) end         ( )     const;
        constexpr decltype(auto) data        ( )     const;
        constexpr decltype(auto) size        ( )     const;
        constexpr decltype(auto) empty       ( )     const;
        constexpr decltype(auto) operator [] ( int );
        constexpr decltype(auto) operator [] ( int ) const; 
    
    public: // String algo
        constexpr bool        begins_with     ( view )                  const;
        constexpr bool        ends_with       ( view )                  const;

        constexpr bool        is_alnum        ( )                       const;
        constexpr bool        is_alpha        ( )                       const;
        constexpr bool        is_ascii        ( )                       const;
        constexpr bool        is_blank        ( )                       const;
        constexpr bool        is_cntrl        ( )                       const;
        constexpr bool        is_digit        ( )                       const;
        constexpr bool        is_lower        ( )                       const;
        constexpr bool        is_punct        ( )                       const;
        constexpr bool        is_space        ( )                       const;
        constexpr bool        is_title        ( )                       const;
        constexpr bool        is_upper        ( )                       const;

        constexpr container&  lower           ( );
        constexpr container&  upper           ( );
        constexpr container&  swap_case       ( );

        constexpr container&  capitalize      ( );
        constexpr container&  title           ( );
        constexpr container&  expand_tabs     ( int = 8 );

        constexpr container&  center          ( int, type = ' ' );
        constexpr container&  left_justify    ( int, type = ' ' );
        constexpr container&  right_justify   ( int, type = ' ' );

        constexpr array<view> partition       ( view )                  const;
        constexpr array<view> right_partition ( view )                  const;

        constexpr array<view> split           ( view = ' ', int = inf ) const;
        constexpr array<view> right_split     ( view = ' ', int = inf ) const;
        constexpr array<view> split_lines     ( )                       const;

        constexpr container&  strip           ( view = ' ' );
        constexpr container&  left_strip      ( view = ' ' );
        constexpr container&  right_strip     ( view = ' ' );

        constexpr container&  encode          ( code, code )                  requires same_as<type,char>;
        constexpr container&  format          ( auto&&... f )                 requires ( ( std::formattable<decay<decltype(f)>,char> or constructible_from<container,decay<decltype(f)>> ) and ... );
        constexpr container&  join            ( string_type auto&&... );

    public: // Array
        constexpr bool        contains        ( view )                  const;
        constexpr int         count           ( view )                  const;
        constexpr bool        exist           ( view )                  const;
        constexpr int         find            ( view )                  const;
        constexpr bool        none            ( view )                  const;
        constexpr container&  remove          ( view );
        constexpr container&  replace         ( view, view );
        constexpr int         right_find      ( view )                  const;
        constexpr array<int>  where           ( view )                  const;

    public: // Regex
        constexpr bool        all             ( const regex& )          const;
        constexpr bool        contains        ( const regex& )          const;
        constexpr int         count           ( const regex& )          const;
        constexpr bool        exist           ( const regex& )          const;
        constexpr view        find            ( const regex& )          const;
        constexpr bool        match           ( const regex& )          const;
        constexpr bool        none            ( const regex& )          const;
        constexpr container&  remove          ( const regex& );
        constexpr container&  replace         ( const regex&, view );
        constexpr view        right_find      ( const regex& )          const;
        constexpr array<view> split           ( const regex& )          const;
        constexpr array<view> where           ( const regex& )          const;
};