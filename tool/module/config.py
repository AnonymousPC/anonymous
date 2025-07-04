import argparse
import os
import sys
os.chdir(f"{os.path.dirname(__file__)}/../..")
os.environ["LANG"] = "en_US.UTF-8"



# Arguments

parser = argparse.ArgumentParser(description="build.py")
parser.add_argument("--type",    choices=["debug", "release"], default="debug")
parser.add_argument("--verbose", action="store_true",                         )
argv = parser.parse_args()
type    = argv.type
verbose = argv.verbose



# Config

if sys.platform == "win32":
    system            = "windows"
    compiler          = "cl"
    linker            = "cl"
    archiever         = "lib"
    executable_suffix = "exe"
elif sys.platform == "linux":
    system            = "linux"
    compiler          = "g++"
    linker            = "g++"
    archiever         = "ar"
    executable_suffix = ""
elif sys.platform == "darwin":
    system            = "macos"
    compiler          = "clang++"
    linker            = "clang++"
    archiever         = "ar"
    executable_suffix = ""

if compiler == "g++":
    compile_flags = [
        "-std=c++26", 
        "-Wall",
        "-fdiagnostics-color=always",
        "-fmodules",
       f"-fmodule-mapper=./bin/{type}/module/mapper.txt",
    ]
    link_flags = ["-static"]
    if type == "debug":
        compile_flags += ["-g",  "-O0", "-DDEBUG" ]
    elif type == "release":
        compile_flags += [       "-O3", "-DNDEBUG"]
        link_flags    += ["-s"]
    module_suffix  = "gcm"
    object_suffix  = "o"
    library_suffix = "a"
elif compiler == "clang++":
    compile_flags = [
        "-std=c++26", 
        "-Wall", 
        "-fdiagnostics-color=always",
       f"-fprebuilt-module-path=./bin/{type}/module",
    ]
    link_flags = []
    if type == "debug":
        compile_flags += ["-g",  "-O0", "-DDEBUG" ]
    elif type == "release":
        compile_flags += [       "-O3", "-DNDEBUG"]
        link_flags    += ["-s"]
    module_suffix  = "pcm"
    object_suffix  = "o"
    library_suffix = "a"
elif compiler == "cl":
    compile_flags = [
        "/std:c++latest",
        "/EHsc",
        "/W4"
    ]
    link_flags = ["/MT"]
    if type == "debug":
        compile_flags += ["/Z7", "/Od", "/DDEBUG" ]
    elif type == "release":
        compile_flags += [       "/O2", "/DNDEBUG"]
    module_suffix  = "ifc"
    object_suffix  = "obj"
    library_suffix = "lib"

define_flags = {
    "abstract": '0', 
    "extends" : ':',
    "in"      : ':', 
    "self"    : "(*this)"
}
