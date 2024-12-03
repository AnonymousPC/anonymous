#pragma once
#include "../string_class/string.hpp"

#define templates            template < class string_type, class char_type >
#define string_algo          string_algo<string_type,char_type>
#define derive_of_self       static_cast<string_type&>(self)
#define const_derive_of_self static_cast<const string_type&>(self)

// Abbreviation

templates
constexpr int string_algo::size ( ) const
{
    return const_derive_of_self.size();
}

templates
constexpr bool string_algo::empty ( ) const
{
    return const_derive_of_self.empty();
}

templates
constexpr decltype(auto) string_algo::begin ( )
{
    return derive_of_self.begin();
}

templates
constexpr decltype(auto) string_algo::begin ( ) const
{
    return const_derive_of_self.begin();
}

templates
constexpr decltype(auto) string_algo::end ( )
{
    return derive_of_self.end();
}

templates
constexpr decltype(auto) string_algo::end ( ) const
{
    return const_derive_of_self.end();
}

templates
constexpr decltype(auto) string_algo::operator [] ( int pos )
{
    return derive_of_self [pos];
}

templates
constexpr decltype(auto) string_algo::operator [] ( int pos ) const
{
    return const_derive_of_self [pos];
}



// Array algo

templates
constexpr string_type& string_algo::insert ( aux::array_type_dim_range<int,0,1> auto pos, const aux::char_type_or_general_string_type<char_type> auto& item, const aux::char_type_or_general_string_type<char_type> auto&... args )
    requires ( not is_view )
{
    return derive_of_self.string_type::array_algo::insert(std::move(pos), string_view(item), string_view(args)...);
}

templates
constexpr string_type& string_algo::push ( const aux::char_type_or_general_string_type<char_type> auto& item, const aux::char_type_or_general_string_type<char_type> auto&... args )
    requires ( not is_view )
{
    return derive_of_self.string_type::array_algo::push(string_view(item), string_view(args)...);
}




// String algo

templates
constexpr bool string_algo::begins_with ( const string_view& str ) const
{
    return size() >= str.size() ? std::equal ( begin(), begin() + str.size(), str.begin(), str.end() ) otherwise false;
}

templates
constexpr string_type& string_algo::capitalize ( )
{
    if ( not empty() )
        self[1] = ap::upper ( self[1] );

    return derive_of_self;
}

templates
constexpr string_type& string_algo::center ( int len, char_type ch )
    requires ( not is_view )
{
    if ( len <= size() )
        return derive_of_self;
    else
    {
        int old_size    = size();
        int left_space  = ( len - old_size )     / 2;
        int right_space = ( len - old_size + 1 ) / 2;

        derive_of_self.resize ( len );

        std::copy_backward ( begin(), begin() + old_size, end() - right_space );
        std::fill_n        ( begin(),             left_space,  ch );
        std::fill_n        ( end() - right_space, right_space, ch );

        return derive_of_self;
    }
}

templates
constexpr string_type& string_algo::encode ( encode_type from, encode_type to )
    requires ( not is_view ) and std::same_as<char_type,char>
{
    if ( from != to )
        try
        {
            return derive_of_self = string_type(boost::locale::conv::between(std::basic_string<char_type>(derive_of_self),
                                                                             to.name(),
                                                                             from.name(),
                                                                             boost::locale::conv::stop));
        }
        catch ( const boost::locale::conv::conversion_error& e )
        {
            throw encode_error("cannot encode string {} from {} into {} [[caused by {}: {}]]", const_derive_of_self, from.name(), to.name(), typeid(e), e.what());
        }
        catch ( const boost::locale::conv::invalid_charset_error& e )
        {
            throw encode_error("cannot encode string {} from {} into {} [[caused by {}: {}]]", const_derive_of_self, from.name(), to.name(), typeid(e), e.what());
        }

    else
        return derive_of_self;
}

templates
constexpr bool string_algo::ends_with ( const string_view& str ) const
{
    if ( size() >= str.size() )
        return std::equal ( end() - str.size(), end(), str.begin(), str.end() );
    else
        return false;
}

templates
constexpr string_type& string_algo::expand_tabs ( int tabs )
    requires ( not is_view )
{
    return derive_of_self.replace ( '\t', string_type(tabs, ' ') );
}

