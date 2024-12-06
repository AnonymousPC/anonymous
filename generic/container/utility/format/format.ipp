#pragma once

} // Out from namespace ap.

/// Array

template < ap::array_type type >
    requires std::formattable<typename type::value_type,char>
class std::formatter<type>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  ( parse_context& );
        template < class format_context > constexpr format_context::iterator format ( const type&, format_context& ) const;

    private: // Auxiliary
        ap::string parse_ctx = "";
};

template < ap::array_type type >
    requires std::formattable<typename type::value_type,char>
template < class parse_context >
constexpr parse_context::iterator std::formatter<type>::parse ( parse_context& ctx )
{
    let b = ctx.begin();
    let e = std::formatter<typename type::value_type>().parse ( ctx );
    parse_ctx = "{:" + ap::string(ap::string_view(b, e)) + '}'; // Try parsing and return to end of format-braces... if error occured then throw exception.
    return e;
}

template < ap::array_type type >
    requires std::formattable<typename type::value_type,char>
template < class format_context >
constexpr format_context::iterator std::formatter<type>::format ( const type& arr, format_context& ctx ) const
{
    // Namespace aux provides 3 helper-functions for print_array:
    // stringalize_array, align_array, print_array.
    // See container/array/array_global.cpp.

    let stringalizer = [this] ( const typename type::value_type& item ) { return ap::string(parse_ctx).format(item); };

    std::stringstream buff;
    let strarr = ap::aux::stringalize_array(buff, arr, stringalizer);
    ap::aux::align_array(strarr);
    ap::aux::print_array(buff, strarr);

    return std::formatter<std::string_view>().format(buff.view(), ctx);
}

/// String

template < ap::string_type type >
class std::formatter<type,typename type::value_type>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  ( parse_context& );
        template < class format_context > constexpr format_context::iterator format ( const type&, format_context& ) const;

    private: // Auxiliary
        mutable std::formatter<std::basic_string_view<typename type::value_type>,typename type::value_type> std_fmt;
};

template < ap::string_type type >
template < class parse_context >
constexpr parse_context::iterator std::formatter<type,typename type::value_type>::parse ( parse_context& ctx )
{
    return std_fmt.parse ( ctx );
}

template < ap::string_type type >
template < class format_context >
constexpr format_context::iterator std::formatter<type,typename type::value_type>::format ( const type& str, format_context& ctx ) const
{
    return std_fmt.format ( std::basic_string_view<typename type::value_type>(str.begin(), str.end()), ctx );
}

namespace ap { // Back into namespace ap.

