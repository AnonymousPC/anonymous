template < class parse_context >
constexpr parse_context::iterator formatter<type_info,char>::parse ( parse_context& ctx )
{
    return formatter<string,char>::parse(ctx);
}

template < class format_context >
constexpr format_context::iterator formatter<type_info,char>::format ( const type_info& val, format_context& ctx ) const
{
    return formatter<string,char>::format(boost::core::demangle(val.name()), ctx);
}