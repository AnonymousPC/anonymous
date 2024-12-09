#pragma once

namespace aux
{
    template < class input_type, class char_type >
    concept char_type_or_general_string_type = std::same_as<input_type,char_type> or general_string_type<input_type,char_type>;
}



/// Class string_algo

template < class string_type,
           class char_type >
class string_algo
{
    private: // Traits
        constexpr static const bool is_view = not requires { &string_type::resize; };
        using string_view_type    = conditional<not aux::string_view_type<string_type>/*see string_global.ipp*/,basic_string_range_view<char_type>,basic_string_view<char_type>>;
        using regex               = basic_regex<char_type>;
        using encode_type         = std::text_encoding;

    public: // Abbreviation
        constexpr int            size        ( ) const;
        constexpr bool           empty       ( ) const;
        constexpr decltype(auto) begin       ( );
        constexpr decltype(auto) begin       ( ) const;
        constexpr decltype(auto) end         ( );
        constexpr decltype(auto) end         ( ) const;
        constexpr decltype(auto) operator [] ( int );
        constexpr decltype(auto) operator [] ( int ) const;

    public: // Array algo
        constexpr       string_type& insert ( aux::array_type_dim_range<int,0,1> auto, const aux::char_type_or_general_string_type<char_type> auto&, const aux::char_type_or_general_string_type<char_type> auto&... ) requires ( not is_view );
        constexpr       string_type& push   (                                          const aux::char_type_or_general_string_type<char_type> auto&, const aux::char_type_or_general_string_type<char_type> auto&... ) requires ( not is_view );

    public: // String algo
        constexpr       bool                    begins_with     ( const general_string_type auto& )                                  const;
        constexpr       string_type&            capitalize      ( );
        constexpr       string_type&            center          ( int, char_type = ' ' )                                                   requires ( not is_view );
        constexpr       string_type&            encode          ( std::text_encoding, std::text_encoding )                                 requires ( not is_view ) and std::same_as<char_type,char>;
        constexpr       bool                    ends_with       ( const general_string_type auto& )                                  const;
        constexpr       string_type&            expand_tabs     ( int = 8 )                                                                requires ( not is_view );
        constexpr       string_type&            format          ( const auto&... args )                                                    requires ( not is_view ) and ( ( std::formattable<decay<decltype(args)>,char> or std::constructible_from<string_type,decay<decltype(args)>> ) and ... );
        constexpr       bool                    is_alnum        ( )                                                                  const;
        constexpr       bool                    is_alpha        ( )                                                                  const;
        constexpr       bool                    is_ascii        ( )                                                                  const;
        constexpr       bool                    is_decimal      ( )                                                                  const;
        constexpr       bool                    is_digit        ( )                                                                  const;
        constexpr       bool                    is_identifier   ( )                                                                  const;
        constexpr       bool                    is_lower        ( )                                                                  const;
        constexpr       bool                    is_space        ( )                                                                  const;
        constexpr       bool                    is_title        ( )                                                                  const;
        constexpr       bool                    is_upper        ( )                                                                  const;
        constexpr       string_type&            join            ( const auto& args )                                                       requires ( not is_view ) and requires { std::declval<string_type>().push(*std::ranges::begin(args)); };
        constexpr       string_type&            left_justify    ( int, char_type = ' ' )                                                   requires ( not is_view );
        constexpr       string_type&            left_strip      ( )                                                                        requires ( not is_view );
        constexpr       string_type&            left_strip      ( const general_string_type auto& )                                        requires ( not is_view );
        constexpr       string_type&            lower           ( );
        constexpr       array<string_view_type> partition       ( const general_string_type auto& );
        constexpr const array<string_view_type> partition       ( const general_string_type auto& )                                  const;
        constexpr       string_type&            right_justify   ( int, char_type = ' ' )                                                   requires ( not is_view );
        constexpr       array<string_view_type> right_partition ( const general_string_type auto& );
        constexpr const array<string_view_type> right_partition ( const general_string_type auto& )                                  const;
        constexpr       array<string_view_type> right_split     ( );
        constexpr const array<string_view_type> right_split     ( )                                                                  const;
        constexpr       array<string_view_type> right_split     ( const general_string_type auto& );
        constexpr const array<string_view_type> right_split     ( const general_string_type auto& )                                  const;
        constexpr       array<string_view_type> right_split     ( const general_string_type auto&, int );
        constexpr const array<string_view_type> right_split     ( const general_string_type auto&, int )                             const;
        constexpr       string_type&            right_strip     ( )                                                                        requires ( not is_view );
        constexpr       string_type&            right_strip     ( const general_string_type auto& )                                        requires ( not is_view );
        constexpr       array<string_view_type> split           ( );
        constexpr const array<string_view_type> split           ( )                                                                  const;
        constexpr       array<string_view_type> split           ( const general_string_type auto& );
        constexpr const array<string_view_type> split           ( const general_string_type auto& )                                  const;
        constexpr       array<string_view_type> split           ( const general_string_type auto&, int );
        constexpr const array<string_view_type> split           ( const general_string_type auto&, int )                             const;
        constexpr       array<string_view_type> split_lines     ( );  
        constexpr const array<string_view_type> split_lines     ( )                                                                  const;
        constexpr       bool                    starts_with     ( const general_string_type auto& )                                  const;
        constexpr       string_type&            strip           ( )                                                                        requires ( not is_view );
        constexpr       string_type&            strip           ( const general_string_type auto& )                                        requires ( not is_view );
        constexpr       string_type&            swap_case       ( );
        constexpr       string_type&            title           ( );
        constexpr       string_type&            upper           ( );
        constexpr       string_type&            zero_fill       ( int )                                                                    requires ( not is_view );

