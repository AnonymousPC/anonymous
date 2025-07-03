module;
#undef extends
#undef in
#undef self
#ifdef __clang__
    #pragma clang diagnostic ignored "-Wdeprecated-missing-comma-variadic-parameter"
#endif
#include <boost/spirit/home/classic.hpp>
#include <boost/spirit/home/karma.hpp>
#include <boost/spirit/home/lex.hpp>
#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/home/x3.hpp>

export module boost.spirit;
import std;

export namespace boost::spirit
{
    
}