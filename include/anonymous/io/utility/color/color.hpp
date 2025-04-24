class color
    extends public tuple<float,float,float,float>
{
    public: // Core
        constexpr color ( ); // Alpha is default set as 1.0.
        constexpr color ( float_type auto, float_type auto, float_type auto );
        constexpr color ( float_type auto, float_type auto, float_type auto, float_type auto );

    public: // Interface
        constexpr       float& red   ( );
        constexpr const float& red   ( ) const;
        constexpr       float& green ( );
        constexpr const float& green ( ) const;
        constexpr       float& blue  ( );
        constexpr const float& blue  ( ) const;
        constexpr       float& alpha ( );
        constexpr const float& alpha ( ) const;
};

// Color: factory
constexpr color red    ( );
constexpr color orange ( );
constexpr color yellow ( );
constexpr color green  ( );
constexpr color blue   ( );
constexpr color purple ( );
constexpr color white  ( );
constexpr color grey   ( );
constexpr color black  ( );



#include "color.cpp"