templates
constexpr string_type& string_algo::format ( const auto&... args )
    requires ( not is_view ) and std::same_as<char_type,char> and ( ( std::formattable<decltype(args),char_type> or std::constructible_from<string_type,decltype(args)> ) and ... )
{
    try
    {
        let b = begin();
        let e = end();
        let explicit_mode = false;

        while ( true )
        {
            let p = std::find(b, e, '{');
            if ( p == e )
                explicit_mode = false;            // Default mode.
            else if ( std::isdigit(*(p+1)) )
                explicit_mode = true;             // Explicit mode.
            else if ( p+1 < e and *(p+1) != '{' )
                explicit_mode = false;            // Implicit mode.
            else
                { b = p + 2; continue; }          // "{{"
            break;
        }

        if ( explicit_mode )
            return derive_of_self = std::vformat(("{0}" + derive_of_self).c_str(), std::make_format_args("", make_const_ref(make_formattable(args))...)).c_str();

        else /* implicit_mode or default_mode */
            return derive_of_self = std::vformat(derive_of_self.c_str(), std::make_format_args(make_const_ref(make_formattable(args))...)).c_str();
    }

    catch ( const std::format_error& e )
    {
        throw format_error("cannot format string \"{}\" with args {} [[caused by {}: {}]]", derive_of_self, tuple(string(typeid(args))...), typeid(e), e.what());
    }
}

