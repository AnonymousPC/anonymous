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

if system == "windows":
    compiler = "g++"
elif system == "linux":
    compiler = "g++"
elif system == "macos":
    compiler = "clang++"

type = sys.argv[1] # debug/release



# Input

modules = [
    "anonymous.basic",
    "anonymous.container",
    "anonymous"
]
compile_args = [
    "-std=c++26", 
    "-g", 
    "-Wall", 
    "-fdiagnostics-color=always"
]
if compiler == "g++":
    compile_args.append("-fmodules")
elif compiler == "clang++":
    compile_args.append("-fprebuilt-module-path=./pcm.cache")
if type == "debug":
    compile_args.append("-O0")
    compile_args.append("-fno-inline")
elif type == "release":
    compile_args.append("-O3")
    compile_args.append("-DNDEBUG")

link_args = [
    "-fuse-ld=lld",
    "-fdiagnostics-color=always"
]
include_path  = ""
lib_path      = ""
libs          = []
if system == "windows":
    include_path = "F:/msys/ucrt64/include"
    lib_path     = "F:/msys/ucrt64/lib"
    libs         = ["advapi32", "bcrypt", "crypto", "kernel32", "mswsock", "ntdll", "shell32", "ssl", "stdc++exp", "tiff", "user32", "ws2_32"]
elif system == "linux":
    include_path = "/usr/include"
    lib_path     = "/usr/lib"
    libs         = []
elif system == "macos":
    include_path = "/opt/homebrew/include"
    lib_path     = "/opt/homebrew/lib"
    libs         = ["bz2", "crypto", "hwloc", "iconv", "icudata", "icui18n", "icuio", "icutu", "icuuc", "jpeg", "lzma", "png", "ssl", "tiff", "tiffxx", "z", "zstd"]


# Task

def compile():
    for module in modules:
        log(module, color="yellow")
        if updatable(module):
            if compiler == "g++":
                run(f"{compiler} "
                    f"{' '.join(compile_args)} "
                    f'-Dabstract=0 -Dextends=: -Din=: -Dself="(*this)" '
                    f"-c ./include/{module.replace('.', '/')}/module.cppm "
                    f"-o ./gcm.cache/{module}.pcm")
            elif compiler == "clang++":
                run(f"{compiler} "
                    f"{' '.join(compile_args)} "
                    f"-Dabstract=0 -Dextends=':' -Din=':' -Dself='(*this)' "
                    f"--precompile ./include/{module.replace('.', '/')}/module.cppm "
                    f"-o ./pcm.cache/{module}.pcm")
                run(f"{compiler} "
                    f"{' '.join(compile_args)} "
                    f"-c ./pcm.cache/{module}.pcm "
                    f"-o ./pcm.cache/{module}.o")
                        
    log("main", color="yellow")
    run(f"{compiler} "
        f"{' '.join(compile_args)} "
        f"-Dabstract=0 -Dextends=':' -Din=':' -Dself='(*this)' "
        f"-c ./main.cpp "
        f"-o ./bin/main.o")


def link():
    linkable = [f"./bin/main.o"]
    if compiler == "g++":
        for file in os.listdir(f"./gcm.cache"):
            if file.endswith(".o"):
                linkable.append(f"./gcm.cache/{file}")
    elif compiler == "clang++":
        for file in os.listdir(f"./pcm.cache"):
            if file.endswith(".o"):
                linkable.append(f"./pcm.cache/{file}")
    
    run (f"{compiler} "
         f"{' '.join(link_args)} "
         f"{' '.join(linkable)} "
         f"-L{lib_path} "
         f"{' '.join(f"-l{lib}" for lib in libs)} "
         f"-o ./bin/main")



# Detail

update = False

def updatable(module):
    bin_time = 0
    try:
        if compiler == "g++":
            bin_time = max(os.path.getmtime(f"./gcm.cache/{module}.gcm"), os.path.getmtime(f"./gcm.cache/{module}.o"))
        elif compiler == "clang++":
            bin_time = max(os.path.getmtime(f"./pcm.cache/{module}.pcm"), os.path.getmtime(f"./pcm.cache/{module}.o"))
    except OSError:
        pass
    
    src_time = 0
    for root, _, files in os.walk(f"./include/{module.replace('.', '/')}"):
        for file in files:
            src_time = max(src_time, os.path.getmtime(f"./{root}/{file}"))

    global update
    if src_time >= bin_time:
        update = True
    return update

def run(command):
    command = re.sub(r'\s+', ' ', command)
    log(command, color="green")
    output = subprocess.run(command, shell=True, check=False, capture_output=True, text=True)
    print(output.stdout, end="", file=sys.stdout)
    print(output.stderr, end="", file=sys.stderr)
    print(output.stderr, end="", file=open(f"./bin/log.txt", 'w'))
    if output.returncode != 0:
        exit(output.returncode)

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


