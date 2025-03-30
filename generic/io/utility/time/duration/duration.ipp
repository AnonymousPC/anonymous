#pragma once

namespace detail
{
    constexpr bool is_same_sign                ( auto, auto... );
    constexpr void regularize_same_signed_time ( int&, int&, int&, int&, int&, int& );
    constexpr void regularize_diff_signed_time ( int&, int&, int&, int&, int&, int& );
}

constexpr duration::duration ( int_type auto hh, int_type auto mm, int_type auto ss, int_type auto ms, int_type auto us, int_type auto ns )
    extends tuple<int,int,int,int,int,int> ( int(hh), int(mm), int(ss), int(ms), int(us), int(ns) )
{
    #ifdef debug
    if ( abs(mm) > 59 or abs(ss) > 59 or abs(ms) > 999 or abs(us) > 999 or abs(ns) > 999 )
        throw value_error("duration {:02d}:{:02d}:{:02d} {:03d}.{:03d}.{:03d} is invalid: value out of domain", hour(), minute(), second(), millisecond(), microsecond(), nanosecond());
    if ( not detail::is_same_sign(hh, mm, ss, ms, us, ns) )
        throw value_error("duration {:02d}:{:02d}:{:02d} {:03d}.{:03d}.{:03d} is invalid: value signed inconsistently", hour(), minute(), second(), millisecond(), microsecond(), nanosecond());
    #endif
}

template < class data_type, class ratio_type >
constexpr duration::duration ( std::chrono::duration<data_type,ratio_type> cvt )
{
    let s1 = std::chrono::duration_cast<std::chrono::seconds>(cvt).count();
    let s2 = std::chrono::duration_cast<std::chrono::nanoseconds>(cvt - std::chrono::seconds(s1)).count();

    self = ap::second(s1) + ap::nanosecond(s2);
}

template < class data_type, class ratio_type >
constexpr duration::operator std::chrono::duration<data_type,ratio_type> ( ) const  // num / den
{
    let s1 = hour()        * 3600    + minute()      * 60   + second();
    let s2 = millisecond() * 1000000 + microsecond() * 1000 + nanosecond();

    return std::chrono::duration<data_type,ratio_type> ( data_type ( s1 * ( static_cast<long double>(ratio_type::den) / ratio_type::num              ) +
                                                                     s2 * ( static_cast<long double>(ratio_type::den) / ratio_type::num / 1000000000 ) ) );
}

constexpr int& duration::hour ( )
{
    return self.template value<1>();
}

constexpr const int& duration::hour ( ) const
{
    return self.template value<1>();
}

constexpr int& duration::minute ( )
{
    return self.template value<2>();
}

constexpr const int& duration::minute ( ) const
{
    return self.template value<2>();
}

constexpr int& duration::second ( )
{
    return self.template value<3>();
}

constexpr const int& duration::second ( ) const
{
    return self.template value<3>();
}

constexpr int& duration::millisecond ( )
{
    return self.template value<4>();
}

constexpr const int& duration::millisecond ( ) const
{
    return self.template value<4>();
}

constexpr int& duration::microsecond ( )
{
    return self.template value<5>();
}

constexpr const int& duration::microsecond ( ) const
{
    return self.template value<5>();
}

constexpr int& duration::nanosecond ( )
{
    return self.template value<6>();
}

constexpr const int& duration::nanosecond ( ) const
{
    return self.template value<6>();
}

constexpr duration hour ( number_type auto hh )
{
    if constexpr ( int_type<decltype(hh)> )
        return duration(hh, 0, 0, 0, 0, 0);
    else
        return hour(int(hh)) + minute((hh - int(hh)) * 60);
}

constexpr duration minute ( number_type auto mm )
{
    if constexpr ( int_type<decltype(mm)> )
        return abs(mm) < 60 ? duration(0, mm, 0, 0, 0, 0) otherwise hour(mm / 60) + duration(0, mm % 60, 0, 0, 0, 0);
    else
        return minute(int(mm)) + second((mm - int(mm)) * 60);
}

