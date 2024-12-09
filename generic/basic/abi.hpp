#pragma once


namespace abi
{
    std::string demangle ( const char* );
    #if __cpp_lib_stacktrace
        std::string demangle ( const std::stacktrace& );
    #else
        std::string demangle ( const boost::stacktrace::stacktrace& );
    #endif

    constexpr const char* red    = "\033[38;2;240;0;0m";
    constexpr const char* yellow = "\033[38;2;240;240;0m";
    constexpr const char* green  = "\033[38;2;0;240;0m";
    constexpr const char* blue   = "\033[38;2;0;120;240m";

    constexpr const char* white      = "\033[38;2;192;192;192m";
    constexpr const char* light_grey = "\033[38;2;144;144;144m";
    constexpr const char* grey       = "\033[38;2;96;96;96m";
    constexpr const char* dark_grey  = "\033[38;2;48;48;48m";

    constexpr std::array<const char*,4> grey_scale = { white, light_grey, grey, dark_grey };

}


#if dll
    #include "abi.cpp"
#endif