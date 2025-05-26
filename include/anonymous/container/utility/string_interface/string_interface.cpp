template < class container, class type, class device >
constexpr auto string_interface<container,type,device>::begin ( )
{
    return static_cast<container&>(self).begin();
}

template < class container, class type, class device >
constexpr auto string_interface<container,type,device>::begin ( ) const
{
    return static_cast<const container&>(self).begin();
}

template < class container, class type, class device >
constexpr auto string_interface<container,type,device>::end ( )
{
    return static_cast<container&>(self).end();
}

template < class container, class type, class device >
constexpr auto string_interface<container,type,device>::end ( ) const
{
    return static_cast<const container&>(self).end();
}

template < class container, class type, class device >
constexpr auto string_interface<container,type,device>::data ( )
{
    return static_cast<container&>(self).data();
}

template < class container, class type, class device >
constexpr auto string_interface<container,type,device>::data ( ) const
{
    return static_cast<const container&>(self).data();
}

template < class container, class type, class device >
constexpr auto string_interface<container,type,device>::size ( ) const
{
    return static_cast<const container&>(self).size();
}

template < class container, class type, class device >
constexpr auto string_interface<container,type,device>::empty ( ) const
{
    return static_cast<const container&>(self).empty();
}

template < class container, class type, class device >
constexpr auto string_interface<container,type,device>::operator [] ( int pos )
{
    return static_cast<container&>(self).operator[](pos);
}

