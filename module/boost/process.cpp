module;
#undef in
#undef self
#include <boost/process.hpp>
#include <boost/process/src/detail/environment_posix.cpp>
#include <boost/process/src/detail/environment_win.cpp>
#include <boost/process/src/detail/last_error.cpp>
#include <boost/process/src/detail/process_handle_windows.cpp>
#include <boost/process/src/detail/throw_error.cpp>
#include <boost/process/src/detail/utf8.cpp>
#include <boost/process/src/environment.cpp>
#include <boost/process/src/error.cpp>
#include <boost/process/src/ext/cmd.cpp>
#include <boost/process/src/ext/cwd.cpp>
#include <boost/process/src/ext/env.cpp>
#include <boost/process/src/ext/exe.cpp>
#include <boost/process/src/ext/proc_info.cpp>
#include <boost/process/src/pid.cpp>
#include <boost/process/src/posix/close_handles.cpp>
#include <boost/process/src/shell.cpp>
#include <boost/process/src/windows/default_launcher.cpp>

export module boost.process;
import std;

export namespace boost::process
{
    
}