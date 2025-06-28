import os
import re
import subprocess
from .config import *
from .run import *

def preprocess_file(source_path, module_path):
    command = ""
    if compiler == "g++" or compiler == "clang++":
        command = f"{compiler} "                                                                          \
                  f"{' '.join(compile_flags)} "                                                           \
                  f"-E -x c++ - "                                                                         \
                  f"-o -"
        if compiler == "g++": 
            if module_path is not None:
                with open(f"./bin/{type}/modules.txt", 'a') as writer:
                    writer.write(f"{module_path.rpartition('/')[2].removesuffix(".cpp")} {module_path}\n")
    elif compiler == "cl":
        command = f"{compiler} "                                                                          \
                  f"/E {source_path}"

    try:
        reader = open(source_path, 'r').read()
        reader = re.sub(r'^\s*#\s*include.*$', "", reader, flags=re.MULTILINE)
        return subprocess.run(command, shell=True, capture_output=True, check=True, text=True, input=reader).stdout
    except FileNotFoundError as e:
        raise Exception(f"fatal error: {e.filename} not found")
    except subprocess.CalledProcessError as e:
        raise Exception(e.stderr)

def compile_module(source_path, module_path, object_path):
    commands = []
    if compiler == "g++":
        commands = [f"g++ "
                    f"{' '.join(compile_flags)} "
                    f"-I ./third_party/include "
                    f"{' '.join(f'-D{key}="{value}"' for key, value in define_flags.items())} "
                    f"-c {source_path} "
                    f"-o {object_path}"]
    elif compiler == "clang++":
        commands = [f"clang++ "
                    f"{' '.join(compile_flags)} "
                    f"-I ./third_party/include "
                    f"{' '.join(f'-D{key}="{value}"' for key, value in define_flags.items())} "
                    f"--precompile -x c++-module {source_path} "
                    f"-o                         {module_path}",
                    
                    f"clang++ "
                    f"{' '.join(compile_flags)} "
                    f"-c {module_path} "
                    f"-o {object_path}"]
    elif compiler == "cl":
        commands = [f"cl "
                    f"{' '.join(compile_flags)} "
                    f"/I ./third_party/include "
                    f"{' '.join(f'/D{key}="{value}"' for key, value in define_flags.items())} "
                    f"/c /interface /TP {source_path} "
                    f"/ifcOutput        {module_path} "
                    f"/Fo               {object_path}"]
        
    for command in commands:
        run(command)
        
def compile_source(source_path, object_path):
    command = ""
    if compiler == "g++" or compiler == "clang++":
        command = f"{compiler} "                                                              \
                  f"{' '.join(compile_flags)} "                                               \
                  f"-I ./third_party/include "                                                \
                  f"{' '.join(f'-D{key}="{value}"' for key, value in define_flags.items())} " \
                  f"-c {source_path} "                                                        \
                  f"-o {object_path}"
    elif compiler == "cl":
        command = f"cl "                                                                      \
                  f"{' '.join(compile_flags)} "                                               \
                  f"/I ./third_party/include "                                                \
                  f"{' '.join(f'/D{key}="{value}"' for key, value in define_flags.items())} " \
                  f"/c  {source_path} "                                                       \
                  f"/Fo {object_path}"
    
    run(command)
        
def link_binary(object_dirs, executable_path):
    link_files = []
    for object_dir in object_dirs:
        for file in os.listdir(f"./{object_dir}"):
            link_files.append (f"./{object_dir}/{file}")

    command = ""
    if compiler == "g++" or compiler == "clang++":
        command = f"{compiler} "             \
                  f"{' '.join(link_flags)} " \
                  f"{' '.join(link_files)} " \
                  f"-o {executable_path}"
    elif compiler == "cl":
        command = f"{compiler} "             \
                  f"{' '.join(link_flags)} " \
                  f"{' '.join(link_files)} " \
                  f"/Fe {executable_path}"

    run(command)




    