constexpr duration second ( number_type auto ss )
{
    if constexpr ( int_type<decltype(ss)> )
        return abs(ss) < 60 ? duration(0, 0, ss, 0, 0, 0) otherwise minute(ss / 60) + duration(0, 0, ss % 60, 0, 0, 0);
    else
        return second(int(ss)) + millisecond((ss - int(ss)) * 1000);
}

constexpr duration millisecond ( number_type auto ms )
{
    if constexpr ( int_type<decltype(ms)> )
        return abs(ms) < 60 ? duration(0, 0, 0, ms, 0, 0) otherwise second(ms / 1000) + duration(0, 0, 0, ms % 1000, 0, 0);
    else
        return millisecond(int(ms)) + microsecond((ms - int(ms)) * 1000);
}

constexpr duration microsecond ( number_type auto us )
{
    if constexpr ( int_type<decltype(us)> )
        return abs(us) < 60 ? duration(0, 0, 0, 0, us, 0) otherwise millisecond(us / 1000) + duration(0, 0, 0, 0, us % 1000, 0);
    else
        return microsecond(int(us)) + nanosecond((us - int(us)) * 1000);
}

constexpr duration nanosecond ( number_type auto ns )
{
    if constexpr ( int_type<decltype(ns)> )
        return abs(ns) < 60 ? duration(0, 0, 0, 0, 0, ns) otherwise microsecond(ns / 1000) + duration(0, 0, 0, 0, 0, ns % 1000);
    else
        return nanosecond(int(ns));
}

constexpr std::ostream& operator << ( std::ostream& left, const duration& right )
{
    if ( right < second(0) )
        return left << '-' << - right;
    else
        return left << "{:02d}:{:02d}:{:02d} {:03d}.{:03d}.{:03d}"s
                       .format(right.hour(), right.minute(), right.second(), right.millisecond(), right.microsecond(), right.nanosecond());
}

constexpr duration operator + ( const duration& right )
{
    return duration ( + right.hour(), + right.minute(), + right.second(), + right.millisecond(), + right.microsecond(), + right.nanosecond() );;
}

constexpr duration operator - ( const duration& right )
{
    return duration ( - right.hour(), - right.minute(), - right.second(), - right.millisecond(), - right.microsecond(), - right.nanosecond() );
}

constexpr duration operator + ( const duration& left, const duration& right )
{
    using tuple = tuple<int,int,int,int,int,int>;
    let [hh, mm, ss, ms, us, ns] = static_cast<const tuple&>(left) + static_cast<const tuple&>(right);
    detail::regularize_same_signed_time(hh, mm, ss, ms, us, ns);
    return duration(hh, mm, ss, ms, us, ns);
}

constexpr duration operator - ( const duration& left, const duration& right )
{
    using tuple = tuple<int,int,int,int,int,int>;
    let [hh, mm, ss, ms, us, ns] = static_cast<const tuple&>(left) - static_cast<const tuple&>(right);
    detail::regularize_diff_signed_time(hh, mm, ss, ms, us, ns);
    return duration(hh, mm, ss, ms, us, ns);
}

constexpr duration operator * ( const duration& left, const number_type auto& right )
{
    using tuple = tuple<int,int,int,int,int,int>;
    let [hh, mm, ss, ms, us, ns] = tuple(static_cast<const tuple&>(left) * right);
    detail::regularize_same_signed_time(hh, mm, ss, ms, us, ns);
    return duration(hh, mm, ss, ms, us, ns);
}

constexpr duration operator * ( const number_type auto& left, const duration& right )
{
    using tuple = tuple<int,int,int,int,int,int>;
    let [hh, mm, ss, ms, us, ns] = tuple(left * static_cast<const tuple&>(right));
    detail::regularize_same_signed_time(hh, mm, ss, ms, us, ns);
    return duration(hh, mm, ss, ms, us, ns);
}

