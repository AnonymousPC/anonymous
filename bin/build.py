system = ""
import sys
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

#define abstract 0    // Usage: virtual int func() = abstract;
#define but and       // Usage: while ( x > 0 but x < 100 ) ...
#define extends :     // Usage: class array extends pubic array_algo { };
#define in :          // Usage: for ( auto element in array ) ...
#define let auto      // Usage: let x = 1;
#define otherwise :   // Usage: x > y ? print("yes") otherwise print("no");
#define self (*this)  // Usage: self[1] = 100;


module_paths  = []
include_paths = []
lib_paths     = []
libs          = []
if system == "windows":
    module_paths  = ["F:/msys/ucrt64/module"]
    include_paths = ["F:/msys/ucrt64/include"]
    lib_paths     = ["F:/msys/ucrt64/lib"]
    libs          = ["advapi32", "bcrypt", "boost_charconv-mt", "boost_date_time-mt", "boost_filesystem-mt", "boost_iostreams-mt", "boost_locale-mt", "boost_process-mt", "boost_stacktrace_basic-mt", "clblast", "crypto",  "jpeg", "kernel32", "mswsock",  "ntdll",  "OpenCL", "png", "shell32", "ssl", "stdc++exp", "tbb12", "tiff", "user32", "ws2_32"]
elif system == "macos":
    module_paths  = ["/opt/homebrew/module"]
    include_paths = ["/opt/homebrew/include"]
    lib_paths     = ["/opt/homebrew/lib"]
    libs          = ["bz2", "crypto", "hwloc", "iconv", "icudata", "icui18n", "icuio", "icutest", "icutu", "icuuc", "jpeg", "lzma", "png", "ssl", "tbb", "tiff", "tiffxx", "z", "zstd"]





# Config

type = sys.argv[1] # debug/release

if system == "windows":
    compiler = "g++"
elif system == "linux":
    compiler = "g++"
elif system == "macos":
    compiler = "clang++"

if type == "debug":
    compile_args.append("-O0")
elif type == "release":
    compile_args.append("-O3")

module_paths.append(f"./bin/{type}")





# Task

compile_args  = ' '.join(compile_args)
link_args     = ' '.join(link_args)
module_paths  = ' '.join(f"-fprebuilt-module-path={module_path}" for module_path  in module_paths )
include_paths = ' '.join(f"-I{include_path}"                     for include_path in include_paths)
lib_paths     = ' '.join(f"-L{lib_path}"                         for lib_path     in lib_paths    )
libs          = ' '.join(f"-l{lib}"                              for lib          in libs         )

def modulize():
    for module in modules:
        if updatable(module):
            run(f"{compiler} {compile_args} include/{dirname(module)}/module.cppm --precompile -o bin/{type}/{filename(module)}.pcm {module_paths} {include_paths}")


def compile():
    run(f"{compiler} {compile_args} bin/{type}/anonymous.pcm -c -o bin/{type}/anonymous.o {module_paths} ")
    run(f"{compiler} {compile_args} main.cpp                 -c -o bin/{type}/main.o      {module_paths} ")



def link():
    run(f"{compiler} {link_args} bin/{type}/main.o bin/{type}/anonymous.o -o bin/{type}/main {lib_paths} {libs} ")




# Detail

def dirname(module):
    return module.replace('.', '/')

def filename(module):
    return module.replace(':', '-')

def updatable(module):
    import os

    try:
        bin_time = os.path.getmtime(f"bin/{type}/{filename(module)}.pcm")
    except OSError:
        return True # Module does not exist, so it needs to be built.
    
    src_time = 0
    for root, _, files in os.walk(f"include/{dirname(module)}"):
        for file in files:
            src_time = max(src_time, os.path.getmtime(f"{root}/{file}"))

    return src_time >= bin_time

def run(command):
    import subprocess

    try:
        import re
        command = re.sub(r'\s+', ' ', command)
        print(command)
        subprocess.run(command, shell=True, check=True, capture_output=True, text=True)
    except subprocess.CalledProcessError as e:
        print(e.stderr, file=sys.stderr)
        open(f"bin/{type}/log.txt", 'w').write(e.stderr)
        exit(-1)




# Main

modulize()
compile()
link()


