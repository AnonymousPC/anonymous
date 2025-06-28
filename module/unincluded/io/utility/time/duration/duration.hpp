class duration
    extends public tuple<int,int,int,int,int,int>
{
    public: // Core
        constexpr duration ( ) = default;
        constexpr duration ( integral auto, integral auto, integral auto, integral auto, integral auto, integral auto );

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
constexpr duration hour        ( numeric auto );
constexpr duration minute      ( numeric auto );
constexpr duration second      ( numeric auto );
constexpr duration millisecond ( numeric auto );
constexpr duration microsecond ( numeric auto );
constexpr duration nanosecond  ( numeric auto );


// Duration: operator
constexpr std::ostream& operator <<  ( std::ostream&,           const duration&         );
constexpr duration      operator  +  ( const duration&                                  );
constexpr duration      operator  +  ( const duration&,         const duration&         );
constexpr duration      operator  -  ( const duration&                                  );
constexpr duration      operator  -  ( const duration&,         const duration&         );
constexpr duration      operator  *  ( const duration&,         const numeric auto& );
constexpr duration      operator  *  ( const numeric auto&, const duration&         );
constexpr duration      operator  /  ( const duration&,         const numeric auto& );
constexpr duration&     operator  += (       duration&,         const duration&         );
constexpr duration&     operator  -= (       duration&,         const duration&         );
constexpr duration&     operator  *= (       duration&,         const numeric auto& );
constexpr duration&     operator  /= (       duration&,         const numeric auto& );

#include "duration.cpp"
