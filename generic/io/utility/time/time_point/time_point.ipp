#pragma once

namespace detail
{
    constexpr int                date_to_int ( tuple<int,int,int> );
    constexpr tuple<int,int,int> int_to_date ( int );
}

constexpr time_point::time_point ( int_type auto YYYY, int_type auto MM, int_type auto DD, int_type auto hh, int_type auto mm, int_type auto ss, int_type auto ms, int_type auto us, int_type auto ns )
    extends tuple<int,int,int,int,int,int,int,int,int> ( YYYY, MM, DD, hh, mm, ss, ms, us, ns )
{
    #if debug
    if ( detail::int_to_date(detail::date_to_int(ap::tuple(YYYY, MM, DD))) != ap::tuple(YYYY, MM, DD) )
        throw value_error("time_point {:04d}-{:04d}-{:04d} {:02d}:{:02d}:{:02d} {:03d}.{:03d}.{:03d} is invalid: date does not exit", year(), month(), day(), hour(), minute(), second(), millisecond(), microsecond(), nanosecond());
    if ( hh > 23 or hh < 0 or mm > 59 or mm < 0 or ss > 59 or ss < 0 or ms > 999 or ms < 0 or us > 999 or us < 0 or ns > 999 or ns < 0 )
        throw value_error("time_point {:04d}-{:04d}-{:04d} {:02d}:{:02d}:{:02d} {:03d}.{:03d}.{:03d} is invalid: value out of domain", year(), month(), day(), hour(), minute(), second(), millisecond(), microsecond(), nanosecond());
    #endif
}

template < class duration_type >
constexpr time_point::time_point ( std::chrono::time_point<std::chrono::system_clock,duration_type> cvt )
    extends time_point ( duration(cvt.time_since_epoch()) + date(1970, 1, 1) + duration(time_zone(), 0, 0, 0, 0, 0) )
{

}

template < class duration_type >
constexpr time_point::operator std::chrono::time_point<std::chrono::system_clock,duration_type> ( ) const
{
    return std::chrono::time_point<std::chrono::system_clock,duration_type>(duration_type(self - date(1970, 1, 1) - duration(time_zone(), 0, 0, 0, 0, 0)));
}

constexpr int& time_point::year ( )
{
    return self.template value<1>();
}

constexpr const int& time_point::year ( ) const
{
    return self.template value<1>();
}

constexpr int& time_point::month ( )
{
    return self.template value<2>();
}

constexpr const int& time_point::month ( ) const
{
    return self.template value<2>();
}

constexpr int& time_point::day ( )
{
    return self.template value<3>();
}

constexpr const int& time_point::day ( ) const
{
    return self.template value<3>();
}

constexpr int& time_point::hour ( )
{
    return self.template value<4>();
}

constexpr const int& time_point::hour ( ) const
{
    return self.template value<4>();
}

constexpr int& time_point::minute ( )
{
    return self.template value<5>();
}

constexpr const int& time_point::minute ( ) const
{
    return self.template value<5>();
}

constexpr int& time_point::second ( )
{
    return self.template value<6>();
}

constexpr const int& time_point::second ( ) const
{
    return self.template value<6>();
}

constexpr int& time_point::millisecond ( )
{
    return self.template value<7>();
}

constexpr const int& time_point::millisecond ( ) const
{
    return self.template value<7>();
}

constexpr int& time_point::microsecond ( )
{
    return self.template value<8>();
}

constexpr const int& time_point::microsecond ( ) const
{
    return self.template value<8>();
}

constexpr int& time_point::nanosecond ( )
{
    return self.template value<9>();
}

constexpr const int& time_point::nanosecond ( ) const
{
    return self.template value<9>();
}

constexpr int time_point::weekday ( ) const
{
    return (detail::date_to_int(ap::tuple(year(), month(), day())) + 5) % 7 + 1;
}

constexpr time_point now ( )
{
    return time_point(std::chrono::system_clock::now());
}

constexpr time_point today ( )
{
    return time_point(now().year(), now().month(), now().day(), 0, 0, 0, 0, 0, 0);
}

constexpr time_point date ( int_type auto YYYY, int_type auto MM, int_type auto DD )
{
    return time_point(YYYY, MM, DD, 0, 0, 0, 0, 0, 0);
}

constexpr std::ostream& operator << ( std::ostream& left, const time_point& right )
{
    return left << "{:04d}-{:02d}-{:02d} {:02d}:{:02d}:{:02d} {:03d}.{:03d}.{:03d}"s
                   .format(right.year(),        right.month(),       right.day(),
                           right.hour(),        right.minute(),      right.second(),
                           right.millisecond(), right.microsecond(), right.nanosecond());
}

constexpr time_point operator + ( const time_point& left, const duration& right )
{
    let dur = hour(detail::date_to_int({left.year(), left.month(), left.day()})) * 24 +
              duration(left.hour(), left.minute(), left.second(), left.millisecond(), left.microsecond(), left.nanosecond()) +
              right;
    let dt = detail::int_to_date(dur.hour() / 24);
    dur.hour() %= 24;

    return time_point(dt.template value<1>(), dt.template value<2>(), dt.template value<3>(), dur.hour(), dur.minute(), dur.second(), dur.millisecond(), dur.microsecond(), dur.nanosecond());
}

