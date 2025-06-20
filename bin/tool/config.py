import argparse
import os
import shutil
import sys

# Arguments

parser = argparse.ArgumentParser(description="build.py")
parser.add_argument("--type",  choices=["debug", "release"], default="debug")
parser.add_argument("--clean", action="store_true")
argv = parser.parse_args()
type = argv.type
if argv.clean:
    for file in os.listdir(f"./bin/{type}/module"):
        os.remove         (f"./bin/{type}/module/{file}")
    for dir  in os.listdir(f"./bin/{type}/cmake"):
        shutil.rmtree     (f"./bin/{type}/cmake/{dir}")
    exit(0)



# Config

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
       f"-fmodule-mapper=./bin/{type}/modules.txt",
        "-Wno-unknown-pragmas"
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





# Initialize

try: os.mkdir(f"./bin/{type}")
except: pass
try: os.mkdir(f"./bin/{type}/cmake")
except: pass
try: os.mkdir(f"./bin/{type}/module")
except: pass

open("./bin/log.txt", 'w')
if compiler == "g++":
    open(f"./bin/{type}/modules.txt", 'w')
