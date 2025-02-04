#pragma once

template < class container, class type, class device >
constexpr decltype(auto) string_algo<container,type,device>::begin ( )
{
    return static_cast<container&>(self).begin();
}

template < class container, class type, class device >
constexpr decltype(auto) string_algo<container,type,device>::begin ( ) const
{
    return static_cast<const container&>(self).begin();
}

template < class container, class type, class device >
constexpr decltype(auto) string_algo<container,type,device>::end ( )
{
    return static_cast<container&>(self).end();
}

template < class container, class type, class device >
constexpr decltype(auto) string_algo<container,type,device>::end ( ) const
{
    return static_cast<const container&>(self).end();
}

template < class container, class type, class device >
constexpr decltype(auto) string_algo<container,type,device>::size ( ) const
{
    return static_cast<const container&>(self).size();
}

template < class container, class type, class device >
constexpr decltype(auto) string_algo<container,type,device>::empty ( ) const
{
    return static_cast<const container&>(self).empty();
}

template < class container, class type, class device >
constexpr decltype(auto) string_algo<container,type,device>::c_str ( ) const
{
    return static_cast<const container&>(self).c_str();
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::begins_with ( view str ) const
{
    return self.size() >= str.size() and
           device::equal(self.begin(), self.begin() + str.size(), str.begin(), str.end());
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::capitalize ( )
{
    if ( not empty() )
        self[1] = std::isupper(self[1]);
    return static_cast<container_type&>(self);
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::center ( int len, type ch )
{
    if ( len <= size() )
        return static_cast<container_type&>(self);
    else
    {
        let old_sz   = size();
        let left_ws  = (len - old_size )    / 2;
        let right_ws = (len - old_size + 1) / 2;
        static_cast<container_type&>(self).resize(len);
        device::copy_backward(begin(), begin() + old_sz, end() - right_ws);
        device::fill(begin(), begin() + left_ws, ch);
        device::fill(end() - right_ws, end(), ch);
        return static_cast<container_type&>(self);
    }
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::encode ( code old_encode, code new_encode )
    requires std::same_as<char_type,char>
{
    if ( old_encode != new_encode )
        try
        {
            return static_cast<container&>(self) =
                       boost::locale::conv::between(
                           std::basic_string<char_type>(derive_of_self),
                           new_encode.name(),
                           old_encode.name(),
                           boost::locale::conv::stop
                       );
        }
        catch ( const boost::locale::conv::conversion_error& e )
        {
            throw encode_error("cannot encode string {} from {} into {}", static_cast<const container_type&>(self), old_encode.name(), new_encode.name()).from(e);
        }
        catch ( const boost::locale::conv::invalid_charset_error& e )
        {
            throw encode_error("cannot encode string {} from {} into {}", static_cast<const container_type&>(self), old_encode.name(), new_encode.name()).from(e);
        }
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::ends_with ( view str ) const
{
    return self.size() >= str.size() and
           device::equal(self.end() - str.size(), self.end(), str.begin(), str.end());
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::expand_tabs ( int len )
{
    #if debug
        if ( len < 0 )
            throw value_error("expand string with negative tabs {}", len);
    #endif
    return replace('\t', basic_string<type,device>(tabs,' '));
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::format ( auto&&... f )
    requires ( ( std::formattable<decay<decltype(f)>,char> or constructible_from<container_type,decay<decltype(f)>> ) and ... )
{
    try
    {
        return detail::get_format_mode(c_str()) == detail::explicit_mode ?
                   static_cast<container_type&>(self) = std::format(std::runtime_format(std::string("{0}") + c_str()), "", detail::make_formattable(args)...) otherwise
                   static_cast<container_type&>(self) = std::format(std::runtime_format(                     c_str()),     detail::make_formattable(args)...));
    }
    catch ( const std::format_error& e )
    {
        throw format_error("cannot format string {} with args {}", static_cast<const container&>(self), tuple(string(typeid(args))...)).from(e);
    }
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_alnum ( ) const
{
    return device::all_of(begin(), end(), std::isalnum<type>);
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_alpha ( ) const
{
    return device::all_of(begin(), end(), std::isalpha<type>);
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_digit ( ) const
{
    return device::all_of(begin(), end(), std::isdigit<type>);
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_lower ( ) const
{
    return device::all_of(begin(), end(), std::islower<type>);
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_space ( ) const
{
    return device::all_of(begin(), end(), std::isspace<type>);
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_upper ( ) const
{
    return device::all_of(begin(), end(), std::isupper<type>);
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::join ( const auto& args )
    requires ( not is_view ) and requires { std::declval<container_type>().push(*std::ranges::begin(args)); }
{
    if constexpr ( requires { args.size(); } )
        return derive_of_self = args
                              | std::views::transform([] (const auto& str) { return basic_string_view<char_type>(str); })
                              | std::views::join_with(derive_of_self)
                              | std::ranges::to<container_type>(std::accumulate(args.begin(), args.end(), 0,
                                                                             [] (const auto& result, const auto& str) { return result + basic_string_view<char_type>(str).size(); }) + (args.size()-1) * size());
    else
        return derive_of_self = args
                              | std::views::transform([] (const auto& str) { return basic_string_view<char_type>(str); })
                              | std::views::join_with(derive_of_self)
                              | std::ranges::to<container_type>();
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::left_justify ( int len, char_type ch )
    requires ( not is_view )
{
    if ( len <= size() )
        return derive_of_self;
    else
    {
        int old_size = size();
        derive_of_self.resize(len);
        derive_of_self[old_size+1,-1].fill(ch);
        return derive_of_self;
    }
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::left_strip ( )
    requires ( not is_view )
{
    return left_strip(' ');
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::left_strip ( const general_string_type auto& chars )
    requires ( not is_view )
{
    let sv = basic_string_view<char_type>(chars);

    int pos = derive_of_self.container_type::array_algo::find([&] (char_type ch) { return not sv.contains(ch); });
    return pos != 0 ? derive_of_self.erase ( 1, pos - 1 ) otherwise
                      derive_of_self.clear(); // Every letter matches.
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::lower ( )
{
    return derive_of_self.each ( ap::lower<char_type> );
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::partition ( const general_string_type auto& str )
{
    return const_cast<const string_algo<container,type,device>&>(self).partition(str);
}

template < class container, class type, class device >
constexpr const array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::partition ( const general_string_type auto& str ) const
{
    let sv = basic_string_view<char_type>(str);

    int pos = find(sv);
    if ( pos != 0 )
        return { const_derive_of_self[1,pos-1], const_derive_of_self[pos,pos+sv.size()-1], const_derive_of_self[pos+sv.size(),size()] };
    else
        return { const_derive_of_self[1,-1], const_derive_of_self[1,0], const_derive_of_self[1,0] };
}



template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::right_partition ( const general_string_type auto& str )
{
    return const_cast<const string_algo<container,type,device>&>(self).right_partition(str);
}

template < class container, class type, class device >
constexpr const array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::right_partition ( const general_string_type auto& str ) const
{
    let sv = basic_string_view<char_type>(str);

    int pos = right_find(sv);
    if ( pos != 0 )
        return { const_derive_of_self[1,pos-1], const_derive_of_self[pos,pos+sv.size()-1], const_derive_of_self[pos+sv.size(),size()] };
    else
        return { const_derive_of_self[1,0], const_derive_of_self[1,0], const_derive_of_self[1,-1] };
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::right_justify ( int len, char_type ch )
    requires ( not is_view )
{
    if ( len <= size() )
        return derive_of_self;
    else
    {
        int old_size = size();
        derive_of_self.resize(len);
        derive_of_self[-old_size,-1] = derive_of_self[1,old_size];
        derive_of_self[1,-old_size-1].fill(ch);
        return derive_of_self;
    }
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::right_split ( )
{
    return const_cast<const string_algo<container,type,device>&>(self).right_split();
}

template < class container, class type, class device >
constexpr const array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::right_split ( ) const
{
    return right_split(' ');
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::right_split ( const general_string_type auto& str )
{
    return const_cast<const string_algo<container,type,device>&>(self).right_split(str);
}

template < class container, class type, class device >
constexpr const array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::right_split ( const general_string_type auto& str ) const
{
    let sv = basic_string_view<char_type>(str);

    vector<int> edges = vector{1-sv.size()}.push ( where(sv) )
                                           .push ( size() + 1 );
    return array<string_view_type> ( edges.size() - 1, [&] ( int i ) { return const_derive_of_self[edges[i]+sv.size(), edges[i+1]-1]; } );
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::right_split ( const general_string_type auto& str, int times )
{
    return const_cast<const string_algo<container,type,device>&>(self).right_split(str, times);
}

template < class container, class type, class device >
constexpr const array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::right_split ( const general_string_type auto& str, int times ) const
{
    #if debug
        if ( times < 0 )
            throw value_error("right-split string with negative times {}", times);
    #endif

    let sv = basic_string_view<char_type>(str);

    vector<int> edges = vector{1-sv.size()}.push ( where(sv) )
                                           .push ( size() + 1 );
    if ( times < edges.size() - 1 )
        edges.erase ( 2, edges.size() - times - 1 );
    return array<string_view_type> ( edges.size() - 1, [&] ( int i ) { return const_derive_of_self[edges[i]+sv.size(), edges[i+1]-1]; } );
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::right_strip ( )
    requires ( not is_view )
{
    return right_strip(' ');
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::right_strip ( const general_string_type auto& chars )
    requires ( not is_view )
{
    let sv = basic_string_view<char_type>(chars);

    int pos = derive_of_self.container_type::array_algo::right_find([&] (char_type ch) { return not sv.contains(ch); });
    return pos != 0 ? derive_of_self.erase ( pos+1, -1 ) otherwise
                      derive_of_self.clear(); // All match to chars.
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::split ( )
{
    return const_cast<const string_algo<container,type,device>&>(self).split();
}

template < class container, class type, class device >
constexpr const array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::split ( ) const
{
    return split(' ');
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::split ( const general_string_type auto& str )
{
    return const_cast<const string_algo<container,type,device>&>(self).split(str);
}

template < class container, class type, class device >
constexpr const array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::split ( const general_string_type auto& str ) const
{
    let sv = basic_string_view<char_type>(str);

    vector<int> edges = vector{1-sv.size()}.push ( where(sv) )
                                           .push ( size() + 1 );
    return array<string_view_type> ( edges.size() - 1, [&] ( int i ) { return const_derive_of_self[edges[i]+sv.size(), edges[i+1]-1]; } );
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::split ( const general_string_type auto& str, int times )
{
    return const_cast<const string_algo<container,type,device>&>(self).split(str, times);
}

template < class container, class type, class device >
constexpr const array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::split ( const general_string_type auto& str, int times ) const
{
    let sv = basic_string_view<char_type>(str);

    vector<int> edges = vector{1-sv.size()}.push ( where(sv) )
                                           .push ( size() + 1 );

    if ( times >= 0 and times < edges.size() - 1 )
        edges.erase ( times + 2, -2 );

    return array<string_view_type> ( edges.size() - 1, [&] ( int i ) { return const_derive_of_self[edges[i]+sv.size(), edges[i+1]-1]; } );
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::split_lines ( )
{
    return const_cast<const string_algo<container,type,device>&>(self).split_lines();
}

template < class container, class type, class device >
constexpr const array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::split_lines ( ) const
{
    vector<int> edges = vector<int>().push   ( const_derive_of_self.container_type::array_algo::where([] (auto ch) { return ch == '\n' or ch == '\r' or ch == '\f'; }) )
                                     .unique ( [&] ( auto pos1, auto pos2 ) { return pos1 + 1 == pos2 and self[pos1] == '\r' and self[pos2] == '\n'; } )
                                     .insert ( 1, 0 );

    // Split_lines is different from split('\n') as the last line will be ignored if it is empty.
    // For example, "line1\nline2\n\n\n" will split_lines() into 4 parts, but split() into 5 parts.
    // Thus, if the last letter is '\n' then regard the last edge as final sign.
    if ( self[-1] != '\n' )
        edges.push ( size() + 1 );

    return array<string_view_type> ( edges.size() - 1, [&] ( int i )
    {
        return const_derive_of_self [ ( i != 1 and
                                        i != edges.size() and
                                        self[edges[i]  ] == '\r' and
                                        self[edges[i]+1] == '\n' ) ?
                                      edges[i] + 2 otherwise edges[i] + 1, edges[i+1] - 1 ];
    } );
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::starts_with ( const general_string_type auto& str ) const
{
    let sv = basic_string_view<char_type>(str);
    return begins_with(sv);
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::strip ( )
    requires ( not is_view )
{
    return strip(' ');
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::strip ( const general_string_type auto& chars )
    requires ( not is_view )
{
    let sv = basic_string_view<char_type>(chars);
    return derive_of_self.left_strip(sv).right_strip(sv);
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::swap_case ( )
{
    return derive_of_self.each ( [] ( char_type& ch )
    {
        if ( ap::is_lower(ch) )
            ch = ap::upper(ch);

        else if ( ap::is_upper(ch) )
            ch = ap::lower(ch);
    } );
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::title ( )
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

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::upper ( )
{
    return derive_of_self.transform ( ap::upper<char_type> );
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::zero_fill ( int len )
    requires ( not is_view )
{
    return derive_of_self.right_justify(len,'0');
}






// Array algo (update)

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::contains ( const general_string_type auto& str ) const
{
    let sv = basic_string_view<char_type>(str);
    return std::search ( begin(), end(), sv.begin(), sv.end() ) != end();
}

template < class container, class type, class device >
constexpr int string_algo<container,type,device>::count ( const general_string_type auto& str ) const
{
    let sv = basic_string_view<char_type>(str);

    int times = 0;
    for ( auto it = begin(); it != end() + 1; it++ )
    {
        it = std::search ( it, end(), sv.begin(), sv.end() );
        times++;
    }
    return times - 1;
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::exist ( const general_string_type auto& str ) const
{
    let sv = basic_string_view<char_type>(str);
    return std::search ( begin(), end(), sv.begin(), sv.end() ) != end();
}

template < class container, class type, class device >
constexpr int string_algo<container,type,device>::find ( const general_string_type auto& str ) const
{
    let sv = basic_string_view<char_type>(str);
    int pos = std::search ( begin(), end(), sv.begin(), sv.end() ) - begin() + 1;
    return pos <= size() ? pos otherwise 0;
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::none ( const general_string_type auto& str ) const
{
    let sv = basic_string_view<char_type>(str);
    return std::search ( begin(), end(), sv.begin(), sv.end() ) == end();
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::remove ( const general_string_type auto& str )
    requires ( not is_view )
{
    let sv = basic_string_view<char_type>(str);

    int p = 1;
    while ( true )
    {
        int f = p + derive_of_self[p,-1].find(sv) - 1;
        if ( f == p - 1 )
            break;
        else
            derive_of_self.erase ( f, f + sv.size() - 1 );
    }
    return derive_of_self;
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::replace ( const general_string_type auto& str1, const general_string_type auto& str2 )
    requires ( not is_view )
{
    let sv1 = basic_string_view<char_type>(str1);
    let sv2 = basic_string_view<char_type>(str2);

    int p = 1;
    while ( true )
    {
        int f = p + derive_of_self[p,-1].find(sv1) - 1;
        if ( f == p - 1 )
            break;
        else
        {
            derive_of_self.erase ( f, f + sv1.size() - 1 )
                          .insert( f, sv2 );
            p = f + sv2.size();
        }
    }
    return derive_of_self;
}

template < class container, class type, class device >
constexpr int string_algo<container,type,device>::right_find ( const general_string_type auto& str ) const
{
    let sv = basic_string_view<char_type>(str);

    int pos = size() - sv.size() + 1;
    while ( pos != 0 )
    {
        if ( const_derive_of_self[pos,pos+sv.size()-1] == sv )
            return pos;
        pos--;
    }
    return 0;
}

template < class container, class type, class device >
constexpr array<int> string_algo<container,type,device>::where ( const general_string_type auto& str ) const
{
    let sv = basic_string_view<char_type>(str);

    array<int> poses;
    for ( auto it = begin(); it != end() + 1; it++ )
    {
        it = std::search ( it, end(), sv.begin(), sv.end() );
        if ( it != end() )
            poses.push ( it - begin() + 1 );
    }
    return poses;
}




// Regex

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::all ( const regex& rgx ) const
{
    return std::regex_match ( begin(), end(), std::basic_regex<char_type>(rgx) );
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::contains ( const regex& rgx ) const
{
    return std::regex_search ( begin(), end(), std::basic_regex<char_type>(rgx) );
}

template < class container, class type, class device >
constexpr int string_algo<container,type,device>::count ( const regex& rgx ) const
{
    return std::distance ( std::regex_iterator<const char_type*>(begin(), end(), std::basic_regex<char_type>(rgx)), std::regex_iterator<const char_type*>() );
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::exist ( const regex& rgx ) const
{
    return std::regex_search ( begin(), end(), std::basic_regex<char_type>(rgx) );
}

template < class container, class type, class device >
constexpr string_algo<container,type,device>::string_view_type string_algo<container,type,device>::find ( const regex& rgx )
{
    return const_cast<const string_algo<container,type,device>&>(self).find(rgx);
}

template < class container, class type, class device >
constexpr const string_algo<container,type,device>::string_view_type string_algo<container,type,device>::find ( const regex& rgx ) const
{
    let mtc   = std::match_results<const char_type*>();
    let found = std::regex_search ( begin(), end(), mtc, std::basic_regex<char_type>(rgx) );
    return found ? const_derive_of_self[mtc.position()+1, mtc.position()+mtc.length()] otherwise const_derive_of_self[1,0];
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::match ( const regex& rgx ) const
{
    return std::regex_match ( begin(), end(), std::basic_regex<char_type>(rgx) );
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::none ( const regex& rgx ) const
{
    return not std::regex_search ( begin(), end(), std::basic_regex<char_type>(rgx) );
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::remove ( const regex& rgx )
    requires ( not is_view )
{
    return derive_of_self = container_type ( std::regex_replace ( std::basic_string<char_type>(derive_of_self), std::basic_regex<char_type>(rgx), std::basic_string<char_type>() ) );
}

template < class container, class type, class device >
constexpr container_type& string_algo<container,type,device>::replace ( const regex& rgx, const general_string_type auto& str )
    requires ( not is_view )
{
    return derive_of_self = container_type ( std::regex_replace ( std::basic_string<char_type>(derive_of_self), std::basic_regex<char_type>(rgx), std::basic_string<char_type>(str) ) );
}

template < class container, class type, class device >
constexpr string_algo<container,type,device>::string_view_type string_algo<container,type,device>::right_find ( const regex& rgx )
{
    return const_cast<const string_algo<container,type,device>&>(self).right_find(std::basic_regex<char_type>(rgx));
}

template < class container, class type, class device >
constexpr const string_algo<container,type,device>::string_view_type string_algo<container,type,device>::right_find ( const regex& rgx ) const
{
    let mtc = std::match_results<const char_type*>();
    for ( let it = std::regex_iterator<const char_type*>(begin(), end(), std::basic_regex<char_type>(rgx)); it != std::regex_iterator<const char_type*>(); ++it )
        mtc = *it;
    let found = not mtc.empty();
    return found ? const_derive_of_self[mtc.position()+1, mtc.position()+mtc.length()] otherwise const_derive_of_self[1,0];
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::split ( const regex& rgx )
{
    return const_cast<const string_algo<container,type,device>&>(self).split(rgx);
}

template < class container, class type, class device >
constexpr const array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::split ( const regex& rgx ) const
{
    if ( std::basic_regex<char_type>(rgx).mark_count() == 0 )
        throw regex_error("cannot split string \"{}\" with regex \"{}\": regex always capture none groups", const_derive_of_self, rgx);

    let mtc     = std::match_results<const char_type*>();
    let matched = std::regex_match ( begin(), end(), mtc, std::basic_regex<char_type>(rgx) );

    if ( not matched )
        throw regex_error("cannot split string \"{}\" with regex \"{}\": string is not matched with regex", const_derive_of_self, rgx);

    return mtc | std::views::drop     (1)
               | std::views::transform([this] (const auto& submtc) { return const_derive_of_self[submtc.first-self.begin()+1, submtc.second-self.begin()]; })
               | std::ranges::to<array<string_view_type>>();
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::where ( const regex& rgx )
{
    return const_cast<const string_algo<container,type,device>&>(self).where(rgx);
}

template < class container, class type, class device >
constexpr const array<typename string_algo<container,type,device>::string_view_type> string_algo<container,type,device>::where ( const regex& rgx ) const
{
    let std_regex = std::basic_regex<char_type>(rgx);
    return std::views::iota     (std::regex_iterator<const char_type*>(begin(), end(), std_regex), std::regex_iterator<const char_type*>())
         | std::views::transform([&] (const auto& mtc) { return const_derive_of_self[mtc->position()+1, mtc->position()+mtc->length()]; })
         | std::ranges::to<array<string_view_type>>();
}


// Strlen

template < class container, class type, class device >
constexpr int string_algo<container,type,device>::strlen ( const char_type* addr )
{
    let p = addr;
    while ( *p != char_type('\0') )
        ++p;

    return p - addr;
}





// Auxiliary

template < class container, class type, class device >
constexpr decltype(auto) string_algo<container,type,device>::make_const_ref ( const auto& item )
{
    return item;
}

template < class container, class type, class device >
constexpr decltype(auto) string_algo<container,type,device>::make_formattable ( const auto& item )
{
    if constexpr ( std::formattable<decltype(item),char_type> )
        return item;
    else
        return basic_string<char_type>(item);
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



constexpr bool is_alnum ( const container_type auto& str )
{
    auto sv = basic_string_view ( str );
    return not sv.empty() and std::all_of ( sv.begin(), sv.end(), [] ( auto ch ) { return ap::is_alnum(ch); } );
}

constexpr bool is_alpha ( const container_type auto& str )
{
    auto sv = basic_string_view ( str );
    return not sv.empty() and std::all_of ( sv.begin(), sv.end(), [] ( auto ch ) { return ap::is_alpha(ch); } );
}

constexpr bool is_ascii ( const container_type auto& str )
{
    auto sv = basic_string_view ( str );
    return not sv.empty() and std::all_of ( sv.begin(), sv.end(), [] ( auto ch ) { return ap::is_ascii(ch); } );
}

constexpr bool is_decimal ( const container_type auto& str )
{
    auto sv = basic_string_view ( str );
    return not sv.empty() and std::all_of ( sv.begin(), sv.end(), [] ( auto ch ) { return ap::is_decimal(ch); } )
                          and std::count  ( sv.begin(), sv.end(), '.' ) <= 1
                          and std::count  ( sv.begin(), sv.end(), '-' ) <= 1;
}

constexpr bool is_digit ( const container_type auto& str )
{
    auto sv = basic_string_view ( str );
    return not sv.empty() and std::all_of ( sv.begin(), sv.end(), [] ( auto ch ) { return ap::is_digit(ch); } );
}

constexpr bool is_identifier ( const container_type auto& str )
{
    auto sv = basic_string_view ( str );
    return not sv.empty() and std::all_of ( sv.begin(), sv.end(), [] ( auto ch ) { return ap::is_alnum(ch) or ch == '_'; } )
                          and ( is_alpha ( sv[1] ) or sv[1] == '_' );
}

constexpr bool is_lower ( const container_type auto& str )
{
    auto sv = basic_string_view ( str );
    return not sv.empty() and std::all_of ( sv.begin(), sv.end(), [] ( auto ch ) { return ap::is_lower(ch); } );
}

constexpr bool is_space ( const container_type auto& str )
{
    auto sv = basic_string_view ( str );
    return not sv.empty() and std::all_of ( sv.begin(), sv.end(), [] ( auto ch ) { return ap::is_space(ch); } );
}

constexpr bool is_title ( const container_type auto& str )
{
    auto sv = basic_string_view ( str );

    return not sv.empty() and std::adjacent_find ( sv.begin(), sv.end(), [] ( auto ch1, auto ch2 ) { return not ap::is_alnum(ch1) and ap::is_lower(ch2); } ) == sv.end()
                          and std::any_of        ( sv.begin(), sv.end(), [] ( auto ch )            { return ap::is_upper(ch); } );
}

constexpr bool is_upper ( const container_type auto& str )
{
    auto sv = basic_string_view ( str );
    return not sv.empty() and std::all_of ( sv.begin(), sv.end(), [] ( auto ch ) { return ap::is_upper(ch); } );
}

constexpr auto lower ( const container_type auto& str )
{
    return basic_string(str).lower();
}

constexpr auto upper ( const container_type auto& str )
{
    return basic_string(str).upper();
}








#undef template < class container, class type, class device >
#undef string_algo<container,type,device>
#undef derive_of_self
#undef const_derive_of_self
