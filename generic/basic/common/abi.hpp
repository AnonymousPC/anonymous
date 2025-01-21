#pragma once

std::string demangle ( const std::type_info& );

#if dll
    #include "abi.cpp"
#endif