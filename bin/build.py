import os
import re
import subprocess
import sys

system = ""
if sys.platform == "win32":
    system = "windows"
elif sys.platform == "linux":
    system = "linux"
elif sys.platform == "darwin":
    system = "macos"



# Input

modules = [
    "anonymous.std",
    "anonymous.basic",
    "anonymous"
]
compile_args = [
    "-std=c++26", 
    "-g", 
    "-Wall", 
    "-fdiagnostics-color=always"
]
link_args = [
    "-fuse-ld=lld"
]
define_args = {
    "abstract": '0', 
    "extends" : ':', 
    "in"      : ":",
    "self"    : "(*this)"
}
module_path   = ""
include_path  = ""
lib_path      = ""
libs          = []
if system == "windows":
    include_path = "F:/msys/ucrt64/include"
    lib_path     = "F:/msys/ucrt64/lib"
    module_path  = "F:/msys/ucrt64/module"
    libs         = ["advapi32", "bcrypt", "crypto", "kernel32", "mswsock", "ntdll",  "OpenCL", "shell32", "ssl", "stdc++exp", "tiff", "user32", "ws2_32"]
elif system == "macos":
    module_path  = "/opt/homebrew/module"
    include_path = "/opt/homebrew/include"
    lib_path     = "/opt/homebrew/lib"
    libs         = ["bz2", "crypto", "hwloc", "iconv", "icudata", "icui18n", "icuio", "icutu", "icuuc", "jpeg", "lzma", "png", "ssl", "tbb", "tiff", "tiffxx", "z", "zstd"]



# Config

type = sys.argv[1] # debug/release

if system == "windows":
    compiler = "g++"
elif system == "linux":
    compiler = "g++"
elif system == "macos":
    compiler = "clang++"

if system == "macos":
    link_args.append("-framework OpenCL")

if type == "debug":
    compile_args.append("-O0")
elif type == "release":
    compile_args.append("-O3")



# Task

compile_args_cmd  = ' '.join(compile_args)
link_args_cmd     = ' '.join(link_args)
define_args_cmd   = ' '.join(f"-D{key}=\"{value}\"" for key, value in define_args.items())
module_path_cmd   = f"-fprebuilt-module-path={module_path} -fprebuilt-module-path=bin/{type}"
include_path_cmd  = f"-I{include_path}"
lib_path_cmd      = f"-L{lib_path}"
libs_cmd          = ' '.join(f"-l{lib}" for lib in libs)

def compile():
    for module in modules:
        if updatable(module):
            run(f"{compiler} {compile_args_cmd} {define_args_cmd} include/{module.replace('.', '/')}/module.cppm --precompile -o bin/{type}/{module}.pcm {module_path_cmd} {include_path_cmd}")
            run(f"{compiler} {compile_args_cmd}                   bin/{type}/{module}.pcm                        -c           -o bin/{type}/{module}.o   {module_path_cmd}                   ")
    
    run(f"{compiler} {compile_args_cmd} {define_args_cmd} main.cpp -c -o bin/{type}/main.o {module_path_cmd} {include_path_cmd}")


def link():
    linkable = []
    for file in os.listdir(f"bin/{type}"):
        if file.endswith(".o"):
            linkable.append(f"bin/{type}/{file}")
    for file in os.listdir(module_path):
        if file.endswith(".o"):
            linkable.append(f"{module_path}/{file}")
    linkable = ' '.join(linkable)
    
    run(f"{compiler} {link_args_cmd} {linkable} -o bin/{type}/main {lib_path_cmd} {libs_cmd} ")



# Detail

def updatable(module):
    try:
        bin_time = os.path.getmtime(f"bin/{type}/{module}.pcm")
    except OSError:
        return True # Module does not exist, so it needs to be built.
    
    src_time = 0
    for root, _, files in os.walk(f"include/{module.replace('.', '/')}"):
        for file in files:
            src_time = max(src_time, os.path.getmtime(f"{root}/{file}"))

    return src_time >= bin_time

def run(command):
    try:
        command = re.sub(r'\s+', ' ', command)
        print(command, '\n')
        subprocess.run(command, shell=True, check=True, capture_output=True, text=True)
    except subprocess.CalledProcessError as e:
        print(e.stderr, '\n', file=sys.stderr)
        open(f"bin/{type}/log.txt", 'w').write(e.stderr)
        exit(-1)



# Main

if __name__ == "__main__":
    compile()
    link()


