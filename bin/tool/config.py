import argparse
import os
import shutil
import sys

# Environment

os.chdir(f"{os.path.dirname(__file__)}/../..")



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
    executable_suffix = "exe"
elif sys.platform == "linux":
    system            = "linux"
    compiler          = "g++"
    executable_suffix = ""
elif sys.platform == "darwin":
    system            = "macos"
    compiler          = "clang++"
    executable_suffix = ""

if compiler == "g++":
    compile_flags = [
        "-std=c++26", 
        "-g",
        "-Wall", 
        "-fdiagnostics-color=always",
        "-fmodules",
       f"-fmodule-mapper=./bin/{type}/modules.txt",
    ]
    if type == "debug":
        compile_flags += ["-O0", "-fno-inline"]
    elif type == "release":
        compile_flags += ["-O3", "-DNDEBUG"]
    link_flags = []
    module_suffix  = "gcm"
    object_suffix  = "o"
    library_suffix = "a"
elif compiler == "clang++":
    compile_flags = [
        "-std=c++26", 
        "-g", 
        "-Wall", 
        "-fdiagnostics-color=always",
       f"-fprebuilt-module-path=./bin/{type}/module",
    ]
    if type == "debug":
        compile_flags += ["-O0", "-fno-inline"]
    elif type == "release":
        compile_flags += ["-O3", "-DNDEBUG"]
    link_flags = []
    module_suffix  = "pcm"
    object_suffix  = "o"
    library_suffix = "a"
elif compiler == "cl":
    compile_flags = [
        "/std:c++latest",
        "/EHsc",
        "/Z7",
        "/W4"
    ]
    if type == "debug":
        compile_flags += ["/Od"]
    elif type == "release":
        compile_flags += ["/O2", "/DNDEBUG"]
    link_flags = []
    module_suffix  = "ifc"
    object_suffix  = "obj"
    library_suffix = "lib"

define_flags = {
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
