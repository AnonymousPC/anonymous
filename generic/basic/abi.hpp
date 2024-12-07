#pragma once


namespace abi
{
    std::string demangle ( const char* );
    std::string demangle ( const std::stacktrace& );
    std::string demangle ( const boost::stacktrace::stacktrace& );

    constexpr const char* red    = "\033[38;2;255;0;0m";
    constexpr const char* yellow = "\033[38;2;255;255;0m";
    constexpr const char* green  = "\033[38;2;0;255;0m";

    constexpr const char* white      = "\033[38;2;200;200;200m";
    constexpr const char* light_grey = "\033[38;2;150;150;150m";
    constexpr const char* grey       = "\033[38;2;100;100;100m";
    constexpr const char* dark_grey  = "\033[38;2;50;50;50m";

    constexpr std::array<const char*,4> grey_scale = { white, light_grey, grey, dark_grey };

}


#if dll
    #include "abi.cpp"
#endif