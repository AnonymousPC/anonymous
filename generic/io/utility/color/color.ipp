#pragma once

/// Class color

// Core

constexpr color::color ( )
    extends color ( 0.0, 0.0, 0.0, 1.0 )
{

}

constexpr color::color ( float_type auto r, float_type auto g, float_type auto b )
    extends tuple<float,float,float,float> ( float(r), float(g), float(b), 1.0 )
{

}

constexpr color::color ( float_type auto r, float_type auto g, float_type auto b, float_type auto a )
    extends tuple<float,float,float,float> ( float(r), float(g), float(b), float(a) )
{

}

// Interface

constexpr float& color::red ( )
{
    return self[1c];
}

constexpr const float& color::red ( ) const
{
    return self[1c];
}

constexpr float& color::green ( )
{
    return self[2c];
}

constexpr const float& color::green ( ) const
{
    return self[2c];
}

constexpr float& color::blue ( )
{
    return self[3c];
}

constexpr const float& color::blue ( ) const
{
    return self[3c];
}

constexpr float& color::alpha ( )
{
    return self[4c];
}

constexpr const float& color::alpha ( ) const
{
    return self[4c];
}



/// Color: factory

constexpr color red ( )
{
    return color ( 1.0, 0.0, 0.0 );
}

constexpr color orange ( )
{
    return color ( 1.0, 0.5, 0.0 );
}

constexpr color yellow ( )
{
    return color ( 1.0, 1.0, 0.0 );
}

constexpr color green ( )
{
    return color ( 0.0, 1.0, 0.0 );
}

constexpr color blue ( )
{
    return color ( 0.0, 0.0, 1.0 );
}

constexpr color purple ( )
{
    return color ( 0.5, 0.0, 0.5 );
}

constexpr color white ( )
{
    return color ( 1.0, 1.0, 1.0 );
}

constexpr color grey ( )
{
    return color ( 0.5, 0.5, 0.5 );
}

constexpr color black ( )
{
    return color ( 0.0, 0.0, 0.0 );
}