module;
#define BOOST_LOCALE_WITH_ICU
#ifdef _WIN32
    #define BOOST_LOCALE_NO_POSIX_BACKEND
#elif defined(__linux__) or defined(__MACH__)
    #define BOOST_LOCALE_NO_WINAPI_BACKEND
#endif
#undef in
#undef self
#include <boost/locale.hpp>
#include <boost/locale/util/gregorian.cpp> // Include this file first
#include <boost/locale/encoding/codepage.cpp>
#undef BOOST_LOCALE_INSTANTIATE
#include <boost/locale/icu/boundary.cpp>
#include <boost/locale/icu/codecvt.cpp>
#include <boost/locale/icu/collator.cpp>
#include <boost/locale/icu/conversion.cpp>
#include <boost/locale/icu/date_time.cpp>
#include <boost/locale/icu/formatter.cpp>
#undef BOOST_LOCALE_INSTANTIATE
#include <boost/locale/icu/formatters_cache.cpp>
#include <boost/locale/icu/icu_backend.cpp>
#include <boost/locale/icu/numeric.cpp>
#include <boost/locale/shared/date_time.cpp>
#include <boost/locale/shared/format.cpp>
#include <boost/locale/shared/formatting.cpp>
#include <boost/locale/shared/generator.cpp>
#include <boost/locale/shared/iconv_codecvt.cpp>
#include <boost/locale/shared/ids.cpp>
#include <boost/locale/shared/localization_backend.cpp>
#include <boost/locale/shared/message.cpp>
#include <boost/locale/shared/mo_lambda.cpp>
#include <boost/locale/std/codecvt.cpp>
#include <boost/locale/std/collate.cpp>
#include <boost/locale/std/converter.cpp>
#include <boost/locale/std/numeric.cpp>
#include <boost/locale/std/std_backend.cpp>
#include <boost/locale/util/codecvt_converter.cpp>
#include <boost/locale/util/default_locale.cpp>
#include <boost/locale/util/encoding.cpp>
#include <boost/locale/util/info.cpp>
#include <boost/locale/util/locale_data.cpp>
#ifdef _WIN32
    #include <boost/locale/win32/collate.cpp>
    #include <boost/locale/win32/converter.cpp>
    #include <boost/locale/win32/lcid.cpp>
    #include <boost/locale/win32/numeric.cpp>
    #include <boost/locale/win32/win_backend.cpp>
#elif defined(__linux__) or defined(__MACH__)
    #include <boost/locale/posix/codecvt.cpp>
    #include <boost/locale/posix/collate.cpp>
    #include <boost/locale/posix/converter.cpp>
    #include <boost/locale/posix/numeric.cpp>
    #include <boost/locale/posix/posix_backend.cpp>
#endif

export module boost.locale;
import std;

export namespace boost::locale
{
    
}