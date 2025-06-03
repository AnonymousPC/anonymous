import os
import re
import subprocess
import sys

# Global

if sys.platform == "win32":
    system = "windows"
elif sys.platform == "linux":
    system = "linux"
elif sys.platform == "darwin":
    system = "macos"

type = sys.argv[1] # debug/release


# Config

modules = [
    "anonymous:basic",
    "anonymous:container",
    "anonymous"
]

if system == "windows":
    compiler          = "cl"
    include_path      = ""
    lib_path          = ""
    libs              = ["advapi32", "bcrypt", "crypto", "kernel32", "mswsock", "ntdll", "shell32", "ssl", "stdc++exp", "tiff", "user32", "ws2_32"]
    executable_suffix = ".exe"
elif system == "linux":
    compiler          = "g++"
    include_path      = "/usr/include"
    lib_path          = "/usr/lib"
    libs              = []
    executable_suffix = ""
elif system == "macos":
    compiler          = "clang++"
    include_path      = "/opt/homebrew/include"
    lib_path          = "/opt/homebrew/lib"
    libs              = ["bz2", "crypto", "hwloc", "iconv", "icudata", "icui18n", "icuio", "icutu", "icuuc", "jpeg", "lzma", "png", "ssl", "tiff", "tiffxx", "z", "zstd"]
    executable_suffix = ""

if compiler == "g++":
    compile_args = [
        "-std=c++26", 
        "-g", 
        "-Wall", 
        "-fdiagnostics-color=always",
        "-fmodules"
    ]
    if type == "debug":
        compile_args.append("-O0")
        compile_args.append("-fno-inline")
    elif type == "release":
        compile_args.append("-O3")
        compile_args.append("-DNDEBUG")

    link_args = ["-fdiagnostics-color=always"]
    module_suffix = ".gcm"
    object_suffix = ".o"
elif compiler == "clang++":
    compile_args = [
        "-std=c++26", 
        "-g", 
        "-Wall", 
        "-fdiagnostics-color=always",
        "-fprebuilt-module-path=./module"
    ]
    if type == "debug":
        compile_args.append("-O0")
        compile_args.append("-fno-inline")
    elif type == "release":
        compile_args.append("-O3")
        compile_args.append("-DNDEBUG")

    link_args = ["-fdiagnostics-color=always"]
    module_suffix = ".pcm"
    object_suffix = ".o"
elif compiler == "cl":
    compile_args = [
        "/std:c++latest",
        "/EHsc",
        "/Z7",
        "/W4"
    ]
    if type == "debug":
        compile_args.append("/Od")
    elif type == "release":
        compile_args.append("/O2")
        compile_args.append("/DNDEBUG")

    link_args = []
    module_suffix = ".ifc"
    object_suffix = ".obj"




# Core

def compile():
    for module in modules:
        log(module, color="yellow")
        if updatable(module):
            if compiler == "g++":
                run(f"{compiler} "
                    f"{' '.join(compile_args)} "
                    f'-Dabstract=0 -Dextends=: -Din=: -Dself="(*this)" '
                    f"-c ./include/{module.replace(':', '/')}/module.cppm "
                    f"-o ./module/{module.replace(':', '-')}.gcm")
            elif compiler == "clang++":
                run(f"{compiler} "
                    f"{' '.join(compile_args)} "
                    f'-Dabstract=0 -Dextends=: -Din=: -Dself="(*this)" '
                    f"--precompile ./include/{module.replace(':', '/')}/module.cppm "
                    f"-o ./module/{module.replace(':', '-')}.pcm")
                run(f"{compiler} "
                    f"{' '.join(compile_args)} "
                    f"-c ./module/{module.replace(':', '-')}.pcm "
                    f"-o ./module/{module.replace(':', '-')}.o")
            elif compiler == "cl":
                run(f"{compiler} "
                    f"{' '.join(compile_args)} "
                    f'/Dabstract=0 /Dextends=: /Din=: /D"self=(*this)" '
                    f"/c /interface /TP ./include/{module.replace(':', '/')}/module.cppm "
                    f"/ifcOutput ./module/{module.replace(':', '-')}.ifc "
                    f"/Fo ./module/{module.replace(':', '-')}.obj")

                        
    log("main", color="yellow")
    if compiler == "g++" or compiler == "clang++":
        run(f"{compiler} "
            f"{' '.join(compile_args)} "
            f'-Dabstract=0 -Dextends=: -Din=: -Dself="(*this)" '
            f"-c ./main.cpp "
            f"-o ./module/main.o")
    elif compiler == "cl":
        run(f"{compiler} "
            f"{' '.join(compile_args)} "
            f'/Dabstract=0 /Dextends=: /Din=: /D"self=(*this)" '
            f"/c ./main.cpp "
            f"/Fo ./module/main.obj")


def link():
    linkable = []
    for file in os.listdir(f"./module"):
        if file.endswith(object_suffix):
            linkable.append(f"./module/{file}")
    
    if compiler == "g++" or compiler == "clang++":
        run (f"{compiler} "
            f"{' '.join(link_args)} "
            f"{' '.join(linkable)} "
            f"-L{lib_path} "
            f"{' '.join(f"-l{lib}" for lib in libs)} "
            f"-o ./bin/main{executable_suffix}")
    elif compiler == "cl":
        run(f"{compiler} "
            f"{' '.join(link_args)} "
            f"{' '.join(linkable)} "
            f'/LIBPATH:"{lib_path}"'
            f"{' '.join(lib for lib in libs)} "
            f"/Fe ./bin/main{executable_suffix}")


# Utility

update = False

def updatable(module):
    bin_time = 0
    try:
        bin_time = min(os.path.getmtime(f"./module/{module.replace(':', '-')}{module_suffix}"), os.path.getmtime(f"./module/{module.replace(':', '-')}.o"))
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


