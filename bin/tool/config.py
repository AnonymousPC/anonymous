import sys

type = "debug"

if sys.platform == "win32":
    system            = "windows"
    compiler          = "cl"
    executable_suffix = ".exe"
elif sys.platform == "linux":
    system            = "linux"
    compiler          = "g++"
    executable_suffix = ""
elif sys.platform == "darwin":
    system            = "macos"
    compiler          = "clang++"
    executable_suffix = ""

if compiler == "g++":
    c_compiler = "gcc"
    compile_args = [
        "-std=c++26", 
        "-g",
        "-Wall", 
        "-fdiagnostics-color=always",
        "-fmodules",
        "-Wno-reserved-module-identifier",
        "-Wno-unknown-attributes"
    ]
    c_compile_args = [
        "-g",
        "-fdiagnostics-color=always"
    ]
    if type == "debug":
        compile_args   += ["-O0", "-fno-inline"]
        c_compile_args += ["-O0", "-fno-inline"]
    elif type == "release":
        compile_args   += ["-O3", "-DNDEBUG"]
        c_compile_args += ["-O3", "-DNDEBUG"]
    link_args = []
    module_suffix  = ".gcm"
    object_suffix  = ".o"
    library_suffix = ".a"
elif compiler == "clang++":
    c_compiler = "clang"
    compile_args = [
        "-std=c++26", 
        "-g", 
        "-Wall", 
        "-fdiagnostics-color=always",
       f"-fprebuilt-module-path=./bin/{type}/module",
        "-Wno-reserved-module-identifier",
        "-Wno-unknown-attributes"
    ]
    c_compile_args = [
        "-g",
        "-fdiagnostics-color=always"
    ]
    if type == "debug":
        compile_args   += ["-O0", "-fno-inline"]
        c_compile_args += ["-O0", "-fno-inline"]
    elif type == "release":
        compile_args   += ["-O3", "-DNDEBUG"]
        c_compile_args += ["-O3", "-DNDEBUG"]
    link_args = []
    module_suffix  = ".pcm"
    object_suffix  = ".o"
    library_suffix = ".a"
elif compiler == "cl":
    c_compiler = "cl"
    compile_args = [
        "/std:c++latest",
        "/EHsc",
        "/Z7",
        "/W4"
    ]
    c_compile_args = ["/Z7"]
    compile_env = ["/EHsc", "/Z7"]
    if type == "debug":
        compile_args += ["/Od"]
    elif type == "release":
        compile_args += ["/O2", "/DNDEBUG"]
    link_args = []
    module_suffix  = ".ifc"
    object_suffix  = ".obj"
    library_suffix = ".lib"

define_args = {
    "abstract": '0', 
    "extends" : ':',
    "in"      : ':', 
    "self"    : "(*this)"
}