    public: // Array algo (update)
        constexpr       bool                    contains        ( const general_string_type auto& )                                  const;
        constexpr       int                     count           ( const general_string_type auto& )                                  const;
        constexpr       bool                    exist           ( const general_string_type auto& )                                  const;
        constexpr       int                     find            ( const general_string_type auto& )                                  const;
        constexpr       bool                    none            ( const general_string_type auto& )                                  const;
        constexpr       string_type&            remove          ( const general_string_type auto& )                                        requires ( not is_view );
        constexpr       string_type&            replace         ( const general_string_type auto&, const general_string_type auto& )       requires ( not is_view );
        constexpr       int                     right_find      ( const general_string_type auto& )                                  const;
        constexpr       array<int>              where           ( const general_string_type auto& )                                  const;

    public: // Regex
        constexpr       bool                    all             ( const regex& )                                                     const;
        constexpr       bool                    contains        ( const regex& )                                                     const;
        constexpr       int                     count           ( const regex& )                                                     const;
        constexpr       bool                    exist           ( const regex& )                                                     const;
        constexpr       string_view_type        find            ( const regex& );
        constexpr const string_view_type        find            ( const regex& )                                                     const;
        constexpr       bool                    match           ( const regex& )                                                     const;
        constexpr       bool                    none            ( const regex& )                                                     const;
        constexpr       string_type&            remove          ( const regex& )                                                           requires ( not is_view );
        constexpr       string_type&            replace         ( const regex&, const general_string_type auto& )                          requires ( not is_view );
        constexpr       string_view_type        right_find      ( const regex& );
        constexpr const string_view_type        right_find      ( const regex& )                                                     const;
        constexpr       array<string_view_type> split           ( const regex& );
        constexpr const array<string_view_type> split           ( const regex& )                                                     const;
        constexpr       array<string_view_type> where           ( const regex& );
        constexpr const array<string_view_type> where           ( const regex& )                                                     const;

    protected: // Strlen
        constexpr static int strlen ( const char_type* );

    private: // Format Auxiliary
        constexpr static decltype(auto) make_const_ref   ( const auto& );
        constexpr static decltype(auto) make_formattable ( const auto& );
};


/// Global



constexpr bool is_alnum      ( char_type auto );
constexpr bool is_alpha      ( char_type auto );
constexpr bool is_ascii      ( char_type auto );
constexpr bool is_decimal    ( char_type auto );
constexpr bool is_digit      ( char_type auto );
constexpr bool is_identifier ( char_type auto ) = delete;
constexpr bool is_lower      ( char_type auto );
constexpr bool is_space      ( char_type auto );
constexpr bool is_title      ( char_type auto ) = delete;
constexpr bool is_upper      ( char_type auto );
constexpr auto lower         ( char_type auto );
constexpr auto upper         ( char_type auto );



constexpr bool is_alnum      ( const string_type auto& );
constexpr bool is_alpha      ( const string_type auto& );
constexpr bool is_ascii      ( const string_type auto& );
constexpr bool is_decimal    ( const string_type auto& );
constexpr bool is_digit      ( const string_type auto& );
constexpr bool is_identifier ( const string_type auto& );
constexpr bool is_lower      ( const string_type auto& );
constexpr bool is_space      ( const string_type auto& );
constexpr bool is_title      ( const string_type auto& );
constexpr bool is_upper      ( const string_type auto& );
constexpr auto lower         ( const string_type auto& );
constexpr auto upper         ( const string_type auto& );



#include "string_algo.ipp"