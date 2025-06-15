import re
import subprocess
from config import *

def preprocess(source_path):
    if compiler == "g++" or compiler == "clang++":    
        commands = [f"{compiler} "
                    f"{' '.join(compile_args)} "
                    f"-E -x c++ - "
                    f"-o -"]
    elif compiler == "cl":
        commands = [f"{compiler} "
                    f"/E {source_path}"]

    for command in commands: 
        try:
            reader = open(source_path, 'r').read()
            reader = re.sub(r'^\s*#\s*include.*$', "", reader, flags=re.MULTILINE)
            return subprocess.run(command, shell=True, capture_output=True, check=True, text=True, input=reader).stdout
        except FileNotFoundError as e:
            raise Exception(f"fatal error: {e.filename} not found")
        except subprocess.CalledProcessError as e:
            raise Exception(e.stderr)

def compile(source_path, module_path, object_path):
    if compiler == "g++":
        commands = [f"g++ "
                    f"{' '.join(compile_args)} "
                    f"-I./third_party/include "
                    f"{' '.join(f'-D{key}="{value}"' for key, value in define_args.items())} "
                    f"-c {source_path} "
                    f"-o {module_path}"]
    elif compiler == "clang++":
        commands = [f"clang++ "
                    f"{' '.join(compile_args)} "
                    f"-I./third_party/include "
                    f"{' '.join(f'-D{key}="{value}"' for key, value in define_args.items())} "
                    f"--precompile -x c++-module {source_path} "
                    f"-o                         {module_path}",
                    
                    f"clang++ "
                    f"{' '.join(compile_args)} "
                    f"-c {module_path} "
                    f"-o {object_path}"]
    elif compiler == "cl":
        commands = [f"cl "
                    f"{' '.join(compile_args)} "
                    f"/I./third_party/include "
                    f"{' '.join(f'/D{key}="{value}"' for key, value in define_args.items())} "
                    f"/c /interface /TP {source_path} "
                    f"/ifcOutput        {module_path} "
                    f"/Fo               {object_path}"]
        
    for command in commands:
        try:
            output = subprocess.run(command, shell=True, capture_output=True, check=True, text=True)
            print(output.stdout, end="", file=sys.stdout)
            print(output.stderr, end="", file=sys.stderr)       
        except subprocess.CalledProcessError as e:
            raise Exception(e.stderr)
        
def link(executable_path):
    if compiler == "g++" or compiler == "clang++":
        commands = [f"{compiler} "
                    f"{' '.join(link_args)} "
                    f"./bin/{type}/module/*{object_suffix} "
                    f"./bin/{type}/module/*{library_suffix} "
                    f"-o {executable_path}"]
    elif compiler == "cl":
        commands = ["echo what??"]

    for command in commands:
        try:
            output = subprocess.run(command, shell=True, capture_output=True, check=True, text=True)
            print(output.stdout, end="", file=sys.stdout)
            print(output.stderr, end="", file=sys.stderr)       
        except subprocess.CalledProcessError as e:
            raise Exception(e.stderr)
        

    

