#pragma once

} // namespace ap

template < ap::int_type type >
struct std::numeric_limits<ap::fraction<type>>
{
    constexpr static const bool                    is_specialized    = true;
    constexpr static const bool                    is_signed         = true;
    constexpr static const bool                    is_integer        = false;
    constexpr static const bool                    is_exact          = true;
    constexpr static const bool                    has_infinity      = false;
    constexpr static const bool                    has_quiet_NaN     = false;
    constexpr static const bool                    has_signaling_NaN = true;
 // constexpr static const std::float_denorm_style has_denorm        = deleted in C++23.
 // constexpr static const bool                    has_denorm_loss   = deleted in C++23.
    constexpr static const std::float_round_style  round_style       = std::round_toward_zero;
    constexpr static const bool                    is_iec559         = false;
    constexpr static const bool                    is_bounded        = true;
    constexpr static const bool                    is_modulo         = false;
    constexpr static const int                     digits            = numeric_limits<type>::digits;
    constexpr static const int                     digits10          = digits * ap::log(10.0,2.0);
    constexpr static const int                     max_digits10      = std::ceil ( digits * ap::log(10.0,2.0) + 1 );
    constexpr static const int                     radix             = 2;
    constexpr static const int                     min_exponent      = - digits + 1;
    constexpr static const int                     min_exponent10    = std::ceil ( min_exponent * ap::log(10.0,2.0) + 1 );
    constexpr static const int                     max_exponent      = digits + 1;
    constexpr static const int                     max_exponent10    = std::ceil ( max_exponent * ap::log(10.0,2.0) + 1 );
    constexpr static const bool                    traps             = false;
    constexpr static const bool                    tinyness_before   = false;

    constexpr static ap::fraction<type>            min()             { return {    -numeric_limits<type>::max(), 1 }; }
    constexpr static ap::fraction<type>            max()             { return {     numeric_limits<type>::max(), 1 }; }
    constexpr static ap::fraction<type>            lowest()          { return { -1, numeric_limits<type>::max()    }; }
    constexpr static ap::fraction<type>            epsilon()         { return { 1,  numeric_limits<type>::max() -1 }; }
    constexpr static ap::fraction<type>            round_error()     { return { 1, 2 }; }
    constexpr static ap::fraction<type>            infinity()        { return 0; }
    constexpr static ap::fraction<type>            queit_NaN()       { return 0; }
    constexpr static ap::fraction<type>            signaling_NaN()   { return { 1, 0 }; }
 // constexpr static ap::fraction<type>            denorm_min()      { deleted in C++23. }
};









namespace ap // Back to namespace ap
{