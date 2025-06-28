template < anonymous::array_type type >
    requires formattable<typename type::value_type,char>
template < class parse_context >
constexpr parse_context::iterator formatter<type>::parse ( parse_context& ctx )
{
    auto b = ctx.begin();
    auto e = formatter<typename type::value_type>().parse(ctx);
    pattern = "{:" + anonymous::string_view(b, e-b) + '}'; // Try parsing and return to end of format-braces... if error occured then throw exception.
    return e;
}

template < anonymous::array_type type >
    requires formattable<typename type::value_type,char>
template < class format_context >
constexpr format_context::iterator formatter<type>::format ( const type& arr, format_context& ctx ) const
{
    // Namespace aux provides 3 helper-functions for print_array:
    // stringalize_array, align_array, print_array.
    // See container/array/array_global.cpp.

    auto stringalizer = [this] ( const typename type::value_type& item ) { return anonymous::string(pattern).format(item); };

    stringstream buff;
    auto strarr = anonymous::detail::stringalize_array(buff, arr, stringalizer);
    anonymous::detail::align_array(strarr);
    anonymous::detail::print_array(buff, strarr);

    return formatter<string_view>().format(buff.view(), ctx);
}

template < anonymous::string_type type >
template < class parse_context >
constexpr parse_context::iterator formatter<type,typename type::value_type>::parse ( parse_context& ctx )
{
    return base.parse(ctx);
}

template < anonymous::string_type type >
template < class format_context >
constexpr format_context::iterator std::formatter<type,typename type::value_type>::format ( const type& str, format_context& ctx ) const
{
    return base.format(basic_string_view<typename type::value_type>(str.data(), str.size()), ctx);
}

