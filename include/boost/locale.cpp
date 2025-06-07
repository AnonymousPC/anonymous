module;
#undef in
#undef self
#define BOOST_LOCALE_WITH_ICU
#define BOOST_LOCALE_NO_POSIX_BACKEND
#define BOOST_LOCALE_NO_WINAPI_BACKEND
#include <boost/locale.hpp>
#include <git/boost/libs/locale/src/util/gregorian.cpp> // Include this file first
#include <git/boost/libs/locale/src/encoding/codepage.cpp>
#undef BOOST_LOCALE_INSTANTIATE
#include <git/boost/libs/locale/src/icu/boundary.cpp>
#include <git/boost/libs/locale/src/icu/codecvt.cpp>
#include <git/boost/libs/locale/src/icu/collator.cpp>
#include <git/boost/libs/locale/src/icu/conversion.cpp>
#include <git/boost/libs/locale/src/icu/date_time.cpp>
#include <git/boost/libs/locale/src/icu/formatter.cpp>
#undef BOOST_LOCALE_INSTANTIATE
#include <git/boost/libs/locale/src/icu/formatters_cache.cpp>
#include <git/boost/libs/locale/src/icu/icu_backend.cpp>
#include <git/boost/libs/locale/src/icu/numeric.cpp>
// #include <git/boost/libs/locale/src/posix/codecvt.cpp>
// #include <git/boost/libs/locale/src/posix/collate.cpp>
// #include <git/boost/libs/locale/src/posix/converter.cpp>
// #include <git/boost/libs/locale/src/posix/numeric.cpp>
// #include <git/boost/libs/locale/src/posix/posix_backend.cpp>
#include <git/boost/libs/locale/src/shared/date_time.cpp>
#include <git/boost/libs/locale/src/shared/format.cpp>
#include <git/boost/libs/locale/src/shared/formatting.cpp>
#include <git/boost/libs/locale/src/shared/generator.cpp>
#include <git/boost/libs/locale/src/shared/iconv_codecvt.cpp>
#include <git/boost/libs/locale/src/shared/ids.cpp>
#include <git/boost/libs/locale/src/shared/localization_backend.cpp>
#include <git/boost/libs/locale/src/shared/message.cpp>
#include <git/boost/libs/locale/src/shared/mo_lambda.cpp>
#include <git/boost/libs/locale/src/std/codecvt.cpp>
#include <git/boost/libs/locale/src/std/collate.cpp>
#include <git/boost/libs/locale/src/std/converter.cpp>
#include <git/boost/libs/locale/src/std/numeric.cpp>
#include <git/boost/libs/locale/src/std/std_backend.cpp>
#include <git/boost/libs/locale/src/util/codecvt_converter.cpp>
#include <git/boost/libs/locale/src/util/default_locale.cpp>
#include <git/boost/libs/locale/src/util/encoding.cpp>
#include <git/boost/libs/locale/src/util/info.cpp>
#include <git/boost/libs/locale/src/util/locale_data.cpp>
// #include <git/boost/libs/locale/src/win32/collate.cpp>
// #include <git/boost/libs/locale/src/win32/converter.cpp>
// #include <git/boost/libs/locale/src/win32/lcid.cpp>
// #include <git/boost/libs/locale/src/win32/numeric.cpp>
// #include <git/boost/libs/locale/src/win32/win_backend.cpp>


export module boost.locale;
export namespace boost::locale
{
    
}