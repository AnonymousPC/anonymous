module;
#undef extends
#undef in
#undef self
#if defined(__GNUC__) and not defined(__clang__)
    #error fixme
#elifdef __clang__
    #pragma clang diagnostic ignored "-Wdeprecated-missing-comma-variadic-parameter"
#elif defined(_MSC_VER) and not defined(__clang__)
    #error fixme
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