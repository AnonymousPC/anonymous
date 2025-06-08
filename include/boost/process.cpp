module;
#undef in
#undef self
#if defined(__GNUC__) and not defined(__clang__)
    #error fixme
#elifdef __clang__
    #pragma clang diagnostic ignored "-Wdeprecated-missing-comma-variadic-parameter"
#elif defined(_MSC_VER) and not defined(__clang__)
    #error fixme
#endif
#include <boost/process.hpp>
#include <git/boost/libs/process/src/detail/environment_posix.cpp>
#include <git/boost/libs/process/src/detail/environment_win.cpp>
#include <git/boost/libs/process/src/detail/last_error.cpp>
#include <git/boost/libs/process/src/detail/process_handle_windows.cpp>
#include <git/boost/libs/process/src/detail/throw_error.cpp>
#include <git/boost/libs/process/src/detail/utf8.cpp>
#include <git/boost/libs/process/src/environment.cpp>
#include <git/boost/libs/process/src/error.cpp>
#include <git/boost/libs/process/src/ext/cmd.cpp>
#include <git/boost/libs/process/src/ext/cwd.cpp>
#include <git/boost/libs/process/src/ext/env.cpp>
#include <git/boost/libs/process/src/ext/exe.cpp>
#include <git/boost/libs/process/src/ext/proc_info.cpp>
#include <git/boost/libs/process/src/pid.cpp>
#include <git/boost/libs/process/src/posix/close_handles.cpp>
#include <git/boost/libs/process/src/shell.cpp>
#include <git/boost/libs/process/src/windows/default_launcher.cpp>

export module boost.process;
import std;

export namespace boost::process
{
    
}