#pragma once

std::string demangle ( const std::type_info& );

#ifdef dll
    #include "abi.cpp"
#endif