module;
#undef in
#undef self
#if defined(__GNUC__) and not defined(__clang__)
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    #pragma GCC diagnostic ignored "-Wdeprecated-variadic-comma-omission"
#elifdef __clang__
    #pragma clang diagnostic ignored "-Wdeprecated-missing-comma-variadic-parameter"
#endif
#include <boost/beast.hpp>

export module boost.beast;
import std;

export namespace boost::beast
{
    
}