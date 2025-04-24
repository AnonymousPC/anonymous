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
    "-fuse-ld=lld",
    "-fdiagnostics-color=always"
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
    define_args["NDEBUG"] = ""



# Task

compile_args_cmd  = ' '.join(compile_args)
link_args_cmd     = ' '.join(link_args)
define_args_cmd   = ' '.join(f"-D{key}=\"{value}\"" for key, value in define_args.items())
module_path_cmd   = f"-fprebuilt-module-path={module_path} -fprebuilt-module-path=module/{type}"
include_path_cmd  = f"-I{include_path}"
lib_path_cmd      = f"-L{lib_path}"
libs_cmd          = ' '.join(f"-l{lib}" for lib in libs)

def compile():
    for module in modules:
        log(module, color="yellow")
        if updatable(module):
            run(f"{compiler} {compile_args_cmd} {define_args_cmd} {module_path_cmd} {include_path_cmd} include/{module.replace('.', '/')}/module.cppm --precompile -o module/{type}/{module}.pcm ")
            run(f"{compiler} {compile_args_cmd}                   {module_path_cmd}                    module/{type}/{module}.pcm                     -c           -o bin/{type}/{module}.o      ")
    
    log("main", color="yellow")
    run(f"{compiler} {compile_args_cmd} {define_args_cmd} {module_path_cmd} {include_path_cmd} main.cpp -c -o bin/{type}/main.o")


def link():
    linkable = [f"bin/{type}/main.o"]
    for module in modules:
        linkable.append(f"bin/{type}/{module}.o")
    for file in os.listdir(module_path):
        if file.endswith(".o"):
            linkable.append(f"{module_path}/{file}")
    linkable = ' '.join(linkable)
    
    run(f"{compiler} {link_args_cmd} {linkable} {lib_path_cmd} {libs_cmd} -o bin/{type}/main")



# Detail

update = False

def updatable(module):
    try:
        m_time = os.path.getmtime(f"module/{type}/{module}.pcm")
        o_time = os.path.getmtime(f"bin/{type}/{module}.o")
        bin_time = max(m_time, o_time)
    except OSError:
        bin_time = 0
    
    src_time = 0
    for root, _, files in os.walk(f"include/{module.replace('.', '/')}"):
        for file in files:
            src_time = max(src_time, os.path.getmtime(f"{root}/{file}"))

    global update
    if src_time >= bin_time:
        update = True
    return update

def run(command):
    try:
        command = re.sub(r'\s+', ' ', command)
        log(command, color="green")
        subprocess.run(command, shell=True, check=True, capture_output=True, text=True)
    except subprocess.CalledProcessError as e:
        print(e.stderr, '\n', file=sys.stderr)
        open(f"bin/{type}/log.txt", 'w').write(e.stderr)
        exit(-1)

def log(message, color=None):
    colormap = {
        "red"   : "\033[38;2;240;240;0m",
        "yellow": "\033[38;2;240;240;0m",
        "green" : "\033[38;2;0;240;0m",
        "white" : "\033[38;2;192;192;192m"
    }

    if color is None:
        print(message)
    else:
        print(f"{colormap[color]}{message}{colormap["white"]}")




# Main

if __name__ == "__main__":
    compile()
    link()