constexpr duration operator / ( const duration& left, const number_type auto& right )
{
    let [hh, mm, ss, ms, us, ns] = left;
    let hh_remain = hh % right;
        hh        = hh / right;
    let mm_remain = (hh_remain * 60   + mm) % right;
        mm        = (hh_remain * 60   + mm) / right;
    let ss_remain = (mm_remain * 60   + ss) % right;
        ss        = (mm_remain * 60   + ss) / right;
    let ms_remain = (ss_remain * 1000 + ms) % right;
        ms        = (ss_remain * 1000 + ms) / right;
    let us_remain = (ms_remain * 1000 + us) % right;
        us        = (ms_remain * 1000 + us) / right;
 // let ns_remain = (us_remain * 1000 + ns) % right;
        ns        = (us_remain * 1000 + ns) / right;
    return duration(hh, mm, ss, ms, us, ns);
}

constexpr duration& operator += ( duration& left, const duration& right )
{
    return left = left + right;
}

constexpr duration& operator -= ( duration& left, const duration& right )
{
    return left = left - right;
}

constexpr duration& operator *= ( duration& left, const number_type auto& right )
{
    return left = left * right;
}

constexpr duration& operator /= ( duration& left, const number_type auto& right )
{
    return left = left / right;
}

constexpr bool detail::is_same_sign ( auto a, auto... args )
{
    if constexpr ( sizeof...(args) == 0 )
        return true;
    else
        return ( a > 0 and ( ( args >= 0 ) and ... ) ) or
               ( a < 0 and ( ( args <= 0 ) and ... ) ) or
               is_same_sign ( args... );
}

constexpr void detail::regularize_same_signed_time ( int& hh, int& mm, int& ss, int& ms, int& us, int& ns )
{
    us += ns / 1000;
    ns %= 1000;

    ms += us / 1000;
    us %= 1000;

    ss += ms / 1000;
    ms %= 1000;

    mm += ss / 60;
    ss %= 60;

    hh += mm / 60;
    mm %= 60;
}

constexpr void detail::regularize_diff_signed_time ( int& hh, int& mm, int& ss, int& ms, int& us, int& ns )
{
    // This function is only called in operator - (duration, duration),
    // which guarantees every int is in range [+=limit].
    // Thus, we can get the final sign by simply observing the parameter sign one by one.

    bool sign = hh != 0 ? hh >  0 otherwise
                mm != 0 ? mm >  0 otherwise
                ss != 0 ? ss >  0 otherwise
                ms != 0 ? ms >  0 otherwise
                us != 0 ? us >  0 otherwise
                          ns >= 0;

    if ( ( ns >= 0 ) == sign )
    {
        us += ns / 1000;
        ns %= 1000;
    }
    else
    {
        us -= ( ns / 1000 + 1 );
        ns  = sign * 1000 + ( ns % 1000 );
    }

    if ( ( us >= 0 ) == sign )
    {
        ms += us / 1000;
        us %= 1000;
    }
    else
    {
        ms -= ( us / 1000 + 1 );
        us  = sign * 1000 + ( us % 1000 );
    }

    if ( ( ms >= 0 ) == sign )
    {
        ss += ms / 1000;
        ms %= 1000;
    }
    else
    {
        ss -= ( ms / 1000 + 1 );
        ms  = sign * 1000 + ( ms % 1000 );
    }

    if ( ( ss >= 0 ) == sign )
    {
        mm += ss / 60;
        ss %= 60;
    }
    else
    {
        mm -= ( ss / 60 + 1 );
        ss  = sign * 60 + ( ss % 60 );
    }

    if ( ( mm >= 0 ) == sign )
    {
        hh += mm / 60;
        mm %= 60;
    }
    else
    {
        hh -= ( mm / 60 + 1 );
        mm  = sign * 60 + ( mm % 60 );
    }
}
