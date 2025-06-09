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
#include <boost/process/detail/environment_posix.cpp>
#include <boost/process/detail/environment_win.cpp>
#include <boost/process/detail/last_error.cpp>
#include <boost/process/detail/process_handle_windows.cpp>
#include <boost/process/detail/throw_error.cpp>
#include <boost/process/detail/utf8.cpp>
#include <boost/process/environment.cpp>
#include <boost/process/error.cpp>
#include <boost/process/ext/cmd.cpp>
#include <boost/process/ext/cwd.cpp>
#include <boost/process/ext/env.cpp>
#include <boost/process/ext/exe.cpp>
#include <boost/process/ext/proc_info.cpp>
#include <boost/process/pid.cpp>
#include <boost/process/posix/close_handles.cpp>
#include <boost/process/shell.cpp>
#include <boost/process/windows/default_launcher.cpp>

export module boost.process;
import std;

namespace boost::process
{
    
}