import os
import re
import subprocess
from module.config import *
from module.run import *

def preprocess_file(export_name, source_file, module_file):
    command = ""
    if compiler == "g++" or compiler == "clang++":
        command = f"{compiler} "                                            \
                  f"{' '.join(compile_flags)} "                             \
                  f"-E -x c++ - "                                           \
                  f"-o -"
        if compiler == "g++":
            if module_file is not None:
                with open(f"./bin/{type}/module/mapper.txt", 'a') as writer:
                    writer.write(f"{export_name} {module_file}\n")
    elif compiler == "cl":
        command = f"{compiler} "                                            \
                  f"/E {source_file}"

    try:
        reader = open(source_file, 'r').read()
        reader = re.sub(r'^\s*#\s*include.*$', "", reader, flags=re.MULTILINE)
        return subprocess.run(command, shell=True, capture_output=True, check=True, text=True, input=reader).stdout
    except FileNotFoundError as e:
        raise Exception(f"fatal error: {e.filename} not found")
    except subprocess.CalledProcessError as e:
        raise Exception(e.stderr)
    
def compile_tool(tool_file):
    exec(f"from {os.path.relpath(tool_file, "./tool").replace('\\', '/').replace('/', '.').removesuffix('.py')} import *")

def compile_module(source_file, include_dir, module_file, object_file):
    commands = []
    if compiler == "g++":
        commands = [f"g++ "
                    f"{' '.join(compile_flags)} "
                    f"-I {include_dir} "
                    f"{' '.join(f'-D {key}="{value}"' for key, value in define_flags.items())} "
                    f"-c {source_file} "
                    f"-o {object_file}"]
    elif compiler == "clang++":
        commands = [f"clang++ "
                    f"{' '.join(compile_flags)} "
                    f"-I {include_dir} "
                    f"{' '.join(f'-D {key}="{value}"' for key, value in define_flags.items())} "
                    f"--precompile -x c++-module {source_file} "
                    f"-o                         {module_file}",
                    
                    f"clang++ "
                    f"{' '.join(compile_flags)} "
                    f"-c {module_file} "
                    f"-o {object_file}"]
    elif compiler == "cl":
        commands = [f"cl "
                    f"{' '.join(compile_flags)} "
                    f"/I {include_dir} "
                    f"{' '.join(f'/D {key}="{value}"' for key, value in define_flags.items())} "
                    f"/c /interface /TP {source_file} "
                    f"/ifcOutput        {module_file} "
                    f"/Fo               {object_file}"]
        
    for command in commands:
        run(command)
        
def compile_source(source_file, include_dir, object_file):
    command = ""
    if compiler == "g++" or compiler == "clang++":
        command = f"{compiler} "                                                              \
                  f"{' '.join(compile_flags)} "                                               \
                  f"-I {include_dir} "                                                        \
                  f"{' '.join(f'-D{key}="{value}"' for key, value in define_flags.items())} " \
                  f"-c {source_file} "                                                        \
                  f"-o {object_file}"
    elif compiler == "cl":
        command = f"cl "                                                                      \
                  f"{' '.join(compile_flags)} "                                               \
                  f"/I {include_dir} "                                                        \
                  f"{' '.join(f'/D{key}="{value}"' for key, value in define_flags.items())} " \
                  f"/c  {source_file} "                                                       \
                  f"/Fo {object_file}"
    
    run(command)
        
def link_binary(object_dir, lib_dir, executable_file):
    link_files = []
    for file in os.listdir(f"./{object_dir}"):
        if file.endswith(f".{object_suffix}"):
            link_files.append(f"./{object_dir}/{file}")
    link_libs = []
    for file in os.listdir(f"./{lib_dir}"):
        if file.endswith(f".{library_suffix}"):
            link_libs.append(f"./{lib_dir}/{file}")
    
    command = ""
    if compiler == "g++" or compiler == "clang++":
        command = f"{compiler} "             \
                  f"{' '.join(link_flags)} " \
                  f"{' '.join(link_files)} " \
                  f"-L {lib_dir} "           \
                  f"{' '.join(link_libs)} "  \
                  f"-o {executable_file}"
    elif compiler == "cl":
        command = f"{compiler} "             \
                  f"{' '.join(link_flags)} " \
                  f"{' '.join(link_files)} " \
                  f"/L {lib_dir} "           \
                  f"{' '.join(link_libs)} "  \
                  f"/Fe {executable_file}"

    run(command)





    

