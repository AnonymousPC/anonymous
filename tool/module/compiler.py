import os
import re
import shutil
import subprocess
from module.config import *
from module.run import *

def preprocess_file(code_file, name=None, module_file=None):
    command = ""
    if compiler == "g++" or compiler == "clang++":
        command = f"{compiler} "                                            \
                  f"{' '.join(compile_flags)} "                             \
                  f"-E -x c++ - "                                           \
                  f"-o -"
        if compiler == "g++":
            if name is not None and module_file is not None:
                with open(f"./bin/{type}/module/mapper.txt", 'a') as writer:
                    writer.write(f"{name} {module_file}\n")
    elif compiler == "cl":
        command = f"{compiler} "                                            \
                  f"/E {code_file}"

    try:
        reader = open(code_file, 'r').read()
        reader = re.sub(r'^\s*#\s*include\s+(?!<version>).*$', "", reader, flags=re.MULTILINE)
        return subprocess.run(command, shell=True, check=True, capture_output=True, text=True, input=reader).stdout
    except FileNotFoundError as e:
        raise Exception(f"fatal error: {e.filename} not found")
    except subprocess.CalledProcessError as e:
        raise Exception(e.stderr)
    
def compile_module(code_file, include_dir, module_file, object_file):
    commands = []
    if compiler == "g++":
        commands = [f"g++ "
                    f"{' '.join(compile_flags)} "
                    f"-I {include_dir} "
                    f"{' '.join(f'-D {key}="{value}"' for key, value in define_flags.items())} "
                    f"-c {code_file} "
                    f"-o {object_file}"]
    elif compiler == "clang++":
        commands = [f"clang++ "
                    f"{' '.join(compile_flags)} "
                    f"-I {include_dir} "
                    f"{' '.join(f'-D {key}="{value}"' for key, value in define_flags.items())} "
                    f"--precompile -x c++-module {code_file} "
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
                    f"/c /interface /TP {code_file} "
                    f"/ifcOutput        {module_file} "
                    f"/Fo               {object_file}"]
        
    for command in commands:
        run(command)
        
def compile_source(code_file, include_dir, object_file):
    command = ""
    if compiler == "g++" or compiler == "clang++":
        command = f"{compiler} "                                                              \
                  f"{' '.join(compile_flags)} "                                               \
                  f"-I {include_dir} "                                                        \
                  f"{' '.join(f'-D{key}="{value}"' for key, value in define_flags.items())} " \
                  f"-c {code_file} "                                                        \
                  f"-o {object_file}"
    elif compiler == "cl":
        command = f"cl "                                                                      \
                  f"{' '.join(compile_flags)} "                                               \
                  f"/I {include_dir} "                                                        \
                  f"{' '.join(f'/D{key}="{value}"' for key, value in define_flags.items())} " \
                  f"/c  {code_file} "                                                       \
                  f"/Fo {object_file}"
    
    run(command)
        
def link_object(object_files, executable_file):
    command = ""
    if linker == "g++" or linker == "clang++":
        command = f"{linker} "                 \
                  f"{' '.join(link_flags)} "   \
                  f"{' '.join(object_files)} " \
                  f"-o {executable_file}"
    elif compiler == "link":
        command = f"link "                     \
                  f"{' '.join(link_flags)} "   \
                  f"{' '.join(object_files)} " \
                  f"/Fe {executable_file}"

    run(command)

def compile_tool(tool_file):
    exec(f"from {os.path.relpath(tool_file, "./tool").replace('\\', '/').replace('/', '.').removesuffix('.py')} import *")

def archieve_libraries(library_files, archieve_file):   
    if archiever == "ar":
        cwd = f"./tmp"
        os.mkdir(cwd)
        try:
            for library_file in library_files:
                run(f"ar x {os.path.relpath(library_file, cwd)}", cwd=cwd)
            run(f"ar rcs {os.path.relpath(archieve_file, cwd)} {' '.join(os.listdir(cwd))}", cwd=cwd)
        finally:
            shutil.rmtree(cwd)
    elif archiever == "lib":
        run(f"lib /OUT:{archieve_file} {' '.join(library_files)}")
        



    

