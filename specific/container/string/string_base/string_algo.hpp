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

    private: // Typedef
        using value_type      = device::template value_type     <type>;
        using reference       = device::template reference      <type>;
        using const_reference = device::template const_reference<type>;
        using pointer         = device::template pointer        <type>;
        using const_pointer   = device::template const_pointer  <type>;

    private: // Abbreviation
        constexpr decltype(auto) begin      ( );
        constexpr decltype(auto) begin      ( ) const;
        constexpr decltype(auto) end        ( );
        constexpr decltype(auto) end        ( ) const;
        constexpr decltype(auto) size       ( ) const;
        constexpr decltype(auto) empty      ( ) const;
        constexpr decltype(auto) c_str      ( ) const;
    
    public: // String algo
        constexpr bool        begins_with     ( view )               const;
        constexpr container&  capitalize      ( );
        constexpr container&  center          ( int,  type = ' ' );
        constexpr container&  encode          ( code, code )               requires std::same_as<type,char> and same_as<device,cpu>;
        constexpr bool        ends_with       ( view )               const;
        constexpr container&  expand_tabs     ( int = 8 );
        constexpr container&  format          ( auto&&... f )         requires ( ( std::formattable<decay<decltype(f)>,char> or constructible_from<container,decay<decltype(f)>> ) and ... );
        constexpr bool        is_alnum        ( )                    const;
        constexpr bool        is_alpha        ( )                    const;
        constexpr bool        is_digit        ( )                    const;
        constexpr bool        is_lower        ( )                    const; // 看std, is_ctrl和is_punct       
        constexpr bool        is_space        ( )                    const;
        constexpr bool        is_upper        ( )                    const;
        constexpr container&  join            ( auto&& r )                 requires string_type<range_value<decltype(r)>>;
        constexpr container&  left_justify    ( int, type = ' ' );
        constexpr container&  left_strip      ( );
        constexpr container&  left_strip      ( view& );
        constexpr container&  lower           ( );
        constexpr array<view> partition       ( view& )              const;
        constexpr container&  right_justify   ( int, type = ' ' );
        constexpr array<view> right_partition ( view )               const;
        constexpr array<view> right_split     ( )                    const;
        constexpr array<view> right_split     ( view )               const;
        constexpr array<view> right_split     ( view, int )          const;
        constexpr container&  right_strip     ( );
        constexpr container&  right_strip     ( view );
        constexpr array<view> split           ( )                    const;
        constexpr array<view> split           ( view )               const;
        constexpr array<view> split           ( view, int )          const;
        constexpr array<view> split_lines     ( )                    const;
        constexpr bool        starts_with     ( view )               const;
        constexpr container&  strip           ( );
        constexpr container&  strip           ( view );
        constexpr container&  swap_case       ( );
        constexpr container&  title           ( );
        constexpr container&  upper           ( );
        constexpr container&  zero_fill       ( int );

    public: // Array algo (update)
        constexpr bool        contains        ( view )               const;
        constexpr int         count           ( view )               const;
        constexpr bool        exist           ( view )               const;
        constexpr int         find            ( view )               const;
        constexpr bool        none            ( view )               const;
        constexpr container&  remove          ( view );
        constexpr container&  replace         ( view, view );
        constexpr int         right_find      ( view )               const;
        constexpr array<int>  where           ( view )               const;

    public: // Regex
        constexpr bool        all             ( const regex& )       const;
        constexpr bool        contains        ( const regex& )       const;
        constexpr int         count           ( const regex& )       const;
        constexpr bool        exist           ( const regex& )       const;
        constexpr view        find            ( const regex& )       const;
        constexpr bool        match           ( const regex& )       const;
        constexpr bool        none            ( const regex& )       const;
        constexpr container&  remove          ( const regex& );
        constexpr container&  replace         ( const regex&, view );
        constexpr view        right_find      ( const regex& )       const;
        constexpr array<view> split           ( const regex& )       const;
        constexpr array<view> where           ( const regex& )       const;
};