templates
constexpr bool string_algo::is_alnum ( ) const
{
    return ap::is_alnum ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_alpha ( ) const
{
    return ap::is_alpha ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_ascii ( ) const
{
    return ap::is_ascii ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_decimal ( ) const
{
    return ap::is_decimal ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_digit ( ) const
{
    return ap::is_digit ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_identifier ( ) const
{
    return ap::is_identifier ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_lower ( ) const
{
    return ap::is_lower ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_space ( ) const
{
    return ap::is_space ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_title ( ) const
{
    return ap::is_title ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_upper ( ) const
{
    return ap::is_upper ( const_derive_of_self );
}

templates
constexpr string_type& string_algo::join ( const auto& strings )
    requires ( not is_view and requires { string_view(*strings.begin()); } )
{
    if constexpr ( requires { strings.size(); } )
        return derive_of_self = strings
                              | std::views::transform([] (const auto& str) { return string_view(str); })
                              | std::views::join_with(derive_of_self)
                              | std::ranges::to<string_type>(std::accumulate(strings.begin(), strings.end(), 0, [] (const auto& result, const auto& str) { return result + string_view(str).size(); }) + size()*(strings.size()-1));
    else
        return derive_of_self = strings
                              | std::views::transform([] (const auto& str) { return string_view(str); })
                              | std::views::join_with(derive_of_self)
                              | std::ranges::to<string_type>();
}

templates
constexpr string_type& string_algo::left_justify ( int len, const string_view& ch )
    requires ( not is_view )
{
    #if debug
        if ( ch.size() != 1 )
            throw value_error("the fill character {} must be exactly one character long", ch);
    #endif

    if ( len <= size() )
        return derive_of_self;
    else
    {
        int old_size = size();
        derive_of_self.resize(len);
        derive_of_self[old_size+1,-1].fill(ch[1]);
        return derive_of_self;
    }
}

templates
constexpr string_type& string_algo::left_strip ( const string_view& chars )
    requires ( not is_view )
{
    int pos = derive_of_self.string_type::array_algo::find([&] (char_type ch) { return not chars.contains(ch); });

    return pos != 0 ? derive_of_self.erase ( 1, pos - 1 ) otherwise
                      derive_of_self.clear(); // Every letter matches.
}

templates
constexpr string_type& string_algo::lower ( )
{
    return derive_of_self.each ( ap::lower<char_type> );
}

templates
constexpr string_algo::array_of_views string_algo::partition ( const string_view& str )
{
    return const_cast<array_line<views>&&> ( const_cast<const string_algo&>(self).partition(str) );
}

templates
constexpr const string_algo::array_of_views string_algo::partition ( const string_view& str ) const
{
    int pos = find ( str );

    if ( pos != 0 )
        return { const_derive_of_self[1,pos-1], const_derive_of_self[pos,pos+str.size()-1], const_derive_of_self[pos+str.size(),size()] };
    else
        return { const_derive_of_self[1,-1], const_derive_of_self[1,0], const_derive_of_self[1,0] };
}



templates
constexpr string_algo::array_of_views string_algo::right_partition ( const string_view& str )
{
    return const_cast<array_line<views>&&> ( const_cast<const string_algo&>(self).right_partition(str) );
}

templates
constexpr const string_algo::array_of_views string_algo::right_partition ( const string_view& str ) const
{
    int pos = right_find ( str );

    if ( pos != 0 )
        return { const_derive_of_self[1,pos-1], const_derive_of_self[pos,pos+str.size()-1], const_derive_of_self[pos+str.size(),size()] };
    else
        return { const_derive_of_self[1,0], const_derive_of_self[1,0], const_derive_of_self[1,-1] };
}

templates
constexpr string_type& string_algo::right_justify ( int len, const string_view& ch )
    requires ( not is_view )
{
    #if debug
        if ( ch.size() != 1 )
            throw value_error("the fill character {} must be exactly one character long", ch);
    #endif

    if ( len <= size() )
        return derive_of_self;
    else
    {
        int old_size = size();
        derive_of_self.resize(len);
        derive_of_self[-old_size,-1] = derive_of_self[1,old_size];
        derive_of_self[1,-old_size-1].fill(ch[1]);

        return derive_of_self;
    }
}

templates
constexpr string_algo::array_of_views string_algo::right_split ( const string_view& str, int times )
{
    return const_cast<array_line<views>&&> ( const_cast<const string_algo&>(self).right_split(str,times) );
}

templates
constexpr const string_algo::array_of_views string_algo::right_split ( const string_view& str, int times ) const
{
    vector<int> edges = vector{1-str.size()}.push ( where(str) )
                                            .push ( size() + 1 );

    if ( times >= 0 and times < edges.size() - 1 )
        edges.erase ( 2, edges.size() - times - 1 );

    return array_line<views> ( edges.size() - 1, [&] ( int i ) { return const_derive_of_self[edges[i]+str.size(), edges[i+1]-1]; } );
}

templates
constexpr string_type& string_algo::right_strip ( const string_view& chars )
    requires ( not is_view )
{
    int pos = derive_of_self.string_type::array_algo::right_find([&] (char_type ch) { return not chars.contains(ch); });

    return pos != 0 ? derive_of_self.erase ( pos+1, -1 ) otherwise
                      derive_of_self.clear(); // All match to chars.
}

templates
constexpr string_algo::array_of_views string_algo::split ( const string_view& str, int times )
{
    return const_cast<array_line<views>&&> ( const_cast<const string_algo&>(self).split(str,times) );
}

templates
constexpr const string_algo::array_of_views string_algo::split ( const string_view& str, int times ) const
{
    vector<int> edges = vector{1-str.size()}.push ( where(str) )
                                            .push ( size() + 1 );

    if ( times >= 0 and times < edges.size() - 1 )
        edges.erase ( times + 2, -2 );

    return array_line<views> ( edges.size() - 1, [&] ( int i ) { return const_derive_of_self[edges[i]+str.size(), edges[i+1]-1]; } );
}

templates
constexpr string_algo::array_of_views string_algo::split_lines ( )
{
    return const_cast<array_line<views>&&> ( const_cast<const string_algo&>(self).split_lines() );
}

templates
constexpr const string_algo::array_of_views string_algo::split_lines ( ) const
{
    vector<int> edges = vector<int>().push   ( const_derive_of_self.string_type::array_algo::where([] (auto ch) { return ch == '\n' or ch == '\r' or ch == '\f'; }) )
                                     .unique ( [&] ( auto pos1, auto pos2 ) { return pos1 + 1 == pos2 and self[pos1] == '\r' and self[pos2] == '\n'; } )
                                     .insert ( 1, 0 );

    // Split_lines is different from split('\n') as the last line will be ignored if it is empty.
    // For example, "line1\nlinr2\n\n\n" will split_lines() into 4 parts, but split() into 5 parts.
    // Thus, if the last letter is '\n' then regard the last edge as final sign.
    if ( self[-1] != '\n' )
        edges.push ( size() + 1 );

    array_line<views> lines ( edges.size() - 1, [&] ( int i )
    {
        return const_derive_of_self [ ( i != 1 and
                                        i != edges.size() and
                                        self[edges[i]  ] == '\r' and
                                        self[edges[i]+1] == '\n' ) ?
                                      edges[i] + 2 otherwise edges[i] + 1, edges[i+1] - 1 ];
    } );

    return lines;
}

templates
constexpr bool string_algo::starts_with ( const string_view& str ) const
{
    return begins_with ( str );
}

templates
constexpr string_type& string_algo::strip ( const string_view& chars )
    requires ( not is_view )
{
    return derive_of_self.left_strip(chars).right_strip(chars);
}

templates
constexpr string_type& string_algo::swap_case ( )
{
    return derive_of_self.each ( [] ( char_type& ch )
    {
        if ( ap::is_lower(ch) )
            ch = ap::upper(ch);

        else if ( ap::is_upper(ch) )
            ch = ap::lower(ch);
    } );
}

templates
constexpr string_type& string_algo::title ( )
{
    let poses = derive_of_self.adjacent_where([] (auto ch1, auto ch2) { return not ap::is_alpha(ch1) and ap::is_alpha(ch2); })
                              .each([] (int& pos) { ++pos; });
    if ( not empty() )
        poses.insert(1, 1);

    self.lower();
    for ( int pos in poses )
        self[pos] = ap::upper ( self[pos] );

    return derive_of_self;
}

templates
constexpr string_type& string_algo::upper ( )
{
    return derive_of_self.transform ( ap::upper<char_type> );
}

templates
constexpr string_type& string_algo::zero_fill ( int len )
    requires ( not is_view )
{
    return derive_of_self.right_justify(len,'0');
}






// Array algo (update)

templates
constexpr bool string_algo::contains ( const string_view& str ) const
{
    return std::search ( begin(), end(), str.begin(), str.end() ) != end();
}

templates
constexpr int string_algo::count ( const string_view& str ) const
{
    int times = 0;
    for ( auto it = begin(); it != end() + 1; it++ )
    {
        it = std::search ( it, end(), str.begin(), str.end() );
        times++;
    }

    return times - 1;
}

templates
constexpr bool string_algo::exist ( const string_view& str ) const
{
    return std::search ( begin(), end(), str.begin(), str.end() ) != end();
}

templates
constexpr int string_algo::find ( const string_view& str ) const
{
    int pos = std::search ( begin(), end(), str.begin(), str.end() ) - begin() + 1;
    return pos <= size() ? pos otherwise 0;
}

templates
constexpr bool string_algo::none ( const string_view& str ) const
{
    return std::search ( begin(), end(), str.begin(), str.end() ) == end();
}

templates
constexpr string_type& string_algo::replace ( const string_view& from, const string_view& to )
    requires ( not is_view )
{
    int p = 1;

    while ( true )
    {
        int f = p + derive_of_self[p,-1].find(from) - 1;

        if ( f == p - 1 )
            break;
        else
        {
            derive_of_self.erase ( f, f + from.size() - 1 )
                          .insert( f, to );
            p = f + to.size();
        }
    }

    return derive_of_self;
}

templates
constexpr string_type& string_algo::remove ( const string_view& str )
    requires ( not is_view )
{
    int p = 1;

    while ( true )
    {
        int f = p + derive_of_self[p,-1].find(str) - 1;

        if ( f == p - 1 )
            break;
        else
            derive_of_self.erase ( f, f + str.size() - 1 );
    }

    return derive_of_self;
}

templates
constexpr int string_algo::right_find ( const string_view& str ) const
{
    int pos = size() - str.size() + 1;

    while ( pos != 0 )
    {
        if ( const_derive_of_self[pos,pos+str.size()-1] == str )
            return pos;
        pos--;
    }

    return 0;
}

templates
constexpr vector<int> string_algo::where ( const string_view& str ) const
{
    vector<int> poses;
    for ( auto it = begin(); it != end() + 1; it++ )
    {
        it = std::search ( it, end(), str.begin(), str.end() );
        if ( it != end() )
            poses.push ( it - begin() + 1 );
    }

    return poses;
}




// Regex

templates
constexpr bool string_algo::all ( const regex& rgx ) const
{
    return std::regex_match ( begin(), end(), std::basic_regex<char_type>(rgx) );
}

templates
constexpr bool string_algo::contains ( const regex& rgx ) const
{
    return std::regex_search ( begin(), end(), std::basic_regex<char_type>(rgx) );
}

templates
constexpr int string_algo::count ( const regex& rgx ) const
{
    return std::distance ( std::regex_iterator<const char_type*>(begin(), end(), std::basic_regex<char_type>(rgx)), std::regex_iterator<const char_type*>() );
}

templates
constexpr bool string_algo::exist ( const regex& rgx ) const
{
    return std::regex_search ( begin(), end(), std::basic_regex<char_type>(rgx) );
}

templates
constexpr string_algo::views string_algo::find ( const regex& rgx )
{
    return const_cast<views&&> ( const_cast<const string_algo&>(self).find(rgx) );
}

templates
constexpr const string_algo::views string_algo::find ( const regex& rgx ) const
{
    let mtc   = std::match_results<const char_type*>();
    let found = std::regex_search ( begin(), end(), mtc, std::basic_regex<char_type>(rgx) );
    return found ? const_derive_of_self[mtc.position()+1, mtc.position()+mtc.length()] otherwise const_derive_of_self[1,0];
}

templates
constexpr bool string_algo::match ( const regex& rgx ) const
{
    return std::regex_match ( begin(), end(), std::basic_regex<char_type>(rgx) );
}

templates
constexpr bool string_algo::none ( const regex& rgx ) const
{
    return not std::regex_search ( begin(), end(), std::basic_regex<char_type>(rgx) );
}

templates
constexpr string_type& string_algo::replace ( const regex& rgx, const string_view& str )
    requires ( not is_view )
{
    return derive_of_self = string_type ( std::regex_replace ( std::basic_string<char_type>(derive_of_self), std::basic_regex<char_type>(rgx), std::basic_string<char_type>(str) ) );
}

templates
constexpr string_type& string_algo::remove ( const regex& rgx )
    requires ( not is_view )
{
    return derive_of_self = string_type ( std::regex_replace ( std::basic_string<char_type>(derive_of_self), std::basic_regex<char_type>(rgx), std::basic_string<char_type>(0, '\0') ) );
}

templates
constexpr string_algo::views string_algo::right_find ( const regex& rgx )
{
    return const_cast<views&&> ( const_cast<const string_algo&>(self).right_find(std::basic_regex<char_type>(rgx)) );
}

templates
constexpr const string_algo::views string_algo::right_find ( const regex& rgx ) const
{
    let mtc = std::match_results<const char_type*>();
    for ( let it = std::regex_iterator<const char_type*>(begin(), end(), std::basic_regex<char_type>(rgx)); it != std::regex_iterator<const char_type*>(); ++it )
        mtc = *it;
    let found = not mtc.empty();
    return found ? const_derive_of_self[mtc.position()+1, mtc.position()+mtc.length()] otherwise const_derive_of_self[1,0];
}

templates
constexpr string_algo::array_of_views string_algo::split ( const regex& rgx )
{
    return const_cast<array_line<views>&&> ( const_cast<const string_algo&>(self).split(rgx) );
}

templates
constexpr const string_algo::array_of_views string_algo::split ( const regex& rgx ) const
{
    if ( std::basic_regex<char_type>(rgx).mark_count() == 0 )
        throw regex_error("cannot split {} with regex {}: regex has not capture groups", const_derive_of_self, rgx);

    let mtc     = std::match_results<const char_type*>();
    let matched = std::regex_match ( begin(), end(), mtc, std::basic_regex<char_type>(rgx) );

    if ( not matched )
        throw regex_error("cannot split {} with regex {}: string is not matched with regex", const_derive_of_self, rgx);

    return mtc | std::views::drop     (1)
               | std::views::transform([this] (const auto& submtc) { return const_derive_of_self[submtc.first-self.begin()+1, submtc.second-self.begin()]; })
               | std::ranges::to<array_line<views>>();
}

templates
constexpr string_algo::array_of_views string_algo::where ( const regex& rgx )
{
    return const_cast<array_line<views>&&> ( const_cast<const string_algo&>(self).where(rgx) );
}

templates
constexpr const string_algo::array_of_views string_algo::where ( const regex& rgx ) const
{
    let std_regex = std::basic_regex<char_type>(rgx);
    return std::views::iota     (std::regex_iterator<const char_type*>(begin(), end(), std_regex), std::regex_iterator<const char_type*>())
         | std::views::transform([&] (const auto& mtc) { return const_derive_of_self[mtc->position()+1, mtc->position()+mtc->length()]; })
         | std::ranges::to<array_line<views>>();
}


// Strlen

templates
constexpr int string_algo::strlen ( const char_type* addr )
{
    let p = addr;
    while ( *p != char_type('\0') )
        ++p;

    return p - addr;
}





// Auxiliary

templates
constexpr decltype(auto) string_algo::make_const_ref ( const auto& item )
{
    return item;
}

templates
constexpr decltype(auto) string_algo::make_formattable ( const auto& item )
{
    if constexpr ( std::formattable<decltype(item),char_type> )
        return item;
    else
        return string_type(item);
}






/// Global


constexpr bool is_alnum ( char_type auto ch )
{
    return ( ch >= 'a' and ch <= 'z' ) or ( ch >= 'A' and ch <= 'Z' ) or ( ch >= '0' and ch <= '9' );
}

constexpr bool is_alpha ( char_type auto ch )
{
    return ( ch >= 'a' and ch <= 'z' ) or ( ch >= 'A' and ch <= 'Z' );
}

constexpr bool is_ascii ( char_type auto ch )
{
    return ch >= 0 and ch <= 127;
}

constexpr bool is_decimal ( char_type auto ch )
{
    return ( ch >= '0' and ch <= '9' ) or ch == '.';
}

constexpr bool is_digit ( char_type auto ch )
{
    return ch >= '0' and ch <= '9';
}

constexpr bool is_lower ( char_type auto ch )
{
    return ch >= 'a' and ch <= 'z';
}

constexpr bool is_space ( char_type auto ch )
{
    return ch == ' ' or ch == '\f' or ch == '\n' or ch == '\r' or ch == '\t' or ch == '\v';
}

constexpr bool is_upper ( char_type auto ch )
{
    return ch >= 'A' and ch <= 'Z';
}

constexpr auto lower ( char_type auto ch )
{
    using result_type = decltype(ch);

    if ( is_upper ( ch ) )
        return result_type ( ch + 'a' - 'A' );
    else
        return ch;
}

constexpr auto upper ( char_type auto ch )
{
    using result_type = decltype(ch);

    if ( is_lower ( ch ) )
        return result_type ( ch + 'A' - 'a' );
    else
        return ch;
}



constexpr bool is_alnum ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_alnum(ch); } );
}

constexpr bool is_alpha ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_alpha(ch); } );
}

constexpr bool is_ascii ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_ascii(ch); } );
}

