template < class type, class device >
constexpr bool detail::char_traits<type,device>::is_ascii ( const type& ch )
{
    return ( greater_equal(ch, '\x00') and less_equal(ch, '\x7f') );
}

template < class type, class device >
constexpr bool detail::char_traits<type,device>::is_print ( const type& ch )
{
    return ( greater_equal(ch, ' ') and less_equal(ch, '~') );
}

template < class type, class device >
constexpr bool detail::char_traits<type,device>::is_alnum ( const type& ch )
{
    return ( greater_equal(ch, '0') and less_equal(ch, '9') ) or
           ( greater_equal(ch, 'A') and less_equal(ch, 'Z') ) or
           ( greater_equal(ch, 'a') and less_equal(ch, 'z') );
}

template < class type, class device >
constexpr bool detail::char_traits<type,device>::is_alpha ( const type& ch )
{
    return ( greater_equal(ch, 'A') and less_equal(ch, 'Z') ) or
           ( greater_equal(ch, 'a') and less_equal(ch, 'z') );
}

template < class type, class device >
constexpr bool detail::char_traits<type,device>::is_upper ( const type& ch )
{
    return ( greater_equal(ch, 'A') and less_equal(ch, 'Z') );
}

template < class type, class device >
constexpr bool detail::char_traits<type,device>::is_lower ( const type& ch )
{
    return ( greater_equal(ch, 'a') and less_equal(ch, 'z') );
}

template < class type, class device >
constexpr bool detail::char_traits<type,device>::is_digit ( const type& ch )
{
    return ( greater_equal(ch, '0') and less_equal(ch, '9') );
}

template < class type, class device >
constexpr bool detail::char_traits<type,device>::is_space ( const type& ch )
{
    return ( greater_equal(ch, '\t') and less_equal(ch, '\r') ) or
           equal_to(ch, ' ');
}

template < class type, class device >
constexpr bool detail::char_traits<type,device>::is_blank ( const type& ch )
{
    return equal_to(ch, '\t') or 
           equal_to(ch, ' ');
}

template < class type, class device >
constexpr bool detail::char_traits<type,device>::is_punct ( const type& ch )
{
    return ( greater_equal(ch, '!') and less_equal(ch, '/') ) or 
           ( greater_equal(ch, ':') and less_equal(ch, '@') ) or
           ( greater_equal(ch, '[') and less_equal(ch, '`') ) or
           ( greater_equal(ch, '{') and less_equal(ch, '~') );
}

template < class type, class device >
constexpr bool detail::char_traits<type,device>::is_cntrl ( const type& ch )
{
    return ( greater_equal(ch, '\x00') and less_equal(ch, '\x1f') ) or 
           equal_to(ch, '\x7f');
}

template < class type, class device >
constexpr void detail::char_traits<type,device>::upper ( type& ch )
{
    if ( is_lower(ch) )
        ch += ('A' - 'a');
}

template < class type, class device >
constexpr void detail::char_traits<type,device>::lower ( type& ch )
{
    if ( is_upper(ch) )
        ch += ('a' - 'A');
}

template < class type, class device >
constexpr void detail::char_traits<type,device>::swap_case ( type& ch )
{
    if ( is_lower(ch) )
        upper(ch);
    else if ( is_upper(ch) )
        lower(ch);
}

template < class type, class device >
constexpr bool detail::char_traits<type,device>::equal_to ( const type& ch1, const type& ch2 )
{
    return device::template char_traits<const type&>::eq(ch1, ch2);
}

template < class type, class device >
constexpr bool detail::char_traits<type,device>::less_equal ( const type& ch1, const type& ch2 )
{
    return device::template char_traits<const type&>::lt(ch1, ch2) or 
           device::template char_traits<const type&>::eq(ch1, ch2);
}

template < class type, class device >
constexpr bool detail::char_traits<type,device>::greater_equal ( const type& ch1, const type& ch2 )
{
    return device::template char_traits<const type&>::lt(ch2, ch1) or 
           device::template char_traits<const type&>::eq(ch2, ch1);
}

template < class type, class device >
constexpr void detail::char_traits<type,device>::title ( type& ch1, type& ch2 )
{
    if ( not is_alpha(ch1) )
        upper(ch2);
    else
        lower(ch2);
}