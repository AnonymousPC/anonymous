#pragma once

/// Class std::formatter<color>

template < class parse_context >
constexpr parse_context::iterator std::formatter<anonymous::color>::parse ( parse_context& ctx )
{
    auto n = 1;

    auto b = ctx.begin();
    auto e = std::find_if(ctx.begin(), ctx.end(), [&] (auto ch) { if (ch=='{') n++; if (ch=='}') n--; return n == 0; });

    parse_ctx = anonymous::string(anonymous::string_view(b, e-b));
    return e;
}

template < class format_context >
constexpr format_context::iterator std::formatter<anonymous::color>::format ( const anonymous::color& c, format_context& ctx ) const
{
    if ( parse_ctx == "" )
        parse_ctx = "(r,g,b)";

    auto str =
        anonymous::string(parse_ctx)
           .replace('r', anonymous::string(c.red  ()))
           .replace('g', anonymous::string(c.green()))
           .replace('b', anonymous::string(c.blue ()));

    auto it = ctx.out();
    for ( char ch in str )
        *(it++) = ch;

    return it;
}



/// Class std::formatter<time_point>

template < class parse_context >
constexpr parse_context::iterator std::formatter<anonymous::time_point>::parse ( parse_context& ctx )
{
    auto n = 1;

    auto b = ctx.begin();
    auto e = std::find_if(ctx.begin(), ctx.end(), [&] (auto ch) { if (ch=='{') n++; if (ch=='}') n--; return n == 0; });

    parse_ctx = anonymous::string(anonymous::string_view(b, e-b));
    return e;
}

template < class format_context >
constexpr format_context::iterator std::formatter<anonymous::time_point>::format ( const anonymous::time_point& c, format_context& ctx ) const
{
    if ( parse_ctx == "" )
        parse_ctx = "YYYY-MM-DD hh:mm:ss ms.us.ns";

    auto str =
        anonymous::string(parse_ctx)
           .replace("YYYY", anonymous::string("{:04d}").format(c.year   ()))
           .replace("MM",   anonymous::string("{:02d}").format(c.month  ()))
           .replace("DD",   anonymous::string("{:02d}").format(c.day    ()))
           .replace("W",    anonymous::string("{:d}"  ).format(c.weekday()))

           .replace("hh",   anonymous::string("{:02d}").format(c.hour  ()))
           .replace("mm",   anonymous::string("{:02d}").format(c.minute()))
           .replace("ss",   anonymous::string("{:02d}").format(c.second()))

           .replace("ms",   anonymous::string("{:03d}").format(c.millisecond()))
           .replace("us",   anonymous::string("{:03d}").format(c.microsecond()))
           .replace("ns",   anonymous::string("{:03d}").format(c.nanosecond ()))

           // And non-fill 0 types...

           .replace("Y",    anonymous::string("{:d}"  ).format(c.year   ()))
           .replace("M",    anonymous::string("{:d}"  ).format(c.month  ()))
           .replace("D",    anonymous::string("{:d}"  ).format(c.day    ()))

           .replace("h",    anonymous::string("{:d}"  ).format(c.hour  ()))
           .replace("m",    anonymous::string("{:d}"  ).format(c.minute()))
           .replace("s",    anonymous::string("{:d}"  ).format(c.second()));

    auto it = ctx.out();
    for ( char ch in str )
        *(it++) = ch;

    return it;
}



/// Class std::formatter<duration>

template < class parse_context >
constexpr parse_context::iterator std::formatter<anonymous::duration>::parse ( parse_context& ctx )
{
    auto n = 1;

    auto b = ctx.begin();
    auto e = std::find_if(ctx.begin(), ctx.end(), [&] (auto ch) { if (ch=='{') n++; if (ch=='}') n--; return n == 0; });

    parse_ctx = anonymous::string(anonymous::string_view(b, e));
    return e;
}

template < class format_context >
constexpr format_context::iterator std::formatter<anonymous::duration>::format ( const anonymous::duration& c, format_context& ctx ) const
{
    if ( parse_ctx == "" )
        parse_ctx = "hh:mm:ss ms.us.ns";

    auto str =
        anonymous::string(parse_ctx)

           .replace("hh", anonymous::string("{:02d}").format(c.hour  ()))
           .replace("mm", anonymous::string("{:02d}").format(c.minute()))
           .replace("ss", anonymous::string("{:02d}").format(c.second()))

           .replace("ms", anonymous::string("{:03d}").format(c.millisecond()))
           .replace("us", anonymous::string("{:03d}").format(c.microsecond()))
           .replace("ns", anonymous::string("{:03d}").format(c.nanosecond ()))

           // And non-fill 0 types...

           .replace("h",  anonymous::string("{:d}"  ).format(c.hour  ()))
           .replace("m",  anonymous::string("{:d}"  ).format(c.minute()))
           .replace("s",  anonymous::string("{:d}"  ).format(c.second()));

    auto it = ctx.out();
    for ( char ch in str )
        *(it++) = ch;

    return it;
}