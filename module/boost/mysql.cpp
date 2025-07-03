module;
#undef in
#undef self
#ifdef __clang__
    #pragma clang diagnostic ignored "-Wdeprecated-missing-comma-variadic-parameter"
#endif
#include <boost/mysql.hpp>

export module boost.mysql;
import std;

export namespace boost::mysql
{
    
}