constexpr bool is_decimal ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_decimal(ch); } )
                            and std::count  ( view.begin(), view.end(), '.' ) <= 1
                            and std::count  ( view.begin(), view.end(), '-' ) <= 1;
}

constexpr bool is_digit ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_digit(ch); } );
}

constexpr bool is_identifier ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_alnum(ch) or ch == '_'; } )
                            and ( is_alpha ( view[1] ) or view[1] == '_' );
}

constexpr bool is_lower ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_lower(ch); } );
}

constexpr bool is_space ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_space(ch); } );
}

constexpr bool is_title ( const string_type auto& str )
{
    auto view = basic_string_view ( str );

    return not view.empty() and std::adjacent_find ( view.begin(), view.end(), [] ( auto ch1, auto ch2 ) { return not ap::is_alnum(ch1) and ap::is_lower(ch2); } ) == view.end()
                            and std::any_of        ( view.begin(), view.end(), [] ( auto ch )            { return ap::is_upper(ch); } );
}

constexpr bool is_upper ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_upper(ch); } );
}

constexpr auto lower ( const string_type auto& str )
{
    return basic_string(str).lower();
}

constexpr auto upper ( const string_type auto& str )
{
    return basic_string(str).upper();
}








#undef templates
#undef string_algo
#undef derive_of_self
#undef const_derive_of_self
