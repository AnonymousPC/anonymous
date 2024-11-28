#pragma once
#include "concept.hpp"

#define first_type typename std::decay<decltype(first)>::type

/// Declaration

/* lambda function */ // void print ( const printable auto&... );
/* lambda function */ // auto input ( const printable auto&... ); See container/utility/utility

#include "utility.ipp"
#undef first_type