module;
#undef in
#undef self
#define BOOST_LOCALE_WITH_ICU
#ifdef _WIN32
    #define BOOST_LOCALE_NO_POSIX_BACKEND
#elif defined(__linux__) or defined(__MACH__)
    #define BOOST_LOCALE_NO_WINAPI_BACKEND
#endif
#include <boost/locale.hpp>
#include <boost/locale/src/util/gregorian.cpp> // Include this file first
#include <boost/locale/src/encoding/codepage.cpp>
#undef BOOST_LOCALE_INSTANTIATE
#include <boost/locale/src/icu/boundary.cpp>
#include <boost/locale/src/icu/codecvt.cpp>
#include <boost/locale/src/icu/collator.cpp>
#include <boost/locale/src/icu/conversion.cpp>
#include <boost/locale/src/icu/date_time.cpp>
#include <boost/locale/src/icu/formatter.cpp>
#undef BOOST_LOCALE_INSTANTIATE
#include <boost/locale/src/icu/formatters_cache.cpp>
#include <boost/locale/src/icu/icu_backend.cpp>
#include <boost/locale/src/icu/numeric.cpp>
#include <boost/locale/src/shared/date_time.cpp>
#include <boost/locale/src/shared/format.cpp>
#include <boost/locale/src/shared/formatting.cpp>
#include <boost/locale/src/shared/generator.cpp>
#include <boost/locale/src/shared/iconv_codecvt.cpp>
#include <boost/locale/src/shared/ids.cpp>
#include <boost/locale/src/shared/localization_backend.cpp>
#include <boost/locale/src/shared/message.cpp>
#include <boost/locale/src/shared/mo_lambda.cpp>
#include <boost/locale/src/std/codecvt.cpp>
#include <boost/locale/src/std/collate.cpp>
#include <boost/locale/src/std/converter.cpp>
#include <boost/locale/src/std/numeric.cpp>
#include <boost/locale/src/std/std_backend.cpp>
#include <boost/locale/src/util/codecvt_converter.cpp>
#include <boost/locale/src/util/default_locale.cpp>
#include <boost/locale/src/util/encoding.cpp>
#include <boost/locale/src/util/info.cpp>
#include <boost/locale/src/util/locale_data.cpp>
#ifdef _WIN32
    #include <boost/locale/src/win32/collate.cpp>
    #include <boost/locale/src/win32/converter.cpp>
    #include <boost/locale/src/win32/lcid.cpp>
    #include <boost/locale/src/win32/numeric.cpp>
    #include <boost/locale/src/win32/win_backend.cpp>
#elif defined(__linux__) or defined(__MACH__)
    #include <boost/locale/src/posix/codecvt.cpp>
    #include <boost/locale/src/posix/collate.cpp>
    #include <boost/locale/src/posix/converter.cpp>
    #include <boost/locale/src/posix/numeric.cpp>
    #include <boost/locale/src/posix/posix_backend.cpp>
#endif

export module boost.locale;
import std;
import icu;

namespace boost::locale
{
    
}