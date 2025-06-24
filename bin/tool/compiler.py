import re
import subprocess
import threading
from config import *

def preprocess_file(export_name, source_path, module_path):
    command = ""
    if compiler == "g++" or compiler == "clang++":
        command = f"{compiler} "                \
                  f"{' '.join(compile_flags)} " \
                  f"-E -x c++ - "               \
                  f"-o -"
        if compiler == "g++": 
            if module_path is not None:
                with open(f"./bin/{type}/modules.txt", 'a') as writer:
                    writer.write(f"{export_name} {module_path}\n")
    elif compiler == "cl":
        command = f"{compiler} "               \
                  f"/E {source_path}"

    try:
        reader = open(source_path, 'r').read()
        reader = re.sub(r'^\s*#\s*include.*$', "", reader, flags=re.MULTILINE)
        return subprocess.run(command, shell=True, capture_output=True, check=True, text=True, input=reader).stdout
    except FileNotFoundError as e:
        raise Exception(f"fatal error: {e.filename} not found")
    except subprocess.CalledProcessError as e:
        raise Exception(e.stderr)
    
def pragma_file(content):
    commands = re.findall(r'^\s*#\s*pragma\s+build\s+"(.*)"$', content, flags=re.MULTILINE)
    env = os.environ.copy()
    env["anonymous"]         = os.getcwd()
    env["parallel"]          = str(os.cpu_count())
    env["type"]              = type
    env["module_suffix"]     = module_suffix
    env["object_suffix"]     = object_suffix
    env["library_suffix"]    = library_suffix
    env["executable_suffix"] = executable_suffix
    _run_command('\n'.join(commands), env=env)

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
        _run_command(command)
        
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
    
    _run_command(command)
        
def link_binary(executable_path):
    link_files = []
    for file in os.listdir   (f"./bin/{type}/module"):
        if os.path.isfile    (f"./bin/{type}/module/{file}") and file.endswith(f".{object_suffix}") or file.endswith(f".{library_suffix}"):
            link_files.append(f"./bin/{type}/module/{file}")

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

    _run_command(command)




    
def _run_command(command, **kwargs):
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, **kwargs)
    e = ""

    def read_stdout():
        while p.poll() is None:
            print(p.stdout.readline(), end="", file=sys.stdout)
    def read_stderr():
        while p.poll() is None:
            nonlocal e
            e += p.stderr.readline()
    stdout_thread = threading.Thread(target=read_stdout)
    stderr_thread = threading.Thread(target=read_stderr)
    stdout_thread.start()
    stderr_thread.start()
    stdout_thread.join()
    stderr_thread.join()

    if p.poll() == 0:
        print(e, end="", file=sys.stderr)
    else:
        raise Exception(e)
