#pragma once

/// Class std::formatter<color>

template < class parse_context >
constexpr parse_context::iterator std::formatter<ap::color>::parse ( parse_context& ctx )
{
    let n = 1;

    let b = ctx.begin();
    let e = std::find_if(ctx.begin(), ctx.end(), [&] (auto ch) { if (ch=='{') n++; if (ch=='}') n--; return n == 0; });

    parse_ctx = ap::string(ap::string_view(b, e));
    return e;
}

template < class format_context >
constexpr format_context::iterator std::formatter<ap::color>::format ( const ap::color& c, format_context& ctx ) const
{
    if ( parse_ctx == "" )
        parse_ctx = "(r,g,b)";

    let str =
        ap::string(parse_ctx)

           .replace('r', ap::string(c.red  ()))
           .replace('g', ap::string(c.green()))
           .replace('b', ap::string(c.blue ()));

    let it = ctx.out();
    for ( char ch in str )
        *(it++) = ch;

    return it;
}



/// Class std::formatter<time_point>

template < class parse_context >
constexpr parse_context::iterator std::formatter<ap::time_point>::parse ( parse_context& ctx )
{
    let n = 1;

    let b = ctx.begin();
    let e = std::find_if(ctx.begin(), ctx.end(), [&] (auto ch) { if (ch=='{') n++; if (ch=='}') n--; return n == 0; });

    parse_ctx = ap::string(ap::string_view(b, e));
    return e;
}

template < class format_context >
constexpr format_context::iterator std::formatter<ap::time_point>::format ( const ap::time_point& c, format_context& ctx ) const
{
    if ( parse_ctx == "" )
        parse_ctx = "YYYY-MM-DD hh:mm:ss ms.us.ns";

    let str =
        ap::string(parse_ctx)
           .replace("YYYY", ap::string("{:04d}").format(c.year   ()))
           .replace("MM",   ap::string("{:02d}").format(c.month  ()))
           .replace("DD",   ap::string("{:02d}").format(c.day    ()))
           .replace("W",    ap::string("{:d}"  ).format(c.weekday()))

           .replace("hh",   ap::string("{:02d}").format(c.hour  ()))
           .replace("mm",   ap::string("{:02d}").format(c.minute()))
           .replace("ss",   ap::string("{:02d}").format(c.second()))

           .replace("ms",   ap::string("{:03d}").format(c.millisecond()))
           .replace("us",   ap::string("{:03d}").format(c.microsecond()))
           .replace("ns",   ap::string("{:03d}").format(c.nanosecond ()))

           // And non-fill 0 types...

           .replace("Y",    ap::string("{:d}"  ).format(c.year   ()))
           .replace("M",    ap::string("{:d}"  ).format(c.month  ()))
           .replace("D",    ap::string("{:d}"  ).format(c.day    ()))

           .replace("h",    ap::string("{:d}"  ).format(c.hour  ()))
           .replace("m",    ap::string("{:d}"  ).format(c.minute()))
           .replace("s",    ap::string("{:d}"  ).format(c.second()));

    let it = ctx.out();
    for ( char ch in str )
        *(it++) = ch;

    return it;
}



/// Class std::formatter<duration>

template < class parse_context >
constexpr parse_context::iterator std::formatter<ap::duration>::parse ( parse_context& ctx )
{
    let n = 1;

    let b = ctx.begin();
    let e = std::find_if(ctx.begin(), ctx.end(), [&] (auto ch) { if (ch=='{') n++; if (ch=='}') n--; return n == 0; });

    parse_ctx = ap::string(ap::string_view(b, e));
    return e;
}

template < class format_context >
constexpr format_context::iterator std::formatter<ap::duration>::format ( const ap::duration& c, format_context& ctx ) const
{
    if ( parse_ctx == "" )
        parse_ctx = "hh:mm:ss ms.us.ns";

    let str =
        ap::string(parse_ctx)

           .replace("hh", ap::string("{:02d}").format(c.hour  ()))
           .replace("mm", ap::string("{:02d}").format(c.minute()))
           .replace("ss", ap::string("{:02d}").format(c.second()))

           .replace("ms", ap::string("{:03d}").format(c.millisecond()))
           .replace("us", ap::string("{:03d}").format(c.microsecond()))
           .replace("ns", ap::string("{:03d}").format(c.nanosecond ()))

           // And non-fill 0 types...

           .replace("h",  ap::string("{:d}"  ).format(c.hour  ()))
           .replace("m",  ap::string("{:d}"  ).format(c.minute()))
           .replace("s",  ap::string("{:d}"  ).format(c.second()));

    let it = ctx.out();
    for ( char ch in str )
        *(it++) = ch;

    return it;
}