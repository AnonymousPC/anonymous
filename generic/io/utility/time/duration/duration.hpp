#pragma once

class duration
    extends public tuple<int,int,int,int,int,int>
{
    public: // Core
        constexpr duration ( ) = default;
        constexpr duration ( int_type auto, int_type auto, int_type auto, int_type auto, int_type auto, int_type auto );

    public: // Conversion
        template < class data_type, class ratio_type > constexpr duration ( std::chrono::duration<data_type,ratio_type> );
        template < class data_type, class ratio_type > constexpr operator   std::chrono::duration<data_type,ratio_type> ( ) const;

    public: // Interface
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
};


// Duration: factory
constexpr duration hour        ( number_type auto );
constexpr duration minute      ( number_type auto );
constexpr duration second      ( number_type auto );
constexpr duration millisecond ( number_type auto );
constexpr duration microsecond ( number_type auto );
constexpr duration nanosecond  ( number_type auto );


// Duration: operator
constexpr std::ostream& operator <<  ( std::ostream&,           const duration&         );
constexpr duration      operator  +  ( const duration&                                  );
constexpr duration      operator  +  ( const duration&,         const duration&         );
constexpr duration      operator  -  ( const duration&                                  );
constexpr duration      operator  -  ( const duration&,         const duration&         );
constexpr duration      operator  *  ( const duration&,         const number_type auto& );
constexpr duration      operator  *  ( const number_type auto&, const duration&         );
constexpr duration      operator  /  ( const duration&,         const number_type auto& );
constexpr duration&     operator  += (       duration&,         const duration&         );
constexpr duration&     operator  -= (       duration&,         const duration&         );
constexpr duration&     operator  *= (       duration&,         const number_type auto& );
constexpr duration&     operator  /= (       duration&,         const number_type auto& );

#include "duration.ipp"