constexpr time_point operator + ( const duration& left, const time_point& right )
{
    let dur = left +
              hour(detail::date_to_int({right.year(), right.month(), right.day()})) * 24 +
              duration(right.hour(), right.minute(), right.second(), right.millisecond(), right.microsecond(), right.nanosecond());
    let dt = detail::int_to_date(dur.hour() / 24);
    dur.hour() %= 24;

    return time_point(dt.template value<1>(), dt.template value<2>(), dt.template value<3>(), dur.hour(), dur.minute(), dur.second(), dur.millisecond(), dur.microsecond(), dur.nanosecond());
}

constexpr duration operator - ( const time_point& left, const time_point& right )
{
    let dur1 = hour(detail::date_to_int({left.year(), left.month(), left.day()})) * 24 +
               duration(left.hour(), left.minute(), left.second(), left.millisecond(), left.microsecond(), left.nanosecond());
    let dur2 = hour(detail::date_to_int({right.year(), right.month(), right.day()})) * 24 +
               duration(right.hour(), right.minute(), right.second(), right.millisecond(), right.microsecond(), right.nanosecond());

    return dur1 - dur2;
}

constexpr time_point operator - ( const time_point& left, const duration& right )
{
    let dur = hour(detail::date_to_int({left.year(), left.month(), left.day()})) * 24 +
              duration(left.hour(), left.minute(), left.second(), left.millisecond(), left.microsecond(), left.nanosecond()) -
              right;
    let dt = detail::int_to_date(dur.hour() / 24);
    dur.hour() %= 24;

    return time_point(dt.template value<1>(), dt.template value<2>(), dt.template value<3>(), dur.hour(), dur.minute(), dur.second(), dur.millisecond(), dur.microsecond(), dur.nanosecond());
}

constexpr time_point& operator += ( time_point& left, const duration& right )
{
    return left = left + right;
}

constexpr time_point& operator -= ( time_point& left, const duration& right )
{
    return left = left - right;
}

constexpr int detail::date_to_int ( tuple<int,int,int> date )
{
    using namespace literals;

    let [y, m, d] = date;

    return + y * 365                                                                                        // Count normal year  from 0000 to y-1.
           + ( y == 0 ? 0 otherwise ( ( y - 1 ) / 4 - ( y - 1 ) / 100 + ( y - 1 ) / 400 + 1 ) )             // Count leap   year  from 0000 to y-1.

           + ( m - 1 ) * 31                                                                                 // Count approx month from 1    to m-1.
           + ( m <= 2 ? 0 otherwise ( y % 4 != 0 or ( y % 100 == 0 but y % 400 != 0 ) ) ? -2 otherwise -1 ) // Count leap   month from 1    to m-1. Here only converts 28/29 to 30.
           + ( m <= 8 ? - ( m - 1 ) / 2 otherwise - ( m - 2 ) / 2 )                                         // Count 30-day month from 1    to m-1.

           + d * 1                                                                                          // Count day from 1 to d.

           - 1;                                                                                             // Minus 0000.01.01.
}

constexpr tuple<int,int,int> detail::int_to_date ( int days )
{
    let y_400      = days / ( 303*365+97*366 ); // Chunk by 400 years.
    let y_400_more = days % ( 303*365+97*366 ); // Chunk by 400 years.

    let y_100      = ( y_400_more - 1 ) / ( 76*365+24*366 ); // As the first 100 years has 1 day more in 0000, minus it.
    let y_100_more = ( y_400_more - 1 ) % ( 76*365+24*366 ) + ( y_100 == 0 ? 1 otherwise 0 ); // If is the first 100 years, add the 1 day back.

    let y_4        = ( y_100_more + ( y_100 == 0 ? 0 otherwise 1 ) ) / ( 3*365+366 ); // If in the first 100 years, only chunk by 4 years; otherwise make up 1 day.
    let y_4_more   = ( y_100_more + ( y_100 == 0 ? 0 otherwise 1 ) ) % ( 3*365+366 ) - ( y_100 != 0 and y_4 == 0 ? 1 otherwise 0 ); // Only in 0100-0103, 0200-0203, 0300-0303 you need to minus 1.

    let y_1        = ( y_4_more - ( y_100 == 0 or y_4 != 0 ? 1 otherwise 0 ) ) / 365; // In 4-year which contains leap years, turn 366 into 365 vice versa.
    let y_1_more   = ( y_4_more - ( y_100 == 0 or y_4 != 0 ? 1 otherwise 0 ) ) % 365 + ( ( y_100 == 0 or y_4 != 0 ) and y_1 == 0 ? 1 otherwise 0 ); // In first year of leap year you should add 1 back.

    let y          = y_400 * 400 + y_100 * 100 + y_4 * 4 + y_1; // Accumulate year.

    let is_leap    = y_1 == 0 and ( y_100 == 0 or y_4 != 0 ); // Judge lear year.

    int m = 1;
    let d = y_1_more + 1; // As first day refers to xxxx.01.01.

    let month_day  = [&] { return m >= 8  ? m % 2 == 0 ? 31 otherwise 30 otherwise
                                  m != 2  ? m % 2 != 0 ? 31 otherwise 30 otherwise
                                  is_leap ?              29 otherwise 28; };
    while ( true )
    {
        let md = month_day();
        if ( d > md )
        {
            d -= md;
            m++;
        }
        else
            break;
    }

    return { y, m, d };
}
