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
constexpr decltype(auto) string_algo<container,type,device>::data ( )
{
    return static_cast<container&>(self).data();
}

template < class container, class type, class device >
constexpr decltype(auto) string_algo<container,type,device>::data ( ) const
{
    return static_cast<const container&>(self).data();
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
constexpr decltype(auto) string_algo<container,type,device>::operator [] ( int pos )
{
    return static_cast<container&>(self).operator[](pos);
}

template < class container, class type, class device >
constexpr decltype(auto) string_algo<container,type,device>::operator [] ( int pos ) const
{
    return static_cast<const container&>(self).operator[](pos);
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::begins_with ( view str ) const
{
    return self.size() >= str.size() and device::equal(self.begin(), self.begin() + str.size(), str.begin(), str.end());
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::ends_with ( view str ) const
{
    return self.size() >= str.size() and device::equal(self.end() - str.size(), self.end(), str.begin(), str.end());
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_alnum ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return std::isalnum(ch); });
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_alpha ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return std::isalpha(ch); });
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_ascii ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return ch >= char(0) and ch <= char(127); });
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_blank ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return std::isblank(ch); });
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_cntrl ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return std::iscntrl(ch); });
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_digit ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return std::isdigit(ch); });
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_lower ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return std::islower(ch); });
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_punct ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return std::ispunct(ch); });
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_space ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return std::isspace(ch); });
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_title ( ) const
{
    return device::adjacent_find(begin(), end(), [] (const auto& a, const auto& b) { return std::isupper(a) and std::isupper(b); }) == end();
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::is_upper ( ) const
{
    return device::all_of(begin(), end(), [] (const auto& ch) { return std::isupper(ch); });
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::lower ( )
{
    device::transform(begin(), end(), begin(), [] (const auto& ch) { return std::tolower(ch); });
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::upper ( )
{
    device::transform(begin(), end(), begin(), [] (const auto& ch) { return std::toupper(ch); });
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::swap_case ( )
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
constexpr container& string_algo<container,type,device>::capitalize ( )
{
    if ( not empty() )
        self[1] = std::isupper(self[1]);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::title ( )
{
    for ( let pos = begin(); pos != end() + 1; pos++ )
    {
        if ( pos != begin() or std::islower(*pos) )
            *pos = std::toupper(*pos);
        pos = device::adjacent_find(begin(), end(), [] (const auto& a, const auto& b) { return not std::isalpha(a) and std::islower(b); });
    }
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::expand_tabs ( int len )
{
    if ( len < 0 )
        throw string_error("expand string with negative tabs {}", len);
    return replace('\t', basic_string<type,device>(len,' '));
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::center ( int len, type ch )
{
    if ( len < 0 )
        throw string_error("center string with negative size {}", len);
    if ( len > size() )
    {
        let old_size    = size();
        let left_space  = (len - old_size )    / 2;
        let right_space = (len - old_size + 1) / 2;
        static_cast<container&>(self).resize(len);
        device::copy_backward(begin(), begin() + old_size, end() - right_space);
        device::fill(begin(), begin() + left_space, ch);
        device::fill(end() - right_space, end(), ch);
    }
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::left_justify ( int len, type ch )
{    
    if ( len < 0 )
        throw string_error("left_justify string with negative size {}", len);
    if ( len > size() )
    {
        int old_size = size();
        static_cast<container&>(self).resize(len);
        device::fill(begin() + old_size, end(), ch);
    }
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::right_justify ( int len, type ch )
{
    if ( len < 0 )
        throw string_error("right_justify string with negative size {}", len);
    if ( len > size() )
    {
        let old_size = size();
        static_cast<container&>(self).resize(len);
        device::copy_backward(begin(), begin() + old_size, end());
        device::fill(begin(), end() - old_size, ch);
    }
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::view> string_algo<container,type,device>::partition ( view str ) const
{
    if ( str.empty() )
        throw string_error("partition string with empty seperator");
    let pos = device::search(self.data(), self.data() + self.size(), str.data(), str.data() + str.size());
    let arr = pos != self.data() + self.size() ? array<view>{view(self.data(),pos-self.data()), view(pos,str.size()), view(pos+str.size(), self.size()-(pos-self.data())-str.size())} otherwise
                                                 array<view>{view(self.data(),self.size()), view(self.data()+self.size(),0), view(self.data()+self.size(),0)};
    return arr;
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::view> string_algo<container,type,device>::right_partition ( view str ) const
{
    if ( str.empty() )
        throw string_error("right_partition string with empty seperator");
    let pos = device::find_end(self.data(), self.data() + self.size(), str.data(), str.data() + str.size());
    return pos != self.data() + self.size() ? array<view>{view(self.data(),pos-self.data()), view(pos,str.size()), view(pos+str.size(), self.size()-(pos-self.data())-str.size())} otherwise
                                              array<view>{view(self.data(),0), view(self.data(),0), view(self.data(),self.size())};
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::view> string_algo<container,type,device>::split ( view str, int times ) const
{
    if ( str.empty() )
        throw string_error("split string with empty seperator");
    if ( times < 0 )
        throw string_error("split string with negative times {}", times);
    let arr = array<view>();
    for ( let pos_1 = self.data(); times >= 0; times-- )
    {
        let pos_2 = times >= 1 ? device::search(pos_1, self.data() + self.size(), str.data(), str.data() + str.size()) otherwise
                                 self.data() + self.size();
        arr.push(view(pos_1, pos_2 - pos_1));
        if ( pos_2 != self.data() + self.size() )
            pos_1 = pos_2 + str.size();
        else
            break;
    }
    return arr;
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::view> string_algo<container,type,device>::right_split ( view str, int times ) const
{
    if ( str.empty() )
        throw string_error("right_split string with empty seperator");
    if ( times < 0 )
        throw string_error("right_split string with negative times {}", times);
    let arr = array<view>();
    for ( let pos_2 = self.data() + self.size(); times >= 0; times-- )
    {
        let pos_1 = times >= 1 ? device::find_end(self.data(), pos_2, str.data(), str.data() + str.size()) otherwise
                                 pos_2;
        if ( pos_1 == pos_2 )
            pos_1 = self.data() - str.size();
        arr.empty() ? arr.push  (   view(pos_1 + str.size(), pos_2 - pos_1 - str.size())) otherwise
                      arr.insert(1, view(pos_1 + str.size(), pos_2 - pos_1 - str.size()));
        if ( pos_1 != self.data() - str.size() )
            pos_2 = pos_1;
        else
            break;
    }
    return arr;
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::view> string_algo<container,type,device>::split_lines ( ) const
{
    return split('\n');
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::strip ( view chars )
{
    return self.left_strip(chars).right_strip(chars);
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::left_strip ( view chars )
{
    if ( chars.empty() )
        throw string_error("left_strip string with empty strip_list");
    let pos = device::find_if(begin(), end(), [&] (const auto& ch) { return not chars.contains(ch); });
    return static_cast<container&>(self).erase(1, pos - begin());
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::right_strip ( view chars )
{
    if ( chars.empty() )
        throw string_error("left_strip string with empty strip_list");
    let pos = end() - 1;
    while ( pos >= begin() and not chars.contains(*pos) )
        pos--;
    return static_cast<container&>(self).erase(pos - begin() + 1, size());
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::encode ( code old_encode, code new_encode )
    requires same_as<type,char> and same_as<device,cpu> 
{
    if ( old_encode != new_encode )
        try
        {
            static_cast<std::string&>(static_cast<container&>(self)) =
                boost::locale::conv::between(
                    std::basic_string<type>(static_cast<const container&>(self)),
                    new_encode.name(),
                    old_encode.name(),
                    boost::locale::conv::stop
                ); 
        }
        catch ( const boost::locale::conv::conversion_error& e )
        {
            throw encode_error("cannot encode string {} from {} into {}", static_cast<const container&>(self), old_encode.name(), new_encode.name()).from(e);
        }
        catch ( const boost::locale::conv::invalid_charset_error& e )
        {
            throw encode_error("cannot encode string {} from {} into {}", static_cast<const container&>(self), old_encode.name(), new_encode.name()).from(e);
        }

    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::format ( auto&&... f )
    requires same_as<type,char> and same_as<device,cpu> and
             ( ( std::formattable<decay<decltype(f)>,char> or constructible_from<container,decay<decltype(f)>> ) and ... )
{
    try
    {
        detail::get_format_mode(data()) == detail::explicit_mode ?
            static_cast<std::string&>(static_cast<container&>(self)) = std::format(std::runtime_format(std::string("{0}") + data()), "", detail::make_formattable(f)...) otherwise
            static_cast<std::string&>(static_cast<container&>(self)) = std::format(std::runtime_format(                     data()),     detail::make_formattable(f)...);
        return static_cast<container&>(self);
    }
    catch ( const std::format_error& e )
    {
        throw format_error("cannot format string {} with args {}", static_cast<const container&>(self), tuple(string(typeid(f))...)).from(e);
    }
}

namespace detail
{
    auto string_join ( const auto& sep, auto&& arg1, auto&&... args )
    {
        if constexpr ( sizeof...(args) >= 1 )
            return string_join(arg1 + sep, std::forward<decltype(args)>(args)...);
        else
            return arg1 + sep;
    }
    
} // namespace detail


template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::join ( string_type auto&&... str )
{
    if constexpr ( sizeof...(str) >= 1 )
        return static_cast<container&>(self) = detail::string_join(static_cast<const container&>(self), std::forward<decltype(str)>(str)...);
    else
        return static_cast<container&>(self);
}






// Array algo (update)

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::contains ( view str ) const
{
    return device::search(self.begin(), self.end(), str.begin(), str.end()) != self.end();
}

template < class container, class type, class device >
constexpr int string_algo<container,type,device>::count ( view str ) const
{
    if ( str.empty() )
        throw string_error("count string with empty substr");

    let pos   = begin();
    let times = 0;
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
constexpr bool string_algo<container,type,device>::exist ( view str ) const
{
    return device::search(self.begin(), self.end(), str.begin(), str.end()) != self.end();
}

template < class container, class type, class device >
constexpr int string_algo<container,type,device>::find ( view str ) const
{
    let pos = device::search(self.begin(), self.end(), str.begin(), str.end());
    return pos != end() ? pos - begin() + 1 otherwise 0;
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::none ( view str ) const
{
    return device::search(self.begin(), self.end(), str.begin(), str.end()) == self.end();
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::remove ( view str )
{
    if ( str.empty() )
        throw string_error("remove string with empty substr");

    let pos = begin();
    while ( true )
    {
        pos = device::search(pos, self.end(), str.begin(), str.end());
        if ( pos != self.end() )
        {
            let idx = pos - begin() + 1;
            static_cast<container&>(self).erase(idx, idx+str.size()-1);
            pos = begin() + idx - 1 + str.size();
        }
        else
            break;
    }
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::replace ( view old_str, view new_str )
{
    let pos = begin();
    while ( true )
    {
        pos = device::search(pos, self.end(), old_str.begin(), old_str.end());
        if ( pos != self.end() )
        {
            let idx = pos - begin() + 1;
            static_cast<container&>(self).erase(idx, idx+old_str.size()-1).insert(idx, new_str);
            pos = begin() + idx - 1 + new_str.size();
        }
        else
            break;
    }
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr int string_algo<container,type,device>::right_find ( view str ) const
{
    let pos = device::find_end(self.begin(), self.end(), str.begin(), str.end());
    return pos != end() ? pos - begin() + 1 otherwise 0;
}

template < class container, class type, class device >
constexpr array<int> string_algo<container,type,device>::where ( view str ) const
{
    let pos = begin();
    let arr = array<int>();
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
constexpr bool string_algo<container,type,device>::all ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    return std::regex_match(begin(), end(), rgx);
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::contains ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    return std::regex_search(begin(), end(), rgx);
}

template < class container, class type, class device >
constexpr int string_algo<container,type,device>::count ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    return std::distance(std::regex_iterator<typename container::const_iterator>(begin(), end(), rgx), std::regex_iterator<typename container::const_iterator>());
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::exist ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    return std::regex_search(begin(), end(), rgx);
}

template < class container, class type, class device >
constexpr int string_algo<container,type,device>::find ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    let mtc   = std::match_results<typename container::const_iterator>();
    let found = std::regex_search(begin(), end(), mtc, rgx);
    return found ? mtc.position() + 1 otherwise 0; 
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::match ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    return std::regex_match(begin(), end(), rgx);
}

template < class container, class type, class device >
constexpr bool string_algo<container,type,device>::none ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    return not std::regex_search(begin(), end(), rgx);
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::remove ( const regex& rgx )
    requires same_as<device,cpu>
{
    return static_cast<container&>(self) =
               container(std::regex_replace(static_cast<const container&>(self), rgx, ""));
}

template < class container, class type, class device >
constexpr container& string_algo<container,type,device>::replace ( const regex& rgx, view str )
    requires same_as<device,cpu>
{
    return static_cast<container&>(self) =
               container(std::regex_replace(static_cast<const container&>(self), rgx, std::basic_string<type>(str.data(), str.size())));
}

template < class container, class type, class device >
constexpr int string_algo<container,type,device>::right_find ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    let mtc = std::match_results<typename container::const_iterator>();
    for ( let it = std::regex_iterator(begin(), end(), rgx); it != std::regex_iterator<typename container::const_iterator>(); ++it )
        mtc = *it;
    let found = not mtc.empty();
    return found ? mtc.position() + 1 otherwise 0;
}

template < class container, class type, class device >
constexpr array<typename string_algo<container,type,device>::view> string_algo<container,type,device>::split ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    if ( std::basic_regex<type>(rgx).mark_count() == 0 )
        throw regex_error("split string with regex \"{}\" which never captures group", rgx);

    let mtc     = std::match_results<typename container::const_iterator>();
    let matched = std::regex_match(begin(), end(), mtc, rgx);

    if ( not matched )
        throw regex_error("split string \"{}\" with regex \"{}\" which is not matched", static_cast<const container&>(self), rgx);

    return mtc | std::views::drop(1)
               | std::views::transform([&] (const auto& submtc) { return view(data()+(submtc.first-begin()), submtc.length()); })
               | std::ranges::to<array<view>>();
}

template < class container, class type, class device >
constexpr array<int> string_algo<container,type,device>::where ( const regex& rgx ) const
    requires same_as<device,cpu>
{
    return std::views::iota(std::regex_iterator(begin(), end(), rgx), std::regex_iterator<typename container::const_iterator>())
         | std::views::transform([] (const auto& mtc) { return mtc->position() + 1; })
         | std::ranges::to<array<int>>();
}