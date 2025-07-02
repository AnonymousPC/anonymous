from module.make import *

cmake(
    module_name="tbb",
    dir="./third_party/oneTBB",
    args=[
        "-DTBB_TEST=false",
        "-DTBB_EXAMPLES=false",
        "-DBUILD_SHARED_LIBS=false"
    ]
)

"""
>>> cat ./third_party/oneTBB/CMakeLists.txt | grep option
    if (CMAKE_CXX${CMAKE_CXX_STANDARD}_STANDARD_COMPILE_OPTION)  # if standard option was detected by CMake
    else()  # if standard option wasn't detected by CMake (e.g. for Intel Compiler with CMake 3.1)
        # TBB_CXX_STD_FLAG should be added to targets via target_compile_options
option(TBB_TEST "Enable testing" ON)
option(TBB_EXAMPLES "Enable examples" OFF)
option(TBB_STRICT "Treat compiler warnings as errors" ON)
option(TBB_WINDOWS_DRIVER "Build as Universal Windows Driver (UWD)" OFF)
option(TBB_NO_APPCONTAINER "Apply /APPCONTAINER:NO (for testing binaries for Windows Store)" OFF)
option(TBB4PY_BUILD "Enable tbb4py build" OFF)
option(TBB_BUILD "Enable tbb build" ON)
option(TBBMALLOC_BUILD "Enable tbbmalloc build" ON)
cmake_dependent_option(TBBMALLOC_PROXY_BUILD "Enable tbbmalloc_proxy build" ON "TBBMALLOC_BUILD" OFF)
option(TBB_CPF "Enable preview features of the library" OFF)
option(TBB_FIND_PACKAGE "Enable search for external oneTBB using find_package instead of build from sources" OFF)
option(TBB_DISABLE_HWLOC_AUTOMATIC_SEARCH "Disable HWLOC automatic search by pkg-config tool" ${CMAKE_CROSSCOMPILING})
option(TBB_ENABLE_IPO "Enable Interprocedural Optimization (IPO) during the compilation" ON)
option(TBB_CONTROL_FLOW_GUARD "Enable Control Flow Guard (CFG) during the compilation" OFF)
option(TBB_FUZZ_TESTING "Enable fuzz testing" OFF)
option(TBB_INSTALL "Enable installation" ON)
option(TBB_FILE_TRIM "Enable __FILE__ trim" ON)
option(TBB_LINUX_SEPARATE_DBG "Enable separation of the debug symbols during the build" OFF)
option(TBB_BUILD_APPLE_FRAMEWORKS "Build as Apple Frameworks" OFF)
    option(TBB_VERIFY_DEPENDENCY_SIGNATURE
"""