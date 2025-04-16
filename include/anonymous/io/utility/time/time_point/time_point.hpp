#pragma once

class time_point // Class time_point always stores zoned_time.
    extends public tuple<int,int,int,int,int,int,int,int,int>
{
    public: // Core
        constexpr time_point ( ) = default;
        constexpr time_point ( int_type auto, int_type auto, int_type auto, int_type auto, int_type auto, int_type auto, int_type auto, int_type auto, int_type auto );

    public: // Conversion
        template < class duration_type > constexpr time_point ( std::chrono::time_point<std::chrono::system_clock,duration_type> );
        template < class duration_type > constexpr operator     std::chrono::time_point<std::chrono::system_clock,duration_type> ( ) const;

    public: // Interface
        constexpr       int& year        ( );
        constexpr const int& year        ( ) const;
        constexpr       int& month       ( );
        constexpr const int& month       ( ) const;
        constexpr       int& day         ( );
        constexpr const int& day         ( ) const;
        constexpr       int& hour        ( );
        constexpr const int& hour        ( ) const;
        constexpr       int& minute      ( );
        constexpr const int& minute      ( ) const;
        constexpr       int& second      ( );
        constexpr const int& second      ( ) const;
        constexpr       int& millisecond ( );
        constexpr const int& millisecond ( ) const;
        constexpr       int& microsecond ( );
        constexpr const int& microsecond ( ) const;
        constexpr       int& nanosecond  ( );
        constexpr const int& nanosecond  ( ) const;
        constexpr       int  weekday     ( ) const;
};


// Time_point: factory
constexpr time_point now   ( );
constexpr time_point today ( );
constexpr time_point date  ( int_type auto, int_type auto, int_type auto );


// Time_point: operator
constexpr std::ostream& operator <<  ( std::ostream&,     const time_point& );
constexpr time_point    operator  +  ( const time_point&, const duration&   );
constexpr time_point    operator  +  ( const duration&,   const time_point& );
constexpr duration      operator  -  ( const time_point&, const time_point& );
constexpr time_point    operator  -  ( const time_point&, const duration&   );
constexpr time_point&   operator  += (       time_point&, const duration&   );
constexpr time_point&   operator  -= (       time_point&, const duration&   );

#include "time_point.cpp"