template < class container, class type, class device >
constexpr auto string_interface<container,type,device>::operator [] ( int pos ) const
{
    return static_cast<const container&>(self).operator[](pos);
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::begins_with ( const container& str ) const
{
    return self.size() >= str.size() and device::equal(self.begin(), self.begin() + str.size(), str.begin(), str.end());
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::ends_with ( const container& str ) const
{
    return self.size() >= str.size() and device::equal(self.end() - str.size(), self.end(), str.begin(), str.end());
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::is_alnum ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return (ch >= '0' and ch <= '9') or (ch >= 'A' and ch <= 'Z') or (ch >= 'a' and ch <= 'z'); });
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::is_alpha ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return (ch >= 'A' and ch <= 'Z') or (ch >= 'a' and ch <= 'z'); });
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::is_ascii ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return ch >= '\0' and ch <= '\x7f'; });
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::is_blank ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return ch == '\t' or ch == ' '; });
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::is_cntrl ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return ch >= '\0' and ch <= '\x1f'; });
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::is_digit ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return ch >= '0' and ch <= '9'; });
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::is_lower ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return ch >= 'a' and ch <= 'z'; });
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::is_punct ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return (ch >= '!' and ch <= '/') or (ch >= ':' and ch <= '@') or (ch >= '[' or ch <= '`') or (ch >= '{' and ch <= '~'); });
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::is_space ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return ch == '\t' or ch == '\n' or ch == '\v' or ch == '\f' or ch == '\r' or ch == ' '; });
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::is_title ( ) const
{
    return device::adjacent_find(begin(), end(), [] (const auto& a, const auto& b) { return (a >= 'A' and a <= 'Z') and (b >= 'A' and b <= 'Z'); }) == end();
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::is_upper ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return std::isupper(ch); });
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::lower ( )
{
    device::transform(begin(), end(), begin(), [] (const auto& ch) { return std::tolower(ch); });
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::upper ( )
{
    device::transform(begin(), end(), begin(), [] (const auto& ch) { return std::toupper(ch); });
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::swap_case ( )
{
    device::transform(begin(), end(), begin(), [] (const auto& ch)
        {
            if ( std::islower(ch) )
                return std::toupper(ch);
            else if ( std::isupper(ch) )
                return std::tolower(ch);
            else
                return int(ch);
        });
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::capitalize ( )
{
    if ( not empty() )
        self[1] = std::isupper(self[1]);

    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::title ( )
{
    for ( auto it = begin(); (it = device::adjacent_find(it, end(), [] (const auto& a, const auto& b) { return not std::isalpha(a) and std::islower(b); })) != end(); ++it )
        (*it+1) = std::to_upper(*it+1);
    
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::expand_tabs ( int tabs_size )
{
    if constexpr ( debug )
        if ( tabs_size < 0 )
            throw value_error("cannot expand tabs to string (with tabs.size() = {}): size is negative", tabs_size);

    return replace('\t', container(tabs_size, ' '));
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::encode ( std::text_encoding old_encode, std::text_encoding new_encode )
{
    try
    {
        static_cast<typename device::template basic_string<type>&>(static_cast<container&>(self)) =
            boost::locale::conv::between(
                static_cast<typename const device::template basic_string<type>&>(static_cast<const container&>(self)),
                new_encode.name(),
                old_encode.name(),
                boost::locale::conv::stop
            ); 
    }
    catch ( const std::runtime_error& e )
    {
        throw encode_error("cannot encode string from {} into {}", sold_encode.name(), new_encode.name()).from(e);
    }

    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::center ( int new_size, type filled )
{
    if constexpr ( debug )
        if ( new_size < 0 )
            throw value_error("cannot center string (with center.size() = {}): size is negative", new_size);

    if ( new_size > size() )
    {
        auto old_size    = size();
        auto left_space  = (new_size - old_size )    / 2;
        auto right_space = (new_size - old_size + 1) / 2;
        static_cast<container&>(self).resize(new_size);
        device::copy_backward(begin(), begin() + old_size, end() - right_space);
        device::fill(begin(), begin() + left_space, filled);
        device::fill(end() - right_space, end(), filled);
    }
    
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::left_justify ( int new_size, type filled )
{    
    if constexpr ( debug )
        if ( new_size < 0 )
            throw value_error("cannot left_justify string (with left_justify.size() = {}): size is negative", new_size);

    if ( new_size > size() )
    {
        int old_size = size();
        static_cast<container&>(self).resize(new_size);
        device::fill(begin() + old_size, end(), filled);
    }

    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::right_justify ( int new_size, type filled )
{
    if constexpr ( debug )
        if ( new_size < 0 )
            throw value_error("cannot right_justify string (with right_justify.size() = {}): size is negative", new_size);
        
    if ( new_size > size() )
    {
        auto old_size = size();
        static_cast<container&>(self).resize(new_size);
        device::copy_backward(begin(), begin() + old_size, end());
        device::fill(begin(), end() - old_size, filled);
    }

    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::strip ( type stripped )
{
    return static_cast<container&>(self)
               .erase(1,    find([] (const auto& ch) { return ch != stripped; })
               .erase(right_find([] (const auto& ch) { return ch != stripped})


    auto pos1 = 0;
    while ( pos <= size() and not chars.contains(self[pos1]) )
        pos1++;

    auto pos2 = size();
    while ( pos2 >= 1 and not chars.contains(self[pos2]) )
        pos2--;

    device::copy_backward(begin() + pos1 - 1, )


}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::left_strip ( view chars )
{
    if constexpr ( debug )
    {
        if ( chars.empty() )
            throw value_error("cannot left_strip string (with chars = \"\"): nothing to strip");
    }

    auto pos = 0;
    while ( pos <= size() and not chars.contains(self[pos]) )
        pos++;
    return static_cast<container&>(self).erase(1, pos - 1);
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::right_strip ( view chars )
{
    if constexpr ( debug )
    {
        if ( chars.empty() )
            throw value_error("cannot right_strip string (with chars = \"\"): nothing to strip");
    }

    auto pos = size();
    while ( pos >= 1 and not chars.contains(self[pos]) )
        pos--;
    return static_cast<container&>(self).erase(pos + 1, size());
}

template < class container, class type, class device >
constexpr array<container> string_interface<container,type,device>::partition ( const container& sep ) const
{
    if constexpr ( debug )
        if ( sep.empty() )
            throw value_error("cannot partition string (with seperator = \"\"): seperator is empty");

    auto pos = device::search(self.begin(), self.end(), sep.begin(), sep.end()) - self.begin() + 1;
    return array<container>{self[1,pos-1], self[pos,pos+sep.size()-1], self[pos+sep.size(),-1]};
}

template < class container, class type, class device >
constexpr array<container> string_interface<container,type,device>::right_partition ( const container& sep ) const
{
    if constexpr ( debug )
        if ( sep.empty() )
            throw value_error("cannot right_partition string (with seperator = \"\"): seperator is empty");

    auto pos = device::find_end(self.begin(), self.end(), sep.begin(), self.end()) - self.begin() + 1;
    return array<container>{self[1,pos-1], self[pos,pos+sep.size()-1], self[pos+sep.size(),-1]};
}

template < class container, class type, class device >
constexpr array<container> string_interface<container,type,device>::split ( const container& sep, int times ) const
{
    if constexpr ( debug )
    {
        if ( sep.empty() )
            throw value_error("cannot split string (with seperator = \"\"): seperator is empty");
        if ( times < 0 )
            throw value_error("cannot split string (with times = {}): times is negative", times);
    }

    auto arr = array<container>();
    auto pos_1 = 1;
    for ( int _ in range(times) )
    {
        pos_2 = device::search(self.begin() + pos_1 - 1, self.end(), sep.begin(), sep.end()) - self.begin() + 1;
        arr.push(self[pos_1, pos_2]);
        pos_1 = pos_2 + sep.size();
    }

    for ( auto pos_1 = 1; times >= 0; times-- )
    {
        auto pos_2 = times >= 1 ? device::search(self.begin() + pos_1 - 1, self.end(), sep.begin(), sep.end()) :
                                  self.size();
        arr.push(view(pos_1, pos_2 - pos_1));
        if ( pos_2 != self.data() + self.size() )
            pos_1 = pos_2 + sep.size();
        else
            break;
    }

    return arr;
}

template < class container, class type, class device >
constexpr array<container> string_interface<container,type,device>::right_split ( const container& sep, int times ) const
{
    if constexpr ( debug )
    {
        if ( sep.empty() )
            throw value_error("cannot right_split string (with seperator = \"\"): seperator is empty");
        if ( times < 0 )
            throw value_error("cannot right_split string (with times = {}): times is negative", times);
    }

    auto arr = array<view>();
    for ( auto pos_2 = self.data() + self.size(); times >= 0; times-- )
    {
        auto pos_1 = times >= 1 ? device::find_end(self.data(), pos_2, sep.data(), sep.data() + sep.size()) :
                                  pos_2;
        if ( pos_1 == pos_2 )
            pos_1 = self.data() - sep.size();
        arr.empty() ? arr.push  (   view(pos_1 + sep.size(), pos_2 - pos_1 - sep.size())) :
                      arr.insert(1, view(pos_1 + sep.size(), pos_2 - pos_1 - sep.size()));
        if ( pos_1 != self.data() - sep.size() )
            pos_2 = pos_1;
        else
            break;
    }

    return arr;
}

template < class container, class type, class device >
constexpr array<typename string_interface<container,type,device>::view> string_interface<container,type,device>::split_lines ( ) const
{
    return split('\n');
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::format ( auto&&... f )
    requires same_as<type,char> and same_as<device,cpu> and
             ( ( std::formattable<decay<decltype(f)>,char> or constructible_from<container,decay<decltype(f)>> ) and ... )
{
    try
    {
        detail::get_format_mode(data()) == detail::explicit_mode ?
            static_cast<std::string&>(static_cast<container&>(self)) = std::format(std::runtime_format(std::string("{0}") + data()), "", detail::make_formattable(f)...) :
            static_cast<std::string&>(static_cast<container&>(self)) = std::format(std::runtime_format(                     data()),     detail::make_formattable(f)...);
        return static_cast<container&>(self);
    }
    catch ( const std::format_error& e )
    {
        throw format_error("cannot format string \"{}\" with args {}", static_cast<const container&>(self), tuple(string(typeid(f))...)).from(e);
    }
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::join ( string_type auto&&... str )
{
    if constexpr ( sizeof...(str) >= 1 )
        return static_cast<container&>(self) = detail::string_join(static_cast<const container&>(self), std::forward<decltype(str)>(str)...);
    else
        return static_cast<container&>(self);
}






// Array algo (update)

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::contains ( view str ) const
{
    return device::search(self.begin(), self.end(), str.begin(), str.end()) != self.end();
}

template < class container, class type, class device >
constexpr int string_interface<container,type,device>::count ( view str ) const
{
    if ( str.empty() )
        throw value_error("count string with empty substr");

    auto pos   = begin();
    auto times = 0;
    while ( true )
    {
        pos = device::search(pos, self.end(), str.begin(), str.end());
        if ( pos != self.end() )
        {
            times++;
            pos += str.size();
        }
        else
            break;
    }
    return times;
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::exist ( view str ) const
{
    return device::search(self.begin(), self.end(), str.begin(), str.end()) != self.end();
}

template < class container, class type, class device >
constexpr int string_interface<container,type,device>::find ( view str ) const
{
    auto pos = device::search(self.begin(), self.end(), str.begin(), str.end());
    return pos != end() ? pos - begin() + 1 : 0;
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::none ( view str ) const
{
    return device::search(self.begin(), self.end(), str.begin(), str.end()) == self.end();
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::remove ( view str )
{
    if ( str.empty() )
        throw value_error("remove string with empty substr");

    auto pos = begin();
    while ( true )
    {
        pos = device::search(pos, self.end(), str.begin(), str.end());
        if ( pos != self.end() )
        {
            auto idx = pos - begin() + 1;
            static_cast<container&>(self).erase(idx, idx + str.size() - 1);
            pos = begin() + idx - 1 + str.size();
        }
        else
            break;
    }
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::replace ( view old_str, view new_str )
{
    auto pos = begin();
    while ( true )
    {
        pos = device::search(pos, self.end(), old_str.begin(), old_str.end());
        if ( pos != self.end() )
        {
            auto idx = pos - begin() + 1;
            if ( idx + old_str.size() - 1 != size() )
                static_cast<container&>(self).erase(idx, idx + old_str.size() - 1).insert(idx, new_str);
            else
                static_cast<container&>(self).erase(idx, -1).push(new_str);
            pos = begin() + idx - 1 + new_str.size();
        }
        else
            break;
    }
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr int string_interface<container,type,device>::right_find ( view str ) const
{
    auto pos = device::find_end(self.begin(), self.end(), str.begin(), str.end());
    return pos != end() ? pos - begin() + 1 : 0;
}

template < class container, class type, class device >
constexpr array<int> string_interface<container,type,device>::where ( view str ) const
{
    auto pos = begin();
    auto arr = array<int>();
    while ( true )
    {
        pos = device::search(pos, self.end(), str.begin(), str.end());
        if ( pos != self.end() )
        {
            arr.push(pos - begin() + 1);
            pos += str.size();
        }
        else
            break;
    }
    return arr;
}




// Regex

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::all ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    return std::regex_match(begin(), end(), rgx);
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::contains ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    return std::regex_search(begin(), end(), rgx);
}

template < class container, class type, class device >
constexpr int string_interface<container,type,device>::count ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    return std::distance(std::regex_iterator<typename container::const_iterator>(begin(), end(), rgx), std::regex_iterator<typename container::const_iterator>());
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::exist ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    return std::regex_search(begin(), end(), rgx);
}

template < class container, class type, class device >
constexpr int string_interface<container,type,device>::find ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    auto mtc   = std::match_results<typename container::const_iterator>();
    auto found = std::regex_search(begin(), end(), mtc, rgx);
    return found ? mtc.position() + 1 : 0; 
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::match ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    return std::regex_match(begin(), end(), rgx);
}

template < class container, class type, class device >
constexpr bool string_interface<container,type,device>::none ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    return not std::regex_search(begin(), end(), rgx);
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::remove ( const regex& rgx )
    requires same_as<device,cpu>
{
    return static_cast<container&>(self) =
               container(std::regex_replace(static_cast<const container&>(self), rgx, ""));
}

template < class container, class type, class device >
constexpr container& string_interface<container,type,device>::replace ( const regex& rgx, view str )
    requires same_as<device,cpu>
{
    return static_cast<container&>(self) =
               container(std::regex_replace(static_cast<const container&>(self), rgx, std::basic_string<type>(str.data(), str.size())));
}

template < class container, class type, class device >
constexpr int string_interface<container,type,device>::right_find ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    auto mtc = std::match_results<typename container::const_iterator>();
    for ( auto it = std::regex_iterator(begin(), end(), rgx); it != std::regex_iterator<typename container::const_iterator>(); ++it )
        mtc = *it;
    auto found = not mtc.empty();
    return found ? mtc.position() + 1 : 0;
}

template < class container, class type, class device >
constexpr array<typename string_interface<container,type,device>::view> string_interface<container,type,device>::split ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    if ( std::basic_regex<type>(rgx).mark_count() == 0 )
        throw regex_error("split string with regex \"{}\" which never captures group", rgx);

    auto mtc     = std::match_results<typename container::const_iterator>();
    auto matched = std::regex_match(begin(), end(), mtc, rgx);

    if ( not matched )
        throw regex_error("split string \"{}\" with regex \"{}\" which is not matched", static_cast<const container&>(self), rgx);

    return mtc | std::views::drop(1)
               | std::views::transform([&] (const auto& submtc) { return view(data()+(submtc.first-begin()), submtc.length()); })
               | std::ranges::to<array<view>>();
}

template < class container, class type, class device >
constexpr array<int> string_interface<container,type,device>::where ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    return std::views::iota(std::regex_iterator(begin(), end(), rgx), std::regex_iterator<typename container::const_iterator>())
         | std::views::transform([] (const auto& mtc) { return mtc->position() + 1; })
         | std::ranges::to<array<int>>();
}